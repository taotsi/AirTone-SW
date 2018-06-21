/*******************************************************************************
 * Brief:   CC8530 driver, run on STM8L15x
 * Author:  taotsi
 * Note:    Based on FW ??
 * Update:  2017.04.15
 *******************************************************************************/

#include "CC8530.h"

#define dummybyte   0x92    // for duplex SPI read, 0b.1001.0010

/* Functions ------------------------------------------------------------------*/

/* Initialization **************************************************************/

/**
  * Brief:  Initialize CC8530.
  * Param:  bbh: CC8530_BBH_BL:  Bootloader SPI commands available. SPI flash
  *                                programming can be performed.
  *              CC8530_BBH_SYS: CC8530 starts the application in flash.
  * Note:
  */
void CC8530_Init(CC8530_BootBehavior_T bbh)
{
    Delay_ms(3);
    //CC8530_SYS_RESET();
    if(bbh == CC8530_BBH_BL) // Boot reset.
    {
        CC8530_BOOT_RESET();
        Delay(10);
        oPrintf(">CC unblock %X",CC8530_BL_UNLOCK_SPI());
        oPrint(">CC8530 Flash Programming");
        /*
        while(CC8530_GET_STATUS() == WAITFOR_BL_UNLOCK);
        if(CC8530_GET_STATUS() == BL_UNLOCK_SUCCEEDED)
        {
            oPrint(">CC8530 Bootloader unlock succeeded!");
        }
        else if(CC8530_GET_STATUS() == BL_UNLOCK_FAILED)
        {
            oPrint(">Error: CC8530 Bootloader unlick failed!");
        }
        */
    }
    else // System reset.
    {
        CC8530_SYS_RESET();
        oPrint(">CC8530 Program Running");
    }
}



/* Basic SPI Operations ********************************************************/

/**
  *
  *
  */
void CC8530_SET_ADDR(uint16_t addr)
{
    //uint8_t stH = 0;
    //uint8_t stL = 0;
    //uint16_t st = 0;

    SPI_8530_CSN_L();
    //oPrintf("MISO=%d", GPIO_ReadInputDataBit(PORT_SPIBUS, PIN_SPI_MISO));
    
    // --------------------------------
    while(GPIO_ReadInputDataBit(PORT_SPIBUS, PIN_SPI_MISO) == 0);

    //stH = SPI_ExchangeByte(addr >> 8);
    //stL = SPI_ExchangeByte(addr & 0xFF);
    SPI_ExchangeByte(addr >> 8);
    SPI_ExchangeByte(addr & 0xFF);

    SPI_8530_CSN_H();

    //st = (stH<<8) + stL;
    //return st;
}

/**
  * Brief:  Execute a specified command.
  * Param:  CmdType: Command type.
  * Param:  nBytes:  Number of bytes in the parameter field, can be from 0 to 255
  * Param:  *param:  Command parameter field.
  * RetVal: A 16-bit status word
  */
void CC8530_CMD_REQ(uint8_t CmdType, uint8_t nBytes, uint8_t* param)
{
    //uint8_t stH = 0;
    //uint8_t stL = 0;
    //uint16_t st = 0;

    uint8_t CmdTemp = CmdType | 0xC0; //[0:1][15:14] = 0b.11

    uint8_t i = 0;

    SPI_8530_CSN_L();
    
    // --------------------------------
    while(GPIO_ReadInputDataBit(PORT_SPIBUS, PIN_SPI_MISO) == 0);

    //stH = SPI_ExchangeByte(CmdTemp);
    //stL = SPI_ExchangeByte(nBytes);
    SPI_ExchangeByte(CmdTemp);
    SPI_ExchangeByte(nBytes);

    for(i = 0; i<nBytes; i++)
    {
        SPI_ExchangeByte(*(param));
        param++;
    }

    SPI_8530_CSN_H();

    //st = (stH<<8) + stL;
    //return st;
}

/**
  *
  * Param:  nBytes: can be from 0 to 4095
  */
