#include "./STD/STD_TYPES.h"
#include "./STD/STD_MATH.h"
#include "./DIO/DIO_INTERFACE.h"
#include "./TIMERS/TIMER0/TIMER0_INTERFACE.h"
#include "DCMOTOR_INTERFACE.h"

void DCMOTOR_init()
{
	TIMER0_init(TIMER0_FASTPWM_MODE, CLK_8_PRESCALER);
	TIMER0_setPWMMode(non_inverted);
	setPinDirection(Port_B, Pin3, Output);

	setPinDirection(MOTOR1_PORT, MOTOR1_INPUT1_PIN, Output);
	setPinDirection(MOTOR1_PORT, MOTOR1_INPUT2_PIN, Output);
	setPinDirection(MOTOR2_PORT, MOTOR2_INPUT1_PIN, Output);
	setPinDirection(MOTOR2_PORT, MOTOR2_INPUT2_PIN, Output);

	setPinValue(MOTOR1_PORT, MOTOR1_INPUT1_PIN, PinLow);
	setPinValue(MOTOR1_PORT, MOTOR1_INPUT2_PIN, PinLow);
	setPinValue(MOTOR2_PORT, MOTOR2_INPUT1_PIN, PinLow);
	setPinValue(MOTOR2_PORT, MOTOR2_INPUT2_PIN, PinLow);

	DCMOTOR_setSpeed(motorSpeed1);
}

void DCMOTOR_setState(et_Motor_State motorState)
{
	switch(motorState)
	{
	case motorStart:
		setPinValue(MOTOR1_PORT, MOTOR1_INPUT1_PIN, PinHigh);
		setPinValue(MOTOR1_PORT, MOTOR1_INPUT2_PIN, PinLow);
		setPinValue(MOTOR2_PORT, MOTOR2_INPUT1_PIN, PinHigh);
		setPinValue(MOTOR2_PORT, MOTOR2_INPUT2_PIN, PinLow);
		break;
	case motorStop:
		setPinValue(MOTOR1_PORT, MOTOR1_INPUT1_PIN, PinLow);
		setPinValue(MOTOR1_PORT, MOTOR1_INPUT2_PIN, PinLow);
		setPinValue(MOTOR2_PORT, MOTOR2_INPUT1_PIN, PinLow);
		setPinValue(MOTOR2_PORT, MOTOR2_INPUT2_PIN, PinLow);
		break;
	}
}


void DCMOTOR_setSpeed(et_Motor_Speed MotorSpeed)
{
	switch(MotorSpeed)
	{
	case motorSpeed1:
		TIMER0_VidDUTYCYCLE(33);
		break;
	case motorSpeed2:
		TIMER0_VidDUTYCYCLE(66);
		break;
	case motorSpeed3:
		TIMER0_VidDUTYCYCLE(100);
		break;
	}
}