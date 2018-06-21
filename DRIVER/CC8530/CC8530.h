/*******************************************************************************
 * Brief:   CC8530 driver, run on STM8L15x
 * Author:  taotsi
 * Update:  2017.04.15
 *******************************************************************************/

#ifndef _CC8530_H_
#define _CC8530_H_

#include "BSP.h"
//#include "stm8L15x.h"

/*-----------------------------------------------------------------------------*/
/* Macros ---------------------------------------------------------------------*/

/* CC8530 controling pins marco definition ********************************************/
/* CC8530 controling pins macro definition */
#define PORT_STM8_8530          GPIOB
#define PIN_SPI_8530_CSN        GPIO_Pin_4
#define PIN_STM8_8530_RSTN      GPIO_Pin_3
#define PIN_8530_STM8_IRQ       GPIO_PIn_2

/* CC8530 RSTN pin marco definition ********************************************/
#define STM8_CC8530_RSTN_H()        PORT_STM8_8530->ODR |= (uint8_t)  PIN_STM8_8530_RSTN
#define STM8_CC8530_RSTN_L()        PORT_STM8_8530->ODR &= (uint8_t)(~PIN_STM8_8530_RSTN)

/* CMD_REQ Command Type ********************************************************/

/* Boot Behaviour */
#define CmdType_BL_UNLOCK_SPI           0x00

/* Flash Programming Through SPI Slave */
#define CmdType_BL_FLASH_MASS_ERASE     0x03
#define CmdType_BL_FLASH_PAGE_PROG      0x07
#define CmdType_BL_FLASH_VERIFY         0x0F

/* EHIF.Device Information Commands */
#define CmdType_DI_GET_CHIP_INFO        0x1F
#define CmdType_DI_GET_DEVICE_INFO      0x1E

/* EHIF.Control Commands */
#define CmdType_EHC_EVT_MASK            0x1A
#define CmdType_EHC_EVT_CLR             0x19

/* EHIF.Audio Network Control and Status Conmmands */
#define CmdType_NWM_DO_SCAN             0x08
#define CmdType_NWM_DO_JOIN             0x09
#define CmdType_NWM_GET_STATUS          0x0A
#define CmdType_NWM_ACH_SET_USAGE       0x0B
#define CmdType_NWM_CONTROL_ENABLE      0x0C
#define CmdType_NWM_CONTROL_SIGNAL      0x0D
#define CmdType_NWM_SET_RF_CH_MASK      0x0E

/* EHIF.Remote Control Commands */
#define CmdType_RC_SET_DATA             0x2D
#define CmdType_RC_GET_DATA             0x2E

/* EHIF.Data Side-Channel Commands */
#define CmdType_DSC_TX_DATAGRAM         0x04
#define CmdType_DSC_RX_DATAGRAM         0x05

/* EHIF.Power Management Commands */
#define CmdType_PM_SET_STATE            0x1C
#define CmdType_PM_GET_DATA             0x1D

/* EHIF.Volume Control Commands */
#define CmdType_VC_SET_VOLUME           0x17
#define CmdType_VC_GET_VOLUME           0x16

/* EHIF.RF and Audio Statistics Commands */
#define CmdType_PS_AUDIO_STATS          0x11
#define CmdType_PS_RF_STATS             0x10

/* EHIF.Calibration Commands */
#define CmdType_CAL_SET_DATA            0x28
#define CmdType_CAL_GET_DATA            0x29

/* EHIF.Utility Commands */
#define CmdType_IO_GET_PIN_VAL          0x2A
#define CmdType_NVS_GET_DATA            0x2B
#define CmdType_NVS_SET_DATA            0x2C

/* EHIF.RF Test Commands */
#define CmdType_RFT_TXTST_CW            0x15
#define CmdType_RFT_TXTST_PN            0x14
#define CmdType_RFT_RXTST_RSSI          0x26
#define CmdType_RFT_TXPER               0x13
#define CmdType_RFT_RXPER               0x12
#define CmdType_RFT_NWKSIM              0x27

/* EHIF.AUdio Test Commands */
#define CmdType_AT_GEN_TONE             0x20
#define CmdType_AT_DET_TONE             0x21

/* EHIF.IO Test Commands */
#define CmdType_IOTST_INPUT             0x22
#define CmdType_IOTST_OUTPUT            0x23



/*-----------------------------------------------------------------------------*/
/* Type Definition-------------------------------------------------------------*/

typedef enum
{
    CC8530_BBH_BL   = (uint8_t)0x01,
    CC8530_BBH_SYS  = (uint8_t)0x00
}
CC8530_BootBehavior_T;