void CC8530_WRITE(uint16_t nBytes, uint8_t* data)
{
    //uint8_t stH = 0;
    //uint8_t stL = 0;
    //uint16_t st = 0;

    uint8_t i = 0;

    SPI_8530_CSN_L();
    
    // --------------------------------
    while(GPIO_ReadInputDataBit(PORT_SPIBUS, PIN_SPI_MISO) == 0);

    //stH = SPI_ExchangeByte(0x80 | (nBytes>>8)); //[0:1][15:12] = 0b.1000
    //stL = SPI_ExchangeByte((uint8_t)nBytes);
    SPI_ExchangeByte(0x80 | (nBytes>>8)); //[0:1][15:12] = 0b.1000
    SPI_ExchangeByte((uint8_t)nBytes);

    for(i = 0; i<nBytes; i++)
    {
        SPI_ExchangeByte(*(data));
        data++;
    }

    SPI_8530_CSN_H();

    //st = (stH<<8) + stL;
    //return st;
}

/**
  *
  * Param:  nBytes: can be from 0 to 4095
  */
void CC8530_READ(uint16_t nBytes, uint8_t* data)
{
    //uint8_t stH = 0;
    //uint8_t stL = 0;
    //uint16_t st = 0;

    uint8_t i = 0;

    SPI_8530_CSN_L();
    
    // --------------------------------
    while(GPIO_ReadInputDataBit(PORT_SPIBUS, PIN_SPI_MISO) == 0);

    //stH = SPI_ExchangeByte(0x90 | (nBytes>>8)); //[0:1][15:12] = 0b.1001
    //stL = SPI_ExchangeByte((uint8_t)nBytes);
    SPI_ExchangeByte(0x90 | (nBytes>>8)); //[0:1][15:12] = 0b.1001
    SPI_ExchangeByte((uint8_t)nBytes);

    for(i = 0; i<nBytes; i++)
    {
        *data = SPI_ExchangeByte(dummybyte);
        data++;
    }

    SPI_8530_CSN_H();

    //st = (stH<<8) + stL;
    //return st;
}

/**
  *
  * Param:  *nBytes: this is a return value.
  */
void CC8530_READBC(uint16_t *nBytes, uint8_t* data)
{
    //uint8_t stH = 0;
    //uint8_t stL = 0;
    //uint16_t st = 0;

    uint8_t nH = 0;
    uint8_t nL = 0;

    uint8_t i = 0;

    SPI_8530_CSN_L();
    
    // --------------------------------
    while(GPIO_ReadInputDataBit(PORT_SPIBUS, PIN_SPI_MISO) == 0);

    //stH = SPI_ExchangeByte(dummybyte); //[0:1][15:12] = 0b.1010
    //stL = SPI_ExchangeByte(dummybyte);
    SPI_ExchangeByte(dummybyte); //[0:1][15:12] = 0b.1010
    SPI_ExchangeByte(dummybyte);

    nH = SPI_ExchangeByte(dummybyte);
    nL = SPI_ExchangeByte(dummybyte);
    *nBytes = (nH<<8) + nL;

    for(i = 0; i<*nBytes; i++)
    {
        *data = SPI_ExchangeByte(dummybyte);
        data++;
    }

    SPI_8530_CSN_H();

    //st = (stH<<8) + stL;
    //return st;
}

/**
  * Brief:  Use SPI only, without RSTN control.
  *
  */
void CC8530_SYS_RESET(void)
{
    /*
    SPI_8530_CSN_L();
    Delay(1);

    SPI_ExchangeByte(0xBF); // 0b.1011.1111
    SPI_ExchangeByte(0xFF); // 0b.1111.1111

    SPI_8530_CSN_H();
    Delay(0);
    SPI_8530_CSN_L();

    while(GPIO_ReadInputDataBit(PORT_SPIBUS, PIN_SPI_MISO) == 0);

    Delay(5);
    SPI_8530_CSN_H();

    GPIO_ResetBits(PORT_SPIBUS, PIN_SPI_MOSI);
    PORT_SPIBUS->ODR &= (uint8_t)(~PIN_SPI_MOSI);
    STM8_CC8530_RSTN_L();
    */


    GPIO_SetBits(PORT_SPIBUS, PIN_SPI_MOSI);
    STM8_CC8530_RSTN_L();

    SPI_8530_CSN_L();
    Delay(2);
    STM8_CC8530_RSTN_H();
    Delay(10);

    SPI_8530_CSN_H();
    Delay(2);
    SPI_8530_CSN_L();

    // --------------------------------
    while(GPIO_ReadInputDataBit(PORT_SPIBUS, PIN_SPI_MISO) == 0);

    Delay(5);
    SPI_8530_CSN_H();
}

