/*******************************************************************************
 * Brief:   Flash library, based on 128Mb M25P128, run on STM8L15x
 * Author:  taotsi
 * Origin:  STM8L152C eval-board based example project
 * Update:  2017.03.30
 * Note:    This driver has not been completet yet.
 *******************************************************************************/
#ifndef _M25P128_H_
#define _M25P128_H_


/* Includes -------------------------------------------------------------------*/
#include "BSP.h"


/* Macros ---------------------------------------------------------------------*/
/* M25P128 controling pins macro definition */
#define PORT_STM8_M25P          GPIOF
#define PIN_SPI_M25P_CSN        GPIO_Pin_0
//#define PIN_STM8_M25P_HOLD      GPIO_Pin_2
//#define PIN_STM8_M25P_W         GPIO_Pin_3

/* Command Macros */
#define M25P_CMD_WRITE          0x02    // Write to Memory instruction
#define M25P_CMD_WRSR           0x01    // Write Status Register instruction
#define M25P_CMD_WREN           0x06    // Write enable instruction
#define M25P_CMD_READ           0x03    // Read from Memory instruction
#define M25P_CMD_RDSR           0x05    // Read Status Register instruction
#define M25P_CMD_RDID           0x9F    // Read identification
#define M25P_CMD_SE             0xD8    // Sector Erase instruction
#define M25P_CMD_BE             0xC7    // Bulk Erase instruction

/* Status Flag */
#define M25P_FLAG_WIP           0x01    // Write In Progress (WIP) flag
#define M25P_FLAG_WEL           0x02    // 
#define M25P_FLAG_SRWD          0x80    // 

/* M25P128 HOLD# and W# pin operations */
//#define STM8_M25P_HOLD_H()      PORT_STM8_M25P->ODR |= (uint8_t)  PIN_STM8_M25P_HOLD
//#define STM8_M25P_HOLD_L()      PORT_STM8_M25P->ODR &= (uint8_t)(~PIN_STM8_M25P_HOLD)
//#define STM8_M25P_W_H()         PORT_STM8_M25P->ODR |= (uint8_t)  PIN_STM8_M25P_W
//#define STM8_M25P_W_L()         PORT_STM8_M25P->ODR &= (uint8_t)(~PIN_STM8_M25P_W)


/* Type Definition-------------------------------------------------------------*/
typedef enum
{
    None        = (uint8_t)0x00,
    Upper64th   = (uint8_t)0x01,
    Upper32nd   = (uint8_t)0x02,
    Upper16th   = (uint8_t)0x03,
    Upper8th    = (uint8_t)0x04,
    Upper4th    = (uint8_t)0x05,
    UpperHalf   = (uint8_t)0x06,
    All         = (uint8_t)0x07
}
M25P_AreaProtct_T;


/* Functions ------------------------------------------------------------------*/
void M25P_Init(void);

void M25P_Write_Page(uint8_t* pBuffer, uint32_t Addr, uint16_t nBytes);
void M25P_Read_Buffer(uint8_t* pBuffer, uint32_t Addr, uint16_t nBytes);
void M25P_Write_Byte(uint8_t byte, uint32_t addr);
uint8_t M25P_Read_Byte(uint32_t addr);

void M25P_Erase_Sector(uint32_t Addr);
void M25P_Erase_Bulk(void);

void M25P_WriteEnable(void);
void M25P_WaitForWriteEnd(void);

uint8_t M25P_Read_Status(void);

void M25P_WriteProtect(M25P_AreaProtct_T area);

#endif
/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/
