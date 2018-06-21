/*******************************************************************************
 * Brief:   OLED library based on SSD1306, run on STM8L152x
 * Author:  Taotsi
 * Origin:  Internet
 * Update:	2017.04.05
 * Note:    This driver is not complete. For more commands, see SSD1306 datasheet.
 *******************************************************************************/

#ifndef _OLED_H_
#define _OLED_H_


/* Includes -------------------------------------------------------------------*/
//#include "stm8l15x_conf.h"
//#include "MyTypeDef.h"
#include "BSP.h"
//#include "logo.h"


/* Macros ---------------------------------------------------------------------*/
/* OLED controling pins macro definition */
#define PORT_STM8_OLED          GPIOC
#define PIN_STM8_OLED_RST       GPIO_Pin_7
#define PIN_STM8_OLED_DC        GPIO_Pin_6
#define PIN_SPI_OLED_CSN        GPIO_Pin_5

/* STM8L15x to OLED control operation. Using register for optimizing. */
#define SPI_OLED_DC_DATA()	PORT_STM8_OLED->ODR |= (uint8_t)  PIN_STM8_OLED_DC
#define SPI_OLED_DC_CMD()	PORT_STM8_OLED->ODR &= (uint8_t)(~PIN_STM8_OLED_DC)
#define SPI_OLED_RST_H()	PORT_STM8_OLED->ODR |= (uint8_t)  PIN_STM8_OLED_RST
#define SPI_OLED_RST_L()	PORT_STM8_OLED->ODR &= (uint8_t)(~PIN_STM8_OLED_RST)


/* Functions ------------------------------------------------------------------*/

/* High layer functions ********************************************************/
void OLED_Init(void);
void OLED_Dis_Char(uint8_t page, uint8_t column, char ch);
void OLED_Dis_Char_Rev(uint8_t page, uint8_t column, char ch);
void OLED_Dis_Str(uint8_t page, uint8_t column, char *str);
void OLED_Dis_Str_Rev(uint8_t page, uint8_t column, char *str);
void OLED_Dis_Pic(uint8_t* data);


/* Low layer functions *********************************************************/
void OLED_Set_Pos(uint8_t page, uint8_t column);
void OLED_WrCmd(uint8_t cmd);
void OLED_WrDat(uint8_t data);
void OLED_Clear(void);
void OLED_Dis_snow(void);

#endif // _OLED_H_

/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/
