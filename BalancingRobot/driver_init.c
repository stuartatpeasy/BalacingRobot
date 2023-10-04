/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

#include <hpl_adc_base.h>

struct spi_m_sync_descriptor SPI_0;
struct timer_descriptor      TIMER_0;

struct adc_sync_descriptor ADC_0;

struct usart_sync_descriptor USART_0;

struct i2c_m_sync_desc I2C_0;

struct pwm_descriptor PWM_0;

struct dac_sync_descriptor DAC_0;

void ADC_0_PORT_init(void)
{

	// Disable digital pin circuitry
	gpio_set_pin_direction(AIN10, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(AIN10, PINMUX_PB02B_ADC_AIN10);

	// Disable digital pin circuitry
	gpio_set_pin_direction(AIN11, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(AIN11, PINMUX_PB03B_ADC_AIN11);
}

void ADC_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, ADC);
	_gclk_enable_channel(ADC_GCLK_ID, CONF_GCLK_ADC_SRC);
}

void ADC_0_init(void)
{
	ADC_0_CLOCK_init();
	ADC_0_PORT_init();
	adc_sync_init(&ADC_0, ADC, (void *)NULL);
}

void EXTERNAL_IRQ_0_init(void)
{
	_gclk_enable_channel(EIC_GCLK_ID, CONF_GCLK_EIC_SRC);

	// Set pin direction to input
	gpio_set_pin_direction(INT10, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(INT10,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_DOWN);

	gpio_set_pin_function(INT10, PINMUX_PA30A_EIC_EXTINT10);

	// Set pin direction to input
	gpio_set_pin_direction(INT11, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(INT11,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_DOWN);

	gpio_set_pin_function(INT11, PINMUX_PA31A_EIC_EXTINT11);

	ext_irq_init();
}

void SPI_0_PORT_init(void)
{

	gpio_set_pin_level(SPI_MOSI,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SPI_MOSI, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SPI_MOSI, PINMUX_PA04D_SERCOM0_PAD0);

	gpio_set_pin_level(SPI_SCK,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SPI_SCK, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SPI_SCK, PINMUX_PA05D_SERCOM0_PAD1);

	// Set pin direction to input
	gpio_set_pin_direction(SPI_MISO, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(SPI_MISO,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(SPI_MISO, PINMUX_PA06D_SERCOM0_PAD2);
}

void SPI_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM0);
	_gclk_enable_channel(SERCOM0_GCLK_ID_CORE, CONF_GCLK_SERCOM0_CORE_SRC);
}

void SPI_0_init(void)
{
	SPI_0_CLOCK_init();
	spi_m_sync_init(&SPI_0, SERCOM0);
	SPI_0_PORT_init();
}

void USART_0_PORT_init(void)
{

	gpio_set_pin_function(USART_TX, PINMUX_PA08D_SERCOM2_PAD0);

	gpio_set_pin_function(USART_RX, PINMUX_PA09D_SERCOM2_PAD1);
}

void USART_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM2);
	_gclk_enable_channel(SERCOM2_GCLK_ID_CORE, CONF_GCLK_SERCOM2_CORE_SRC);
}

void USART_0_init(void)
{
	USART_0_CLOCK_init();
	usart_sync_init(&USART_0, SERCOM2, (void *)NULL);
	USART_0_PORT_init();
}

void I2C_0_PORT_init(void)
{

	gpio_set_pin_pull_mode(I2C_SDA,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(I2C_SDA, PINMUX_PA22C_SERCOM3_PAD0);

	gpio_set_pin_pull_mode(I2C_SCL,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(I2C_SCL, PINMUX_PA23C_SERCOM3_PAD1);
}

void I2C_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM3);
	_gclk_enable_channel(SERCOM3_GCLK_ID_CORE, CONF_GCLK_SERCOM3_CORE_SRC);
	_gclk_enable_channel(SERCOM3_GCLK_ID_SLOW, CONF_GCLK_SERCOM3_SLOW_SRC);
}

void I2C_0_init(void)
{
	I2C_0_CLOCK_init();
	i2c_m_sync_init(&I2C_0, SERCOM3);
	I2C_0_PORT_init();
}

void delay_driver_init(void)
{
	delay_init(SysTick);
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_0_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TC3);
	_gclk_enable_channel(TC3_GCLK_ID, CONF_GCLK_TC3_SRC);

	timer_init(&TIMER_0, TC3, _tc_get_timer());
}

void PWM_0_PORT_init(void)
{

	gpio_set_pin_function(PWM_WO0, PINMUX_PA24E_TC5_WO0);

	gpio_set_pin_function(PWM_WO1, PINMUX_PA25E_TC5_WO1);
}

void PWM_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TC5);
	_gclk_enable_channel(TC5_GCLK_ID, CONF_GCLK_TC5_SRC);
}

void PWM_0_init(void)
{
	PWM_0_CLOCK_init();
	PWM_0_PORT_init();
	pwm_init(&PWM_0, TC5, _tc_get_pwm());
}

void DAC_0_PORT_init(void)
{

	// Disable digital pin circuitry
	gpio_set_pin_direction(DAC0_VOUT, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(DAC0_VOUT, PINMUX_PA02B_DAC_VOUT);

	// Disable digital pin circuitry
	gpio_set_pin_direction(DAC0_VREFP, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(DAC0_VREFP, PINMUX_PA03B_DAC_VREFP);
}

void DAC_0_CLOCK_init(void)
{

	_pm_enable_bus_clock(PM_BUS_APBC, DAC);
	_gclk_enable_channel(DAC_GCLK_ID, CONF_GCLK_DAC_SRC);
}

void DAC_0_init(void)
{
	DAC_0_CLOCK_init();
	dac_sync_init(&DAC_0, DAC);
	DAC_0_PORT_init();
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA00

	gpio_set_pin_level(MOTOR_STB,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(MOTOR_STB, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(MOTOR_STB, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA07

	gpio_set_pin_level(SPI_nSS,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	// Set pin direction to output
	gpio_set_pin_direction(SPI_nSS, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SPI_nSS, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA10

	gpio_set_pin_level(MOTORA0,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(MOTORA0, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(MOTORA0, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA11

	gpio_set_pin_level(MOTORA1,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(MOTORA1, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(MOTORA1, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA12

	gpio_set_pin_level(MOTORA2,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(MOTORA2, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(MOTORA2, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA13

	gpio_set_pin_level(MOTORA3,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(MOTORA3, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(MOTORA3, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB22

	gpio_set_pin_level(nLED_GREEN,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	// Set pin direction to output
	gpio_set_pin_direction(nLED_GREEN, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(nLED_GREEN, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB23

	gpio_set_pin_level(nLED_RED,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	// Set pin direction to output
	gpio_set_pin_direction(nLED_RED, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(nLED_RED, GPIO_PIN_FUNCTION_OFF);

	ADC_0_init();
	EXTERNAL_IRQ_0_init();

	SPI_0_init();

	USART_0_init();

	I2C_0_init();

	delay_driver_init();

	TIMER_0_init();
	PWM_0_init();

	DAC_0_init();
}
