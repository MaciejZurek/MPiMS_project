/*
 * bluetooth.c
 *
 *  Created on: May 5, 2021
 *      Author: rydze
 */

#include "bluetooth.h"

void Receive_Data() {
	HAL_UART_Receive_IT(&huart1, DataR, Size);
	if (DataR[0]==1 || DataR[1]==1) {
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
		}
		else if (DataR[0]==2 || DataR[1]==2) {
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
		}
		else if (((DataR[0]==3 || DataR[1]==3) && !flag) && !wykrycie) {
				TIM1->CCR1 = 5;
				flag=1;
			}
		else if (((DataR[0]==3 || DataR[1]==3) && flag) && !wykrycie) {
				TIM1->CCR1 += 5;
			}
			else if (((DataR[0]==4 || DataR[1]==4) && !flag) && !wykrycie) {
				TIM1->CCR2 = 5;
				flag=1;
			}
			else if (((DataR[0]==4 || DataR[1]==4) && flag) && !wykrycie) {
				TIM1->CCR2 += 5;
						}
			else if (((DataR[0]==5 || DataR[1]==5) && !flag) && !wykrycie) {
				TIM1->CCR3 = 5;
				flag=1;
			}
			else if (((DataR[0]==5 || DataR[1]==5) && flag) && !wykrycie) {
				TIM1->CCR3 += 5;
						}
			else if (((DataR[0]==6 || DataR[1]==6) && !flag) && !wykrycie) {
				TIM1->CCR4 = 5;
				flag=1;
			}
			else if (((DataR[0]==6 || DataR[1]==6) && flag) && !wykrycie) {
				TIM1->CCR4 += 5;
						}
			else {
				TIM1->CCR1 = 0;
				TIM1->CCR2 = 0;
				TIM1->CCR3 = 0;
				TIM1->CCR4 = 0;
				flag=0;
						}

	DataR[0]=0;
	DataR[1]=0;
}


void Send_Data(int DataS) {
		HAL_UART_Transmit(&huart1, &DataS, 1, 10);
	}
