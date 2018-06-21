/*******************************************************************************
 * Brief:   Flash library, based on 128MB M25P128, run on STM8L15x
 * Author:	taotsi
 * Origin:  STM8L152C eval-board based example project
 * UpDate:	2017.03.30
 * Note:    This driver has not been completet yet.
 *******************************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "M25P128.h"


/* Functions ------------------------------------------------------------------*/

/**
  * Brief:  Initialize the M25P128 driver.
  */
void M25P_Init(void)
{

    /* Note: SPI pins have been configured in SPI_Config(). */
    
  
    //STM8_M25P_HOLD_H();
    //STM8_M25P_W_H();
}


/**
  * Brief:  Writes more than one byte to the FLASH with a single WRITE cycle
  *           (Page WRITE sequence).
  * Note:   The number of byte can't exceed the FLASH page size.
  * Param:  pBuffer: Pointer to the buffer  containing the data to be written
  *                    to the FLASH.
  * Param:  Addr:    FLASH's internal address to write to.
  * Param:  nBytes:  Number of bytes to write to the FLASH, must be equal
  *                    or less than 256 which is the page size of M25P128.
  */
void M25P_Write_Page(uint8_t* pBuffer, uint32_t Addr, uint16_t nBytes)
{
    M25P_WriteEnable();

    SPI_M25P_CSN_L();

    SPI_ExchangeByte(M25P_CMD_WRITE);

    SPI_ExchangeByte((uint8_t)((Addr & 0xFF0000)>>16));
    SPI_ExchangeByte((uint8_t)((Addr & 0xFF00)>>8));
    SPI_ExchangeByte((uint8_t)(Addr & 0xFF));

    while(nBytes--)
    {
        SPI_ExchangeByte(*pBuffer);
        pBuffer++;
    }

    SPI_M25P_CSN_H();

    M25P_WaitForWriteEnd();
}


/**
  * Brief:  Reads a block of data from the FLASH.
  * Param:  pBuffer: pointer to the buffer that receives the data read from the FLASH.
  * Param:  Addr:    FLASH's internal address to read from.
  * Param:  nBytes:  number of bytes to read from the FLASH.
  */
void M25P_Read_Buffer(uint8_t* pBuffer, uint32_t Addr, uint16_t nBytes)
{
    SPI_M25P_CSN_L();

    SPI_ExchangeByte(M25P_CMD_READ);

    SPI_ExchangeByte((uint8_t)((Addr & 0xFF0000)>>16));
    SPI_ExchangeByte((uint8_t)((Addr & 0xFF00)>>8));
    SPI_ExchangeByte((uint8_t)(Addr & 0xFF));

    while(nBytes--)
    {
        *pBuffer = SPI_ReadByte();
        //oPrintf("%X", *pBuffer);
        pBuffer++;
    }

    SPI_M25P_CSN_H();
}


void M25P_Write_Byte(uint8_t byte, uint32_t addr)
{
    M25P_WriteEnable();
    SPI_M25P_CSN_L();
    SPI_ExchangeByte(M25P_CMD_WRITE);

    SPI_ExchangeByte((uint8_t)((addr & 0xFF0000)>>16));
    SPI_ExchangeByte((uint8_t)((addr & 0xFF00)>>8));
    SPI_ExchangeByte((uint8_t)(addr & 0xFF));

    SPI_ExchangeByte(byte);

    SPI_M25P_CSN_H();
    M25P_WaitForWriteEnd();
}


uint8_t M25P_Read_Byte(uint32_t addr)
{
    uint8_t byteread;
    SPI_M25P_CSN_L();
    
    SPI_ExchangeByte(M25P_CMD_READ);

    SPI_ExchangeByte((uint8_t)((addr & 0xFF0000)>>16));
    SPI_ExchangeByte((uint8_t)((addr & 0xFF00)>>8));
    SPI_ExchangeByte((uint8_t)(addr & 0xFF));

    byteread =  SPI_ExchangeByte(0xFF);
    
    SPI_M25P_CSN_H();
    
    return byteread;
}


