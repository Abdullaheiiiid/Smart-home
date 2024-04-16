#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

/* Enumeration of ADC channels */
typedef enum {
    CH0,
    CH1,
    CH2,
    CH3,
    CH4,
    CH5,
    CH6,
    CH7
} CHN;

/* Callback function type for ADC completion */
typedef void (*ADC_callback)(uint16);

/** Initialize the ADC module */
void ADC_init();

/** Start ADC conversion on the specified channel */
void ADC_startConversion(uint8 CH);

/** Set the callback function for ADC completion */
void ADC_setCallback(ADC_callback callback);

#endif /* ADC_INTERFACE_H */
