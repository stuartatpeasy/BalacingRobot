#include <atmel_start.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "hardware/adxl345.h"
#include "hardware/bd68888_spi.h"
#include "hardware/motorgroup.h"
#include "hardware/steppermotor.h"
#include "hardware/tli493.h"


//static MotorGroup_t g_motorgroup;
static ADXL345Measurement_t g_accelerometer_data;
static struct timer_task task_propulsion_motor, task_accelerometer;


static void cb_propulsion_motor(const struct timer_task * const timer_task)
{
//    motorgroup_isr(&g_motorgroup);
    bd68888_spi_motor_isr();
}


static void cb_accelerometer(const struct timer_task * const timer_task)
{
    adxl345_read_reg(ADXL345Reg_DATAX0, &g_accelerometer_data, 6);
}


int main(void)
{
    StepperMotor_t stepper;
    struct io_descriptor *usart_io, *spi_io;

	atmel_start_init();         // Initialise MCU, drivers and firmware
    stepper_motor_init(&stepper, MOTORA0);

    usart_sync_get_io_descriptor(&USART_0, &usart_io);
    usart_sync_set_baud_rate(&USART_0, 230400);
    usart_sync_enable(&USART_0);

    gpio_set_pin_level(SPI_nSS, true);
    spi_m_sync_get_io_descriptor(&SPI_0, &spi_io);
    spi_m_sync_set_mode(&SPI_0, SPI_MODE_3);
    spi_m_sync_set_char_size(&SPI_0, SPI_CHAR_SIZE_8);
    spi_m_sync_set_data_order(&SPI_0, SPI_DATA_ORDER_LSB_1ST);
    spi_m_sync_enable(&SPI_0);

    bd68888_spi_init(spi_io, MOTOR_STB);

    // TODO init ADXL345 - verify DEVID

    // Enable accelerometer
    adxl345_init(&I2C_0);
    adxl345_write_reg_byte(ADXL345Reg_DATA_FORMAT, ADXL345_FULL_RES);
    adxl345_write_reg_byte(ADXL345Reg_POWER_CTL, ADXL345_MEASURE);

    // Initialise timer
	task_propulsion_motor.interval  = 1;
	task_propulsion_motor.cb        = cb_propulsion_motor;
	task_propulsion_motor.mode      = TIMER_TASK_REPEAT;

    task_accelerometer.interval     = 50;
    task_accelerometer.cb           = cb_accelerometer;
    task_accelerometer.mode         = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &task_propulsion_motor);
	timer_add_task(&TIMER_0, &task_accelerometer);
	timer_start(&TIMER_0);

    /*
        A = limb_front_left         joint_hip
        B = limb_front_left         joint_knee
        C = limb_rear_left          joint_hip
        D = limb_rear_left          joint_knee
    */
    bd68888_spi_motor_set_motion(limb_front_left, joint_hip, 512);
    bd68888_spi_motor_set_motion(limb_front_left, joint_knee, -512);
    bd68888_spi_motor_set_motion(limb_rear_left, joint_hip, 512);
    bd68888_spi_motor_set_motion(limb_rear_left, joint_knee, -512);

    uint8_t power = 0; // , dir = 1;
    while(1)
    {
        char buf[48];
        float x, z, angle;
        int32_t angle_millirads;

        // Do accelerometer things
        x = g_accelerometer_data.x * 4;
        z = g_accelerometer_data.z * 4;
        angle = atan(x / z);                // FIXME - handle z = 0

        if(z < 0)
        {
            if(x > 0)
                angle = angle + M_PI;
            else if(x < 0)
                angle = angle - M_PI;
        }
        angle_millirads = 180000 * angle / M_PI;

        sprintf(buf, "(%4d, %4d, %4d) -> %ld deg; power=%3d\n", g_accelerometer_data.x * 4,
                g_accelerometer_data.y * 4, g_accelerometer_data.z * 4, angle_millirads / 1000,
                power);
        io_write(usart_io, (uint8_t *) buf, strlen(buf));

        delay_ms(100);
    }
}
