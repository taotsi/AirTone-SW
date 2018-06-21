/*******************************************************************************
 * Brief:    Using GPIO to simulate I2C , based on STM8L15x, uesed for AK4637EN
 * Author:   Taotsi
 * Update:   2017.04.03
 *******************************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "I2Csim.h"


/* Variavles ------------------------------------------------------------------*/
/* extern Variables*************************************************************/
/* Used for test purpose. nAck record the times ACK is waited for.
     nAckErr record the times ACK is not received.                 */
extern uint16_t nAckErr = 0;
extern uint16_t nAck = 0;

//extern void Delay(uint16_t t);



/* Functions ------------------------------------------------------------------*/

/**
  *  Brief:  Initialize SDA and SCL as GPIO.
  */
void I2Csim_Init(void)
{
    GPIO_Init(PORT_I2Csim, PIN_I2Csim_SCL, GPIO_Mode_Out_PP_High_Fast);

    GPIO_Init(PORT_I2Csim, PIN_I2Csim_SDA, GPIO_Mode_Out_PP_High_Fast);
    //GPIO_Init(PORT_I2Csim, PIN_I2Csim_SDA, GPIO_Mode_In_PU_No_IT);
}

/**
  * Brief:  Send a START signal in Master mode.
  *         Toggling SDA from high to low while SCL being high makes a START to the slave.
  */
void I2Csim_START(void)
{
    SDA_OUT();

    SDA_HIGH();
    SCL_HIGH();
    SDA_LOW();
    SCL_LOW();
}

/**
  * Brief:  Send a STOP signal in Master mode.
  *         Toggling SDA from low to high while SCL being high makes a STOP to the slave.
  */
void I2Csim_STOP(void)
{
    SDA_OUT();

    SCL_LOW();
    SDA_LOW();
    SCL_HIGH();
    SDA_HIGH();
}

/**
  * Brief:  Send an ACK signal in Master mode.
  *         Sending the 9th pulse on SCL after sending a byte
  *           while SDA being LOW maks a ACK to the slave.
  */
void I2Csim_ACK(void)
{
    SDA_OUT();

    SDA_LOW();
    SCL_LOW();
    Delay(2);
    SCL_HIGH();
    Delay(2);
    SCL_LOW();
    Delay(2);
}

/**
  * Brief:  Send no ACK signal in Master mode.
  *         Sending the 9th pulse on SCL after sending a byte
  *           while SDA being HIGH means no ACK sent to the slave.
  */
void I2Csim_NoACK(void)
{
    SDA_OUT();

    SDA_HIGH();
    SCL_LOW();
    Delay(2);
    SCL_HIGH();
    Delay(2);
    SCL_LOW();
    Delay(2);
}

/*
 * Brief:   Make an ACK 9th pulse in Master mode, check and wait for ACK
 *            from the slave during the pulse.
 * RetVal:  ACK_NotRcvd: No ACK received
 *          ACK_Rcvd:    ACK received
 */
ACK_RcvStatus_T I2Csim_WaitForACK(void)
{
    uint8_t ErrTime = 0;
    SDA_IN();
    //SDA_HIGH();
    //Delay(2);
    SCL_HIGH();
    Delay(2);
    while(SDA_READ())
    {
        ErrTime++;
        if(ErrTime > 7)
        {
            // I2Csim_STOP();
            return ACK_NotRcvd;
        }
    }
    SCL_LOW();
    //Delay(2);
    return ACK_Rcvd;
}

/**
  * Brief:  Send a byte to slave in Master mode.
  *         This does not include START or STOP generation.
  * Param:  byte:   Byte you want to send.
  * Param:  ACK_Cmd:   ACK_ENABLE:  Will wait for ACK from the slave
  *                    ACK_DISABLE: Won't wait for ACK from the slave.
  *                                   Still will send the 9th pulse though.
  * RetVal: None
  */
