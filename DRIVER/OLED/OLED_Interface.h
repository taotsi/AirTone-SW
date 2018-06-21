/*******************************************************************************
 * Brief:   UI interface library, based on OLED library, run on STM8L15x
 * Author:	taotsi
 * Update:	2017.03.27
 *******************************************************************************/

#ifndef _OLED_INTERFACE_H_
#define _OLED_INTERFACE_H_

/* Includes -------------------------------------------------------------------*/
#include "BSP.h"


/* Macros ---------------------------------------------------------------------*/
#define oBuffSize    64

#define oProgSW_UnStarted       1
#define oProgSW_Running         3


/* Functions ------------------------------------------------------------------*/
void oInterface_Init();

void oProgBar_Start();
void oProgBar_Dis(uint8_t prog);
void oProgBar_End();

void oPrint(char* string);
void oPrintf(char* str, ...);
void oPrintNum(uint16_t x);


void oDisplay(void);
void oDisplay_slide(void);
void oDisplayPointer(int p);

#endif // _OLED_INTERFACE_H_

/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/
