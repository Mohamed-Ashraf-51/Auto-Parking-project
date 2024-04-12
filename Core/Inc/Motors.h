/*
 * Motors.h
 *
 *  Created on: Jan 11, 2024
 *      Author: Ahmed
 */

#ifndef INC_MOTORS_H_
#define INC_MOTORS_H_

/**********Includes***********************/
#include "gpio.h"
#include "stm32f4xx_it.h"
#include "tim.h"
#include "stm32f4xx_hal_tim.h"
/***********Macro*************************/

/**********Macro Functions****************/

/**********Data Type Declaration**************/

/*********APIS************************/
void Motor_ForWard(uint16_t Motor_Speed);
void Motor_BackWard(uint16_t Motor_Speed);
void Motor_Stop(void);



#endif /* INC_MOTORS_H_ */
