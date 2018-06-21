/*******************************************************************************
 * Brief:   Using GPIO to simulate SPI, based on STM8L15x
 * Author:  taotsi
 * Update:  2017.01.05
 * Note:    Since internal SPI works, this library has been abandoned
 *******************************************************************************/

#include "SPIsim.h"

// based on STM8L151C8 GPIO
void SPIsim_Init()
{
    GPIO_Init(PORT_SPIsim, PIN_SPIsim_SCLK, GPIO_Mode_Out_PP_Low_Fast); //CHOL=0, 0 when idle
    GPIO_Init(PORT_SPIsim, PIN_SPIsim_MOSI, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(PORT_SPIsim, PIN_SPIsim_MISO, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(PORT_SPIsim, PIN_SPIsim_OLED_CSN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(PORT_SPIsim, PIN_SPIsim_OLED_DC, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(PORT_SPIsim, PIN_SPIsim_OLED_RST, GPIO_Mode_Out_PP_High_Fast); // OLED resets when RST Low
}

void SPIsim_Write_Byte(uint8_t byte)
{    
    for(int i=7; i>=0; i--)
    {
        SPIsim_SCLK_L();
        if(byte&(1<<i))
            SPIsim_MOSI_H();
        else
            SPIsim_MOSI_L();
        SPIsim_SCLK_H();  // CPHA=0, capture at first clock transition edge
    }
}

uint8_t SPIsim_Read_Byte(void)
{
    return 0;
}

void SPIsim_Write_String(uint8_t* string, int nBytes)
{
    
}

void SPIsim_Read_String(uint8_t* string, int nBytes)
{
    
}


/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/