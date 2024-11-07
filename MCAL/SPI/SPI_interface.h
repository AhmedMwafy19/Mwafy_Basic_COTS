#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

void SPI_voidInit(void);
uint8 SPI_u8TransceiveSynch(uint8 Copu_u8Data);/* Send Garbage Value in case of receiving*/
uint8 SPI_u8TransceiveAsynch(uint8 * Copu_u8Data , void (*Copy_voidFunc)(void));

#endif
