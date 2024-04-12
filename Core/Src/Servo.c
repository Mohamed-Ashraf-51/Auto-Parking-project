/*
 * Servo.c
 *
 *  Created on: Jan 11, 2024
 *      Author: Ahmed
 */
#include "Servo.h"


void Servo_Rotate_Angle(uint8_t Angle , uint8_t direction)
{

	uint8_t Calibration = Angle ;
	if(SERVO_TURN_RIGHT == direction){
		Calibration = SERVO_CENTER - Calibration;
	}
	else if(SERVO_TURN_LEFT == direction){
		Calibration = SERVO_CENTER + Calibration;

	}
	else{}

	htim3.Instance->CCR3 = Calibration;
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}
