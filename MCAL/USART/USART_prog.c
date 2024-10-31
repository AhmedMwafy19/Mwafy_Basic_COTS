#include "STD_TYPES.h"
#include "ErrorState.h"
#include "BIT_MATH.h"

#include "USART_prv.h"
#include "USART_cfg.h"
#include "USART_reg.h"
#include "USART_interface.h"

static uint8* UARTpu8Result = NULL;
static uint8* UART_pu8ValueSend = NULL;
static uint8 UART_Recieve_BufferSize = 0;
static uint8 UART_Transmit_BufferSize = 0;
static uint8 UART_u8Counter = 0;
static uint8 UART_u8_TransmitCounter = 0;
static void (*UART_pvNotificationFunc)(void) = NULL;
static void (*UART_pvNotificationFunc_Transmit)(void) = NULL;

static uint8 u8Flag = IDEL ;


void USART_voidInit(void){
	/* Enabling Transmitter & receiver */
#if USART_ACTIVATION == USART_TX_RX_BOTH
	SET_BIT(UCSRB , UCSRB_RXEN);
	SET_BIT(UCSRB , UCSRB_TXEN);
#elif USART_ACTIVATION == USART_RX_ONLY
	SET_BIT(UCSRB , UCSRB_RXEN);
	CLR_BIT(UCSRB , UCSRB_TXEN);
#elif USART_ACTIVATION == USART_TX_ONLY
	SET_BIT(UCSRB , UCSRB_TXEN);
	CLR_BIT(UCSRB , UCSRB_RXEN);
#else
#error Wrong_Configuration
#endif

/* Setting Parity Mode
*Setting Number of stop bits
*Setting Number of bits transferred in every frame
*Setting Clock Polarity
*/

UCSRC =( (1<<UCSRC_URSEL) | (USART_u8MODE << UCSRC_UMSEL) | (PARITY_BIT0 << UCSRC_UPM0) | (PARITY_BIT1 << UCSRC_UPM1) | ( USART_STOP_BITS << UCSRC_USBS) | (BITSELECTION1 << UCSRC_UCSZ1) | (BITSELECTION0 << UCSRC_UCSZ0) | (CLOCK_u8Polarity << UCSRC_UCPOL) );

#if USART_u8BitMode == FIVE_BITS
	CLR_BIT(UCSRB , UCSRB_UCSZ2);
#elif USART_u8BitMode == SIX_BITS
	CLR_BIT(UCSRB , UCSRB_UCSZ2);
#elif USART_u8BitMode == SEVEN_BITS
	CLR_BIT(UCSRB , UCSRB_UCSZ2);
#elif USART_u8BitMode == EIGHT_BITS
	CLR_BIT(UCSRB , UCSRB_UCSZ2);
#elif USART_u8BitMode == NINE_BITS
	SET_BIT(UCSRB , UCSRB_UCSZ2);
#else
#error Wrong_Configuration
#endif
/*Configuring BaudRate*/
#if USART_u8MODE == USART_CLK_ASYNCH
	UBRRL =(uint8)( (MC_CLOCK_FREQUENCY / (16 * USART_u8BAUDRATE)) - 1 ) ;
	UBRRH = ( (MC_CLOCK_FREQUENCY / (16 * USART_u8BAUDRATE)) - 1 ) >> 8u ;
#elif USART_u8MODE == USART_CLK_SYNCH
	UBRRL =( (MC_CLOCK_FREQUENCY / (2 * USART_u8BAUDRATE)) - 1 ) ;
	UBRRH = ( (MC_CLOCK_FREQUENCY / (2 * USART_u8BAUDRATE)) - 1 ) >> 8u ;
#else
#error Wrong_Configuration
#endif

}

uint8 USART_u8SendByte(uint8 Copy_u8Data){
	uint8 Local_u8ErrorState = OK;
	uint32 Local_u32Counter = 0 ;
	while(GET_BIT(UCSRA , UCSRA_UDRE) == 0 && Local_u32Counter++ < TIME_OUT);
	if(Local_u32Counter > TIME_OUT){
		Local_u8ErrorState = TIME_OUT_ERR;
	}
	else {
	UDR = Copy_u8Data;
	}
	return Local_u8ErrorState;
}


