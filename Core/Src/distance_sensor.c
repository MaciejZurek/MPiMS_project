/*
 * distance_sensor.c
 *
 *  Created on: 19 maj 2021
 *      Author: mzuru
 */

#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "distance_sensor.h"
#include "bluetooth.h"

volatile uint16_t impulse_time;
volatile uint16_t distance;
extern volatile uint8_t Data;
extern volatile _Bool wykrycie;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	impulse_time = (uint16_t)((uint16_t)HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2) - (uint16_t)HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1));
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
	Receive_Data();
	__HAL_TIM_SET_COUNTER(&htim2, 0);
}

void delay_us(uint16_t time)
{
	__HAL_TIM_SET_COUNTER(&htim3,0);
	while(__HAL_TIM_GET_COUNTER(&htim3) < time);
}

void US_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim2);				// tim2 with interrupts
	HAL_TIM_Base_Start_IT(&htim3);				// tim3 with interrupts
	__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_CC2);	// enable interrupt on channel2 of tim2 (falling edge capture)
	HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_1);	// start tim2 ch1 in input capture mode (rising edge)
	HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_2);	// start tim2 ch2 in input capture mode (falling edge)
	__HAL_TIM_SET_COUNTER(&htim2, 0);			// set tim2 counter to 0
	HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_RESET);
}

void US_start(void)
{
	HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_SET);	// trigger high for 10 us
	delay_us(1);
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_RESET);	// trigger low, and waiting for another tasks and distance calculating
	delay_us(10000);
	distance = (uint16_t)(impulse_time/2.0 * 0.0343);

	if ((distance < 50) & (distance > 20))
	{
		Data = 8;
		Send_Data(Data);
		wykrycie = 0;
	}
	else if (distance <= 20)
	{
		Data = 9;
		Send_Data(Data);
		wykrycie=1;
	}
	else
	{
		Data = 7;
		Send_Data(Data);
		wykrycie = 0;
	}
}

