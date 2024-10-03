#ifndef ADC_CFG_H
#define ADC_CFG_H
/*Configure ADC prescalar division factor    1-DIVISION_BY_2
 	 	 	 	 	 	 	 	 	 	 	 2-DIVISION_BY_4
 	 	 	 	 	 	 	 	 	   	   	 3-DIVISION_BY_8
       	   	   	   	   	   	   	   	   	   	 4-DIVISION_BY_16
                                             5-DIVISION_BY_32
                                             6-DIVISION_BY_64
                                      	  	 7-DIVISION_BY_128
*/
#define ADC_u8PRESCALAR_DIVISIONFACTOR     DIVISION_BY_128
/*Configue Where does prescalar bits begins & channels*/
#define PRESCALAR_BITS_POS 0u
#define CHANNELS_BITS_POS 0u
/*Pick Which Mode You're using the ADC 1)BIT_8MODE
									   2)BIT_10MODE*/
#define ADC_u8MODE BITMODE_EIGHT

/*Configure The Reference Voltage from 1) ADC_AREF
 * 									   2) ADC_AVCC
 * 									   3) ADC_INTERNAL_VOLT*/
#define ADC_u8REF_VOLT  ADC_AVCC
#endif
