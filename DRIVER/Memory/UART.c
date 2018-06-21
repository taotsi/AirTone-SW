/*******************************************************************************
 * Brief:
 * Author:  taotsi
 * Update:  2017.04.26
 *******************************************************************************/

#include "UART.h"

/* Functions ------------------------------------------------------------------*/
/**
  * Param: baud: can be fsysclk/16 at most.
  *
  */
void UART_Config(uint16_t baud)
{
    //disableInterrupts();

    CLK_PeripheralClockConfig(CLK_Peripheral_USART1 , ENABLE);

    USART_Init(USART1,
               baud,
               USART_WordLength_8b,
               USART_StopBits_1,
               USART_Parity_No,
               (USART_Mode_Rx | USART_Mode_Tx));

    //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);

    //enableInterrupts();
}


/**
  *
  *
  */
void UART_Send_Byte(uint8_t byte)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData8(USART1, byte);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}


/**
  *
  *
  */
uint8_t UART_Receive_Byte()
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return USART_ReceiveData8(USART1);
}


/**
  *
  *
  */
void UART_Send_String(uint16_t nBytes, uint8_t string[])
{
    uint8_t i = 0;
    for(i = 0; i<nBytes; i++)
    {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData8(USART1, string[i]);
    }
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}


/**
  *
  *
  */
void UART_Receive_String(uint16_t nBytes, uint8_t string[])
{
    uint8_t i = 0;
    for(i = 0; i<nBytes; i++)
    {
        while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
        string[i] = USART_ReceiveData8(USART1);
    }
}

/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/
