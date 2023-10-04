/*
 * tli493.c
 *
 * Created: 25/09/2021 13:12:16
 *  Author: swallace
 */

#include "tli493.h"


static struct
{
    struct i2c_m_sync_desc * desc;
    struct io_descriptor * io;
} g_ctx;


// tli493_init() - use the I2C descriptor in <desc> to initialise and enable the I2C interface.
//
void tli493_init(struct i2c_m_sync_desc * const desc)
{
    g_ctx.desc = desc;
    i2c_m_sync_get_io_descriptor(desc, &g_ctx.io);
    i2c_m_sync_enable(desc);
    i2c_m_sync_set_slaveaddr(desc, TLI493_I2C_ADDR_A0, I2C_M_SEVEN);
/*
    uint8_t val;

    val = 0xff;
    io_write(g_ctx.io, &val, 1);
    io_write(g_ctx.io, &val, 1);
    val = 0x00;
    io_write(g_ctx.io, &val, 1);
    io_write(g_ctx.io, &val, 1);

    delay_us(30);
*/
    while(1)
        tli493_read_reg_byte(TLI493Reg_DIAG);
}


// tli493_read_reg_byte() - read and return a byte from the TLI493 register specified by <reg>.
//
uint8_t tli493_read_reg_byte(const TLI493Reg_t reg)
{
    uint8_t buf;
    uint8_t ret;

    ret = i2c_m_sync_cmd_read(g_ctx.desc, TLI493Reg_DIAG, &buf, 1);
    
//    io_write(g_ctx.io, &reg, 1);
//    io_read(g_ctx.io, &ret, 1);

    return ret;
}
