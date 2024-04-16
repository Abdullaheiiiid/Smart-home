
#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

// SPI CONTROL REGISTER       
#define SPCR     *((volatile uint8 *) 0x2D)

//spi interrupt enable
#define SPCR_SPIE    7 

//spi enable
#define SPCR_SPE     6 

//data order lsb(write1) or msb(WRITE0) 
#define SPCR_DORD    5 

// MASTER OR SLAVE SELECT MASTER(WRITE1),SLAVE(WRITE0)
#define SPCR_MSTR    4

// CLOCK POLARITY LOW(WRITE0),HIGH(WRITE1)
#define SPCR_CPOL    3

/*
CLOCK PHASE
SAMPLE(LEADING) AND SETUP(TRALLING) WRITE(0)
SETUP(LEADING) AND SAMPLE(TRALLING) WRITE(1)
*/
#define SPCR_CPHA    2

// SPI CLOCK RATE SELECT ,MASTER ONLY
#define SPCR_SPR1    1
#define SPCR_SPR0    0

//SPI STATUS REGISTER
#define SPSR      *((volatile uint8 *) 0x2E)

//SPI INTERRUPT FLAG 
#define SPSR_SPIF     7 

//WRITE COLLISION FLAG
#define SPSR_WCOL     6

// DOUBLE SPEED BIT 
#define SPSR_SPI2X    0


// SPI DATA REGISTER 
#define SPDR    *((volatile uint16 *) 0x2F)


#define SPSR_MSB     7 
#define SPSR_LSB     0


#endif
