/*
 * adxl345.c
 *
 * Created: 07/08/2021 11:55:31
 *  Author: swallace
 */

#include "adxl345.h"


static struct
{
    struct io_descriptor * io;
} g_ctx;


// adxl345_init() - use the I2C descriptor in <desc> to initialise and enable the I2C interface.
//
void adxl345_init(struct i2c_m_sync_desc * const desc)
{
	i2c_m_sync_get_io_descriptor(desc, &g_ctx.io);
	i2c_m_sync_enable(desc);
	i2c_m_sync_set_slaveaddr(desc, ADXL345_I2C_ADDR, I2C_M_SEVEN);
}


// adxl345_read_reg_byte() - read and return a byte from the register specified by <reg>.
//
uint8_t adxl345_read_reg_byte(const ADXL345Reg_t reg)
{
    uint8_t ret;

    io_write(g_ctx.io, &reg, 1);
    io_read(g_ctx.io, &ret, 1);

    return ret;
}


// adxl345_read_reg_word() - read and return the 16-bit word from the register specified by <reg>.
//
uint16_t adxl345_read_reg_word(const ADXL345Reg_t reg)
{
    uint16_t ret;

    io_write(g_ctx.io, &reg, 1);
    io_read(g_ctx.io, (uint8_t *) &ret, 2);

    return ret;
}


// adxl345_read_reg() - use the IO descriptor <io> to read <count> bytes into <buf>, starting from
// the register offset specified by <reg>.
//
void adxl345_read_reg(const ADXL345Reg_t reg, void * const buf, const size_t count)
{
    io_write(g_ctx.io, &reg, 1);
    io_read(g_ctx.io, buf, count);
}


// adxl345_write_reg_byte() - use the IO descriptor <io> to write the byte <val> into the register
// specified by <reg>.
//
void adxl345_write_reg_byte(const ADXL345Reg_t reg, const uint8_t val)
{
    uint8_t packet[2] = {reg, val};

    io_write(g_ctx.io, packet, sizeof(packet));
}


// adxl345_measure() - read acceleration data from the device into <data>.
//
void adxl345_measure(ADXL345Measurement_t * const data)
{
    adxl345_read_reg(ADXL345Reg_DATAX0, data, 6);
}