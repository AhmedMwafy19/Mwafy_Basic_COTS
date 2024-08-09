#include "STD_TYPES.h"
#include "ErrorState.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "SWITCH_prv.h"
#include "SWITCH_interface.h"
#include "SWITCH_cfg.h"


uint8 SWITCH_u8ReadSwitchState(const SWITCH_CONFIGURATION * Copy_pstructSwitch , uint8 * Copy_pu8SwitchState){
	uint8 Local_u8ErrorState = OK,Local_u8SwitchState;
	if(Copy_pstructSwitch != NULL && Copy_pu8SwitchState != NULL){ /*Check the validity of the pointers*/
		DIO_u8ReadPinValue(Copy_pstructSwitch -> SWITCH_u8SwitchPort,Copy_pstructSwitch -> SWITCH_u8SwitchPin, &Local_u8SwitchState);//reading pin value
		
		if(Copy_pstructSwitch -> SWITCH_u8SwitchPullType == PULL_UP){/*check pull type of the switch*/
			if(Local_u8SwitchState == DIO_u8PINVALUE_LOW){
				*Copy_pu8SwitchState = SWITCH_PRESSED;
			}
			else *Copy_pu8SwitchState = SWITCH_RELEASED;
		}
		else if(Copy_pstructSwitch -> SWITCH_u8SwitchPullType == PULL_DOWN){

			if(Local_u8SwitchState == DIO_u8PINVALUE_HIGH){
							*Copy_pu8SwitchState = SWITCH_PRESSED;
						}
						else *Copy_pu8SwitchState = SWITCH_RELEASED;
		}
		else Local_u8ErrorState = NOK; //invalid pull type
}
else {
	Local_u8ErrorState = NULL_PTR_ERR ; /*Pointers are invalid */
}
return Local_u8ErrorState;
}
