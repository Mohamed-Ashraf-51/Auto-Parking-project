/*
 * UltraSonic.h
 *
 *  Created on: Jan 11, 2024
 *      Author: Ahmed
 */

#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_

/**********Includes***********************/
#include "gpio.h"
#include "stm32f4xx_it.h"
#include "tim.h"
#include "stm32f4xx_hal_tim.h"
#include "cmsis_os.h"

/***********Macro*************************/
#define US_ECHO_CH1		0
#define US_ECHO_CH2		1
#define US_ECHO_CH3		2
#define US_ECHO_CH4		3


/**********Macro Functions****************/


/**********Data Type Declaration**************/
extern volatile uint32_t differ[];
extern volatile double distance[];
extern osSemaphoreId_t Sensor_Sem1Handle;

/*********APIS************************/
void UltraSonic_Read(uint8_t US_Trigger_Pin);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void delay_us(uint16_t time);


#endif /* INC_ULTRASONIC_H_ */
