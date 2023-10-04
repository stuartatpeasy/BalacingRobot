#ifndef MOTORGROUP_H_
#define MOTORGROUP_H_
/*
 * motorgroup.h
 *
 * Created: 01/08/2021 18:23:38
 *  Author: swallace
 */


#define MOTORGROUP_NMOTORS      (2)


typedef enum MotorMode
{
    MotorModeCoast      = 0,
    MotorModeReverse    = 7,
    MotorModeForward    = 13,
    MotorModeBrake      = 15
} MotorMode_t;


typedef struct Motor
{
    MotorMode_t     mode;
    uint8_t         power;
} Motor_t;


typedef struct MotorGroup
{
    struct io_descriptor *  spi;
    uint8_t                 clock;
    uint8_t                 strobe_pin;
    Motor_t                 motor[MOTORGROUP_NMOTORS];
} MotorGroup_t;


MotorGroup_t * motorgroup_init(MotorGroup_t * const group, struct io_descriptor * const spi,
                               const uint8_t strobe_pin);
MotorGroup_t * motorgroup_set_power(MotorGroup_t * const group, const uint8_t motor,
                                    const uint8_t power);
MotorGroup_t * motorgroup_set_mode(MotorGroup_t * const group, const uint8_t motor,
                                   const MotorMode_t mode);
void motorgroup_isr(MotorGroup_t * const group);

#endif /* MOTORGROUP_H_ */