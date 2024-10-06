#ifndef LDR_INTERFACE_H
#define LDR_INTERFACE_H

typedef enum{
	Total_Darkness ,
	Weak_Light_intensity ,
	Medium_Light_intensity ,
	Strong_Light_intensity ,
	Maximum_Light_intensity
}LDR_EN;

LDR_EN LDR_EnGetLightIntensity(void);

#endif
