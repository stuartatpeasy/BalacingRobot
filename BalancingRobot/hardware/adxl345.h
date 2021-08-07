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


typedef enum ADXL345Reg
{
    ADXL345Reg_DEVID            = 0x00,         // Device ID
    ADXL345Reg_THRESH_TAP       = 0x1D,         // Tap threshold
    ADXL345Reg_OFSX             = 0x1E,         // X-axis offset
    ADXL345Reg_OFSY             = 0x1F,         // Y-axis offset
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
    ADXL345Reg_TAP_AXES         = 0x2A,         // Axis control for single tap / double tap
    ADXL345Reg_ACT_TAP_STATUS   = 0x2B,         // Source of single tap / double tap
    ADXL345Reg_BW_RATE          = 0x2C,         // Data rate and power mode control
    ADXL345Reg_POWER_CTL        = 0x2D,         // Power-saving features control
    ADXL345Reg_INT_ENABLE       = 0x2E,         // Interrupt enable control
    ADXL345Reg_INT_MAP          = 0x2F,         // Interrupt mapping control
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


uint8_t adxl345_read_reg(struct io_descriptor * const io, const ADXL345Reg_t reg);
void adxl345_write_reg(struct io_descriptor * const io, const ADXL345Reg_t reg, const uint8_t val);


#endif /* ADXL345_H_ */