void I2Csim_Send_Byte(uint8_t byte, ACK_Cmd_T ACK_Cmd)
{
/* In case that ACK is not received, use goto to send again. */
//This code is not being used for now.
//SENDAGAIN:

    SDA_OUT();

    /* Send the byte, MSB. */
    SCL_LOW();
    for(int n=0; n<8; n++)
    {
        SCL_LOW();
        // --
        //Delay(10);
        if( (byte&0x80)>>7 )
        {
            SDA_HIGH();
        }
        else
        {
            SDA_LOW();
        }
        byte <<= 1;
        // --
        //Delay(10);
        SCL_HIGH();
        Delay(2);
        SCL_LOW();
        // --
        //Delay(10);
    }

    /* In case that WaitForACK does not work, use this for alternative. */
    // This code is not being used for now.
    /*
    SCL_HIGH();
    Delay(1);
    SCL_LOW();
    */

    /* Generate the 9th pulse, check and wait for ACK from the slave. */
    if(ACK_Cmd == ACK_ENABLE)
    {
        ACK_RcvStatus_T ack = I2Csim_WaitForACK();
        if(ack == ACK_NotRcvd)
        {
            //goto SENDAGAIN;  // this code is not being used for now.
            //oPrint("No ACK received!"); // Remind if ACK is not received.
            nAckErr++;  // used for test purpose. see above.
        }
        else if(ack == ACK_Rcvd)
        {
            //oPrint("ACK received!");
        }
        nAck++;  // used for test purpose. see above.
    }
}


/*
 * Param:  ACK_Cmd: ACK_ENABLE:   Will send an ACK to the slave.
 *                  ACK_DISABLE:  Won't send an ACK to the slave.
 * RetVal: The byte received
 */
uint8_t I2Csim_Receive_Byte(ACK_Cmd_T ACK_Cmd)
{
    uint8_t byte = 0;

    SDA_IN();

    /* Receive the byte, MSB. */
    SCL_LOW();
    for(int n=0; n<8; n++)
    {
        SCL_LOW();
        Delay(2);
        SCL_HIGH();
        byte <<= 1;
        if(SDA_READ())
        {
            byte++;
        }
        Delay(2);
    }

    /* Send or not send the ACK. Will send the 9th pulse either. */
    if(ACK_Cmd == ACK_ENABLE)
        I2Csim_ACK();
    else
        I2Csim_NoACK();

    return byte;
}


/**
  * Brief:  Used for test purpose, to count how many times ACK is not received.
  * Param:  n: How many times of ACK should the function test.
  */
void ACK_test(uint8_t n)
{
    oPrintf("nAckErr=%d", nAckErr);
    oPrintf("nAck=%d", nAck);

    for(uint8_t i=0; i<n; i++)
    {
        uint8_t reg = 0x0A;
        uint8_t regaddr = 0x05;
        uint8_t regwr = 3;
        //oPrintStrNum("1,reg=", reg);

        //oPrintStrNum("Read addr ", regaddr);
        reg = AK4637_Read_Reg(regaddr);
        //oPrintStrNum("2,reg=", reg);

        //oPrintStrNum("Write reg as ", regwr);
        AK4637_Write_Reg(regaddr, regwr);
    //oPrint("Read it again");
        reg = AK4637_Read_Reg(regaddr);
        //oPrintStrNum("3,reg=", reg);

        oPrintf("test %d ", i+1);
    }

    oPrintf("nAck=%d", nAck);
    oPrintf("nAckErr=%d", nAckErr);
    nAckErr = 0;
    nAck = 0;
}

/**
  * Brief:  The first two communications are doomed to fail. So this two must
  *           happen before any real communications. Strange though, it's necessary.
  */
void I2Csim_DummyPre(void)
{
    AK4637_Read_Reg(0x00);

    nAckErr = 0;
    nAck = 0;
    //oPrint("I2C dummy read");
}

/*
void I2Csim_Send_OneByte(uint8_t Addr, uint8_t Byte)
{
    I2Csim_START();

    I2Csim_Send_Byte(Addr);
    I2Csim_Send_Byte(Byte);

    I2Csim_STOP();
}

void I2Csim_Send_TwoBytes(uint8_t Addr, uint8_t Byte_1, uint8_t Byte_2)
{
    I2Csim_START();

    I2Csim_Send_Byte(Addr);
    //I2Csim_WaitForACK();
    I2Csim_Send_Byte(Byte_1);
    //I2Csim_WaitForACK();
    I2Csim_Send_Byte(Byte_2);
    //I2Csim_WaitForACK();

    I2Csim_STOP();
}

uint8_t I2Csim_Receive_OneByte(uint8_t Addr)
{
    return 0;
}
*/

/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/