typedef enum
{
    Protocol_MASTER = (uint8_t)0x01,
    Protocol_SLAVE  = (uint8_t)0x02
}
CC8530_Protocol_Mode_T;


typedef enum
{
    CMDREQ_RDY        = (uint16_t)0x8000 ,

    /* Power Status */
    PWR_ACTIVE        = (uint16_t)0x0A00 ,
    PWR_LOW           = (uint16_t)0x0800 ,
    PWR_STBY_LC       = (uint16_t)0x0600 ,  // local standby
    PWR_STBY_NWK      = (uint16_t)0x0400 ,  // network Standby
    PWR_OFF           = (uint16_t)0x0000 ,

    WASP_CONN         = (uint16_t)0x0100 ,

    /* Event */
    EVT_DSC_RX_AVAIL  = (uint16_t)0x0080 ,
    EVT_DSC_TX_AVAIL  = (uint16_t)0x0040 ,
    EVT_DSC_RESET     = (uint16_t)0x0020 ,  // Must clear
    EVT_SPI_ERROR     = (uint16_t)0x0010 ,  // Must clear
    EVT_VOL_CHG       = (uint16_t)0x0008 ,  // Must clear
    EVT_PS_CHG        = (uint16_t)0x0004 ,  // Must clear
    EVT_NWK_CHG       = (uint16_t)0x0002 ,  // Must clear
    EVT_SR_CHG        = (uint16_t)0x0001    // Must clear
}
CC8530_SPI_Status_T;


typedef enum
{
    WAITFOR_BL_UNLOCK    = (uint16_t)0x8021,
    BL_UNLOCK_SUCCEEDED  = (uint16_t)0x8020,
    BL_UNLOCK_FAILED     = (uint16_t)0x0022
}
CC8530_BL_UNLOCK_Status_T;


typedef enum
{
    ME_INPROGRESS  = (uint16_t)0x0002,
    ME_SUCCEEDED   = (uint16_t)0x8003,
    ME_FAILED      = (uint16_t)0x8004, 
    Error          = (uint16_t)0x0000 
}
CC8530_BL_FLASH_MASS_ERASE_Status_T;


typedef enum
{
    PROG_INPROGRESS  = (uint16_t)0x000A,
    PROG_SUCCEEDED   = (uint16_t)0x800B,
    PROG_FAILED      = (uint16_t)0x800C
}
CC8530_BL_FLASH_PAGE_PROG_Status_T;


typedef enum
{
    VERIF_INPROGRESS  = (uint16_t)0x000D,
    VERIF_SUCCEEDED   = (uint16_t)0x800E,
    VERIF_FAILED      = (uint16_t)0x800F
}
CC8530_BL_FLASH_VERIFY_Status_T;


typedef enum
{
    EHIF_IRQ_ActiveLow  = (uint8_t)0x00,
    EHIF_IRQ_ActiveHigh = (uint8_t)0x01
}
CC8530_EHIF_IRQ_POL_T;


typedef enum
{
    MSK_DSC_RX_AVAIL  = (uint8_t)0x80,
    MSK_DSC_TX_AVAIL  = (uint8_t)0x40,
    MSK_DSC_RESET     = (uint8_t)0x20,
    MSK_SPI_ERROR     = (uint8_t)0x10,
    MSK_VOL_CHG       = (uint8_t)0x08,
    MSK_PS_CHG        = (uint8_t)0x04,
    MSK_NWK_CHG       = (uint8_t)0x02,
    MSK_SR_CHG        = (uint8_t)0x01
}
CC8530_EHC_EVT_MASK_T;


typedef enum
{
    CLR_MSK_DSC_RESET  = (uint8_t)0x20,
    CLR_MSK_SPI_ERROR  = (uint8_t)0x10,
    CLR_MSK_VOL_CHG    = (uint8_t)0x08,
    CLR_MSK_PS_CHG     = (uint8_t)0x04,
    CLR_MSK_NWK_CHG    = (uint8_t)0x02,
    CLR_MSK_SR_CHG     = (uint8_t)0x01
}
CC8530_EHC_EVT_CLR_T;


typedef enum
{
    scan_max_1 = (uint8_t)0x01,
    scan_max_2 = (uint8_t)0x02,
    scan_max_3 = (uint8_t)0x03,
    scan_max_4 = (uint8_t)0x04,
    scan_max_5 = (uint8_t)0x05,
    scan_max_6 = (uint8_t)0x06,
    scan_max_7 = (uint8_t)0x07,
    scan_max_8 = (uint8_t)0x08
}
CC8530_SCAN_MAX_T;