/**
  * Brief:  Resets CC85xx and enters the bootloader where the flash programming
  *           interface is available.
  * Note:   RSTN
  */
void CC8530_BOOT_RESET(void)
{
    /*
    SPI_8530_CSN_L();
    Delay(1);

    SPI_ExchangeByte(0xB0); // 0b.1011.0000
    SPI_ExchangeByte(0x00); // 0b.0000.0000
    //Delay(2)

    SPI_8530_CSN_H();
    Delay(3);
    SPI_8530_CSN_L();

    while(GPIO_ReadInputDataBit(PORT_SPIBUS, PIN_SPI_MISO) == 0);

    Delay(5);
    SPI_8530_CSN_H();
    */

    GPIO_ResetBits(PORT_SPIBUS, PIN_SPI_MOSI);
    //PORT_SPIBUS->ODR &= (uint8_t)(~PIN_SPI_MOSI);
    STM8_CC8530_RSTN_L();

    SPI_8530_CSN_L();
    Delay(2);
    STM8_CC8530_RSTN_H();
    Delay(10);

    SPI_8530_CSN_H();
    Delay(2);
    SPI_8530_CSN_L();

    // --------------------------------
    while(GPIO_ReadInputDataBit(PORT_SPIBUS, PIN_SPI_MISO) == 0);

    Delay(5);
    SPI_8530_CSN_H();
}

/**
  *
  *
  */
uint16_t CC8530_GET_STATUS(void)
{
    uint8_t stH = 0;
    uint8_t stL = 0;
    uint16_t st  = 0;

    SPI_8530_CSN_L();
    
    // --------------------------------
    while(GPIO_ReadInputDataBit(PORT_SPIBUS, PIN_SPI_MISO) == 0);

    stH = SPI_ExchangeByte(0x80); //0b.1000.0000
    stL = SPI_ExchangeByte(0x00); //0b.0000.0000

    SPI_8530_CSN_H();

    st = (stH<<8) + stL;
    return st;
}

/**
  * Param:  addr: Only RAM can be written, whose address is from 0x6000 to 0x7FFF.
  */
void CC8530_Write_Byte(uint16_t addr, uint8_t byte)
{
    uint8_t temp = byte;
    CC8530_SET_ADDR(addr);
    CC8530_WRITE(1, &temp);
}


/**
  * Param:  Only RAM can be read, whose address is from 0x6000 to 0x7FFF.
  */
uint8_t CC8530_Read_Byte(uint16_t addr)
{
    uint8_t byte;
    CC8530_SET_ADDR(addr);
    CC8530_READ(1, &byte);
    return byte;
}


/**
  * Param:  addr: Only RAM can be written, whose address is from 0x6000 to 0x7FFF.
  */
void CC8530_Write_String(uint16_t addr, uint8_t *str, uint16_t nBytes)
{
    CC8530_SET_ADDR(addr);
    CC8530_WRITE(nBytes, str);
    
}


/**
  * Param:  Only RAM can be read, whose address is from 0x6000 to 0x7FFF.
  */
void CC8530_Read_String(uint16_t addr, uint8_t *str, uint16_t nBytes)
{
    CC8530_SET_ADDR(addr);
    CC8530_READ(nBytes, str);
}


/* Boot Behaviour **************************************************************/

/**
  * Brief:  Unlock CC8530 Bootloader.
  * Note:   This command is only available and only relevant after a BOOT_RESET().
  * RetVal: WAITFOR_BL_UNLOCK:
  *         BL_UNLOCK_SUCCEEDED:
  *         BL_UNLOCK_FAILED:
  */
