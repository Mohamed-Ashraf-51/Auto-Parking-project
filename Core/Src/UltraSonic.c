/*
 * UltraSonic.c
 *
 *  Created on: Jan 11, 2024
 *      Author: Ahmed
 */

#include "UltraSonic.h"

/* USER CODE BEGIN PV */
volatile uint8_t CH_Var[4] = {0};
volatile uint32_t time[4] = {0};
volatile double distance[4] = {0};
volatile double current_distance[4] = {0};
volatile uint32_t ticks = 0;
volatile uint32_t ic_val_1[4] = {0};
volatile uint32_t ic_val_2[4] = {0};
volatile uint32_t differ[4] = {0};

/* USER CODE END PV */

/* USER CODE BEGIN PFP */

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // if the interrupt source is channel1
	{
		if(CH_Var[US_ECHO_CH1]==0)
		{
			//Read the first IC_value (counter) value in this moment
			ic_val_1[US_ECHO_CH1] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			CH_Var[US_ECHO_CH1] = 1;
			//Modify the polarity to capture the falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if(CH_Var[US_ECHO_CH1]==1){
			//Read the first IC_value (counter) value in this moment
			ic_val_2[US_ECHO_CH1] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			__HAL_TIM_SET_COUNTER(htim,0);
			if(ic_val_2[US_ECHO_CH1] > ic_val_1[US_ECHO_CH1]){
				differ[US_ECHO_CH1] = ic_val_2[US_ECHO_CH1] - ic_val_1[US_ECHO_CH1];

			}
			else{
				differ[US_ECHO_CH1] = (65535 - ic_val_1[US_ECHO_CH1]) + ic_val_2[US_ECHO_CH1];
			}
			current_distance[US_ECHO_CH1] = differ[US_ECHO_CH1] * 0.034/2;
			if(current_distance[US_ECHO_CH1]<50){
				distance[US_ECHO_CH1] = current_distance[US_ECHO_CH1];
			}
			else{}
			CH_Var[US_ECHO_CH1] = 0;
			//Modify the polarity to capture the Rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			//__HAL_TIM_DISABLE_IT(&htim1,TIM_IT_CC1);
			osSemaphoreRelease(Sensor_Sem1Handle);
		}
		else{}
	}
	else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)  // if the interrupt source is channel2
	{
		if(CH_Var[US_ECHO_CH2]==0)
		{
			//Read the first IC_value (counter) value in this moment
			ic_val_1[US_ECHO_CH2] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			CH_Var[US_ECHO_CH2] = 1;
			//Modify the polarity to capture the falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if(CH_Var[US_ECHO_CH2]==1){
			//Read the first IC_value (counter) value in this moment
			ic_val_2[US_ECHO_CH2] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			__HAL_TIM_SET_COUNTER(htim,0);
			if(ic_val_2[US_ECHO_CH2] > ic_val_1[US_ECHO_CH2]){
				differ[US_ECHO_CH2] = ic_val_2[US_ECHO_CH2] - ic_val_1[US_ECHO_CH2];

			}
			else{
				differ[US_ECHO_CH2] = (65535 - ic_val_1[US_ECHO_CH2]) + ic_val_2[US_ECHO_CH2];
			}
			current_distance[US_ECHO_CH2] = differ[US_ECHO_CH2] * 0.0323/2;
			if(current_distance[US_ECHO_CH2]<50){
			distance[US_ECHO_CH2] = current_distance[US_ECHO_CH2];
			}
			else{}
			CH_Var[US_ECHO_CH2] = 0;
			//Modify the polarity to capture the Rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
			//__HAL_TIM_DISABLE_IT(&htim1,TIM_IT_CC1);
			osSemaphoreRelease(Sensor_Sem1Handle);
		}
		else{}
	}
	else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)  // if the interrupt source is channel3
	{
		if(CH_Var[US_ECHO_CH3]==0)
		{
			//Read the first IC_value (counter) value in this moment
			ic_val_1[US_ECHO_CH3] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
			CH_Var[US_ECHO_CH3] = 1;
			//Modify the polarity to capture the falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if(CH_Var[US_ECHO_CH3]==1){
			//Read the first IC_value (counter) value in this moment
			ic_val_2[US_ECHO_CH3] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
			__HAL_TIM_SET_COUNTER(htim,0);
			if(ic_val_2[US_ECHO_CH3] > ic_val_1[US_ECHO_CH3]){
				differ[US_ECHO_CH3] = ic_val_2[US_ECHO_CH3] - ic_val_1[US_ECHO_CH3];

			}
			else{
				differ[US_ECHO_CH3] = (65535 - ic_val_1[US_ECHO_CH3]) + ic_val_2[US_ECHO_CH3];
			}
			current_distance[US_ECHO_CH3] = differ[US_ECHO_CH3] * 0.033067/2;
			if(current_distance[US_ECHO_CH3]<50){
			distance[US_ECHO_CH3] = current_distance[US_ECHO_CH3];
			}
			else{}
			CH_Var[US_ECHO_CH3] = 0;
			//Modify the polarity to capture the Rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_RISING);
			//__HAL_TIM_DISABLE_IT(&htim1,TIM_IT_CC1);
			osSemaphoreRelease(Sensor_Sem1Handle);
		}
		else{}
	}
	else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)  // if the interrupt source is channel4
	{
		if(CH_Var[US_ECHO_CH4]==0)
		{
			//Read the first IC_value (counter) value in this moment
			ic_val_1[US_ECHO_CH4] = HAL_TIM_ReadCapturedValue(htim, US_ECHO_CH4);
			CH_Var[US_ECHO_CH4] = 1;
			//Modify the polarity to capture the falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_4, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if(CH_Var[US_ECHO_CH4]==1){
			//Read the first IC_value (counter) value in this moment
			ic_val_2[US_ECHO_CH4] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
			__HAL_TIM_SET_COUNTER(htim,0);
			if(ic_val_2[US_ECHO_CH4] > ic_val_1[US_ECHO_CH4]){
				differ[US_ECHO_CH4] = ic_val_2[US_ECHO_CH4] - ic_val_1[US_ECHO_CH4];

			}
			else{
				differ[US_ECHO_CH4] = (65535 - ic_val_1[US_ECHO_CH4]) + ic_val_2[US_ECHO_CH4];
			}
			current_distance[US_ECHO_CH4] = differ[US_ECHO_CH4] * 0.017357/2;
			if(current_distance[US_ECHO_CH4]<120){
			distance[US_ECHO_CH4] = current_distance[US_ECHO_CH4];
			}
			else{}
			CH_Var[US_ECHO_CH4] = 0;
			//Modify the polarity to capture the Rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_4, TIM_INPUTCHANNELPOLARITY_RISING);
			//__HAL_TIM_DISABLE_IT(&htim1,TIM_IT_CC1);
			osSemaphoreRelease(Sensor_Sem1Handle);
		}
		else{}
	}
	else{}

}

void delay_us(uint16_t time)
{
	__HAL_TIM_SET_COUNTER(&htim1,0);
	while(__HAL_TIM_GET_COUNTER(&htim1)< time);
}

void UltraSonic_Read(uint8_t US_Trigger_Pin)
{

	  HAL_GPIO_WritePin(GPIOB, US_Trigger_Pin, GPIO_PIN_SET);
	  delay_us(10);
	  HAL_GPIO_WritePin(GPIOB, US_Trigger_Pin, GPIO_PIN_RESET);
	  __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4);
//	 HAL_Delay(10);
}