typedef enum
{
    REQ_Enable  = (uint8_t)0x01,
    REQ_Disable = (uint8_t)0x00
}
CC8530_REQ_WPM_PAIR_SIGNAL_T;


typedef enum
{
    RSSI_m0dB    = (uint8_t)0x00,
    RSSI_m1dB    = (uint8_t)0x01,
    RSSI_m2dB    = (uint8_t)0x02,
    RSSI_m4dB    = (uint8_t)0x04,
    RSSI_m8dB    = (uint8_t)0x08,
    RSSI_m16dB   = (uint8_t)0x10,
    RSSI_m32dB   = (uint8_t)0x20,
    RSSI_m64dB   = (uint8_t)0x40,
    RSSI_m128dB  = (uint8_t)0x80
}
CC8530_REQ_RSSI_T;


typedef enum
{
    NWM_FOUND      = 0x01,
    NWM_NOT_FOUND  = 0x00
}
CC8530_NWM_SCAN_RESULT_T;

/*-----------------------------------------------------------------------------*/
/* Functions ------------------------------------------------------------------*/

/* Initialization **************************************************************/
void CC8530_Init(CC8530_BootBehavior_T bbh);

/* Basic SPI Operations ********************************************************/
void CC8530_SET_ADDR(uint16_t addr);
void CC8530_CMD_REQ(uint8_t command, uint8_t nBytes, uint8_t* parameter);
void CC8530_WRITE(uint16_t nBytes, uint8_t* data);
void CC8530_READ(uint16_t nBytes, uint8_t* data);
void CC8530_READBC(uint16_t *nBytes, uint8_t* data);
void CC8530_SYS_RESET(void);
void CC8530_BOOT_RESET(void);
uint16_t CC8530_GET_STATUS(void);

void CC8530_Write_Byte(uint16_t addr, uint8_t byte);
uint8_t CC8530_Read_Byte(uint16_t addr);
void CC8530_Write_String(uint16_t addr, uint8_t *str, uint16_t nBytes);
void CC8530_Read_String(uint16_t addr, uint8_t *str, uint16_t nBytes);


/* Boot Behaviour **************************************************************/
uint16_t CC8530_BL_UNLOCK_SPI(void);

/* Flash Programming through SPI Slave *****************************************/
CC8530_BL_FLASH_MASS_ERASE_Status_T CC8530_BL_FLASH_MASS_ERASE(void);
uint16_t CC8530_BL_FLASH_PAGE_PROG(uint16_t addr_ram, uint16_t addr_flash);
void CC8530_BL_FLASH_VERIFY(uint32_t nImageBytes, uint8_t CRC32[4]);

/* EHIF Command Set ************************************************************/

/* EHIF.Device Information Commands */
void CC8530_DI_GET_CHIP_INFO(uint8_t info[24]);
void CC8530_DI_GET_DEVICE_INFO(uint8_t info[12]);

/* EHIF.Control Commands */
void CC8530_EHC_EVT_MASK(CC8530_EHIF_IRQ_POL_T pol, CC8530_EHC_EVT_MASK_T mask);
void CC8530_EHC_EVT_CLR(CC8530_EHC_EVT_CLR_T evt);

/* EHIF.Audio Network Control and Status Conmmands */
CC8530_NWM_SCAN_RESULT_T CC8530_NWM_DO_SCAN(CC8530_SCAN_MAX_T scan_max,
                                            uint16_t scan_timeout,
                                            uint32_t manf_id,
                                            uint32_t prod_id_mask,
                                            uint32_t prod_id_ref,
                                            CC8530_REQ_WPM_PAIR_SIGNAL_T req,
                                            CC8530_REQ_RSSI_T rssi,
                                            uint8_t list[][28]);
void CC8530_NWM_DO_JOIN(uint16_t join_timeout, uint32_t device_id, uint32_t manf_id,
                        uint32_t prod_id_mask, uint32_t prod_id_ref);
void CC8530_NWM__GET_STATUS(uint8_t *status);


/* EHIF.Remote Control Commands */


/* EHIF.Data Side-Channel Commands */


/* EHIF.Power Management Commands */


/* EHIF.Volume Control Commands */


/* EHIF.RF and Audio Statistics Commands */


/* EHIF.Calibration Commands */


/* EHIF.Utility Commands */


/* EHIF.RF Test Commands */


/* EHIF.AUdio Test Commands */


/* EHIF.IO Test Commands */





#endif // _CC8530_H_

/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/
