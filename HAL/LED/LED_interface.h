#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H
typedef struct{
	uint8 LED_u8PORT;  //Which port led is connected to
	uint8 LED_u8PIN;   //which pin in that port the led is connected to
	uint8 LED_u8ACTIVETYPE; //Led is 1)ACTIVE_LOW , 2)ACTIVE_HIGH
}LED_CONFIGURATION;
/* Example of how to configure the LED In the application file (main)
LED_CONFIGURATION LED1 ={
		.LED_u8PORT = DIO_u8PORTA,
		.LED_u8PIN =  DIO_u8PIN0,
		.LED_u8ACTIVETYPE = ACTIVE_HIGH
}; */
uint8 LED_u8TurnOn(const LED_CONFIGURATION * Copy_pstructLed);
uint8 LED_u8TurnOff(const LED_CONFIGURATION * Copy_pstructLed);
uint8 LED_u8ToggleLed(const LED_CONFIGURATION * Copy_pstructLed);

#endif
