#ifndef MOTOR_H_
#define MOTOR_H_
/*
 * motor.h
 *
 * Created: 01/08/2021 18:23:38
 *  Author: swallace
 */ 


typedef enum MotorMode
{
    MotorModeCoast,
    MotorModeBrake,
    MotorModeRun
} MotorMode_t;


typedef struct Motor
{
    uint8_t         pin;
    MotorMode_t     mode;
    int8_t          power;
} Motor_t;


Motor_t * motor_init(Motor_t * const motor, const uint8_t pin);
Motor_t * motor_set_power(Motor_t * const motor, const int8_t power);
Motor_t * motor_set_brake(Motor_t * const motor, const bool brake);

#endif /* MOTOR_H_ */