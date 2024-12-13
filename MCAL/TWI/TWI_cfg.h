/*
 * TWI_cfg.h
 *
 *  Created on: Dec 13, 2024
 *      Author: Computec
 */
#ifndef TWI_CFG_H
#define TWI_CFG_H

/*Configure MCU Clock Frequency*/
#define MCU_CLK_FREQUENCY   16000000u

/*Configure Desired Clock*/
#define  SCL_CLK  400000u

/*Configure prescalar Bits  1)DIVISION_BY_ONE
 * 							2)DIVISION_BY_FOUR
 * 							3)DIVISION_BY_16
 * 							4)DIVISION_BY_64
 * 								*/

#define TWI_PRESCALAR   DIVISION_BY_ONE
#endif
