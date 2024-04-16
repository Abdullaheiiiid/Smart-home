#include "../STD/STD_TYPES.h"
#include "../STD/STD_MATH.h"
#include "../ADC/ADC_INTERFACE.h"
#include "LDR_INTERFACE.h"
#include "../SPI/SPI_INTERFACE.h"
uint8 percentage = 0;
static uint8 currentMode = 0;
void LDR_handleADCResult(uint16 result) {
	uint16 value = result;
	percentage = 100-(((float)value / 1023)*100);
    if(currentMode == 0){
        if(percentage <= 50){
            SPI_transceive('R');
        }
        else{
            SPI_transceive('r');
        }
    }
}


void LDR_init(){
    ADC_setCallback(LDR_handleADCResult);
}

void LDR_calculate(uint8 CH, uint8 mode){
    currentMode = mode;
    ADC_startConversion(CH);
}

uint8 LDR_getPercentage(){
    return percentage;
}
