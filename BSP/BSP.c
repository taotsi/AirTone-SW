/********************************************************************************
 * Brief:   Board support package, including STM8L15x function packages and
 *          other devices' board-level packages.
 * Author:	taotsi
 * Update:	2017.04.04
 *******************************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "BSP.h"

/* Variavles ------------------------------------------------------------------*/
/* Extern Variables*************************************************************/
extern volatile uint8_t UI=1;

extern uint16_t nAckErr;
extern uint16_t nAck;

/* Private Variables ***********************************************************/
volatile uint32_t TimingDelay;


/* Functions ------------------------------------------------------------------*/

/* System Initialization and Configuration *************************************/

void System_Config(void)
{
    SCLK_Config();
    TIM4_Config();
    SPI_Config();
    UART_Config(57600);

    OLED_Init();
    oInterface_Init();

    M25P_Init();
    MemMng_Config();
    
    KEY_Config();
    
    Battery_Config();
    
    CC8530_Init(CC8530_BBH_BL);

    I2C_Config();
    /* To make I2C normal, this is necessary. I dont know why though.
         And this code must be exactly here. It wont work if it is called
         by other functions. shit, this is strange. Just let it be.      */
    //I2Csim_DummyPre();
    
    AK4637_Init();
    AK4637_SignalPath(DAC_No_DigitalBlock);
    
    oPrint(">System Inited");
}
/*
PRIORITY:
SCLK before all;
SPI before OLED;
SPI before 8530;
SPI before M25P;
I2C before 4637;
TIM4 before OLED;
OLED before oInterface;
M25P before MemMng;
oInterface before all non-stm8l drivers;
*/

void SCLK_Config(void)
{
    CLK_DeInit();
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);

    CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
}

void TIM4_Config(void)
{
    disableInterrupts();

    //16MHz/128=125KHz, PERIOD=124, (124+1)/125KHz=1ms
    TIM4_TimeBaseInit(TIM4_Prescaler_128, TIM4_PERIOD);
    TIM4_ClearFlag(TIM4_FLAG_Update); // clear update flag
    TIM4_ITConfig(TIM4_IT_Update, ENABLE);// denable update interrupt
    TIM4_Cmd(ENABLE);

    enableInterrupts();
}

void KEY_Config(void)
{
    disableInterrupts();

    GPIO_Init(PORT_KEY, KEY_Back|KEY_Down|KEY_Enter|KEY_Up|
              KEY_1|KEY_2, GPIO_Mode_In_PU_IT);

    EXTI_DeInit();
    EXTI_SelectPort(EXTI_Port_E);
    EXTI_SetPinSensitivity(EXTI_Pin_0,EXTI_Trigger_Falling);
    EXTI_SetPinSensitivity(EXTI_Pin_1,EXTI_Trigger_Falling);
    EXTI_SetPinSensitivity(EXTI_Pin_2,EXTI_Trigger_Falling);
    EXTI_SetPinSensitivity(EXTI_Pin_3,EXTI_Trigger_Falling);
    EXTI_SetPinSensitivity(EXTI_Pin_4,EXTI_Trigger_Falling);
    EXTI_SetPinSensitivity(EXTI_Pin_5,EXTI_Trigger_Falling);
    //EXTI_SetPinSensitivity(EXTI_Pin_6,EXTI_Trigger_Falling);

    enableInterrupts();
}


/* Battery Monitor *************************************************************/

/**
  * Brief:  Initialize the related ADC.
  */
void Battery_Config(void)
{
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1 , ENABLE);
    GPIO_Init(GPIOA, GPIO_Pin_6, GPIO_Mode_In_FL_No_IT); // Battery voltage monitoring
    ADC_Init(ADC1, ADC_ConversionMode_Single,
             ADC_Resolution_12Bit,  ADC_Prescaler_2);
    ADC_ChannelCmd(ADC1, ADC_Channel_0, ENABLE);
    ADC_Cmd(ADC1, ENABLE);
}


/**
  * Brief:  Get the ADC value from battery.
  * Note:   The actual voltage the ADC gets is 2/3 of the battery output voltage.
  *           Or rather, the battery voltage is divided by a 20k and a 10k resistor.
  * Note:   The returned value is not converted into real voltage.
  *           This will be done later.
  * Param:  nSample:  How many times ADC will sample.
  * RetVal: Average value of several samples.
  */
uint16_t Battery_GetVoltage(uint16_t nSample)
{
    uint16_t DataSum = 0;
    uint16_t DataAvr = 0;
    for(uint16_t i=0; i<nSample; i++)
    {
        ADC_SoftwareStartConv(ADC1);
        while(ADC_GetFlagStatus(ADC1 , ADC_FLAG_EOC) == RESET);
        ADC_ClearFlag(ADC1 , ADC_FLAG_EOC);
        DataSum += ADC_GetConversionValue(ADC1);
    }
    DataAvr = DataSum / nSample;
    return DataAvr;
}


/* SPI Operation ***************************************************************/

/**
  * Brief:  SPI bus and other related controling line configuration
  */
