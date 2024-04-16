#ifndef LDR_INTERFACE_H
#define LDR_INTERFACE_H

void LDR_init();

void LDR_calculate(uint8 CH, uint8 mode);

uint8 LDR_getPercentage();
#endif /* LDR_INTERFACE_H */
