#ifndef ICU_PRIVATE_H
#define ICU_PRIVATE_H


#define TCNT1           *((volatile uint8*) 0x4C)

#define TCCR1A           *((volatile uint8*) 0x4F)
#define TCCR1B           *((volatile uint8*) 0x4E)


#define TIMSK           *((volatile uint8*) 0x59)

#define ICR1           *((volatile uint8*) 0x46)

#define TCCR1B_WGM13     4
#define TCCR1B_WGM12     3
#define TCCR1B_CS12      2
#define TCCR1B_CS11      1
#define TCCR1B_CS10      0
#define TCCR1B_ICNC1     1
#define TCCR1B_ICES1     0


#define TCCR1B_TICIE1    5

#endif /*ICU_PRIVATE_H*/
