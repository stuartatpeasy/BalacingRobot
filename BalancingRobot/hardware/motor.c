/*
 * motor.c
 *
 * Created: 01/08/2021 18:24:13
 *  Author: swallace
 */ 

#include <atmel_start.h>
#include <stdint.h>
#include "hardware/motor.h"


Motor_t * motor_init(Motor_t * const motor, const uint8_t pin)
{
    motor->pin = pin;
    motor->mode = MotorModeCoast;
    motor->power = 0;

    gpio_set_port_level(GPIO_PORT(pin), 0xf << GPIO_PIN(pin), false);

    return motor;
}


Motor_t * motor_set_power(Motor_t * const motor, const int8_t power)
{
    motor->mode = power ? MotorModeRun : MotorModeCoast;
    motor->power = power;
    
    return motor;
}


Motor_t * motor_set_brake(Motor_t * const motor, const bool brake)
{
    motor->power = 0;
    motor->mode = brake ? MotorModeBrake : MotorModeCoast;
    
    return motor;
}
