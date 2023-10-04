#ifndef TLI493_H_
#define TLI493_H_
/*
 * tli493.h
 *
 * Created: 25/09/2021 13:01:24
 *  Author: swallace
 */

#include <atmel_start.h>
#include <stdint.h>


#define TLI493_I2C_ADDR_A0      (0x35)          // } TLI493 I2C default device addresses.  There
#define TLI493_I2C_ADDR_A1      (0x22)          // } are four address variants.
#define TLI493_I2C_ADDR_A2      (0x78)          // }
#define TLI493_I2C_ADDR_A3      (0x44)          // }


// TLI493 registers
//
typedef enum TLI493Reg
{
    TLI493Reg_BX                = 0x00,         // X magnetic value MSBs
    TLI493Reg_BY                = 0x01,         // Y magnetic value MSBs
    TLI493Reg_BZ                = 0x02,         // Z magnetic value MSBs
    TLI493Reg_TEMP              = 0x03,         // Temperature value MSBs
    TLI493Reg_BX2               = 0x04,         // Magnetic values LSBs
    TLI493Reg_TEMP2             = 0x05,         // Temperature and magnetic LSBs and device address
    TLI493Reg_DIAG              = 0x06,         // Sensor diagnostic and status register
    TLI493Reg_XL                = 0x07,         // Wake up X lower threshold LSBs
    TLI493Reg_XH                = 0x08,         // Wake up X upper threshold MSBs
    TLI493Reg_YL                = 0x09,         // Wake up Y lower threshold LSBs
    TLI493Reg_YH                = 0x0a,         // Wake up Y upper threshold MSBs
    TLI493Reg_ZL                = 0x0b,         // Wake up Z lower threshold LSBs
    TLI493Reg_ZH                = 0x0c,         // Wake up Z upper threshold MSBs
    TLI493Reg_WU                = 0x0d,         // Wake up enable and X thresholds LSBs
    TLI493Reg_TMODE             = 0x0e,         // Test mode and wake up Y thresholds LSBs
    TLI493Reg_TPHASE            = 0x0f,         // Test phase and wake up Z thresholds LSBs
    TLI493Reg_CONFIG            = 0x10,         // Configuration register
    TLI493Reg_MOD1              = 0x11,         // Power mode, interrupt, address, parity
    TLI493Reg_MOD2              = 0x13,         // Low power mode update rate
    TLI493Reg_VER               = 0x16          // Version register
} TLI493Reg_t;


void tli493_init(struct i2c_m_sync_desc * const desc);
uint8_t tli493_read_reg_byte(const TLI493Reg_t reg);

#endif /* TLI493_H_ */