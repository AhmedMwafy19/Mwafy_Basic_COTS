#ifndef USART_PRV_H
#define USART_PRV_H



#define USART_TX_ONLY    1u
#define USART_RX_ONLY     2u
#define USART_TX_RX_BOTH  3u


#define USART_CLK_SYNCH   1u
#define USART_CLK_ASYNCH   0u

#define EVEN_PARITY   1u
#define ODD_PARITY 	2u
#define NO_PARITY 3u

#define STOP_ONE_BIT   0u
#define STOP_TWO_BIT   1u

#define FIVE_BITS     5u
#define SIX_BITS      6u
#define SEVEN_BITS    7u
#define EIGHT_BITS    8u
#define NINE_BITS     9u

#define TRANSMIT_RISING    0u
#define TRANSMIT_FALLING   1u

#define TIME_OUT 500000u


#define IDEL 0u
#define BUSY 1u
#endif
