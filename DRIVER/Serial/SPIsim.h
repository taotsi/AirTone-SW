/*******************************************************************************
 * Brief:   Using GPIO to simulate SPI, based on STM8L15x
 * Author:  taotsi
 * Update:  2017.03.26
 * Note:    Since internal SPI works, this library has been abandoned
 *******************************************************************************/
#ifndef _SPIsim_H_
#define _SPIsim_H_

#include "BSP.h"

#define PORT_SPIsim        GPIOB
#define PIN_SPIsim_SCLK        GPIO_Pin_5
#define PIN_SPIsim_MOSI        GPIO_Pin_6
#define PIN_SPIsim_MISO        GPIO_Pin_7
#define PIN_SPIsim_OLED_CSN    GPIO_Pin_3
#define PIN_SPIsim_OLED_DC    GPIO_Pin_2
#define PIN_SPIsim_OLED_RST    GPIO_Pin_1

// Using register for optimizing
#define SPIsim_SCLK_H()        PORT_SPIsim->ODR |= PIN_SPIsim_SCLK
#define SPIsim_SCLK_L()        PORT_SPIsim->ODR &= (uint8_t)(~PIN_SPIsim_SCLK)
#define SPIsim_MOSI_H()        PORT_SPIsim->ODR |= PIN_SPIsim_MOSI
#define SPIsim_MOSI_L()        PORT_SPIsim->ODR &= (uint8_t)(~PIN_SPIsim_MOSI)

// OLED spi active when CSN low. Using register for optimizing
#define SPIsim_OLED_CSN_H()    PORT_SPIsim->ODR |= PIN_SPIsim_OLED_CSN
#define SPIsim_OLED_CSN_L()    PORT_SPIsim->ODR &= (uint8_t)(~PIN_SPIsim_OLED_CSN)
#define SPIsim_OLED_DC_DATA()    PORT_SPIsim->ODR |= PIN_SPIsim_OLED_DC
#define SPIsim_OLED_DC_CMD()    PORT_SPIsim->ODR &= (uint8_t)(~PIN_SPIsim_OLED_DC)
#define SPIsim_OLED_RST_H()    PORT_SPIsim->ODR |= PIN_SPIsim_OLED_RST
#define SPIsim_OLED_RST_L()    PORT_SPIsim->ODR &= (uint8_t)(~PIN_SPIsim_OLED_RST)


void SPIsim_Init();
void SPIsim_Write_Byte(uint8_t byte);
uint8_t SPIsim_Read_Byte(void);
void SPIsim_Write_String(uint8_t* string, int nBytes);
void SPIsim_Read_String(uint8_t* string, int nBytes);

#endif // _SPIsim_H_

/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/