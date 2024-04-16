#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H


#define ADMUX   *((volatile uint8*) 0x27)

#define ADCSRA  *((volatile uint8*) 0x26)

#define ADC     *((volatile uint16*) 0x24)


#endif /*ADC_PRIVATE_H*/