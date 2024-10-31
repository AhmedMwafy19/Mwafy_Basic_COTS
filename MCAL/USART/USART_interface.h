#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

void USART_voidInit(void);
uint8 USART_u8SendByte(uint8 Copy_u8Data);
uint8 USART_u8RecieveByte(uint8 * Copy_u8Data);

uint8 USART_u8SendBufferSynch(uint8 * Copy_u8Data , uint8 Copy_u8Size);
uint8 USART_u8RecieveBufferSynch(uint8 * Copy_u8Data , uint8 Copy_u8Size);

uint8 USART_u8RecieveBufferASynch(uint8 * Copy_pu8Data ,uint8 Copy_u8Size, void (*Copy_voidFunc)(void));
uint8 USART_u8SendBufferASynch(uint8 * Copy_pu8Data , uint8 Copy_u8Size ,void (*Copy_voidFunc)(void));

#endif
