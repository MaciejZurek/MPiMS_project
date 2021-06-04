/*
 * distance_sensor.h
 *
 *  Created on: 19 maj 2021
 *      Author: mzuru
 */

#ifndef INC_DISTANCE_SENSOR_H_
#define INC_DISTANCE_SENSOR_H_

#include "main.h"

#define TIME2DISTANCE 58
#define SENSOR_MAX_RANGE 200 // 2 - 200 cm

void US_Init(void);
void delay_us(uint16_t time);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void US_start(void);

#endif /* INC_DISTANCE_SENSOR_H_ */
