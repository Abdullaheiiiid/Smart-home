#include "../STD/STD_TYPES.h"
#include "../STD/STD_MATH.h"
#include "../DIO/DIO_INTERFACE.h"
#include "SPI_PRIVATE.h"
#include "SPI_INTERFACE.h"
#include <stddef.h>

void SPI_masterInit()
{
    setPinDirection(Port_B,Pin4, Input);
	setPinDirection(Port_B,Pin5, Output);
	setPinDirection(Port_B,Pin6, Input);
	setPinDirection(Port_B,Pin7, Output);
	//select clk pol=0 ; clk ph=0
	CLEAR_BIT(SPCR,SPCR_CPHA);
	CLEAR_BIT(SPCR,SPCR_CPOL);

	//select master mode
	SET_BIT(SPCR,SPCR_MSTR);

	//set data order MSB
	CLEAR_BIT(SPCR,SPCR_DORD);

	//select clk in master
	CLEAR_BIT(SPSR,SPSR_SPI2X);
	CLEAR_BIT(SPCR,SPCR_SPR1);
	CLEAR_BIT(SPCR,SPCR_SPR0);

	//enable spi
	SET_BIT(SPCR,SPCR_SPE);
}

void SPI_sleveInit(void)
{	
	setPinDirection(Port_B,Pin4, Input);
	setPinDirection(Port_B,Pin5, Input);
	setPinDirection(Port_B,Pin6, Output);
	setPinDirection(Port_B,Pin7, Input);
	//select sleve mode
	CLEAR_BIT(SPCR,SPCR_MSTR);

	//set data order MSB
	CLEAR_BIT(SPCR,SPCR_DORD);

	//enable spi
	SET_BIT(SPCR,SPCR_SPE);
}

uint8 SPI_transceive(uint8 Copy_U8data)
{
	//send data
	SPDR = Copy_U8data ;

	//flag check
	while(!GET_BIT(SPSR,SPSR_SPIF));
	return SPDR ;
}