uint16_t CC8530_BL_UNLOCK_SPI(void)
{
    uint16_t status;
    
    uint8_t pars[4] = {0x25, 0x05, 0xB0, 0x07}; // Fixed value. Magic number
    
    //status = CC8530_CMD_REQ(CmdType_BL_UNLOCK_SPI, 4, pars);
    //oPrintf("%X", status);
    CC8530_CMD_REQ(CmdType_BL_UNLOCK_SPI, 4, pars);
    
    
    status = CC8530_GET_STATUS();
    //oPrintf("%X", status);
    //while(CC8530_GET_STATUS() != 0x8020);
    return status;
    /*
    status = CC8530_GET_STATUS();
    oPrintf("%X", status);
    */
    /*
    if(status == 0x8021)
        return WAITFOR_BL_UNLOCK;
    else if(status ==0x8020)
        return BL_UNLOCK_SUCCEEDED;
    else if(status == 0x0022)
        return BL_UNLOCK_FAILED;
    else
        return 0;
    */
}



/* Flash Programming through SPI Slave *****************************************/

/**
  * Brief:  Erases all flash contents including program memory and application
  *           non-volatile storage.
  * Note:   This command is available only in the bootloader after unlocking has
  *           been performed.
  * Note:   This command shall always be executed prior to executing the
  *           BL_FLASH_PAGE_PROG.
  * RetVal: ME_INPROGRESS: Mass erase in progress.
  *         ME_SUCCEEDED:  Mass erase completed successfully.
  *         ME_FAILED:     Command failed due to incorrect KEY parameter.
  */
CC8530_BL_FLASH_MASS_ERASE_Status_T CC8530_BL_FLASH_MASS_ERASE(void)
{
    uint8_t pars[4] = {0x25, 0x05, 0x13, 0x37};

    uint16_t st;
    
    CC8530_CMD_REQ(CmdType_BL_FLASH_MASS_ERASE, 4, pars);
    
    do 
    {
        st = CC8530_GET_STATUS();
    } 
    while(st == (uint16_t)ME_INPROGRESS);
    //oPrintf("%X", st);
    
    if(st == (uint16_t)ME_SUCCEEDED)
        return ME_SUCCEEDED;
    else if(st == (uint16_t)ME_FAILED)
        return ME_FAILED;
    else
        return Error;
}


/**
  * Brief:  Programs a single 1 kB flash page using the data which has been
  *           written to the given RAM location.
  * Note:   This command is available only in the bootloader after unlocking
  *           has been performed.
  * Note:   This command should only be performed on flash pages not programmed
  *           after the last successful BL_FLASH_MASS_ERASE command.
  * RetVal: PROG_INPROGRESS: Programming in progress.
  *         PROG_SUCCEEDED:  Programming completed successfully.
  *         PROG_FAILED:     Command failed due to incorrect KEY parameter.
  */
uint16_t CC8530_BL_FLASH_PAGE_PROG(uint16_t addr_ram, uint16_t addr_flash)
{
    uint8_t pars[10] = {0x00, 0x00, 0x00, 0x00,
                        0x01, 0x00,               // Fixed value. 1 KB page size
                        0x25, 0x05, 0x13, 0x37};  // Fixed value. Magic number

    pars[0] = (uint8_t)(addr_ram >> 8);
    pars[1] = (uint8_t)addr_ram;
    pars[2] = (uint8_t)(addr_flash>>8);
    pars[3] = (uint8_t)addr_flash;

    uint16_t st;
    CC8530_CMD_REQ(CmdType_BL_FLASH_PAGE_PROG, 10, pars);
    
    st = CC8530_GET_STATUS();
    //oPrintf("%X", st);

    return st;
}


/**
  * Brief:  Verifies that the flash programming succeeded by calculating a CRC32
  *           checksum over the entire image, and comparing it against the expected
  *           checksum value.
  * Param:  nImageBytes:  Can be found in the Intel HEX file at address 0x801C
  *                         as a 32-bit value.
  * RetVal: VERIF_INPROGRESS: Verification in progress.
  *         VERIF_SUCCEEDED:  Verification completed successfully (the image is intact).
  *         VERIF_FAILED:     Command failed due to checksum mismatch.
  * Note:   Actually the CRC32 value calculated can be read out. It won't be done in
  *           this function, for now.
  */
