#include "./STD/STD_TYPES.h"
#include "./STD/STD_MATH.h"
#include "./DIO/DIO_INTERFACE.h"
#include "TIMER0_PRIVATE.h"
#include "TIMER0_INTERFACE.h"
#include <stddef.h>

static TIMER0_Callback timer0Callback = NULL;
static uint8 counter = 0;
static uint32 timex = 0;
static ed_TIMEDEF typex = mS;

void TIMER0_init(et_TIMER0MODE mode, et_TIMERPRESCALER prescaller){
    switch (mode)
    {
    case TIMER0_NORMAL_MODE:
        CLEAR_BIT(TCCR0, TCCR0_WGM00);
        CLEAR_BIT(TCCR0, TCCR0_WGM01);
        break;
    case TIMER0_CTC_MODE:
        CLEAR_BIT(TCCR0, TCCR0_WGM00);
        SET_BIT(TCCR0, TCCR0_WGM01);
        break;
    case TIMER0_FASTPWM_MODE:
        SET_BIT(TCCR0, TCCR0_WGM00);
        SET_BIT(TCCR0, TCCR0_WGM01);
        break;
    case TIMER0_PHASECORRECT_MODE:
        SET_BIT(TCCR0, TCCR0_WGM00);
        CLEAR_BIT(TCCR0, TCCR0_WGM01);
        break;
    default:
        break;
    }

    TCCR0 &= 0xF8;
    TCCR0 |= prescaller;
}

void TIMER_INIT_SASA(){
    SET_BIT(TCCR0, TCCR0_WGM00);
    SET_BIT(TCCR0, TCCR0_WGM01);

    OCR0 = 64;

    SET_BIT(TCCR0, 5);
    CLEAR_BIT(TCCR0, 4);

    CLEAR_BIT(TCCR0, TCCR0_CS00);
    SET_BIT(TCCR0, TCCR0_CS01);
    CLEAR_BIT(TCCR0, TCCR0_CS02);
}

void TIMER0_OVF_IE(){
    SET_BIT(TIMSK, TIMSK_TOIE0);
}

void TIMER0_OVF_ID(){
    CLEAR_BIT(TIMSK, TIMSK_TOIE0);
}

void TIMER0_CMP_IE(){
    SET_BIT(TIMSK, TIMSK_OCIE0);
}

void TIMER0_CMP_ID(){
    CLEAR_BIT(TIMSK, TIMSK_OCIE0);
}

void TIMER0_setCompareValue(uint8 value) {
    OCR0 = value;
}

void TIMER0_setValue(uint8 value) {
    TCNT0 = value;
}

void TIMER0_setCallback(TIMER0_Callback callback) {
    timer0Callback = callback;
}


void TIMER0_VidDUTYCYCLE(uint8 dutyCycle)
{
    uint8 compVal = (uint8)(((uint32)(dutyCycle * 255)) / 100);
    TIMER0_setCompareValue(compVal);
}

void TIMER0_setPWMMode(ed_TIMER0PWM mode){
    switch (mode)
    {
    case inverted:
        SET_BIT(TCCR0, TCCR0_COM00);
        SET_BIT(TCCR0, TCCR0_COM01);
        break;
    case non_inverted:
        SET_BIT(TCCR0, TCCR0_COM01);
        CLEAR_BIT(TCCR0, TCCR0_COM00);
        break;
    default:
        break;
    }
}

void TIMER_executeByInterval(TIMER0_Callback callback, uint32 time, ed_TIMEDEF type){
    switch (type)
    {
    case S:
        {
            if(counter == 0){
                TCCR0 &= 0xF8;
                TCCR0 |= 5;
                TIMER0_setCompareValue(125);
                timer0Callback = callback;
            }
            timex = time;
            counter++;
            uint32 counterVAl = (time/(0.000064))/125;
            if (counter == counterVAl) {
                if (timer0Callback != NULL) {
                    timer0Callback();
                }
                counter = 0;
            }
        }
        break;
    case mS:
        {
            if(counter == 0){
                TCCR0 &= 0xF8;
                TCCR0 |= 5;
                TIMER0_setCompareValue(125);
                timer0Callback = callback;
            }
            timex = time;
            counter++;
            uint32 counterVAl = (time*0.001/(0.000064))/125;
            if (counter == counterVAl) {
                if (timer0Callback != NULL) {
                    timer0Callback();
                }
                counter = 0;
            }
            
        }
        break;
    default:
        break;
    }
}

void __vector_11(void) __attribute__((signal, used));
void __vector_11(void) {
    TIMER_executeByInterval(timer0Callback, timex, typex);
}
