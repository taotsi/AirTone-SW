/*******************************************************************************
 * Brief:    Using GPIO to simulate I2C , based on STM8L15x, uesed for AK4637EN
 * Author:   Taotsi
 * Update:   2016.04.03
 *******************************************************************************/
#ifndef _I2Csim_H_
#define _I2Csim_H_


/* Includes -------------------------------------------------------------------*/
#include "BSP.h"


/* Types ----------------------------------------------------------------------*/
/* enum Type Definition*********************************************************/

/**
  * Indicates if Acknowledge is received in the Master Transmitter mode.
  */
typedef enum
{
    ACK_NotRcvd = 0,
    ACK_Rcvd = !ACK_NotRcvd
}
ACK_RcvStatus_T;

/**
  * In Master Transmitter mode, it indicates if the master should check ACK 
  *   from the slave after a byte sent.
  * In Master Receiver mode, it indicates if the master should send an ACK 
  *   to the slave after a byte received.
  */
typedef enum
{
    ACK_DISABLE = 0,
    ACK_ENABLE  = !DISABLE
}
ACK_Cmd_T;

/**
  * 
  */
  /*
typedef enum
{
    SDA_IN = 0,
    SDA_OUT = !SDA_IN
}
SDA_Direction_T;
*/

/* Macros ---------------------------------------------------------------------*/
/* Pin definition */
#define PORT_I2Csim         GPIOC
#define PIN_I2Csim_SDA      GPIO_Pin_0
#define PIN_I2Csim_SCL      GPIO_Pin_1

/* IO direction */
#define SDA_IN()    {GPIO_Init(PORT_I2Csim, PIN_I2Csim_SDA, GPIO_Mode_In_PU_No_IT);}
#define SDA_OUT()   {GPIO_Init(PORT_I2Csim, PIN_I2Csim_SDA, GPIO_Mode_Out_PP_High_Fast);}
//#define SDA_IN()        
//#define SDA_OUT()

/* SDA pin External Interrupt command */
#define SDA_IT_DISABLE() {GPIOC->CR2 &= 0x00;}
#define SDA_IT_ENABLE()  {GPIOC->CR2 |= 0x7F;}

/* IO operation */
#define SDA_HIGH()      GPIO_SetBits(PORT_I2Csim, PIN_I2Csim_SDA)
#define SDA_LOW()       GPIO_ResetBits(PORT_I2Csim, PIN_I2Csim_SDA)
#define SCL_HIGH()      GPIO_SetBits(PORT_I2Csim, PIN_I2Csim_SCL)
#define SCL_LOW()       GPIO_ResetBits(PORT_I2Csim, PIN_I2Csim_SCL)
#define SDA_READ()      GPIO_ReadInputDataBit(PORT_I2Csim, PIN_I2Csim_SDA)


/* Functions ------------------------------------------------------------------*/
void I2Csim_Init(void);
void I2Csim_START(void);
void I2Csim_STOP(void);
void I2Csim_ACK(void);
void I2Csim_NoACK(void);
ACK_RcvStatus_T I2Csim_WaitForACK(void);
void I2Csim_Send_Byte(uint8_t Byte, ACK_Cmd_T ACK_Cmd);
uint8_t I2Csim_Receive_Byte(ACK_Cmd_T ACK_Cmd);

//void I2Csim_SDA_Direction(SDA_Direction_T dir);

void ACK_test(uint8_t n);
void I2Csim_DummyPre(void); // I dont know why, but this is necessary.

/*
void I2Csim_Send_OneByte(uint8_t Addr, uint8_t Byte);
void I2Csim_Send_TwoBytes(uint8_t Addr, uint8_t Byte_1, uint8_t Byte_2);
uint8_t I2Csim_Receive_OneByte(uint8_t Addr);
*/

#endif // _I2Csim_H_

/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/