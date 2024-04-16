#include "../STD/STD_TYPES.h"
#include "../STD/STD_MATH.h"
#include "../ADC/ADC_INTERFACE.h"
#include "LM35_INTERFACE.h"
#include "../SPI/SPI_INTERFACE.h"
#include <util/delay.h>
static uint16 temperature = 0;
static uint8 currentMode = 0;
void LM35_handleADCResult(uint16 result) {

    temperature = (((uint32)result * 5UL * 100) / (1024UL));
    if(currentMode == 0){    
        if(temperature <= 25){
            SPI_transceive('d');
        }else if(temperature > 25 && temperature <= 30){
            SPI_transceive('D');
        }else if(temperature > 30 && temperature <= 35){
            SPI_transceive('2');
        }else if(temperature > 35){
            SPI_transceive('3');
        }
    }
}

void LM35_init(){
    ADC_setCallback(LM35_handleADCResult);
}

void LM35_calculate(uint8 CH, uint8 mode){
    currentMode = mode;
    ADC_startConversion(CH);
}

uint16 LM35_getTemperature(){
    return temperature;
}