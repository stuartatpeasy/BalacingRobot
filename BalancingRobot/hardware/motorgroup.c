/*
    motorgroup.c - control a group of motors connected via H-bridges driven by 2EDN8523 gate
                   drivers.

    Each half of the H-bridge has two inputs and implements the following truth table:

    +--------+------------------------------------------+
    | I1  I0 | Function                                 |
    +--------+------------------------------------------+
    |  0   0 | sink current - connect motor leg to GND  |
    |  0   1 | sink current - connect motor leg to GND  |
    |  1   0 | source current - connect motor leg to V+ |
    |  1   1 | disconnect (coast)                       |
    +--------+------------------------------------------+

    This truth table avoids any illegal states (e.g. both drivers active on the same side of the
    bridge, resulting in a short circuit) and ensures safe transitions between source/sink states
    even if I1 and I0 are not updated simultaneously.

    The 2EDN8523 gate controllers have internal pull-up resistors on their inputs.  The default
    behaviour if the drivers are in a high-impedance state (e.g. during startup) is therefore
    equivalent to [I1 = 1, I0 = 1], which disconnects the motor.

    The overall truth table for the four H-bridge inputs is:

    +----------------+-----+----------------+-----------+
    |  left   right  |     |   Function     |   Motor   |
    | I1  I0  I1  I0 | Dec | left    right  | behaviour |
    +----------------+-----+----------------+-----------+
    |  0   0   0   0 |   0 | sink    sink   | brake     |
    |  0   0   0   1 |   1 | sink    sink   | brake     |
    |  0   0   1   0 |   2 | sink    source | forward   |
    |  0   0   1   1 |   3 | sink    coast  | (invalid) |
    |  0   1   0   0 |   4 | sink    sink   | brake     |
    |  0   1   0   1 |   5 | sink    sink   | brake     |
    |  0   1   1   0 |   6 | sink    source | forward   |
    |  0   1   1   1 |   7 | sink    coast  | (invalid) |
    |  1   0   0   0 |   8 | source  sink   | reverse   |
    |  1   0   0   1 |   9 | source  sink   | reverse   |
    |  1   0   1   0 |  10 | source  source | brake     |
    |  1   0   1   1 |  11 | source  coast  | (invalid) |
    |  1   1   0   0 |  12 | coast   sink   | (invalid) |
    |  1   1   0   1 |  13 | coast   sink   | (invalid) |
    |  1   1   1   0 |  14 | coast   source | (invalid) |
    |  1   1   1   1 |  15 | coast   coast  | coast     |
    +----------------+-----+----------------+-----------+

    The two motors are connected to the microcontroller via an open-drain serial-to-parallel driver
    on the SPI bus.  This is necessary because the 2EDN8523 inputs are internally pulled up to the
    motor drive voltage, which is nominally 12V.  This means that 12V appears on the pins connected
    to the 2EDN8253 device.  The open-drain drivers have the effect of inverting the control
    signals, so the final truth table (excluding unused/invalid states) for both motors is:

    +----------------+----------------+------+-----------+-----------+
    |    Motor 1     |    Motor 2     |      |           |           |
    |  left   right  |  left   right  |      |  Motor 1  |  Motor 2  |
    | I1  I0  I1  I0 | I1  I0  I1  I0 | Hex  | behaviour | behaviour |
    +----------------+----------------+------+-----------+-----------+
    |  0   0   0   0 |  0   0   0   0 | 0x00 |  coast    |  coast    |
    |  0   0   0   0 |  0   1   1   1 | 0x07 |  coast    |  reverse  |
    |  0   0   0   0 |  1   1   0   1 | 0x0d |  coast    |  forward  |
    |  0   0   0   0 |  1   1   1   1 | 0x0f |  coast    |  brake    |
    |  0   1   1   1 |  0   1   1   1 | 0x77 |  reverse  |  reverse  |
    |  0   1   1   1 |  0   0   0   0 | 0x7d |  reverse  |  coast    |
    |  0   1   1   1 |  1   1   0   1 | 0x7f |  reverse  |  forward  |
    |  0   1   1   1 |  1   1   1   1 | 0x77 |  reverse  |  brake    |
    |  1   1   0   1 |  0   0   0   0 | 0xdd |  forward  |  coast    |
    |  1   1   0   1 |  0   1   1   1 | 0xdf |  forward  |  reverse  |
    |  1   1   0   1 |  1   1   0   1 | 0xd7 |  forward  |  forward  |
    |  1   1   0   1 |  1   1   1   1 | 0xdd |  forward  |  brake    |
    |  1   1   1   1 |  0   0   0   0 | 0xff |  brake    |  coast    |
    |  1   1   1   1 |  0   1   1   1 | 0xf7 |  brake    |  reverse  |
    |  1   1   1   1 |  1   1   0   1 | 0xfd |  brake    |  forward  |
    |  1   1   1   1 |  1   1   1   1 | 0xff |  brake    |  brake    |
    +----------------+----------------+------------------------------+
 */

#include <atmel_start.h>
#include <stdint.h>
#include "hardware/motorgroup.h"
#include "lib/gpio.h"


MotorGroup_t * motorgroup_init(MotorGroup_t * const group, struct io_descriptor * const spi,
                               const uint8_t strobe_pin)
{
    for(size_t n = 0; n < MOTORGROUP_NMOTORS; ++n)
    {
        Motor_t * const motor = &group->motor[n];

        motor->mode = MotorModeCoast;
        motor->power = 0;
    }

    group->clock = 0;
    group->spi = spi;
    group->strobe_pin = strobe_pin;

    return group;
}


MotorGroup_t * motorgroup_set_power(MotorGroup_t * const group, const uint8_t motor,
                                    const uint8_t power)
{
    if(motor < MOTORGROUP_NMOTORS)
        group->motor[motor].power = power;

    return group;
}


MotorGroup_t * motorgroup_set_mode(MotorGroup_t * const group, const uint8_t motor,
                              const MotorMode_t mode)
{
    if(motor < MOTORGROUP_NMOTORS)
        group->motor[motor].mode = mode;

    return group;
}


void motorgroup_isr(MotorGroup_t * const group)
{
    uint32_t data = 0;

    for(size_t n = 0; n < MOTORGROUP_NMOTORS; ++n)
    {
        MotorMode_t mode;
        Motor_t * const motor = &group->motor[n];

        switch(motor->mode)
        {
            case MotorModeBrake:
            case MotorModeForward:
            case MotorModeReverse:
                mode = (group->clock < motor->power) ? motor->mode : MotorModeCoast;
                break;

            case MotorModeCoast:
            default:
                mode = MotorModeCoast;
                break;
        }

        data <<= 4;
        data |= mode;
    }

    // send SPI data
    for(size_t nwords = (MOTORGROUP_NMOTORS + 1) >> 1; nwords--; data >>= 8)
    {
        const uint8_t byte = data;

        io_write(group->spi, &byte, 1);
    }

    gpio_pulse_pin_pos(group->strobe_pin);

    ++group->clock;
}
