#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include "ADC_reg.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"


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
	/*Disable Auto Trigger mode*/
	CLR_BIT(ADCSRA,ADCSRA_ADATE);
	/*No interrupt for now*/
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