uint8 USART_u8RecieveByte(uint8 * Copy_u8Data){
	uint8 Local_u8ErrorState = OK;
	uint32 Local_u32Counter = 0 ;
	if(Copy_u8Data != NULL){

		while(GET_BIT(UCSRA , UCSRA_RXC) == 0 && Local_u32Counter++ < TIME_OUT);
		if(Local_u32Counter > TIME_OUT){
				Local_u8ErrorState = TIME_OUT_ERR;
			}
		else {
		*Copy_u8Data = UDR ;
		}
	}
	else {
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState ;
}


uint8 USART_u8SendBufferSynch(uint8 * Copy_u8Data , uint8 Copy_u8Size){
	uint8 Local_u8ErrorState = OK , Local_u8Counter;
	if(Copy_u8Data != NULL){
		for(Local_u8Counter = 0 ; Local_u8Counter < Copy_u8Size ; Local_u8Counter++){
			USART_u8SendByte(Copy_u8Data[Local_u8Counter]);
		}
	}
	else {
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8 USART_u8RecieveBufferSynch(uint8 * Copy_u8Data , uint8 Copy_u8Size){
	uint8 Local_u8ErrorState = OK , Local_u8Counter;
	if(Copy_u8Data != NULL){
		for(Local_u8Counter = 0 ; Local_u8Counter < Copy_u8Size ; Local_u8Counter++){
			USART_u8RecieveByte(&Copy_u8Data[Local_u8Counter]);
		}
	}
	else {
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}


uint8 USART_u8RecieveBufferASynch(uint8 * Copy_pu8Data ,uint8 Copy_u8Size, void (*Copy_voidFunc)(void)){
	uint8 Local_u8ErrorState = OK ;
	if(Copy_pu8Data != NULL && Copy_voidFunc != NULL){
		if(u8Flag == IDEL){
			u8Flag = BUSY ;
/*Putting The value variable & notification function as global for ISR*/
		UARTpu8Result = Copy_pu8Data ;
		UART_pvNotificationFunc = Copy_voidFunc ;
		UART_Recieve_BufferSize = Copy_u8Size ;
/*Enable UART Receiving Interrupt*/
	SET_BIT(UCSRB , UCSRB_RXCIE);
		}
		else {
			Local_u8ErrorState = UART_BUSY_ERR ;
		}

	}
	else {
		Local_u8ErrorState = NULL_PTR_ERR ;
	}

	return Local_u8ErrorState ;
}


uint8 USART_u8SendBufferASynch(uint8 * Copy_pu8Data , uint8 Copy_u8Size ,void (*Copy_voidFunc)(void)){
	uint8 Local_u8ErrorState = OK ;
	if(Copy_pu8Data != NULL && Copy_voidFunc != NULL){
		if(u8Flag == IDEL){
			u8Flag = BUSY ;
/*Putting The value variable & notification function as global for ISR*/
		UART_pu8ValueSend = Copy_pu8Data ;
		UART_Transmit_BufferSize = Copy_u8Size ;
		UART_pvNotificationFunc_Transmit = Copy_voidFunc ;


/*Enable UART Transmitting Interrupt*/
		SET_BIT(UCSRB , UCSRB_UDRIE);
		}
		else {
			Local_u8ErrorState = UART_BUSY_ERR ;
		}

	}
	else {
		Local_u8ErrorState = NULL_PTR_ERR ;
	}

	return Local_u8ErrorState ;
}



__attribute__((signal)) void __vector_13(void);

void __vector_13(void){
	if(UART_pvNotificationFunc != NULL && UARTpu8Result != NULL)
	{

		if(UART_u8Counter < UART_Recieve_BufferSize){
			UARTpu8Result[UART_u8Counter++] = UDR ;
			if(UART_u8Counter == UART_Recieve_BufferSize){
				/*Disable Receiving Complete Interrupt*/
				 CLR_BIT(UCSRB , UCSRB_RXCIE);
				/*Call the notification function*/
					UART_pvNotificationFunc();
					UART_u8Counter = 0;
			}
		}


	else{
/*Disable Receiving Complete Interrupt*/
 CLR_BIT(UCSRB , UCSRB_RXCIE);
/*Call the notification function*/
	UART_pvNotificationFunc();
	UART_u8Counter = 0;
		}
/*Enabling UART Again*/
	u8Flag = IDEL;
	}
	else
	{
		/*Do Nothing */
	}
}



__attribute__((signal)) void __vector_14(void);

void __vector_14(void){
	if(UART_pvNotificationFunc_Transmit != NULL && UART_pu8ValueSend != NULL)
	{

		if(UART_u8_TransmitCounter < UART_Transmit_BufferSize){
			UDR = UART_pu8ValueSend[UART_u8_TransmitCounter++] ;
			if(UART_u8_TransmitCounter == UART_Transmit_BufferSize){
				/*Disable Receiving Complete Interrupt*/
				 CLR_BIT(UCSRB , UCSRB_UDRIE);
				/*Call the notification function*/
				 UART_pvNotificationFunc_Transmit();
					UART_u8_TransmitCounter = 0;
			}
		}


	else{
		/*Disable Receiving Complete Interrupt*/
						 CLR_BIT(UCSRB , UCSRB_UDRIE);
						/*Call the notification function*/
						 UART_pvNotificationFunc_Transmit();
							UART_u8_TransmitCounter = 0;
		}
/*Enabling UART Again*/
	u8Flag = IDEL;
	}
	else
	{
		/*Do Nothing */
	}
}
