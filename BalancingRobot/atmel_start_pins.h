/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD21 has 8 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7

#define MOTOR_STB GPIO(GPIO_PORTA, 0)
#define DAC0_VOUT GPIO(GPIO_PORTA, 2)
#define DAC0_VREFP GPIO(GPIO_PORTA, 3)
#define SPI_MOSI GPIO(GPIO_PORTA, 4)
#define SPI_SCK GPIO(GPIO_PORTA, 5)
#define SPI_MISO GPIO(GPIO_PORTA, 6)
#define SPI_nSS GPIO(GPIO_PORTA, 7)
#define USART_TX GPIO(GPIO_PORTA, 8)
#define USART_RX GPIO(GPIO_PORTA, 9)
#define MOTORA0 GPIO(GPIO_PORTA, 10)
#define MOTORA1 GPIO(GPIO_PORTA, 11)
#define MOTORA2 GPIO(GPIO_PORTA, 12)
#define MOTORA3 GPIO(GPIO_PORTA, 13)
#define I2C_SDA GPIO(GPIO_PORTA, 22)
#define I2C_SCL GPIO(GPIO_PORTA, 23)
#define PWM_WO0 GPIO(GPIO_PORTA, 24)
#define PWM_WO1 GPIO(GPIO_PORTA, 25)
#define INT10 GPIO(GPIO_PORTA, 30)
#define INT11 GPIO(GPIO_PORTA, 31)
#define AIN10 GPIO(GPIO_PORTB, 2)
#define AIN11 GPIO(GPIO_PORTB, 3)
#define nLED_GREEN GPIO(GPIO_PORTB, 22)
#define nLED_RED GPIO(GPIO_PORTB, 23)

#endif // ATMEL_START_PINS_H_INCLUDED
