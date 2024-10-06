#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrorState.h"
#include "ADC_interface.h"
#include "ADC_reg.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"

static uint16* ADC_pu16Result = NULL;
static void (*ADC_pvNotificationFunc)(void) = NULL;

static uint8 u8Flag = IDEL ;

void ADC_voidInit(void){
/*Initialization Reference Voltage*/
#if ADC_u8REF_VOLT == ADC_AVCC
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);
#elif ADC_u8REF_VOLT == ADC_AREF
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);
#elif ADC_u8REF_VOLT == ADC_INTERNAL_VOLT
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);
#else
#error Wrong ADC REF Choice
#endif


/*Initializing Left Or Right Adjust Mode*/
#if ADC_u8MODE == BITMODE_EIGHT
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_u8MODE == BITMODE_TEN
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error Wrong ACD CONFIGURATION OPTION

#endif


/*Initializing Trigger Mode*/
#if ADC_u8TRIGGER_MODE == ADC_SINGLE_CONV
	CLR_BIT(ADCSRA,ADCSRA_ADATE);
#elif ADC_u8TRIGGER_MODE == ADC_AUTOTRIGGER
	SET_BIT(ADCSRA,ADCSRA_ADATE);
#else
#error Wrong trigger mode
#endif

/*Disabling interrupts */
	CLR_BIT(ADCSRA,ADCSRA_ADIE);


/*Initializing Prescaler Circuit */
	ADCSRA &= PRESCALAR_BITCLR ;
	ADCSRA |= (ADC_u8PRESCALAR_DIVISIONFACTOR << PRESCALAR_BITS_POS) ;



/*Enable The ADC (last thing after all settings is organized correctly)*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);

}

uint16 ADC_u16GetChannelReading(uint8 Copy_u8Channel){
/*Initializing the ADC channel to be read*/
	ADMUX &= CHANNELS_BITCLR;
	ADMUX |= (Copy_u8Channel << CHANNELS_BITS_POS);
	
/*To start conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);

/*Handling the flag with polling*/
	while(GET_BIT(ADCSRA,ADCSRA_ADIF)==0);
	SET_BIT(ADCSRA,ADCSRA_ADIF);

#if ADC_u8MODE == BITMODE_EIGHT
	return (ADCH);
#elif ADC_u8MODE == BITMODE_TEN
	return (ADC);
#else
#error Wrong ACD CONFIGURATION OPTION

#endif

}
uint8 ADC_u8StartConvertionSynch(uint8 Copy_u8Channel , uint16 * Copy_pu16ADCval){
	uint8 Local_u8ErrorState = OK ;
	uint32 Local_u32TimeOut = 0 ;
	if(Copy_pu16ADCval != NULL){
		if(u8Flag == IDEL){

		u8Flag = BUSY ;
/*Initializing the ADC channel to be read*/
	ADMUX &= CHANNELS_BITCLR;
	ADMUX |= (Copy_u8Channel << CHANNELS_BITS_POS);

/*To start conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);

/*Handling the flag with polling*/
	while((GET_BIT(ADCSRA,ADCSRA_ADIF)==0) && Local_u32TimeOut++ < TIMEOUT_VAL);
	SET_BIT(ADCSRA,ADCSRA_ADIF);

	if(Local_u32TimeOut < TIMEOUT_VAL){
#if ADC_u8MODE == BITMODE_EIGHT
	*Copy_pu16ADCval = (ADCH);
#elif ADC_u8MODE == BITMODE_TEN
	*Copy_pu16ADCval = (ADC);
#else
#error Wrong ACD CONFIGURATION OPTION

#endif
	}
	else {
		Local_u8ErrorState = TIME_OUT_ERR ;
	}

	}
		else {
			Local_u8ErrorState = ADC_BUSY_ERR;
			}
	}
	else {
		Local_u8ErrorState = NULL_PTR_ERR ;
	}

	return Local_u8ErrorState ;
}


uint8 ADC_u8StartConvertionAsynch(uint8 Copy_u8Channel , uint16 * Copy_pu16ADCval , void (*Copy_voidFunc)(void)){
	uint8 Local_u8ErrorState = OK ;
	if(Copy_pu16ADCval != NULL && Copy_voidFunc != NULL){
		if(u8Flag == IDEL){
			u8Flag = BUSY ;
/*Putting The value variable & notification function as global for ISR*/
		ADC_pu16Result = Copy_pu16ADCval ;
		ADC_pvNotificationFunc = Copy_voidFunc ;

/*Initializing the ADC channel to be read*/
	ADMUX &= CHANNELS_BITCLR;
	ADMUX |= (Copy_u8Channel << CHANNELS_BITS_POS);

/*To start conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);

/*Enable ADC Interrupt*/
	SET_BIT(ADCSRA , ADCSRA_ADIE);
		}
		else {
			Local_u8ErrorState = ADC_BUSY_ERR ;
		}

	}
	else {
		Local_u8ErrorState = NULL_PTR_ERR ;
	}

	return Local_u8ErrorState ;
}


__attribute__((signal)) void __vector_16(void);

void __vector_16(void){
	if(ADC_pvNotificationFunc != NULL && ADC_pu16Result != NULL)
	{

#if ADC_u8MODE == BITMODE_EIGHT
	*ADC_pu16Result = (ADCH);
#elif ADC_u8MODE == BITMODE_TEN
	*ADC_pu16Result = (ADC);
#else
#error Wrong ACD CONFIGURATION OPTION
#endif

/*Disable Conversion Complete Interrupt*/
CLR_BIT(ADCSRA , ADCSRA_ADIE);

/*Call the notification function*/
	ADC_pvNotificationFunc();

/*Enabling ADC Again*/
	u8Flag = IDEL;
	}
	else
	{
		/*Do Nothing */
	}
}
