#ifndef EXTI_CFG_H
#define EXTI_CFG_H

/*Configure The sense control option for INT0 1)EXTI_LOW_LEVEL ,
         									  2)EXTI_ON_CHANGE ,
 											  3)EXTI_FALLING_EDGE
 											  4)EXTI_RISING_EGDE */
#define INT0_SENSE_CTRL EXTI_FALLING_EDGE
/*Configure The sense control option for INT0 1)EXTI_LOW_LEVEL ,
         									  2)EXTI_ON_CHANGE ,
 											  3)EXTI_FALLING_EDGE
 											  4)EXTI_RISING_EGDE */
#define INT1_SENSE_CTRL EXTI_FALLING_EDGE
/*Configure The sense control option for INT2
 											  1)EXTI_FALLING_EDGE
 											  2)EXTI_RISING_EGDE */
#define INT2_SENSE_CTRL EXTI_FALLING_EDGE

/*Configure the intial state of INT0 1)ENABLED
 * 									 2)DISABLED*/
#define INT0_INIT_STATE ENABLED
/*Configure the intial state of INT1 1)ENABLED
 * 									 2)DISABLED*/
#define INT1_INIT_STATE ENABLED
/*Configure the intial state of INT2 1)ENABLED
 * 									 2)DISABLED*/
#define INT2_INIT_STATE DISABLED

#endif