void CC8530_BL_FLASH_VERIFY(uint32_t nImageBytes, uint8_t CRC32[4])
{
    uint8_t pars[8] = {0x00, 0x00, 0x80, 0x00,  // Fixed value. Data address.
                       0x00, 0x00, 0x00, 0x00};
    pars[4] = (uint8_t)(nImageBytes >> 24);
    pars[5] = (uint8_t)(nImageBytes >> 16);
    pars[6] = (uint8_t)(nImageBytes >> 8);
    pars[7] = (uint8_t)nImageBytes;

    CC8530_CMD_REQ(CmdType_BL_FLASH_VERIFY, 8, pars);
    
    CC8530_READ(4, CRC32);
}


/* EHIF Command Set ************************************************************/
/* EHIF.Device Information Commands */

/**
  * Brief:  Returns hardware/firmware information.
  * Param:  info[24]: See user guide pdf in page 104.
  * Note:   Available even on un-programmed devices.
  *         Available in all operational modes.
  */
void CC8530_DI_GET_CHIP_INFO(uint8_t info[24])
{
    uint8_t pars[2] = {0x00, 0xB0}; // Fixed number.
    CC8530_CMD_REQ(CmdType_DI_GET_CHIP_INFO, 2, pars);

    CC8530_READ(24, info);
}


/**
  * Brief:  Returns unique device ID and manufacturer-specific information.
  * Param:  info[12]: See user guide pdf in page 104.
  * Note:   Available in all operational modes.
  */
void CC8530_DI_GET_DEVICE_INFO(uint8_t info[12])
{
    CC8530_CMD_REQ(CmdType_DI_GET_DEVICE_INFO, 0, 0x00);

    CC8530_READ(12, info);
}



/* EHIF Command Set ************************************************************/
/* EHIF.Control Commands */

/**
  * Brief:  Configures the EHIF interrupt pin event mask.
  * Param:  pol:   Determines polarity of interrupt pin:
  *                  EHIF_IRQ_ActiveLow:
  *                  EHIF_IRQ_ActiveHigh:
  * Param:  mask:  MSK_DSC_RX_AVAIL:
  *                MSK_DSC_TX_AVAIL:
  *                MSK_DSC_RESET:
  *                MSK_SPI_ERROR:
  *                MSK_VOL_CHG:
  *                MSK_PS_CHG:
  *                MSK_NWK_CHG:
  *                MSK_SR_CHG:
  * Note:   The mask setting takes effect immediately so executing this command
  *           may cause an immediate interrupt.
  */
void CC8530_EHC_EVT_MASK(CC8530_EHIF_IRQ_POL_T pol, CC8530_EHC_EVT_MASK_T mask)
{
    uint8_t pars[2] = {(uint8_t)pol, (uint8_t)mask};
    CC8530_CMD_REQ(CmdType_EHC_EVT_MASK, 2, pars);
}


/**
  * Brief:  Clear EHIF event flags.
  * Param:  evt:  MSK_DSC_RESET:
  *               MSK_SPI_ERROR:
  *               MSK_VOL_CHG:
  *               MSK_PS_CHG:
  *               MSK_NWK_CHG:
  *               MSK_SR_CHG:
  * Note:   The flag clearing takes effect before the CMDREQ_RDY flag is asserted
  *           so host controller interrupt can safely be re-enabled at that point
  *           in time.
  */
void CC8530_EHC_EVT_CLR(CC8530_EHC_EVT_CLR_T evt)
{
    uint8_t par = (uint8_t)evt;
    CC8530_CMD_REQ(CmdType_EHC_EVT_CLR, 1, &par);
}



/* EHIF Command Set ************************************************************/
/* EHIF.Audio Network Control and Status Conmmands */

