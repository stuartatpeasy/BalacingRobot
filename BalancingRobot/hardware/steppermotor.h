#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_
/*
 * steppermotor.h
 *
 * Created: 01/08/2021 18:25:15
 *  Author: swallace
 */ 


typedef struct StepperMotor
{
    uint16_t        seq;
    uint8_t         pin;
    int8_t          duty;
} StepperMotor_t;


StepperMotor_t * stepper_motor_init(StepperMotor_t * const motor, const uint8_t pin);
StepperMotor_t * stepper_motor_step(StepperMotor_t * const motor, const bool dir);

#endif /* STEPPERMOTOR_H_ */