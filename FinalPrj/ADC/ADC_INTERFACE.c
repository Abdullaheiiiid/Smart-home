#include "./STD/STD_TYPES.h"
#include "./STD/STD_MATH.h"
#include "./DIO/DIO_INTERFACE.h"
#include "ADC_CONFIG.h"
#include "ADC_PRIVATE.h"
#include "ADC_INTERFACE.h"
#include <stddef.h>

/* Static variable to hold the callback function */
static ADC_callback adcCallback = NULL;

/** ADC Initialization */
void ADC_init() {
    /* Set the voltage reference to internal 5V reference */
    SET_BIT(ADMUX, ADMUX_REFS0);
    CLEAR_BIT(ADMUX, ADMUX_REFS0);

    /* Left-justify ADC result */
    CLEAR_BIT(ADMUX, ADMUX_ADLAR);

    /* Set ADC prescaler to 128 */
    SET_BIT(ADCSRA, ADCSRA_ADPS0);
    SET_BIT(ADCSRA, ADCSRA_ADPS1);
    SET_BIT(ADCSRA, ADCSRA_ADPS2);

    /* Enable ADC */
    SET_BIT(ADCSRA, ADCSRA_ADEN);

    /* Enable ADC interrupt */
    SET_BIT(ADCSRA, ADCSRA_ADIE);
}

/** Start ADC Conversion on the specified channel */
void ADC_startConversion(uint8 CH) {
    ADMUX &= 0b11100000; // Clear the channel bits
    ADMUX |= CH;         // Set the channel

    /* Start ADC conversion */
    SET_BIT(ADCSRA, ADCSRA_ADSC);
}

/** Set the callback function for ADC */
void ADC_setCallback(ADC_callback callback) {
    adcCallback = callback; // Set the callback function
}

/** ADC Conversion Complete Interrupt Service Routine */
void __vector_16(void) __attribute__((signal,  used)); // ADC conversion complete vector
void __vector_16(void) {
    if (adcCallback != NULL) {
        adcCallback(ADC); // Call the callback function with the ADC result
    }
}