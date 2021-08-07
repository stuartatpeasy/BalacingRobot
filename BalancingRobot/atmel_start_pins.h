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

#define PA02 GPIO(GPIO_PORTA, 2)
#define PA03 GPIO(GPIO_PORTA, 3)
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
#define MOTORB0 GPIO(GPIO_PORTA, 14)
#define MOTORB1 GPIO(GPIO_PORTA, 15)
#define MOTORB2 GPIO(GPIO_PORTA, 16)
#define MOTORB3 GPIO(GPIO_PORTA, 17)
#define MOTORC0 GPIO(GPIO_PORTA, 18)
#define MOTORC1 GPIO(GPIO_PORTA, 19)
#define MOTORC2 GPIO(GPIO_PORTA, 20)
#define MOTORC3 GPIO(GPIO_PORTA, 21)
#define I2C_SDA GPIO(GPIO_PORTA, 22)
#define I2C_SCL GPIO(GPIO_PORTA, 23)
#define PWM_WO0 GPIO(GPIO_PORTA, 24)
#define PWM_WO1 GPIO(GPIO_PORTA, 25)
#define PB02 GPIO(GPIO_PORTB, 2)
#define PB03 GPIO(GPIO_PORTB, 3)
#define IRQ6 GPIO(GPIO_PORTB, 22)
#define IRQ7 GPIO(GPIO_PORTB, 23)

#endif // ATMEL_START_PINS_H_INCLUDED