/**
  * Brief:  Erases the specified FLASH sector.
  * Param : Addr: address of the sector to erase.
  */
void M25P_Erase_Sector(uint32_t Addr)
{
    //oPrint(">M25P Sector Erasing");
    M25P_WriteEnable();

    SPI_M25P_CSN_L();

    SPI_ExchangeByte(M25P_CMD_SE);

    SPI_ExchangeByte((uint8_t)((Addr & 0xFF0000)>>16));
    SPI_ExchangeByte((uint8_t)((Addr & 0xFF00)>>8));
    SPI_ExchangeByte((uint8_t)(Addr & 0xFF));

    SPI_M25P_CSN_H();

    //M25P_WaitForWriteEnd();

    //uint8_t i = 0;

    oProgBar_Start();
    SPI_M25P_CSN_L();
    SPI_ExchangeByte(M25P_CMD_RDSR);
    for(uint8_t i = 0; ((SPI_ExchangeByte(0xA5)) & M25P_FLAG_WIP) == SET; i++ )
    {
        Delay_ms(35);
        oProgBar_Dis(i++);
    }
    SPI_M25P_CSN_H();
    oProgBar_End();
    
    oPrint(">M25P Sector Erased");
}


/**
  * Brief:  Erases the entire FLASH.
  * Note:   When thare are block being protected, bulk erasion won't work.
  *           So the protection status should be checked before erasing.
  *           and the status whether the erasion succeeds or fails should
  *           be returned.
  */
void M25P_Erase_Bulk(void)
{
    M25P_WriteEnable();

    SPI_M25P_CSN_L();

    SPI_ExchangeByte(M25P_CMD_BE);

    SPI_M25P_CSN_H();

    //M25P_WaitForWriteEnd();
    
    oProgBar_Start();
    SPI_M25P_CSN_L();
    SPI_ExchangeByte(M25P_CMD_RDSR);
    for(uint8_t i = 0; ((SPI_ExchangeByte(0xA5)) & M25P_FLAG_WIP) == SET; i++)
    {
        Delay_ms(200);
        oProgBar_Dis(i);
    }
    SPI_M25P_CSN_H();
    oProgBar_End();
}


/**
  * Brief:  Enables the write access to the FLASH.
  */
void M25P_WriteEnable(void)
{
    SPI_M25P_CSN_L();
    SPI_ExchangeByte(M25P_CMD_WREN);
    SPI_M25P_CSN_H();
}


/**
  * Brief:  Polls the status of the Write In Progress (WIP) flag in the FLASH's
  *           status register and loop until write opertaion has completed.
  */
void M25P_WaitForWriteEnd(void)
{
    uint8_t FlashStatus = 0;

    SPI_M25P_CSN_L();
    SPI_ExchangeByte(M25P_CMD_RDSR);
    do
    {
        /* sent a dummy byte to generate the clock needed
             by the Flash. You can read status register continuously. */
        FlashStatus = SPI_ExchangeByte(0xA5);
    }
    while((FlashStatus & M25P_FLAG_WIP) == SET);
    SPI_M25P_CSN_H();
}


uint8_t M25P_Read_Status(void)
{
    SPI_M25P_CSN_L();
    SPI_ExchangeByte(M25P_CMD_RDSR);
    SPI_M25P_CSN_H();
    return SPI_ReadByte();
}


/**
  *
  * 注意：这个函数还不能用，不知道为啥！
  */
void M25P_WriteProtect(M25P_AreaProtct_T area)
{
    uint8_t st = M25P_Read_Status();
    st &= (area<<2);
    
    SPI_M25P_CSN_L();
    SPI_ExchangeByte(M25P_CMD_WRSR);
    SPI_ExchangeByte(st);
    SPI_M25P_CSN_H();
}
/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/