/**
  * Brief:  Used by protocol slaves to perform a scan of the whole 2.4 GHz band for
  *           PurePath Wireless networks within range matching filtering criteria,
  *           and returns a list of those found.
  * Param:  scan_max:      Maximum number of networks to locate before ending scan.
  *                        Range [1,8].
  * Param:  scan_timeout:  Timeout of scan operation in increments of 10 ms.
  * Param:  manf_id:       Manufacturer ID filtering criteria.
  *                        A value of 0 lists all networks regardless of manufacturer
  *                          ID, any other value lists only networks with a matching
  *                          manufacturer ID.
  * Param:  prod_id_mask:  Product/family ID mask and reference value to be used as
  *                          filtering criteria. Only networks with
  *                            PROD_ID&PROD_ID_MASK == PROD_ID_REF&PROD_ID_MASK
  *                          will be listed. Thus a PROD_ID_MASK value of 0 will
  *                          disable filtering based on product ID.
  * Param:  prod_id_ref:   See above.
  * Param:  req:           Require that the protocol master is signaling that it is
  *                          attempting to pair with a new slave.
  *                        Can be:
  *                          REQ_Enable
  *                          REQ_Disable
  * Param:  rssi:          Required RSSI minimum value of the first received master
  *                          packet when acquiring network during scan operation
  *                          (signed 2‟s complement, 0 → ~0 dBm). Set to -128 dBm to
  *                          disable the criteria.
  *                        Can be:
  *                          RSSI_m0dB
  *                          RSSI_m1dB
  *                          RSSI_m2dB
  *                          RSSI_m4dB
  *                          RSSI_m8dB
  *                          RSSI_m16dB
  *                          RSSI_m32dB
  *                          RSSI_m64dB
  *                          RSSI_m128dB
  * Param:  list:          See user guide pdf P106.
  * RetVal:                The result of network scanning:
  *                          NWM_FOUND
  *                          NWM_NOT_FOUND
  * Note:   Only available in host-controlled protocol slaves.
  * Note:   Depending on the number of networks found, the number of returned
  *           bytes will be N * 28, where N is between 0 and scan_max.
  * 注：这里仅仅把list数据读回来，不进行分析。以后另外建个函数来分析这些数据。
  */
CC8530_NWM_SCAN_RESULT_T CC8530_NWM_DO_SCAN(CC8530_SCAN_MAX_T scan_max,
                                            uint16_t scan_timeout,
                                            uint32_t manf_id,
                                            uint32_t prod_id_mask,
                                            uint32_t prod_id_ref,
                                            CC8530_REQ_WPM_PAIR_SIGNAL_T req,
                                            CC8530_REQ_RSSI_T rssi,
                                            uint8_t list[][28])
{
    uint8_t pars[16];

    pars[0] = (((uint8_t)scan_max)<<5) | (scan_timeout>>8);

    pars[1] = (uint8_t)scan_timeout;

    pars[2] = (uint8_t)(manf_id>>24);
    pars[3] = (uint8_t)(manf_id>>16);
    pars[4] = (uint8_t)(manf_id>>8);
    pars[5] = (uint8_t) manf_id;

    pars[6] = (uint8_t)(prod_id_mask>>24);
    pars[7] = (uint8_t)(prod_id_mask>>16);
    pars[8] = (uint8_t)(prod_id_mask>>8);
    pars[9] = (uint8_t) prod_id_mask;

    pars[10] = (uint8_t)(prod_id_ref>>24);
    pars[11] = (uint8_t)(prod_id_ref>>16);
    pars[12] = (uint8_t)(prod_id_ref>>8);
    pars[13] = (uint8_t) prod_id_ref;

    pars[14] = 0x00; // Fixed value.

    pars[15] = (uint8_t)rssi;

    CC8530_CMD_REQ(CmdType_NWM_DO_SCAN, 16, pars);


    uint16_t nBytes = 0;
    CC8530_READBC(&nBytes, list[0]);

    if(nBytes == 0)
        return NWM_NOT_FOUND;
    else
        return NWM_FOUND;
}


