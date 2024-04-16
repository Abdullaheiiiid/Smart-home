#include "../../STD/STD_TYPES.h"
#include "../../STD/STD_MATH.h"
#include "../../DIO/DIO_INTERFACE.h"
#include "ICU_PRIVATE.h"
#include "ICU_INTERFACE.h"
#include <stddef.h>


void ICU_init(){

    SET_BIT(TCCR1B, TCCR1B_ICES1);

    SET_BIT(TIMSK, TCCR1B_TICIE1);
}

void ICU_setTrigger(et_ICUTYPE edge){
    if(edge == ICU_RISING_EDGE){
        SET_BIT(TCCR1B, TCCR1B_ICES1);
    }
    else if(edge == ICU_FALLING_EDGE){
        CLEAR_BIT(TCCR1B, TCCR1B_ICES1);
    }

}

void ICU_IE(){
    SET_BIT(TIMSK, TCCR1B_TICIE1);
}

void ICU_ID(){
    CLEAR_BIT(TIMSK, TCCR1B_TICIE1);
}

uint16 ICU_readICU(){
    return ICR1;
}
