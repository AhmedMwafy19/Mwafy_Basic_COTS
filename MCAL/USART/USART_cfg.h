#ifndef USART_CFG_H
#define USART_CFG_H
/*Configure whether you will work with both TX & RX or one of them 1)USART_TX_ONLY
 * 																   2)USART_RX_ONLY
 * 																   3)USART_TX_RX_BOTH */

#define USART_ACTIVATION  USART_TX_RX_BOTH

/*Configure whether you will work with synchronous or Asynchronous 1)USART_CLK_SYNCH
 * 																   2)USART_CLK_ASYNCH */

/*Configure Baud_Rate*/
#define USART_u8BAUDRATE   9600u
#define MC_CLOCK_FREQUENCY 16000000u

#define USART_u8MODE  USART_CLK_ASYNCH
/*In case of synch ,configure clock polarity 1)TRANSMIT_RISING
 * 											 2)TRANSMIT_FALLING*/

#define CLOCK_u8Polarity TRANSMIT_RISING

/*Configure Parity Mode 1)EVEN_PARITY
 * 						2)ODD_PARITY
 * 						3)NO_PARITY*/
#define PARITY_u8Mode NO_PARITY
#if PARITY_u8Mode == NO_PARITY
#define PARITY_BIT0    0u
#define PARITY_BIT1    1u
#elif PARITY_u8Mode == EVEN_PARITY
#define PARITY_BIT0    0u
#define PARITY_BIT1    1u
#elif PARITY_u8Mode == ODD_PARITY
#define PARITY_BIT0    0u
#define PARITY_BIT1    1u
#else
#error Wrong_Configuration
#endif
/*Configue Number of stop bits  1)STOP_ONE_BIT
 * 								2)STOP_TWO_BIT*/

#define USART_STOP_BITS  STOP_ONE_BIT
/*Configure Number Of data transferred in every frame 1) FIVE_BITS
 * 													  2) SIX_BITS
 * 													  3) SEVEN_BITS
 * 													  4) EIGHT_BITS
 * 													  5) NINE_BITS  */

#define USART_u8BitMode    EIGHT_BITS

#if USART_u8BitMode == FIVE_BITS
#define BITSELECTION1  0u
#define BITSELECTION0  0u
#elif USART_u8BitMode == SIX_BITS
#define BITSELECTION1  0u
#define BITSELECTION0  1u
#elif USART_u8BitMode == SEVEN_BITS
#define BITSELECTION1  1u
#define BITSELECTION0  0u
#elif USART_u8BitMode == EIGHT_BITS
#define BITSELECTION1  1u
#define BITSELECTION0  1u
#elif USART_u8BitMode == NINE_BITS
#define BITSELECTION1  0u
#define BITSELECTION0  1u
#else
#error Wrong_Configuration
#endif




#endif
