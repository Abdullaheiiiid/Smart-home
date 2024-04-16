#ifndef LM35_INTERFACE_H
#define LM35_INTERFACE_H



void LM35_init();

void LM35_calculate(uint8 CH, uint8 mode);

uint16 LM35_getTemperature();


#endif /* LM35_INTERFACE_H */