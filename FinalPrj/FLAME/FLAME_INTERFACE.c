#include "../STD/STD_TYPES.h"
#include "../STD/STD_MATH.h"
#include "../ADC/ADC_INTERFACE.h"
#include "../SPI/SPI_INTERFACE.h"
#include "FLAME_interface.h"

void FLAME_handleADCResult(uint16 result) {
	uint16 value = result;
	float volt = ((float)value * 0.00488);
    if(volt <= 2.5){
        SPI_transceive('f');
    }
    else{
        SPI_transceive('F');
    }
}

void FLAME_init(){
    ADC_setCallback(FLAME_handleADCResult);
}

void FLAME_calculate(uint8 CH){
    ADC_startConversion(CH);
}
