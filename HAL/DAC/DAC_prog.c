#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "DAC_cfg.h"
#include "DAC_interface.h"
#include "DAC_prv.h"
void DAC_voidSetAnalogSignal(uint16 Copy_u16Voltage){
	uint16 Local_u16DigitalVal ;
	Local_u16DigitalVal = Copy_u16Voltage / (DAC_u8REF_VOLTAGE / DAC_u8RESOLUTION);

	DIO_u8SetPortValue(DAC_u8PORT , Local_u16DigitalVal);

}
