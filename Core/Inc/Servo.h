/*
 * Servo.h
 *
 *  Created on: Jan 11, 2024
 *      Author: Ahmed
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

/**********Includes***********************/
#include "gpio.h"
#include "stm32f4xx_it.h"
#include "tim.h"
#include "stm32f4xx_hal_tim.h"
/***********Macro*************************/
#define SERVO_TURN_RIGHT 			0
#define SERVO_TURN_LEFT 			1

#define SERVO_FULL_ANGLE			15
#define SERVO_CENTER				63
/**********Macro Functions****************/

/**********Data Type Declaration**************/

/*********APIS************************/
void Servo_Rotate_Angle(uint8_t Angle, uint8_t direction);


#endif /* INC_SERVO_H_ */