void SPI_Config(void)
{
#if SPITYPE == SPI_sim
    SPIsim_Init();
#else // If SPI type is in-chip.
    CLK_PeripheralClockConfig(CLK_Peripheral_SPI1, ENABLE);

    GPIO_Init(PORT_SPIBUS, PIN_SPI_SCLK, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(PORT_SPIBUS, PIN_SPI_MOSI, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(PORT_SPIBUS, PIN_SPI_MISO, GPIO_Mode_In_PU_No_IT);

    SPI_Init(SPI1, SPI_FirstBit_MSB, SPI_BaudRatePrescaler_2, SPI_Mode_Master,
             SPI_CPOL_Low, SPI_CPHA_1Edge, SPI_Direction_2Lines_FullDuplex,
             SPI_NSS_Soft, 0x07);
    /* Note: 3 slaves happen to share the same relationship between CPOL and CPHA. */

    GPIO_Init(PORT_STM8_8530, PIN_SPI_8530_CSN, GPIO_Mode_Out_PP_High_Fast);
    //GPIO_Init(PORT_SPIBUS, PIN_SPI_8530_CSN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(PORT_STM8_OLED, PIN_SPI_OLED_CSN, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(PORT_STM8_M25P, PIN_SPI_M25P_CSN, GPIO_Mode_Out_PP_High_Fast);
#endif

    /* OLED controling line */
    GPIO_Init(PORT_STM8_OLED, PIN_STM8_OLED_DC, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(PORT_STM8_OLED, PIN_STM8_OLED_RST, GPIO_Mode_Out_PP_High_Fast);

    /* M25P128 controling line */
    //GPIO_Init(PORT_STM8_M25P, PIN_STM8_M25P_W, GPIO_Mode_Out_PP_High_Fast);
    //GPIO_Init(PORT_STM8_M25P, PIN_STM8_M25P_HOLD, GPIO_Mode_Out_PP_High_Fast);

    /* CC8530 controling line */
    GPIO_Init(PORT_STM8_8530, PIN_STM8_8530_RSTN, GPIO_Mode_Out_PP_High_Fast);

    SPI_Cmd(SPI1, ENABLE);
}


/**
  * Brief:  Exchange a byte for a byte with the slave.
  * Note:   In full duplex mod, reading is occuring while writing.
  * Param:  byte: Byte to send.
  * RetVal: Byte received.
  */
uint8_t SPI_ExchangeByte(uint8_t byte)
{
    while (SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET);
    SPI_SendData(SPI1, byte);

    while (SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE) == RESET);
    return SPI_ReceiveData(SPI1);
}

uint8_t SPI_ReadByte(void)
{
    return (SPI_ExchangeByte(0xA5)); // dummy byte
}


/* I2C Operation ***************************************************************/
/* For AK4637EN only. */

void I2C_Config(void)
{
#if I2CTYPE == I2C_sim
    I2Csim_Init();
#else // if it's I2C_chip

    //disableInterrupts();

    CLK_PeripheralClockConfig(CLK_Peripheral_I2C1, ENABLE);
    I2C_Init(I2C1, I2C_SPEED, 0xA0, I2C_Mode_I2C, I2C_DutyCycle_2,
             I2C_Ack_Enable, I2C_AcknowledgedAddress_7bit);
    //I2C_ITConfig(I2C1, (I2C_IT_T)(I2C_IT_EVT | I2C_IT_BUF), ENABLE);

    //enableInterrupts();

#endif

    GPIO_Init(PORT_STM8_4637, PIN_STM8_4637_PDN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(PORT_STM8_4637, PIN_STM8_4637_LD, GPIO_Mode_Out_PP_High_Fast);
}

/* Note: The integrated I2C is not very practical for AK4637EN,
           so I've decided to use the simulated type. */
#if I2CTYPE == I2C_chip

void I2C_Write_Byte(uint8_t byte)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));


    I2C_GenerateSTART(I2C1, ENABLE);

    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2C1, I2C_Address_4637, I2C_Direction_Transmitter);

    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    I2C_SendData(I2C1, byte);

    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    I2C_GenerateSTOP(I2C1, ENABLE);


    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
}

uint8_t I2C_Read_Byte(void)
{
    uint8_t temp = 0;

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

    I2C_GenerateSTART(I2C1, ENABLE);

    // EV5
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2C1, I2C_Address_4637, I2C_Direction_Receiver);

    // EV6
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

    I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);

    while ((I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET));

    temp = I2C_ReceiveData(I2C1);

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

    return temp;
}

void I2C_Write_String(uint8_t* string, uint8_t nBytes)
{
    uint8_t Idx = 0;

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

    I2C_GenerateSTART(I2C1, ENABLE);

    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2C1, I2C_Address_4637, I2C_Direction_Transmitter);

    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    I2C_SendData(I2C1, string[Idx]);

    Idx++;
    nBytes--;

    while(nBytes)
    {
        // EV8
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));

        I2C_SendData(I2C1, string[Idx]);

        Idx++;
        nBytes--;
    }

    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    I2C_GenerateSTOP(I2C1, ENABLE);

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
}

void I2C_Read_String(uint8_t* buffer, uint8_t nBytes)
{
    uint8_t Idx = 0;

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

    I2C_GenerateSTART(I2C1, ENABLE);

    // EV5
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2C1, I2C_Address_4637, I2C_Direction_Receiver);

    // EV6
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

    while(nBytes)
    {
        if(nBytes == 1)
        {
            I2C_AcknowledgeConfig(I2C1, DISABLE);
            I2C_GenerateSTOP(I2C1, ENABLE);

            // EV7
            while ((I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET));
            buffer[Idx] = I2C_ReceiveData(I2C1);

            Idx++;
            nBytes--;
        }
        if(nBytes != 1)
        {
            // EV7
            while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));

            buffer[Idx] = I2C_ReceiveData(I2C1);

            Idx++;
            nBytes--;
        }
        /*
        if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
        {
            Buffer[Idx] = I2C_ReceiveData(I2C1);

            Idx++;
            nBytes--;
        }
        */
    }

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
}
#endif // #if I2CTYPE == I2C_chip



/* BSP Functions ***************************************************************/

void Delay_ms(__IO uint32_t nTime)
{
    TimingDelay = nTime;
    while (TimingDelay != 0);
}// see rest part in stm8l15x_it.c


void TimingDelay_Decrement(void)
{
    if(TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}// written for tim4 delay


/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/
