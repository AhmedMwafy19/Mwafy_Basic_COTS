#include "STD_TYPES.h"
#include "MAP.h"

sint32 STD_MAP(sint32 Copy_s32MinInput ,sint32 Copy_s32MaxInput ,sint32 Copy_s32MinOutput ,sint32 Copy_s32MaxOutput , sint32 Copy_s32Input_Val ){
	
	sint32 Local_s32NewVal = 0 ;
	Local_s32NewVal = Copy_s32MinOutput + ( ( (Copy_s32Input_Val - Copy_s32MinInput) * (Copy_s32MaxOutput - Copy_s32MinOutput) ) / (Copy_s32MaxInput-Copy_s32MinInput) ) ;
	
	return Local_s32NewVal ;
	
}