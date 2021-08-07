/*
 * adxl345.c
 *
 * Created: 07/08/2021 11:55:31
 *  Author: swallace
 */

#include "adxl345.h"


uint8_t adxl345_read_reg(struct io_descriptor * const io, const ADXL345Reg_t reg)
{
    uint8_t ret;

    io_write(io, &reg, 1);
    io_read(io, &ret, 1);

    return ret;
}


void adxl345_write_reg(struct io_descriptor * const io, const ADXL345Reg_t reg, const uint8_t val)
{
    uint8_t packet[2] = {reg, val};

    io_write(io, packet, sizeof(packet));
}
