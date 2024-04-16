#ifndef DCMOTOR_INTERFACE_H
#define DCMOTOR_INTERFACE_H

#define MOTOR1_PORT  		Port_A
#define MOTOR2_PORT  		Port_A

#define MOTOR1_INPUT1_PIN   Pin0
#define MOTOR1_INPUT2_PIN   Pin1
#define MOTOR2_INPUT1_PIN   Pin2
#define MOTOR2_INPUT2_PIN   Pin3

typedef enum
{
	motorStart,
	motorStop
}et_Motor_State;

typedef enum
{
	motorSpeed1,
	motorSpeed2,
	motorSpeed3
}et_Motor_Speed;

void DCMOTOR_init();

void DCMOTOR_setState(et_Motor_State motorState);

void DCMOTOR_setSpeed(et_Motor_Speed MotorSpeed);

#endif /* DCMOTOR_INTERFACE_H */
