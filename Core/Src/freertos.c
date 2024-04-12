/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Motors.h"
#include "UltraSonic.h"
#include "Servo.h"
#include "math.h"
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PARKING_OK		1
#define PARKING_NOK		0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint32_t Parking_status = PARKING_NOK;
/* USER CODE END Variables */
/* Definitions for Searching_Task */
osThreadId_t Searching_TaskHandle;
const osThreadAttr_t Searching_Task_attributes = {
  .name = "Searching_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Parking_Task */
osThreadId_t Parking_TaskHandle;
const osThreadAttr_t Parking_Task_attributes = {
  .name = "Parking_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for UltraSonic1Task */
osThreadId_t UltraSonic1TaskHandle;
const osThreadAttr_t UltraSonic1Task_attributes = {
  .name = "UltraSonic1Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for UltraSonic2Task */
osThreadId_t UltraSonic2TaskHandle;
const osThreadAttr_t UltraSonic2Task_attributes = {
  .name = "UltraSonic2Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for UltraSonic3Task */
osThreadId_t UltraSonic3TaskHandle;
const osThreadAttr_t UltraSonic3Task_attributes = {
  .name = "UltraSonic3Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for UltraSonic4Task */
osThreadId_t UltraSonic4TaskHandle;
const osThreadAttr_t UltraSonic4Task_attributes = {
  .name = "UltraSonic4Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Parking_Sem1 */
osSemaphoreId_t Parking_Sem1Handle;
const osSemaphoreAttr_t Parking_Sem1_attributes = {
  .name = "Parking_Sem1"
};
/* Definitions for Sensor_Sem1 */
osSemaphoreId_t Sensor_Sem1Handle;
const osSemaphoreAttr_t Sensor_Sem1_attributes = {
  .name = "Sensor_Sem1"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Searching_Mode(void *argument);
void Parking_Mode(void *argument);
void UltraSonic1_Read(void *argument);
void UltraSonic2_Read(void *argument);
void UltraSonic3_Read(void *argument);
void UltraSonic4_Read(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of Parking_Sem1 */
  Parking_Sem1Handle = osSemaphoreNew(1, 0, &Parking_Sem1_attributes);

  /* creation of Sensor_Sem1 */
  Sensor_Sem1Handle = osSemaphoreNew(1,1, &Sensor_Sem1_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Searching_Task */
  Searching_TaskHandle = osThreadNew(Searching_Mode, NULL, &Searching_Task_attributes);

  /* creation of Parking_Task */
  Parking_TaskHandle = osThreadNew(Parking_Mode, NULL, &Parking_Task_attributes);

  /* creation of UltraSonic1Task */
  UltraSonic1TaskHandle = osThreadNew(UltraSonic1_Read, NULL, &UltraSonic1Task_attributes);

  /* creation of UltraSonic2Task */
  UltraSonic2TaskHandle = osThreadNew(UltraSonic2_Read, NULL, &UltraSonic2Task_attributes);

  /* creation of UltraSonic3Task */
  UltraSonic3TaskHandle = osThreadNew(UltraSonic3_Read, NULL, &UltraSonic3Task_attributes);

  /* creation of UltraSonic4Task */
  UltraSonic4TaskHandle = osThreadNew(UltraSonic4_Read, NULL, &UltraSonic4Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Searching_Mode */
/**
  * @brief  Function implementing the Searching_Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Searching_Mode */
void Searching_Mode(void *argument)
{
  /* USER CODE BEGIN Searching_Mode */
  /* Infinite loop */
  for(;;)
  {
	  if(Parking_status == PARKING_NOK){
		  //HAL_Delay(2000);
		  Servo_Rotate_Angle(0, SERVO_TURN_LEFT);
		  //HAL_Delay(10);
		 // Motor_Stop();
		  Motor_ForWard(300);

		  while((distance[US_ECHO_CH3]<15)){
			  	 Motor_ForWard(300);
			  	 //HAL_Delay(30);
			  	 osDelay(30);
			  	 Motor_Stop();
			  	 //HAL_Delay(10);
			  	 osDelay(20);
		  }
		  Motor_Stop();
	      //HAL_Delay(1000);
		 // osDelay(1000);
		  //HAL_Delay(15);
		  while((distance[US_ECHO_CH2]>15)){
		      Motor_Stop();
			  //HAL_Delay(10);
			  osDelay(20);
			  Motor_ForWard(300);
		  //while(distance[US_ECHO_CH2]>=15);
		      //HAL_Delay(30);
			  osDelay(30);
		  }
	      Motor_Stop();
	      //HAL_Delay(1000);
		  osDelay(1000);
		  Parking_status = PARKING_OK;
		  osSemaphoreRelease(Parking_Sem1Handle);

	  }
	  else{/*Nothing*/}

    //osDelay(100);
  }
  /* USER CODE END Searching_Mode */
}

/* USER CODE BEGIN Header_Parking_Mode */
/**
* @brief Function implementing the Parking_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Parking_Mode */
void Parking_Mode(void *argument)
{
  /* USER CODE BEGIN Parking_Mode */
	//int i=0;
  /* Infinite loop */
  for(;;)
  {

		osSemaphoreAcquire(Parking_Sem1Handle,osWaitForever);
		while(Parking_status != PARKING_OK);
		Servo_Rotate_Angle(15, SERVO_TURN_RIGHT);
		while (distance[US_ECHO_CH2]<20){
					 Motor_ForWard(300);
					 //HAL_Delay(20);
					  osDelay(20);
					 Motor_Stop();
					 //HAL_Delay(20);
					  osDelay(20);
					}
		Motor_Stop();
		//HAL_Delay(1000);
		  osDelay(1000);
		Servo_Rotate_Angle(15, SERVO_TURN_LEFT);
		//HAL_Delay(50);

		while (distance[US_ECHO_CH4]>15){
			 Motor_BackWard(300);
			 //HAL_Delay(20);
			  osDelay(20);
			 Motor_Stop();
			 //HAL_Delay(20);
			  osDelay(20);
			}
		Motor_Stop();
		//HAL_Delay(1000);
		  osDelay(1000);
		Servo_Rotate_Angle(15, SERVO_TURN_RIGHT);
		//HAL_Delay(500);
		//HAL_Delay(50);
		while (distance[US_ECHO_CH4]>10){
			Motor_BackWard(300);
			//HAL_Delay(20);
			  osDelay(30);
			Motor_Stop();
			//HAL_Delay(20);
			  osDelay(20);
					}
		Motor_Stop();
		Servo_Rotate_Angle(0, SERVO_TURN_LEFT);
		osDelay(1000);
		while (abs(distance[US_ECHO_CH1]-distance[US_ECHO_CH4])>=3){
				//Motor_Stop();
				//Servo_Rotate_Angle(0, SERVO_TURN_LEFT);
				//Parking_status = PARKING_OK;
				//HAL_Delay(10000);

				if(distance[US_ECHO_CH4]<5){
				Motor_ForWard(300);
				//HAL_Delay(10);
				//Motor_Stop();
				//HAL_Delay(10);
			    }

			    else if(distance[US_ECHO_CH1]<5){
				Motor_BackWard(300);
				//HAL_Delay(20);
				//Motor_Stop();
				//HAL_Delay(20);

				}
				else{}
		}
		Motor_Stop();
		/*HAL_Delay(100);
		Servo_Rotate_Angle(15, SERVO_TURN_RIGHT);
	    HAL_Delay(50);
	    Motor_BackWard(300);
	    HAL_Delay(1000);
		if (abs(distance[US_ECHO_CH1]-distance[US_ECHO_CH4])<=5){
		Motor_Stop();
		Servo_Rotate_Angle(0, SERVO_TURN_LEFT);
		//Parking_status = PARKING_OK;
		HAL_Delay(10000);
		}
		else if(distance[US_ECHO_CH4]<7){
		Motor_ForWard(300);
		HAL_Delay(10);
	    }
	    else if(distance[US_ECHO_CH1]<7){
		Motor_BackWard(300);
		HAL_Delay(10);
		}
		else{}
*/
    //osDelay(100);
  }
  /* USER CODE END Parking_Mode */
}

/* USER CODE BEGIN Header_UltraSonic1_Read */
/**
* @brief Function implementing the UltraSonic1Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_UltraSonic1_Read */
void UltraSonic1_Read(void *argument)
{
  /* USER CODE BEGIN UltraSonic1_Read */
  /* Infinite loop */
  for(;;)
  {
	 osSemaphoreAcquire(Sensor_Sem1Handle,100);
	 UltraSonic_Read(US_Trigger_1_Pin);
     osDelay(10);
  }
  /* USER CODE END UltraSonic1_Read */
}

/* USER CODE BEGIN Header_UltraSonic2_Read */
/**
* @brief Function implementing the UltraSonic2Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_UltraSonic2_Read */
void UltraSonic2_Read(void *argument)
{
  /* USER CODE BEGIN UltraSonic2_Read */
  /* Infinite loop */
  for(;;)
  {
	 osSemaphoreAcquire(Sensor_Sem1Handle,100);
	 UltraSonic_Read(US_Trigger_2_Pin);
     osDelay(10);
  }
  /* USER CODE END UltraSonic2_Read */
}

/* USER CODE BEGIN Header_UltraSonic3_Read */
/**
* @brief Function implementing the UltraSonic3Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_UltraSonic3_Read */
void UltraSonic3_Read(void *argument)
{
  /* USER CODE BEGIN UltraSonic3_Read */
  /* Infinite loop */
  for(;;)
  {
	 osSemaphoreAcquire(Sensor_Sem1Handle,100);
	 UltraSonic_Read(US_Trigger_3_Pin);
	 osDelay(10);
  }
  /* USER CODE END UltraSonic3_Read */
}

/* USER CODE BEGIN Header_UltraSonic4_Read */
/**
* @brief Function implementing the UltraSonic4Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_UltraSonic4_Read */
void UltraSonic4_Read(void *argument)
{
  /* USER CODE BEGIN UltraSonic4_Read */
  /* Infinite loop */
  for(;;)
  {
	 osSemaphoreAcquire(Sensor_Sem1Handle,100);
	 UltraSonic_Read(US_Trigger_4_Pin);
     osDelay(10);
  }
  /* USER CODE END UltraSonic4_Read */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

