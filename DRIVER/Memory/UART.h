/*******************************************************************************
 * Brief:
 * Author:  taotsi
 * Update:  2017.04.26
 *******************************************************************************/

#ifndef _UART_H_
#define _UART_H_

#include "BSP.h"

/* Functions ------------------------------------------------------------------*/
void UART_Config(uint16_t baud);

void UART_Send_Byte(uint8_t byte);
uint8_t UART_Receive_Byte();

void UART_Send_String(uint16_t nBytes, uint8_t string[]);
void UART_Receive_String(uint16_t nBytes, uint8_t string[]);

#endif // _UART_H_
/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/
