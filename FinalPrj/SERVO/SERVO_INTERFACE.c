#include "./STD/STD_TYPES.h"
#include "./STD/STD_MATH.h"
#include "./DIO/DIO_INTERFACE.h"
#include "TIMERS/TIMER1/TIMER1_INTERFACE.h"
#include "TIMERS/TIMER1/TIMER1_PRIVATE.h"


void SERVO_init()
{
	
	TIMER1_setPWMMode(non_inverted);
	TIMER1_init(TIMER1_FASTPWM_MODE, TIMER1_CLK_64_PRESCALER);
	ICR1=(uint16)((0.02)/(64*1.0/F_CPU));
	setPinDirection(Port_D, Pin4, Output);
	setPinDirection(Port_D, Pin5, Output);
    
}
void SERVO_setDegree(int d)
{
    double onTime = (d*0.002)/180;
	OCR1A = (uint16)((onTime)/(64*1.0/F_CPU));
}