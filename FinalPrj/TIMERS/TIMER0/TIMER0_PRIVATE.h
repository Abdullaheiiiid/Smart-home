#ifndef TIMER0_PRIVATE_H
#define TIMER0_PRIVATE_H


#define TCNT0           *((volatile uint8*) 0x52)

#define TCCR0           *((volatile uint8*) 0x53)

#define OCR0            *((volatile uint8*) 0x5C)

#define TIMSK           *((volatile uint8*) 0x59)

/*MODE*/
#define TCCR0_WGM00     6
#define TCCR0_WGM01     3

/*PRESCALER*/
#define TCCR0_CS00      0
#define TCCR0_CS01      1
#define TCCR0_CS02      2

/*PWM OCR0 OUTPUT*/
#define TCCR0_COM00     4
#define TCCR0_COM01     5

/*INTERUPT PINS*/
#define TIMSK_OCIE0     1
#define TIMSK_TOIE0     0


#endif /*TIMER0_PRIVATE_H*/
