#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrorState.h"

#include "SPI_prv.h"
#include "SPI_interface.h"
#include "SPI_cfg.h"
#include "SPI_reg.h"

static uint8 u8Flag = IDEL ;
static void (*SPI_pvNotificationFunc)(void) = NULL;
static uint8* SPIpu8Result = NULL;
void SPI_voidInit(void){
	/*Set the order in which data is transferred*/
#if SPI_DATA_ORDER == SPI_MSB_FIRST
	CLR_BIT(SPCR,SPCR_DORD);
#elif SPI_DATA_ORDER == SPI_LSB_FIRST
	SET_BIT(SPCR,SPCR_DORD);
#else
#error Wrong Configuration
#endif
	/*Set the peripheral as master or slave*/
#if SPI_MODE == SPI_SLAVE
	CLR_BIT(SPCR,SPCR_MSTR);
#elif SPI_MODE == SPI_MASTER
	SET_BIT(SPCR,SPCR_MSTR);
#else
#error Wrong Configuration
#endif

/*Leave Clock Polarity & Phase on Initial Value*/
	/*Configure SPI clock rate*/
#if SPI_CLOCK_RATE == MC_RATE_DIVIDED_BY_128
	SET_BIT(SPCR,SPCR_SPR1);
	SET_BIT(SPCR,SPCR_SPR0);
#elif SPI_CLOCK_RATE == MC_RATE_DIVIDED_BY_16
	CLR_BIT(SPCR,SPCR_SPR1);
	SET_BIT(SPCR,SPCR_SPR0);
#elif SPI_CLOCK_RATE == MC_RATE_DIVIDED_BY_4
	CLR_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPCR,SPCR_SPR0);
#elif SPI_CLOCK_RATE == MC_RATE_DIVIDED_BY_64
	SET_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPCR,SPCR_SPR0);
#else
#error Wrong Configuration
#endif

/*In Case of doubling required*/
#if SPI_RATE_DOUBLING == 0u
	CLR_BIT(SPSR , SPSR_SPI2X);
#elif SPI_RATE_DOUBLING == 1u
	SET_BIT(SPSR , SPSR_SPI2X);
#else
#error Wrong Configuration
#endif

	/*Enable SPI Peripheral*/
	SET_BIT(SPCR , SPCR_SPE);
}


uint8 SPI_u8TransceiveSynch(uint8 Copu_u8Data){
	/*Send Data*/
	SPDR = Copu_u8Data ;
	/*Polling Until The process is completed*/
	while(GET_BIT(SPSR,SPSR_SPIF)==0);

	/*Return Received Value*/

	return SPDR ;
}

uint8 SPI_u8TransceiveAsynch(uint8 * Copu_u8Data , void (*Copy_voidFunc)(void)){
	uint8 Local_u8ErrorState = OK ;
	/*Enable Interrupt*/
	SET_BIT(SPCR , SPCR_SPIE);
		if(Copy_voidFunc != NULL){
			if(u8Flag == IDEL){
				u8Flag = BUSY ;
				SPI_pvNotificationFunc = Copy_voidFunc ;
				SPIpu8Result = Copu_u8Data ;
		/*Send Data*/
		SPDR = *Copu_u8Data ;
			}
			else {
				Local_u8ErrorState = SPI_BUSY_ERR ;
			}
		}
		else {
			Local_u8ErrorState = NULL_PTR_ERR;
		}


	return Local_u8ErrorState;
}

__attribute__((signal)) void __vector_12(void);

void __vector_12(void){
	if(SPI_pvNotificationFunc != NULL)
	{
		*SPIpu8Result = SPDR ;
		/*Disable  Interrupt*/
			 CLR_BIT(SPCR , SPCR_SPIE);
		/*Call the notification function*/
			SPI_pvNotificationFunc();

/*Enabling SPI Again*/
	u8Flag = IDEL;
	}
	else
	{
		/*Do Nothing */
	}
}

