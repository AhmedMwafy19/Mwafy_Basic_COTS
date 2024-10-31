#ifndef USART_REG_H
#define USART_REG_H

/*The Transmitted data memory location and recieved data memory location
 * share the same memory address which is refered to as UDR register ,
 * For 5-, 6-, or 7-bit characters the upper unused bits will be ignored by the Transmitter
 and set to zero by the Receiver.
 *For 9-bit data , the ninth bit is stored in a different bit in a different register
  */
#define UDR 	 *((volatile uint8 *)0x2C)


#define UCSRA 	 *((volatile uint8 *)0x2B)
#define UCSRA_RXC  7u //Receive complete flag
#define UCSRA_TXC  6u //Transmission complete flag
#define UCSRA_UDRE  5u //indication that transmission is ready flag
#define UCSRA_FE  4u //Frame error flag
#define UCSRA_DOR  3u //Data over run error flag i.e: transmission is too fast that data has been lost not received
#define UCSRA_PE  2u //Parity error flag
#define UCSRA_U2X  1u //For doubling communication speed "unnecessary"
#define UCSRA_MPCM  0u //To use more than 2 systems in uart "Master & slave "


#define UCSRB 	 *((volatile uint8 *)0x2A)
#define UCSRB_RXCIE  7u // RX Complete Interrupt Enable
#define UCSRB_TXCIE  6u //TX Complete Interrupt Enable
#define UCSRB_UDRIE  5u //USART Data Register Empty Interrupt Enable
#define UCSRB_RXEN  4u // Receiver Enable
#define UCSRB_TXEN 3u //Transmitter Enable
#define UCSRB_UCSZ2  2u // The UCSZ2 bits combined with the UCSZ1:0 bit in UCSRC sets the number of data bits(Character Size) in a frame the receiver and transmitter use
#define UCSRB_RXB8  1u //It holds the ninth bit of the received data in case of 9 bit mode
#define UCSRB_TXB8  0u //It holds the ninth bit of the Transmitted data in case of 9 bit mode

#define UCSRC 	 *((volatile uint8 *)0x40)
#define UCSRC_URSEL 7u // Register Select This bit selects between accessing the UCSRC or the UBRRH Register.
#define UCSRC_UMSEL 6u // USART Mode Select
#define UCSRC_UPM1  5u /*Parity Mode bits*/
#define UCSRC_UPM0  4u
#define UCSRC_USBS	3u // Stop Bit Select
#define UCSRC_UCSZ1  2u
#define UCSRC_UCSZ0  1u
#define UCSRC_UCPOL	0u // Clock Polarity


#define UBRRH 	 *((volatile uint8 *)0x40)

#define UBRRL 	 *((volatile uint8 *)0x29)

#endif
