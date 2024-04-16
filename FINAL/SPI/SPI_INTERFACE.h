#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

void SPI_masterInit(void);

void SPI_sleveInit(void);

uint8 SPI_transceive(uint8 Copy_U8data);



#endif /* SPI_INTERFACE_H */
