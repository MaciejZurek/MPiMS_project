/*
 * bluetooth.h
 *
 *  Created on: May 5, 2021
 *      Author: rydze
 */
#include "main.h"

#ifndef INC_BLUETOOTH_H_
#define INC_BLUETOOTH_H_

extern UART_HandleTypeDef huart1;
extern volatile uint8_t DataR[2];
extern int Size;
extern volatile _Bool flag;
extern volatile _Bool wykrycie;

void Receive_Data();
void Send_Data(int DataS);


#endif /* INC_BLUETOOTH_H_ */
