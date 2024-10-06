#include "STD_TYPES.h"

#include "ADC_interface.h"
#include "LM35_cfg.h"
#include "LM35_interface.h"
#include "LM35_prv.h"

uint16 LM35_u16GetTemp(void){
	uint16 Local_u16AnalogVal = 0;
	uint16 Local_u16Temperature = 0 ;
	ADC_u8StartConvertionSynch(LM35_u8Channel , &Local_u16AnalogVal);

	Local_u16Temperature = (uint16)((uint32)Local_u16AnalogVal * LM35_u16RefVol) / (LM35_u16Resolution * 10ul );

	return Local_u16Temperature ;
}
