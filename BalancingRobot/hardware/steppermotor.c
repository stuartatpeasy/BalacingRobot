/*
 * steppermotor.c
 *
 * Created: 01/08/2021 18:25:25
 *  Author: swallace
 */

#include <atmel_start.h>
#include <stdint.h>
#include "hardware/steppermotor.h"

#define STEPPER_SEQ_FULL        (0xc639)
#define STEPPER_SEQ_MASK        (0x000f)

#define STEPPER_SEQ_CW(seq)     ((uint16_t) (((seq) << 12) | ((seq) >> 4)))
#define STEPPER_SEQ_CCW(seq)    ((uint16_t) (((seq) >> 12) | ((seq) << 4)))


StepperMotor_t * stepper_motor_init(StepperMotor_t * const motor, const uint8_t pin)
{
    motor->seq = STEPPER_SEQ_FULL;
    motor->pin = pin;

    gpio_set_port_level(GPIO_PORT(pin), 0xf << GPIO_PIN(pin), false);

    return motor;
}


StepperMotor_t * stepper_motor_step(StepperMotor_t * const motor, const bool dir)
{
    const enum gpio_port port = GPIO_PORT(motor->pin);
    const uint8_t pin = GPIO_PIN(motor->pin);
    const uint16_t seq = motor->seq;
    const uint32_t mask = 0xf << pin;

    gpio_toggle_port_level(port,
        (gpio_get_port_level(port) & mask) ^ ((seq & STEPPER_SEQ_MASK) << pin));

    motor->seq = dir ? STEPPER_SEQ_CW(seq) : STEPPER_SEQ_CCW(seq);

    return motor;
}


