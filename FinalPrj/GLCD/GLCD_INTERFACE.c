#include "./STD/STD_TYPES.h"
#include "./STD/STD_MATH.h"
#include "./DIO/DIO_INTERFACE.h"
#include "GLCD_CONFIG.h"
#include "GLCD_INTERFACE.h"
#include <stdio.h>
#include <util/delay.h>

static uint8 count = 0;

void GLCD_sendCommand(uint8 CMD, uint8 cs){
	if( cs == 1 ){
		setPinValue(LCD_CONT_CS1, LCD_CS1, PinHigh);
	}
	if( cs == 2 ){
		setPinValue(LCD_CONT_CS2, LCD_CS2, PinHigh);
	}
	setPinValue(LCD_CONT_DI, LCD_DI, PinLow);
	setPinValue(LCD_CONT_EN, LCD_EN, PinHigh);
	setPinValue(LCD_DATA_DB0, LCD_DB0, GET_BIT(CMD, 0));
	setPinValue(LCD_DATA_DB1, LCD_DB1, GET_BIT(CMD, 1));
	setPinValue(LCD_DATA_DB2, LCD_DB2, GET_BIT(CMD, 2));
	setPinValue(LCD_DATA_DB3, LCD_DB3, GET_BIT(CMD, 3));
	setPinValue(LCD_DATA_DB4, LCD_DB4, GET_BIT(CMD, 4));
	setPinValue(LCD_DATA_DB5, LCD_DB5, GET_BIT(CMD, 5));
	setPinValue(LCD_DATA_DB6, LCD_DB6, GET_BIT(CMD, 6));
	setPinValue(LCD_DATA_DB7, LCD_DB7, GET_BIT(CMD, 7));
	//setPortValue(LCD_DATA, CMD);
	setPinValue(LCD_CONT_EN, LCD_EN, PinLow);
	_delay_us(10);
	if( cs == 1 ){
		setPinValue(LCD_CONT_CS1, LCD_CS1, PinLow);
	}
	if( cs == 2 ){
		setPinValue(LCD_CONT_CS2, LCD_CS2, PinLow);
	}
}
 
void GLCD_sendData(uint8 Data, uint8 cs){
	if( cs == 1 ){
		setPinValue(LCD_CONT_CS1, LCD_CS1, PinHigh);
	}
	if( cs == 2 ){
		setPinValue(LCD_CONT_CS2, LCD_CS2, PinHigh);
	}
	setPinValue(LCD_CONT_DI, LCD_DI, PinHigh);
	setPinValue(LCD_CONT_EN, LCD_EN, PinHigh);
	
	setPinValue(LCD_DATA_DB0, LCD_DB0, GET_BIT(Data, 0));
	setPinValue(LCD_DATA_DB1, LCD_DB1, GET_BIT(Data, 1));
	setPinValue(LCD_DATA_DB2, LCD_DB2, GET_BIT(Data, 2));
	setPinValue(LCD_DATA_DB3, LCD_DB3, GET_BIT(Data, 3));
	setPinValue(LCD_DATA_DB4, LCD_DB4, GET_BIT(Data, 4));
	setPinValue(LCD_DATA_DB5, LCD_DB5, GET_BIT(Data, 5));
	setPinValue(LCD_DATA_DB6, LCD_DB6, GET_BIT(Data, 6));
	setPinValue(LCD_DATA_DB7, LCD_DB7, GET_BIT(Data, 7));

	setPinValue(LCD_CONT_EN, LCD_EN, PinLow);
	_delay_us(10);
	if( cs == 1 ){
		setPinValue(LCD_CONT_CS1, LCD_CS1, PinLow);
	}
	if( cs == 2 ){
		setPinValue(LCD_CONT_CS2, LCD_CS2, PinLow);
	}
}

 
 
void GLCD_moveCursor(uint8 row, uint8 col){
	if(col < 64){
		GLCD_sendCommand(0x40 + col, 1);
		GLCD_sendCommand(0x40 + 0, 2);
	}
	else{
		GLCD_sendCommand(0x40 + 0, 1);
		GLCD_sendCommand(0x40 + col - 63 ,2);
	}
 
	GLCD_sendCommand(0xB8 + row,1);
	GLCD_sendCommand(0xB8 + row,2);
	count = col;
}
 
void GLCD_sendChar(uint8 Char){
	for (int i=0;i<5;i++)
	{
		if(count < 64) GLCD_sendData(Font5x8[((Char - 32) * 5) + i], 1);
		else GLCD_sendData(Font5x8[((Char - 32) * 5) + i], 2);
		count++;
	}
	GLCD_sendData(0, (count < 64) ? 1 : 2);
	count++;
	if (count > 127)
	{
		count = 0;
	}
}
 
 
void GLCD_sendString(char *str){
    for (uint8 i = 0; str[i] != '\0'; i++){
        GLCD_sendChar(str[i]);
    }
}
 
 
void GLCD_init(){
	setPinDirection(LCD_DATA_DB0, LCD_DB0, Output);
	setPinDirection(LCD_DATA_DB1, LCD_DB1, Output);
	setPinDirection(LCD_DATA_DB2, LCD_DB2, Output);
	setPinDirection(LCD_DATA_DB3, LCD_DB3, Output);
	setPinDirection(LCD_DATA_DB4, LCD_DB4, Output);
	setPinDirection(LCD_DATA_DB5, LCD_DB5, Output);
	setPinDirection(LCD_DATA_DB6, LCD_DB6, Output); 
	setPinDirection(LCD_DATA_DB7, LCD_DB7, Output); 

	setPinDirection(LCD_CONT_EN, LCD_EN, Output);
	setPinDirection(LCD_CONT_DI, LCD_DI, Output);
	setPinDirection(LCD_CONT_CS1, LCD_CS1, Output);
	setPinDirection(LCD_CONT_CS2, LCD_CS2, Output);
	
	GLCD_sendCommand(0x3F,1);
	GLCD_sendCommand(0x3F,2);
	count = 0;
}
 

void GLCD_sendLogo(){
	uint16 tcount = 0;
	for (int i = 0; i < 8; i++)
	{
		count=0;
		GLCD_moveCursor(i, 0);
		for (int j = tcount; j < tcount + 128; j++)
		{
			if(count<64) GLCD_sendData(IPL_Logo[j],1);
			else GLCD_sendData(IPL_Logo[j],2);
			count++;
		}
		tcount += 128;
	}
}

void GLCD_clearLCD(){
 
	for (int i = 0; i < 8; i++)
	{
		GLCD_moveCursor(i, 0);
		for(int j=0;j<128;j++){
			GLCD_sendData(0,1);
			GLCD_sendData(0,2);
		}
	}	
	count=0;
	GLCD_moveCursor(0,0);
}









