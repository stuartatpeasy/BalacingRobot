/*
 * adxl345.c
 *
 * Created: 07/08/2021 11:55:31
 *  Author: swallace
 */

#include "adxl345.h"


// adxl345_read_reg_byte() - use the IO descriptor <io> to read and return a byte from the register
// specified by <reg>.
//
uint8_t adxl345_read_reg_byte(struct io_descriptor * const io, const ADXL345Reg_t reg)
{
    uint8_t ret;

    io_write(io, &reg, 1);
    io_read(io, &ret, 1);

    return ret;
}


// adxl345_read_reg_word() - use the IO descriptor <io> to read and return the 16-bit word from the
// register specified by <reg>.
//
uint16_t adxl345_read_reg_word(struct io_descriptor * const io, const ADXL345Reg_t reg)
{
    uint16_t ret;

    io_write(io, &reg, 1);
    io_read(io, (uint8_t *) &ret, 2);

    return ret;
}


// adxl345_read_reg() - use the IO descriptor <io> to read <count> bytes into <buf>, starting from
// the register offset specified by <reg>.
//
void adxl345_read_reg(struct io_descriptor * const io, const ADXL345Reg_t reg, uint8_t * const buf,
                      const size_t count)
{
    io_write(io, &reg, 1);
    io_read(io, buf, count);
}


// adxl345_write_reg_byte() - use the IO descriptor <io> to write the byte <val> into the register
// specified by <reg>.
//
void adxl345_write_reg_byte(struct io_descriptor * const io, const ADXL345Reg_t reg, const uint8_t val)
{
    uint8_t packet[2] = {reg, val};

    io_write(io, packet, sizeof(packet));
}
