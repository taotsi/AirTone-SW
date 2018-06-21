/********************************************************************************
 * Brief:   Board support package, including STM8L15x function packages and
 *          other devices' board-level packages.
 * Author:	taotsi
 * Update:	2017.04.04
 *******************************************************************************/
#ifndef _BSP_H_
#define _BSP_H_


/* Includes -------------------------------------------------------------------*/
#include "stm8l15x_conf.h"
#include "SPIsim.h"
#include "I2Csim.h"

#include "OLED.h"
#include "OLED_Interface.h"
#include "M25P128.h"
#include "UART.h"
#include "AK4637.h"
#include "CC8530.h"
#include "MemManage.h"

#include "MyTypeDef.h"
#include "string.h"
#include "BasicOp.h"
#include "stdlib.h"
#include "stdarg.h"


/* Variables -----------------------------------------------------------------*/
/* extern Variables************************************************************/
extern volatile uint8_t UI;

// number of bytes to write or read; extern for interrupt service
//extern uint8_t nBytes_I2C = 0;

//extern uint8_t logo_guitar[];


/* Macros ---------------------------------------------------------------------*/

/* */
#define TIM4_PERIOD	124

/* SPI type for complier option, integrated or simulated. */
#define SPI_sim         0
#define SPI_chip        1
#define SPITYPE         SPI_chip

/* I2C type for complier option, integrated or simulated. */
#define I2C_sim         0
#define I2C_chip        1
#define I2CTYPE         SPI_sim

/* Key Macros */
#define PORT_KEY        GPIOE
#define KEY_Up          GPIO_Pin_2
#define KEY_Down        GPIO_Pin_0
#define KEY_Back        GPIO_Pin_4
#define KEY_Enter       GPIO_Pin_1
#define KEY_1           GPIO_Pin_5
#define KEY_2           GPIO_Pin_3

/* SPI Bus Macros for integrated type, controling three slaves. */
#define PORT_SPIBUS             GPIOB
#define PIN_SPI_SCLK            GPIO_Pin_5
#define PIN_SPI_MOSI            GPIO_Pin_6
#define PIN_SPI_MISO            GPIO_Pin_7


/* SPI CSN operation. Using register operation for optimizing */
#define SPI_8530_CSN_H()	PORT_STM8_8530->ODR |= (uint8_t)  PIN_SPI_8530_CSN
#define SPI_8530_CSN_L()	PORT_STM8_8530->ODR &= (uint8_t)(~PIN_SPI_8530_CSN)
#define SPI_OLED_CSN_H()	PORT_STM8_OLED->ODR |= (uint8_t)  PIN_SPI_OLED_CSN
#define SPI_OLED_CSN_L()	PORT_STM8_OLED->ODR &= (uint8_t)(~PIN_SPI_OLED_CSN)
#define SPI_M25P_CSN_H()	PORT_STM8_M25P->ODR |= (uint8_t)  PIN_SPI_M25P_CSN
#define SPI_M25P_CSN_L()	PORT_STM8_M25P->ODR &= (uint8_t)(~PIN_SPI_M25P_CSN)

/* I2C Address of AK4637EN */
#define I2C_Address_4637           0x24
#define I2C_Address_4637_W         0x24     // Address with Write command.
#define I2C_Address_4637_R         0x25     // Address with Read command.

/* I2C speed for integrated type. */
//#define I2C_SPEED               300000      // The unit is Hz.

/* Function-like Macro */
/* Delay T = t + 2 (us) */
/* 2us的常数是在寄存器翻转IO时得到的，实际应该是1.1us左右 */
#define Delay(t)    {asm("NOP");for(uint16_t i=0; i<t; i++){asm("NOP");asm("NOP");asm("NOP");}}



/* Functions ------------------------------------------------------------------*/

/* System Initialization and Configuration *************************************/
void System_Config(void);
void SCLK_Config(void);
void TIM4_Config(void);
void KEY_Config(void);

/* Battery Monitor *************************************************************/
void Battery_Config(void);
uint16_t Battery_GetVoltage(uint16_t nSample); //nSample, ADC采样次数；取平均值。

/* SPI Operation ***************************************************************/
// Noet: for three slaves
void SPI_Config(void);
uint8_t SPI_ExchangeByte(uint8_t byte); // for full duplex mod, read while sending.
uint8_t SPI_ReadByte(void);

/* I2C Operation ***************************************************************/
void I2C_Config(void);

#if I2CTYPE == I2C_chip

void I2C_Write_Byte(uint8_t byte);
uint8_t I2C_Read_Byte(void);
void I2C_Write_String(uint8_t* String, uint8_t nBytes);
void I2C_Read_String(uint8_t* buffer, uint8_t nBytes);

#endif // #if I2CTYPE == I2C_chip

/* BSP Functions ***************************************************************/
void Delay_ms(__IO uint32_t nTime);
void TimingDelay_Decrement(void);



#endif // _BSP_H_
/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/
