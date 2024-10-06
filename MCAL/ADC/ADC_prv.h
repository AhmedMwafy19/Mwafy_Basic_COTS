#ifndef ADC_PRV_H
#define ADC_PRV_H

#define DIVISION_BY_2       0u
#define DIVISION_BY_4  		2u
#define DIVISION_BY_8  		3u
#define DIVISION_BY_16 		4u
#define DIVISION_BY_32 		5u
#define DIVISION_BY_64 		6u
#define DIVISION_BY_128		7u


#define ADC_AVCC   1u
#define ADC_AREF   2u
#define ADC_INTERNAL_VOLT   3u


#define PRESCALAR_BITCLR 0b11111000
#define CHANNELS_BITCLR  0b11100000
#define BITMODE_EIGHT 1u
#define BITMODE_TEN 2u

#define TIMEOUT_VAL 500000u

#define ADC_SINGLE_CONV 1u
#define ADC_AUTOTRIGGER 2u

#define IDEL 0U
#define BUSY 1U

#endif
