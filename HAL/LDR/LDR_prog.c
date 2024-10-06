#include "STD_TYPES.h"
#include "ADC_interface.h"
#include "LDR_cfg.h"
#include "LDR_interface.h"
#include "LDR_prv.h"

LDR_EN LDR_EnGetLightIntensity(void){
	uint16 Local_u16AnalogVal;
	uint16 Local_u16LightIntensity ;
	ADC_u8StartConvertionSynch(LDR_u8ADCChannel , &Local_u16AnalogVal);
	Local_u16LightIntensity =  (uint16)((uint32)Local_u16AnalogVal * LDR_u16RefVal) / (LDR_u16Resolution );

	if(Local_u16LightIntensity <= LDR_MIN){
			return Total_Darkness;
		}
	else if(Local_u16LightIntensity < LDR_SEC_MIN){
			return Weak_Light_intensity;
		}
	else if(Local_u16LightIntensity < LDR_SEC_MAX){
					return Medium_Light_intensity;
				}
	else if(Local_u16LightIntensity < LDR_MAX){
					return Strong_Light_intensity;
				}
	else {
		return Maximum_Light_intensity;
			}


}
