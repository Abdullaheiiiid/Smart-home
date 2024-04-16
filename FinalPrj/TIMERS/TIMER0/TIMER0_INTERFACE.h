#ifndef TIMER0_INTERFACE_H
#define TIMER0_INTERFACE_H

typedef enum{
    TIMER0_NORMAL_MODE,
    TIMER0_PHASECORRECT_MODE,
    TIMER0_CTC_MODE,
    TIMER0_FASTPWM_MODE
} et_TIMER0MODE;

typedef enum{
    NO_CLOCK_SOURCE,
    NO_PRESCALLING,
    CLK_8_PRESCALER,
    CLK_64_PRESCALER,
    CLK_256_PRESCALER,
    CLK_1024_PRESCALER,
    EXTERNAL_CLOCK_FALLINGEDGE,
    EXTERNAL_CLOCK_RISINGEDGE
} et_TIMERPRESCALER;

typedef enum{
    inverted,
    non_inverted
}ed_TIMER0PWM;

typedef enum{
    mS,
    S
}ed_TIMEDEF;

typedef void (*TIMER0_Callback)(void);

void TIMER0_init(et_TIMER0MODE mode, et_TIMERPRESCALER prescaler);
void TIMER0_OVF_IE();
void TIMER0_CMP_IE();
void TIMER0_OVF_ID();
void TIMER0_CMP_ID();
void TIMER0_VidDUTYCYCLE(uint8 dutyCycle);
void TIMER_executeByInterval(TIMER0_Callback callback, uint32 time, ed_TIMEDEF type);
void TIMER0_setPWMMode(ed_TIMER0PWM mode);
void TIMER0_setCallback(TIMER0_Callback callback);
void TIMER0_setCompareValue(uint8 value);
void TIMER0_setValue(uint8 value);
void TIMER_INIT_SASA();

#endif /* TIMER0_INTERFACE_H */