/**
  * Brief: Used by protocol slaves to join a specific PurePath Wireless network
  *          or the first found that matches the specified criteria.
  *        The command is also used to leave a network.
  * Param:  join_timeout:  Timeout in increments of 10 ms for joining network.
  *         device_id:     Network ID of network to join (device ID of master).
  *                        A value of 0x00000000 means leave network if currently
  *                          connected.
  *                        A value of 0xFFFFFFFF means join any network where
  *                          master is currently attempting to pair with a new slave
  * Param:  manf_id:       Manufacturer ID filtering criteria.
  *                        A value of 0 lists all networks regardless of manufacturer
  *                          ID, any other value lists only networks with a matching
  *                          manufacturer ID.
  * Param:  prod_id_mask:  Product/family ID mask and reference value to be used as
  *                          filtering criteria. Only networks with
  *                            PROD_ID&PROD_ID_MASK == PROD_ID_REF&PROD_ID_MASK
  *                          will be listed. Thus a PROD_ID_MASK value of 0 will
  *                          disable filtering based on product ID.
  * Param:  prod_id_ref:   See above.
  * Note:   EVT_NWK_CHG – will be signaled when a network connection is lost – or if
  *           this DO_JOIN command fails.
  * Note:   Only available on host-controlled protocol slaves.
  * Note:   The host controller should use NWM_GET_STATUS to determine the outcome of
  *           the command and to store the network ID for future pairing operations
  *           if required.
  * Note:   The command will use ~500 ms to scan the entire RF channel space once.
  *         Using a JOIN_TO value below 50 (= 500 ms) is not recommended.
  */
void CC8530_NWM_DO_JOIN(uint16_t join_timeout, uint32_t device_id, uint32_t manf_id,
                        uint32_t prod_id_mask, uint32_t prod_id_ref)
{
    uint8_t pars[18];

    pars[0] = (uint8_t)(join_timeout>>8);
    pars[1] = (uint8_t) join_timeout;

    pars[2] = (uint8_t)(device_id>>24);
    pars[3] = (uint8_t)(device_id>>16);
    pars[4] = (uint8_t)(device_id>>8);
    pars[5] = (uint8_t) device_id;

    pars[6] = (uint8_t)(manf_id>>24);
    pars[7] = (uint8_t)(manf_id>>16);
    pars[8] = (uint8_t)(manf_id>>8);
    pars[9] = (uint8_t) manf_id;

    pars[10] = (uint8_t)(prod_id_mask>>24);
    pars[11] = (uint8_t)(prod_id_mask>>16);
    pars[12] = (uint8_t)(prod_id_mask>>8);
    pars[13] = (uint8_t) prod_id_mask;

    pars[14] = (uint8_t)(prod_id_ref>>24);
    pars[15] = (uint8_t)(prod_id_ref>>16);
    pars[16] = (uint8_t)(prod_id_ref>>8);
    pars[17] = (uint8_t) prod_id_ref;

    CC8530_CMD_REQ(CmdType_NWM_DO_JOIN, 18, pars);
}

/**
  * 注：该函数不对状态值进行分析，以后再想办法分析。
  */
void CC8530_NWM__GET_STATUS(uint8_t *status)
{
    CC8530_CMD_REQ(CmdType_NWM_GET_STATUS, 0, 0x00);

    uint16_t nBytes = 0;
    CC8530_READBC(&nBytes, status);

    // 待续...
}


/* EHIF Command Set ************************************************************/
/* EHIF.Remote Control Commands */



/* EHIF Command Set ************************************************************/
/* EHIF.Data Side-Channel Commands */



/* EHIF Command Set ************************************************************/
/* EHIF.Power Management Commands */



/* EHIF Command Set ************************************************************/
/* EHIF.Volume Control Commands */



/* EHIF Command Set ************************************************************/
/* EHIF.RF and Audio Statistics Commands */



/* EHIF Command Set ************************************************************/
/* EHIF.Calibration Commands */



/* EHIF Command Set ************************************************************/
/* EHIF.Utility Commands */



/* EHIF Command Set ************************************************************/
/* EHIF.RF Test Commands */



/* EHIF Command Set ************************************************************/
/* EHIF.AUdio Test Commands */



/* EHIF Command Set ************************************************************/
/* EHIF.IO Test Commands */





/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/