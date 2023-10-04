#ifndef BD68888_SPI_H_
#define BD68888_SPI_H_
/*
    bd68888_spi.h - control a group of stepper motors attached to one or more BD68888 motor
    drivers.  The BD68888 motor driver input pins are driven by the outputs of a set of
    serial-to-parallel shift registers; the set of shift registers is in turn driven via SPI.

    Stuart Wallace <stuartw@atom.net>, January 2022.
*/

#include <stdint.h>
#include <atmel_start.h>


enum limb
{
    limb_front_left     = 0,
    limb_rear_left      = 1,
    limb_front_right    = 2,
    limb_rear_right     = 3,
    limb_max            = 4
};

enum joint
{
    joint_hip           = 0,
    joint_knee          = 1,
    joint_max           = 2
};


void bd68888_spi_init(struct io_descriptor * const spi, const uint8_t strobe_pin);
void bd68888_spi_motor_set_motion(const enum limb limb, const enum joint joint,
                                  const uint16_t motion);
void bd68888_spi_motor_isr();

#endif
