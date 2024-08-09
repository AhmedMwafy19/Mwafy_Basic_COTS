#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H

/*Using post built configuration ,Because Multiple SSD could be used*/
typedef struct{
	uint8 SSD_TYPE; //COMMON_ANODE OR COMMON_CATHODE , ETA KIT
	uint8 SSD_LEDPORT; //which port is connected to the 7 or 8 pins of (a,b,c,d,e,f,g)
	uint8 SSD_LEDAPIN; //Led a starts in pin0 or pin1 in port
	uint8 SSD_ENABLE_PORT; //the common (A/C) pin is connected to which port
	uint8 SSD_ENABLE_PIN; //the common (A/C) pin is connected to which pin in port
}SSD_CONFIGURATION;


/*Example of how to configure the SSD In the application file (main.c)
SSD_CONFIGURATION SSD_ONE = {
	.SSD_TYPE=COMMON_CATHODE,
	.SSD_LEDPORT=DIO_u8PORTC,
	.SSD_LEDAPIN = DIO_u8PIN0,
	.SSD_ENABLE_PORT= DIO_u8PORTD,
	.SSD_ENABLE_PIN = DIO_u8PIN0
};
*/

uint8 SSDLED_u8ON(const SSD_CONFIGURATION * Copy_pstructSSD); //function to activate the 7-segment

uint8 SSDLED_u8OFF(const SSD_CONFIGURATION * Copy_pstructSSD);//function to deactivate the 7-segment

uint8 SSDLED_u8DisplayNumber(const SSD_CONFIGURATION * Copy_pstructSSD,uint8 Copy_u8Number); //function to display a number on the 7-segment


#endif
