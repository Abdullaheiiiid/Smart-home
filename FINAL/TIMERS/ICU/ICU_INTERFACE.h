#ifndef ICU_INTERFACE_H
#define ICU_INTERFACE_H



typedef enum{
    ICU_FALLING_EDGE,
    ICU_RISING_EDGE
}et_ICUTYPE;




void ICU_init();

void ICU_setTrigger(et_ICUTYPE edge);
void ICU_IE();
void ICU_ID();
uint16 ICU_readICU();



#endif /* ICU_INTERFACE_H */

