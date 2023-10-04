/*
    bd68888_spi.c - control a group of stepper motors attached to one or more BD68888 motor
    drivers.  The BD68888 motor driver input pins are driven by the outputs of a set of
    serial-to-parallel shift registers; the set of shift registers is in turn driven via SPI.

    Stuart Wallace <stuartw@atom.net>, January 2022.


    BD68888 quarter-stepping sequence, little-endian, LSB-first:

     Phase      I01 I11   P1  I02 I12 P2        Hex
     -----------------------------------------------
      1          0   0     1   1   1   1        0x0f
      2          0   0     1   0   1   1        0x0b
      3          1   0     1   1   0   1        0x2d
      4          0   1     1   0   0   1        0x19
      5          1   1     0   0   0   1        0x31
      6          0   1     0   0   0   1        0x11
      7          1   0     0   1   0   1        0x25
      8          0   0     0   0   1   1        0x03
      9          0   0     0   1   1   0        0x06
     10          0   0     0   0   1   0        0x02
     11          1   0     0   1   0   0        0x24
     12          0   1     0   0   0   0        0x10
     13          1   1     1   0   0   0        0x38
     14          0   1     1   0   0   0        0x18
     15          1   0     1   1   0   0        0x2c
     16          0   0     1   0   1   0        0x0a
     -----------------------------------------------
     disable     1   1     1   1   1   1        0x3f
     -----------------------------------------------
*/

#include "hardware/bd68888_spi.h"
#include <strings.h>


#define PHASE_MASK          (0xf)
#define BITS_PER_MOTOR      (6)
#define MOTOR_DISABLE       (0x3f)

#define FOR_EACH(p, i)      for((i) = (p); (i) < (&(p)[(sizeof(p) / sizeof((p)[0]))]); ++(i))

typedef struct motor
{
    int16_t motion;
    uint8_t phase;
    uint8_t speed;      // FIXME - implement this
} motor_t;

const uint8_t g_quarter_step[] =
    {0x0f, 0x0b, 0x2d, 0x19, 0x31, 0x11, 0x25, 0x03,
     0x06, 0x02, 0x24, 0x10, 0x38, 0x18, 0x2c, 0x0a};

static uint64_t bd68888_spi_motors_tick();
static void bd68888_spi_send_data(const uint64_t data);

static volatile motor_t g_motors[limb_max * joint_max];
static struct io_descriptor * g_spi;
static uint8_t g_strobe_pin;


void bd68888_spi_init(struct io_descriptor * const spi, const uint8_t strobe_pin)
{
    bzero((void *) g_motors, sizeof(g_motors));
    g_spi = spi;
    g_strobe_pin = strobe_pin;

    bd68888_spi_send_data(bd68888_spi_motors_tick());
}


static uint64_t bd68888_spi_motors_tick()
{
    uint64_t data = 0;
    volatile motor_t *m;

    FOR_EACH(g_motors, m)
    {
        data <<= BITS_PER_MOTOR;

        if(m->motion)                               // Motor is in motion
        {
            const int8_t dir = (m->motion > 0) ? 1 : -1;

            data |= g_quarter_step[((dir > 0) ? m->phase : ~m->phase) & PHASE_MASK];

            if((++m->phase & PHASE_MASK) == 0)      // Is step complete?
                m->motion -= dir;                   // Yes: deduct from motion
        }
        else
            data |= MOTOR_DISABLE;
    }

    return data;
}


static void bd68888_spi_send_data(const uint64_t data)
{
    const uint16_t len =
        ((sizeof(g_motors) / sizeof(g_motors[0])) * BITS_PER_MOTOR) / 8;

    gpio_set_pin_level(SPI_nSS, false);
    io_write(g_spi, (const uint8_t *) &data, len);
    gpio_set_pin_level(SPI_nSS, true);
}


void bd68888_spi_motor_set_motion(const enum limb limb, const enum joint joint, const uint16_t motion)
{
    g_motors[(limb * joint_max) + joint].motion = motion;
}


void bd68888_spi_motor_isr()
{
    static uint8_t tick = 0;

    bd68888_spi_send_data(bd68888_spi_motors_tick());

    ++tick;
}
