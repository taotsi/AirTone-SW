/*******************************************************************************
 * Brief:   Memory Management Library.
 * Author:  taotsi
 * Update:  2017.04.30
 *******************************************************************************/
#include "MemManage.h"

/* Functions ------------------------------------------------------------------*/

/**
  *
  */
void MemMng_Config(void)
{
    
    /* Get CC8530 Master HEX from PC if there's no one already there. */
    if(M25P_Read_Byte(FIndx_CCIMG_Master_Origin_SW) != FSW_CCIMG_Master_Origin_Written)
    {
        oPrint(">Waiting for transferring the Original HEX of CC8530 Master Image...");
        MemMng_DataTrans_PC_M25P(FIndx_CCIMG_Master_Origin, DtSz_CCIMG_Origin);
        M25P_Write_Byte(FSW_CCIMG_Master_Origin_Written, FIndx_CCIMG_Master_Origin_SW);
    }
    
    /* If the HEX of the CC8530 Master Image has not been processed */
    if(M25P_Read_Byte(FIndx_CCIMG_Master_Processed_SW) != FSW_CCIMG_Master_Processed_Written)
    {
        oPrint(">Processing the Original HEX of CC8530 Master Image...");
        MemMng_DataProc_Char_HEX(FIndx_CCIMG_Master_Origin, FIndx_CCIMG_Master_Processed, 2048);
        M25P_Write_Byte(FSW_CCIMG_Master_Processed_Written, FIndx_CCIMG_Master_Processed_SW);
    }
    
    /* Get CC8530 Slave HEX from PC if there's no one already there. */
    if(M25P_Read_Byte(FIndx_CCIMG_Slave_Origin_SW) != FSW_CCIMG_Slave_Origin_Written)
    {
        oPrint(">>Waiting for transferring the Original HEX of CC8530 Slave Image");
        MemMng_DataTrans_PC_M25P(FIndx_CCIMG_Slave_Origin, DtSz_CCIMG_Origin);
        M25P_Write_Byte(FSW_CCIMG_Slave_Origin_Written, FIndx_CCIMG_Slave_Origin_SW);
    }
    
    /* If the HEX of the CC8530 Slave Image has not been processed */
    if(M25P_Read_Byte(FIndx_CCIMG_Slave_Processed_SW) != FSW_CCIMG_Slave_Processed_Written)
    {
        oPrint(">>Processing the Original HEX of CC8530 Slave Image...");
        MemMng_DataProc_Char_HEX(FIndx_CCIMG_Slave_Origin, FIndx_CCIMG_Slave_Processed, 2048);
        M25P_Write_Byte(FSW_CCIMG_Slave_Processed_Written, FIndx_CCIMG_Slave_Processed_SW);
    }
    
}

/**
  * Brief:  Transfer data from PC through UART to the Flash
  * Param:  addr:   Destination address in M25P128.
  * param:  nBytes: Number of bytes to transfer.
  * Note:   Baudrate can be 57600 at most.
  */
void MemMng_DataTrans_PC_M25P(uint32_t addr, uint32_t nBytes)
{
    M25P_Erase_Sector(addr);
    
    //oPrint(">Waiting for Data transfering to start, from PC to Flash...");

    disableInterrupts();

    uint32_t i = 0;

    oProgBar_Start();
    for(i = 0; i < nBytes; i++)
    {
        M25P_Write_Byte(UART_Receive_Byte(), addr++);
        //oPrintf("%X",&tempByte);
        oProgBar_Dis((i*128)/nBytes);
    }
    oProgBar_End();

    enableInterrupts();
    
    //oPrint(">Data transferrd!");
}


/**
  * 
  * Param:  addr_src:  Starting address of the source image data for CC8530.
  * Note:   There are 32768 bytes in total to transfer.
  */
void MemMng_DataTrans_M25P_CC8530_IMG(uint32_t addr_src)
{
    CC8530_BL_FLASH_MASS_ERASE();
    oPrint(">CC8530 Flash Erased!");
    
    uint16_t i;
    uint8_t j;
    uint8_t buff[16];
    
    oPrint(">CC8530 Image Programming int the Flash...");
    oProgBar_Start();
    for(j = 0; j < 31; j++)
    {
        for(i = 0; i < 64; i++)
        {
            M25P_Read_Buffer(buff, FIndx_CCIMG_Master_Processed + 1024*j + 16*i, 16);
            
            CC8530_Write_String(0x6000 + 16*i, buff, 16);
        }
        CC8530_BL_FLASH_PAGE_PROG(0x6000, 0x8000 + 1024*j);
        while(CC8530_GET_STATUS() == 0x000A);
        
        oProgBar_Dis((j+1)*128/31);
    }
    oProgBar_End();
}


/**
  *
  *
  */
void MemMng_DataProc_Char_HEX(uint32_t addr_origin, uint32_t addr_new, uint16_t nRows)
{
    uint32_t j = 0;
    uint8_t i = 0;
    
    uint8_t num = 0;
    uint8_t num_H = 0;
    uint8_t num_L = 0;
    char char_H, char_L;
    
    M25P_Erase_Sector(addr_new);
    
    oPrint(">Data Processing...");
    
    oProgBar_Start();
    for(j = 0; j < nRows; j++)
    {
        for(i = 0; i < 16; i++)
        {
            char_H = M25P_Read_Byte(addr_origin + j*43 + 9 + 2*i);
            char_L = M25P_Read_Byte(addr_origin + j*43 + 9 + 2*i+1);
            num_H = Char2Num(char_H);
            num_L = Char2Num(char_L);
            num = (num_H << 4) + num_L;
            
            M25P_Write_Byte(num, addr_new + j*16 + i);
            //oPrintf("%X", M25P_Read_Byte(addr_new + j*16 + i))
        }
        oProgBar_Dis((j+1)*128/nRows);
    }
    oProgBar_End();
    
    oPrint(">Data processed!");
}

/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/