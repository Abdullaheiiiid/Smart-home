#ifndef GLCD_INTERFACE_H
#define GLCD_INTERFACE_H




void GLCD_init();

void GLCD_sendCommand(uint8 CMD, uint8 cs);

void GLCD_sendData(uint8 Data, uint8 cs);


void GLCD_moveCursor(uint8 row, uint8 col);

void GLCD_sendChar(uint8 Char);



void GLCD_sendString(char *str);


void GLCD_sendLogo();

void GLCD_clearLCD();

#endif /*GLCD_INTERFACE_H*/