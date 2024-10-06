#ifndef ADC_REG_H
#define ADC_REG_H

#define ADMUX   *((volatile uint8*) 0x27) /*Register For multiplexing & Reference voltage method*/
#define ADMUX_REFS1 7u  /* for reference pin1*/
#define ADMUX_REFS0 6u  /*for reference pin0*/
#define ADMUX_ADLAR 5u  /*to pick between left & right adjust*/

#define ADCSRA  *((volatile uint8*) 0x26) /*Register ADC Control & status*/
#define ADCSRA_ADEN 7u  /*Enable*/
#define ADCSRA_ADSC 6u  /*Start conversion*/
#define ADCSRA_ADATE 5u /*To enable automatic trigger mode*/
#define ADCSRA_ADIF 4u  /*flag to be set when conversion is completed*/
#define ADCSRA_ADIE 3u  /*ADC interrupt enable*/


#define ADCL  *((volatile uint8*) 0x24)  /*Least significant bits register (data )*/
#define ADCH  *((volatile uint8*) 0x25) /*Most significant pins register (data )*/
#define ADC   *((volatile uint16*) 0x24)  /*pointer to access both when operating on 10bit adc*/
#endif
