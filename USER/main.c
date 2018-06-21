/******************************************************************
 * Author:	taotsi
 * UpDate:	2017.01.06
 ******************************************************************/

#include "BSP.h"

extern uint16_t BV = 0;
extern uint8_t logo_guitar[];
extern volatile uint8_t UI;

extern uint16_t nAckErr;
extern uint16_t nAck;

extern uint8_t sw = 1;

extern uint16_t dlct = 0;

void main(void)
{
    System_Config();
    


    /*
    oPrintf("%X", AK4637_Read_Reg(MdCtrl2_Address));
    AK4637_Write_Reg(MdCtrl2_Address, 0xC8);
    oPrintf("%X", AK4637_Read_Reg(MdCtrl2_Address));
    */
    
    /*// these codes works!
    uint8_t imgsz[2];
    M25P_Read_Buffer(imgsz, FIndx_CCIMG_Master_Size, 2);
    //oPrintf("%X %X %X %X", imgsz[0],imgsz[1]);
    uint16_t imgsize = (imgsz[0] << 8) + imgsz[1];
    oPrintf("%X", imgsize);
    
    uint8_t CRC32[4];
    MemMng_DataTrans_M25P_CC8530_IMG(FIndx_CCIMG_Slave_Processed);
    CC8530_BL_FLASH_VERIFY(imgsize, CRC32);
    oPrintf("%X %X %X %X", CRC32[0],CRC32[1],CRC32[2],CRC32[3]);
    */
    
    /*
    uint8_t info[24];
    CC8530_DI_GET_CHIP_INFO(info);
    oPrintf("%X %X", info[0], info[1]);
    */
    
    
    //CC8530_SYS_RESET();
    /*
    uint8_t br = CC8530_Read_Byte(0x6005);
    oPrintf("%X", br);
    CC8530_Write_Byte(0x6005, 0x2C);
    br = CC8530_Read_Byte(0x6005);
    oPrintf("%X", br);
    */
    //MemMng_DataProc_Char_HEX(FIndx_CCIMG_Master_Origin, FIndx_CCIMG_Master_Processed, 2048);
    
    while (1)
    {
        while(UI==0)
        {
            oPrintf("%c", UART_Receive_Byte());
        }
        while(UI==1)
        {
            OLED_Dis_Str_Rev(0, 90, "tick");
            Delay_ms(500);
            OLED_Dis_Str(0, 90, "tock");
            Delay_ms(500);
        }
    }
}

/* ------------------------- End of file ------------------------ */
/******************************************************************/
