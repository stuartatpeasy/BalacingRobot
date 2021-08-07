#ifndef ADXL345_H_
#define ADXL345_H_
/*
 * adxl345.h
 *
 * Created: 07/08/2021 11:55:45
 *  Author: swallace
 */

#include <atmel_start.h>
#include <stdint.h>


#define ADXL345_DEVID           (0xe5)      // ADXL345 device ID (register 0x00), 345 in octal


#define ADXL345_DATARATE_MASK   (0xf)
#define ADXL345_DATARATE_SHIFT  (0)
#define ADXL345_LOW_POWER       (1 << 4)    // Low power flag


typedef enum ADXL345DataRate
{
    ADXL345DataRate_0HZ1        = 0x0,
    ADXL345DataRate_0HZ2        = 0x1,
    ADXL345DataRate_0HZ39       = 0x2,
    ADXL345DataRate_0HZ78       = 0x3,
    ADXL345DataRate_1HZ56       = 0x4,
    ADXL345DataRate_3HZ13       = 0x5,
    ADXL345DataRate_6HZ25       = 0x6,
    ADXL345DataRate_12HZ5       = 0x7,
    ADXL345DataRate_25HZ        = 0x8,
    ADXL345DataRate_50HZ        = 0x9,
    ADXL345DataRate_100HZ       = 0xa,
    ADXL345DataRate_200HZ       = 0xb,
    ADXL345DataRate_400HZ       = 0xc,
    ADXL345DataRate_800HZ       = 0xd,
    ADXL345DataRate_1600HZ      = 0xe,
    ADXL345DataRate_3200HZ      = 0xf
} ADXL345DataRate_t;


// Flags for POWER_CTL register (0x2d)
//
#define ADXL345_LINK            (1 << 5)        // 1 = disable activity fn until inactive
#define ADXL345_AUTO_SLEEP      (1 << 4)        // 1 = sleep on inactivity
#define ADXL345_MEASURE         (1 << 3)        // 1 = measure g; 0 = standby
#define ADXL345_SLEEP           (1 << 2)        // 1 = normal mode; 0 = sleep mode

// Enumeration of possible sampling frequencies when sleep mode is enabled
typedef enum ADXL345WakeupFreq
{
    ADXL345Wakeup_8Hz           = 0,
    ADXL345Wakeup_4Hz           = 1,
    ADXL345Wakeup_2Hz           = 2,
    ADXL345Wakeup_1Hz           = 3
} ADXL345WakeupFreq_t;


// Flags for DATA_FORMAT register (0x31)
//
#define ADXL345_SELF_TEST       (1 << 7)        // 1 = selt-test; 0 = disable self-test
#define ADXL345_SPI             (1 << 5)        // 1 = 3-wire SPI; 0 = 4-wire SPI
#define ADXL345_INT_INVERT      (1 << 4)        // 1 = interrupts active low; 0 = active high
#define ADXL345_FULL_RES        (1 << 3)        // 1 = full-res (4mg/LSB) mode; 0 = 10-bit mode
#define ADXL345_JUSTIFY         (1 << 2)        // 1 = left-justify data; 0 = right-justify

// Enumeration of possible sensitivity ranges
typedef enum ADXL345Range
{
    ADXL345Range_2g             = 0,
    ADXL345Range_4g             = 1,
    ADXL345Range_8g             = 2,
    ADXL345Range_16g            = 3,
} ADXL345Range_t;


// ADXL345 registers
//
typedef enum ADXL345Reg
{
    ADXL345Reg_DEVID            = 0x00,         // Device ID
    ADXL345Reg_THRESH_TAP       = 0x1d,         // Tap threshold
    ADXL345Reg_OFSX             = 0x1e,         // X-axis offset
    ADXL345Reg_OFSY             = 0x1f,         // Y-axis offset
    ADXL345Reg_OFSZ             = 0x20,         // Z-axis offset
    ADXL345Reg_DUR              = 0x21,         // Tap duration
    ADXL345Reg_Latent           = 0x22,         // Tap latency
    ADXL345Reg_Duration         = 0x23,         // Tap window
    ADXL345Reg_THRESH_ACT       = 0x24,         // Activity threshold
    ADXL345Reg_THRESH_INACT     = 0x25,         // Inactivity threshold
    ADXL345Reg_TIME_INACT       = 0x26,         // Inactivity time
    ADXL345Reg_ACT_INACT_CTL    = 0x27,         // Axis enable control for (in)activity detection
    ADXL345Reg_THRESH_FF        = 0x28,         // Free-fall threshold
    ADXL345Reg_TIME_FF          = 0x29,         // Free-fall time
    ADXL345Reg_TAP_AXES         = 0x2a,         // Axis control for single tap / double tap
    ADXL345Reg_ACT_TAP_STATUS   = 0x2b,         // Source of single tap / double tap
    ADXL345Reg_BW_RATE          = 0x2c,         // Data rate and power mode control
    ADXL345Reg_POWER_CTL        = 0x2d,         // Power-saving features control
    ADXL345Reg_INT_ENABLE       = 0x2e,         // Interrupt enable control
    ADXL345Reg_INT_MAP          = 0x2f,         // Interrupt mapping control
    ADXL345Reg_INT_SOURCE       = 0x30,         // Source of interrupts
    ADXL345Reg_DATA_FORMAT      = 0x31,         // Data format control
    ADXL345Reg_DATAX0           = 0x32,         // X-axis data 0
    ADXL345Reg_DATAX1           = 0x33,         // X-axis data 1
    ADXL345Reg_DATAY0           = 0x34,         // Y-axis data 0
    ADXL345Reg_DATAY1           = 0x35,         // Y-axis data 1
    ADXL345Reg_DATAZ0           = 0x36,         // Z-axis data 0
    ADXL345Reg_DATAZ1           = 0x37,         // Z-axis data 1
    ADXL345Reg_FIFO_CTL         = 0x38,         // FIFO control
    ADXL345Reg_FIFO_STATUS      = 0x39          // FIFO status
} ADXL345Reg_t;


uint8_t adxl345_read_reg_byte(struct io_descriptor * const io, const ADXL345Reg_t reg);
uint16_t adxl345_read_reg_word(struct io_descriptor * const io, const ADXL345Reg_t reg);
void adxl345_read_reg(struct io_descriptor * const io, const ADXL345Reg_t reg, uint8_t * const buf,
                  const size_t count);
void adxl345_write_reg_byte(struct io_descriptor * const io, const ADXL345Reg_t reg, const uint8_t val);


#endif /* ADXL345_H_ */