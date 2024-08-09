#ifndef SWITCH_INTERFACE_H
#define SWITCH_INTERFACE_H
#define SWITCH_PRESSED 3  //use it as an indication that sitch is pressed
#define SWITCH_RELEASED 4 // //use it as an indication that sitch isn't pressed
typedef struct{
	uint8 SWITCH_u8SwitchPort;
	uint8 SWITCH_u8SwitchPin;
	uint8 SWITCH_u8SwitchPullType; /*Pick one 1)PULL_UP 2)PULL_DOWN*/
}SWITCH_CONFIGURATION;

/*Example of how to configure the Switch in the application (main file)
SWITCH_CONFIGURATION Switch1 = {
		.SWITCH_u8SwitchPort = DIO_u8PORTC,
		.SWITCH_u8SwitchPin = DIO_u8PIN0,
		.SWITCH_u8SwitchPullType = PULL_UP
};
*/
uint8 SWITCH_u8ReadSwitchState(const SWITCH_CONFIGURATION * Copy_pstructSwitch , uint8 * Copy_pu8SwitchState);
																				/*Recieves the address of the variable*
																				Storing the state of the switch*/
#endif
