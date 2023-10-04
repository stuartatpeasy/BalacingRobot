/*
 * gpio.h
 *
 * Created: 29/08/2021 11:57:17
 *  Author: swallace
 */


#ifndef GPIO_H_
#define GPIO_H_

#include <atmel_start.h>


// gpio_set_port_pins() - write the value specified by <value> to the port specified by <port>,
// changing the state of only those pins whose corresponding bit in <mask> is set to 1.  This
// function is inexplicably missing from the core GPIO library.
//
static inline void gpio_set_port_pins(const enum gpio_port port, const uint32_t mask,
                                        const uint32_t value)
{
    gpio_toggle_port_level(port, (gpio_get_port_level(port) & mask) ^ value);
};


// gpio_pulse_pin_pos() - set the state of the pin specified by <pin> to logic 1, then execute a
// NOP, then set the state of the pin to logic 0.
//
static inline void gpio_pulse_pin_pos(const uint8_t pin)
{
    gpio_set_pin_level(pin, true);
    asm("nop");
    gpio_set_pin_level(pin, false);
};


#endif /* GPIO_H_ */