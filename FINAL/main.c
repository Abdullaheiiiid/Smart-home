#include "STD/STD_TYPES.h"
#include "STD/STD_MATH.h"
#include "DIO/DIO_INTERFACE.h"
#include "SPI/SPI_INTERFACE.h"
#include "DCMOTOR/DCMOTOR_INTERFACE.h"
#include "SERVO/SERVO_INTERFACE.h"

#include <util/delay.h>

#define RELAY_PORT    Port_A
#define RELAY_PIN     Pin4
#define BUZZER_PORT    Port_A
#define BUZZER_PIN     Pin5

int main(void)
{


    DCMOTOR_init();
    SERVO_init();
    setPinDirection(RELAY_PORT, RELAY_PIN, Output);
    setPinValue(RELAY_PORT, RELAY_PIN, PinLow);
    setPinDirection(BUZZER_PORT, BUZZER_PIN, Output);
	setPinValue(BUZZER_PORT, BUZZER_PIN, PinLow);
    SPI_sleveInit();
    for(;;){
    	uint8 ch = SPI_transceive(0);
    	switch(ch){
    	case 'd':
    		DCMOTOR_setState(motorStop);
    		break;
    	case 'D':
			DCMOTOR_setState(motorStart);
			break;
    	case '1':
    		DCMOTOR_setState(motorStart);
			DCMOTOR_setSpeed(motorSpeed1);
			break;
    	case '2':
    		DCMOTOR_setState(motorStart);
    		DCMOTOR_setSpeed(motorSpeed2);
    		break;
    	case '3':
    		DCMOTOR_setState(motorStart);
    		DCMOTOR_setSpeed(motorSpeed3);
    		break;
    	case 'R':
    		setPinValue(RELAY_PORT, RELAY_PIN, PinHigh);
			break;
    	case 'r':
    		setPinValue(RELAY_PORT, RELAY_PIN, PinLow);
			break;
    	case 'F':
    		setPinValue(BUZZER_PORT, BUZZER_PIN, PinHigh);
    		SERVO_setDegree(180);
			break;
		case 'f':
			setPinValue(BUZZER_PORT, BUZZER_PIN, PinLow);
			SERVO_setDegree(0);
			break;
    	default:
		break;
    	}
    }

    return 0;
}

