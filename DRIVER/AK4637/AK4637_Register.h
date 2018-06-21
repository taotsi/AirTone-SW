/*******************************************************************************
 * Brief:   Library for AK4637EN, run on STM8L15x
 * Author:  ZhiYe
 * Update:  2017.04.04
 *******************************************************************************/
#ifndef _AK4637_Register_h_
#define _AK4637_Register_h_

//#include "MyTypeDef.h"

/* temporary area **************************************************************/


/* 
 * Power Management ************************************************************
 **/
typedef struct {
    __IO uint8_t PwMng1;
    __IO uint8_t PwMng2;
}
PwMng_T;

//Power Management Registers Address
#define PwMng1_Address    0x00                                                                                                                                                                                                          
#define PwMng2_Address    0x01

//Power Management Registers Initial Value
#define PwMng1_InitVal    0x00
#define PwMng2_InitVal    0x00

//Power Management Registers Bits Defination
#define PwMng1_PMADC      0x01
#define PwMng1_PMDAC      0x04
#define PwMng1_LOSEL      0x08
#define PwMng1_PMBP       0x20
#define PwMng1_PMVCM      0x40
#define PwMng1_PMPFIL     0x80

#define PwMng2_PMSL       0x02
#define PwMng2_PMPLL      0x04
#define PwMng2_MS         0x08

//Power Management Registers Bits typedef enum
typedef enum {
    PwMng1_PMADC_PowerUp   =   (uint8_t)PwMng1_PMADC,
    PwMng1_PMADC_PowerDown = ~((uint8_t)PwMng1_PMADC)
}
PwMng1_PMADC_T;

typedef enum {
    PwMng1_PMDAC_PowerUp   =   (uint8_t)PwMng1_PMDAC,
    PwMng1_PMDAC_PowerDown = ~((uint8_t)PwMng1_PMDAC)
}
PwMng1_PMDAC_T;

typedef enum {
    PwMng1_LOSEL_LineOut    =   (uint8_t)PwMng1_LOSEL,
    PwMng1_LOSEL_SpeakerOut = ~((uint8_t)PwMng1_LOSEL)
}
PwMng1_LOSEL_T;

typedef enum {
    PwMng1_PMBP_PowerUp   =   (uint8_t)PwMng1_PMBP,
    PwMng1_PMBP_PowerDown = ~((uint8_t)PwMng1_PMBP)
}
PwMng1_PMBP_T;

typedef enum {
    PwMng1_PMVCM_PowerUp   =   (uint8_t)PwMng1_PMVCM,
    PwMng1_PMVCM_PowerDown = ~((uint8_t)PwMng1_PMVCM)
}
PwMng1_PMVCM_T;

typedef enum {
    PwMng1_PMPFIL_PowerUp   =   (uint8_t)PwMng1_PMPFIL,
    PwMng1_PMPFIL_PowerDown = ~((uint8_t)PwMng1_PMPFIL)
}
PwMng1_PMPFIL_T;

typedef enum {
    PwMng2_PMSL_PowerUp   =   (uint8_t)PwMng2_PMSL,
    PwMng2_PMSL_PowerDown = ~((uint8_t)PwMng2_PMSL)
}
PwMng2_PMSL_T;

typedef enum {
    PwMng2_PMPLL_PowerUp   =   (uint8_t)PwMng2_PMPLL,
    PwMng2_PMPLL_PowerDown = ~((uint8_t)PwMng2_PMPLL)
}
PwMng2_PMPLL_T;

typedef enum {
    PwMng2_MS_Master =   (uint8_t)PwMng2_MS ,
    PwMng2_MS_Slave  = ~((uint8_t)PwMng2_MS)
}
PwMng2_MS_T;


/* 
 * Signal Select ***************************************************************
 **/
typedef struct {
    __IO uint8_t Select1;
    __IO uint8_t Select2;
    __IO uint8_t Select3;
}
SgnlSlct_T;

//Signal Select Registers Address
#define SgnlSlct1_Address           0x02
#define SgnlSlct2_Address           0x03
#define SgnlSlct3_Address           0x04

//Signal Select Registers Initial Value
#define SgnlSlct1_InitVal           0x06
#define SgnlSlct2_InitVal           0x00
#define SgnlSlct3_InitVal           0x40

//Signal Select Registers Bits Defination
#define Signal_Select1_MGAIN_0dB         0x00
#define Signal_Select1_MGAIN_3dB         0x01
#define Signal_Select1_MGAIN_6dB         0x02
#define Signal_Select1_MGAIN_9dB         0x03
#define Signal_Select1_MGAIN_12dB        0x04
#define Signal_Select1_MGAIN_15dB        0x05
#define Signal_Select1_MGAIN_18dB        0x06
#define Signal_Select1_MGAIN_21dB        0x07
#define Signal_Select1_MGAIN_24dB        0x40
#define Signal_Select1_MGAIN_27dB        0x41
#define Signal_Select1_MGAIN_30dB        0x42
#define Signal_Select1_PMMP                     0x08
#define Signal_Select1_DACS                     0x20
#define Signal_Select1_SLPSN                    0x80
//剩下两个写函数里
#define Signal_Select2_MDIF                     0x01
#define Signal_Select2_MICL                     0x10
#define Signal_Select2_SPKG_6_4dB               0x00
#define Signal_Select2_SPKG_8_4dB               0x40
#define Signal_Select2_SPKG_11_1dB              0x80
#define Signal_Select2_SPKG_14_9dB              0xC0

#define Signal_Select3_DACL                     0x20
#define Signal_Select3_LVCM_0dB_1_3             0X00
#define Signal_Select3_LVCM_2dB_1_5             0X40
#define Signal_Select3_LVCM_2dB_1_3             0X80
#define Signal_Select3_LVCM_4dB_1_5             0XC0

//Signal Select Registers Bits typedef enum
typedef enum {
    SgnlSlct1_MGAIN_0dB =  (uint8_t)Signal_Select1_MGAIN_0dB,
    SgnlSlct1_MGAIN_3dB =  (uint8_t)Signal_Select1_MGAIN_3dB,
    SgnlSlct1_MGAIN_6dB =  (uint8_t)Signal_Select1_MGAIN_6dB,
    SgnlSlct1_MGAIN_9dB =  (uint8_t)Signal_Select1_MGAIN_9dB,
    SgnlSlct1_MGAIN_12dB = (uint8_t)Signal_Select1_MGAIN_12dB,
    SgnlSlct1_MGAIN_15dB = (uint8_t)Signal_Select1_MGAIN_15dB,
    SgnlSlct1_MGAIN_18dB = (uint8_t)Signal_Select1_MGAIN_18dB,
    SgnlSlct1_MGAIN_21dB = (uint8_t)Signal_Select1_MGAIN_21dB,
    SgnlSlct1_MGAIN_24dB = (uint8_t)Signal_Select1_MGAIN_24dB,
    SgnlSlct1_MGAIN_27dB = (uint8_t)Signal_Select1_MGAIN_27dB,
    SgnlSlct1_MGAIN_30dB = (uint8_t)Signal_Select1_MGAIN_30dB
}
SgnlSlct1_MGAIN_T;

typedef enum {
    SgnlSlct1_PMMP_PowerUp   =   (uint8_t)Signal_Select1_PMMP,
    SgnlSlct1_PMMP_PowerDown = ~((uint8_t)Signal_Select1_PMMP)
}
SgnlSlct1_PMMP_T;

typedef enum {
    SgnlSlct1_DACS_ON  =   (uint8_t)Signal_Select1_DACS,
    SgnlSlct1_DACS_OFF = ~((uint8_t)Signal_Select1_DACS)
}
SgnlSlct1_DACS_T;

typedef enum {
    SgnlSlct1_SLPSN_Normal    =   (uint8_t)Signal_Select1_SLPSN,
    SgnlSlct1_SLPSN_PowerSave = ~((uint8_t)Signal_Select1_SLPSN)
}
SgnlSlct1_SLPSN_T;

typedef enum {
    SgnlSlct2_MDIF_SingleEnded =   (uint8_t)Signal_Select2_MDIF,
    SgnlSlct2_MDIF_Differential   = ~((uint8_t)Signal_Select2_MDIF)
}
SgnlSlct2_MDIF_T;

typedef enum {
    SgnlSlct2_MICL_2_0V  =   (uint8_t)Signal_Select2_MICL,
    SgnlSlct2_MICL_2_4V  = ~((uint8_t)Signal_Select2_MICL)
}
SgnlSlct2_MICL_T;

typedef enum {
    SgnlSlct2_SPKG_6_4dB  = (uint8_t)Signal_Select2_SPKG_6_4dB,
    SgnlSlct2_SPKG_8_4dB  = (uint8_t)Signal_Select2_SPKG_8_4dB,
    SgnlSlct2_SPKG_11_1dB = (uint8_t)Signal_Select2_SPKG_11_1dB,
    SgnlSlct2_SPKG_14_9dB = (uint8_t)Signal_Select2_SPKG_14_9dB
}
SgnlSlct2_SPKG_T;

typedef enum {
    SgnlSlct3_DACL_ON  = (uint8_t)Signal_Select3_DACL,
    SgnlSlct3_DACL_OFF = (uint8_t)Signal_Select3_DACL
}    
SgnlSlct3_DACL_T;

typedef enum {
        SgnlSlct3_LVCM_0dB_1_3  = (uint8_t) Signal_Select3_LVCM_0dB_1_3,
        SgnlSlct3_LVCM_2dB_1_5  = (uint8_t)Signal_Select3_LVCM_2dB_1_5,        
        SgnlSlct3_LVCM_2dB_1_3  = (uint8_t)Signal_Select3_LVCM_2dB_1_3,       
        SgnlSlct3_LVCM_4dB_1_5  = (uint8_t) Signal_Select3_LVCM_4dB_1_5         
}
SgnlSlct3_LVCM_T;


/* 
 * Mode control ****************************************************************
 **/
typedef struct {
    __IO uint8_t Control1;
    __IO uint8_t Control2;
    __IO uint8_t Control3;    
}
MdCtrl_T;

//Mode control Registers Address
#define MdCtrl1_Address        0x05
#define MdCtrl2_Address        0x06
#define MdCtrl3_Address        0x07

//Mode Control Registers Initial Value
#define MdCtrl1_Initval        0x50
#define MdCtrl2_Initval        0x0B
#define MdCtrl3_Initval        0x02

//Mode Control Registers Bits Defination
#define Mode_Control1_BCKO_16fs         0x00
#define Mode_Control1_BCKO_32fs         0x01
#define Mode_Control1_BCKO_64fs         0x02
#define Mode_Control1_BCKO_N_A          0x03

#define Mode_Control1_PLL_NA            0x00
#define Mode_Control1_PLL_16fs          0x10
#define Mode_Control1_PLL_32fs          0x20
#define Mode_Control1_PLL_64fs          0x30
#define Mode_Control1_PLL_11M2896Hz     0x40
#define Mode_Control1_PLL_12M288Hz      0x50
#define Mode_Control1_PLL_12MHz         0x60
#define Mode_Control1_PLL_24MHz         0x70
#define Mode_Control1_PLL_13M5Hz        0xC0
#define Mode_Control1_PLL_27MHz         0xD0

#define Mode_Control1_CKOFF             0x04

#define Mode_Control2_FS_8kHz           0x01
#define Mode_Control2_FS_11k025Hz       0x02
#define Mode_Control2_FS_12kHz          0x03
#define Mode_Control2_FS_16kHz          0x05
#define Mode_Control2_FS_22k05Hz        0x06
#define Mode_Control2_FS_24kHz          0x07
#define Mode_Control2_FS_32kHz          0x09
#define Mode_Control2_FS_44k1Hz         0x0A
#define Mode_Control2_FS_48kHz          0x0B

#define Mode_Control2_CM_256fs          0x00
#define Mode_Control2_CM_384fs          0x40
#define Mode_Control2_CM_512fs          0x80
#define Mode_Control2_CM_1024fs         0xC0

#define Mode_Control3_DIF_16bitDSP      0x00
#define Mode_Control3_DIF_24_16bitMSB   0x01
#define Mode_Control3_DIF_24bitMSB      0x02
#define Mode_Control3_DIF_24_16bitI2S   0x03
#define Mode_Control3_BCKP              0x04
#define Mode_Control3_MSBS              0x08
#define Mode_Control3_SMUTE             0x20
#define Mode_Control3_THDET             0x40
#define Mode_Control3_TSDSEL            0x80


//MdCtrl Registers Bits typedef enum
typedef enum {
    MdCtrl1_BCKO_16fs = (uint8_t)Mode_Control1_BCKO_16fs,
    MdCtrl1_BCKO_32fs = (uint8_t)Mode_Control1_BCKO_32fs,
    MdCtrl1_BCKO_64fs = (uint8_t)Mode_Control1_BCKO_64fs,
    MdCtrl1_BCKO_N_A  = (uint8_t)Mode_Control1_BCKO_N_A
}
MdCtrl1_BCKO_T;

typedef enum {
    MdCtrl1_PPL_NA        = (uint8_t)Mode_Control1_PLL_NA,
    MdCtrl1_PLL_16fs      = (uint8_t)Mode_Control1_PLL_16fs,
    MdCtrl1_PLL_32fs      = (uint8_t)Mode_Control1_PLL_32fs,
    MdCtrl1_PLL_64_fs     = (uint8_t)Mode_Control1_PLL_64fs,
    MdCtrl1_PLL_11M2896Hz = (uint8_t)Mode_Control1_PLL_11M2896Hz,
    MdCtrl1_PLL_12M288Hz  = (uint8_t)Mode_Control1_PLL_12M288Hz,
    MdCtrl1_PLL_12MHz     = (uint8_t)Mode_Control1_PLL_12MHz,
    MdCtrl1_PLL_24MHz     = (uint8_t)Mode_Control1_PLL_24MHz,
    MdCtrl1_PLL_13M5Hz    = (uint8_t)Mode_Control1_PLL_13M5Hz,
    MdCtrl1_PLL_27MHz     = (uint8_t)Mode_Control1_PLL_27MHz
}
MdCtrl1_PLL_T;

typedef enum {
    MdCtrl1_CKOFF =   (uint8_t)Mode_Control1_CKOFF,
    MdCtrl1_CKOUT = ~((uint8_t)Mode_Control1_CKOFF)
}
MdCtrl1_CKOFF_T;

typedef enum {
    MdCtrl2_FS_8kHz      = (uint8_t)Mode_Control2_FS_8kHz,
    MdCtrl2_FS_11k025Hz  = (uint8_t)Mode_Control2_FS_11k025Hz,
    MdCtrl2_FS_12kHz     = (uint8_t)Mode_Control2_FS_12kHz,
    MdCtrl2_FS_16kHz     = (uint8_t)Mode_Control2_FS_16kHz,
    MdCtrl2_FS_22k05Hz   = (uint8_t)Mode_Control2_FS_22k05Hz,
    MdCtrl2_FS_24kHz     = (uint8_t)Mode_Control2_FS_24kHz,
    MdCtrl2_FS_32kHz     = (uint8_t)Mode_Control2_FS_32kHz,
    MdCtrl2_FS_44k1Hz    = (uint8_t)Mode_Control2_FS_44k1Hz,
    MdCtrl2_FS_48kHz     = (uint8_t)Mode_Control2_FS_48kHz
}
MdCtrl2_FS_T;

typedef enum {
    MdCtrl2_CM_256fs  = (uint8_t)Mode_Control2_CM_256fs,
    MdCtrl2_CM_384fs  = (uint8_t)Mode_Control2_CM_384fs,
    MdCtrl2_CM_512fs  = (uint8_t)Mode_Control2_CM_512fs,
    MdCtrl2_CM_1024fs = (uint8_t)Mode_Control2_CM_1024fs
}
MdCtrl2_CM_T;

typedef enum {
    MdCtrl3_DIF_DSP         = (uint8_t)Mode_Control3_DIF_16bitDSP,
    MdCtrl3_DIF_24_16bitMSB = (uint8_t)Mode_Control3_DIF_24_16bitMSB,
    MdCtrl3_DIF_24bitMSB    = (uint8_t)Mode_Control3_DIF_24bitMSB,
    MdCtrl3_DIF_I2S         = (uint8_t)Mode_Control3_DIF_24_16bitI2S
}
MdCtrl3_DIF_T;

typedef enum {
    MdCtrl3_BCKP_FallingEdge =   (uint8_t)Mode_Control3_BCKP,
    MdCtrl3_BCKP_RisingEdge  = ~((uint8_t)Mode_Control3_BCKP)     
}
MdCtrl3_BCKP_T;

typedef enum {
    MdCtrl3_MSBS_OneClk  =   (uint8_t)Mode_Control3_MSBS,
    MdCtrl3_MSBS_HalfClk = ~((uint8_t)Mode_Control3_MSBS)     
}
MdCtrl3_MSBS_T;

typedef enum {
    MdCtrl3_SMUTE_SoftMute =   (uint8_t)Mode_Control3_SMUTE,
    MdCtrl3_SMUTE_Normal   = ~((uint8_t)Mode_Control3_SMUTE)     
}
MdCtrl3_SMUTE_T;

typedef enum {
    MdCtrl3_THDET_ThermalShutDown  =   (uint8_t)Mode_Control3_THDET,
    MdCtrl3_THDET_Normal           = ~((uint8_t)Mode_Control3_THDET)     
}
MdCtrl3_THDET_T;

typedef enum {
    MdCtrl3_TSDSEL_ManualPowerUp    =   (uint8_t)Mode_Control3_TSDSEL,
    MdCtrl3_TSDSEL_AutomaticPowerUp = ~((uint8_t)Mode_Control3_TSDSEL)     
}
MdCtrl3_TSDSEL_T;


/* 
 * Digital MIC *****************************************************************
 **/
typedef struct {
    __IO uint8_t MIC;
}
DigitMIC_T;

//Digital MIC  Registers Address
#define DigitMIC_Address      0x08

//Digital MIC Initial Value
#define DigitMIC_InitVal      0x00

//Digital MIC Registers Bits Defination
#define DigitMIC_DMIC         0x01
#define DigitMIC_DCLKP        0x02
#define DigitMIC_DCLKE        0x08
#define DigitMIC_PMDM         0x10

typedef enum {
    DigitMIC_DMIC_DigitMIC =   (uint8_t)DigitMIC_DMIC,
    DigitMIC_DMIC_AnalogMIC  = ~((uint8_t)DigitMIC_DMIC)     
}
DigitMIC_DMIC_T;

typedef enum {
    DigitMIC_DCLKP_FallingEdge  =   (uint8_t)DigitMIC_DCLKP,
    DigitMIC_DCLKP_RisingEdge  = ~((uint8_t)DigitMIC_DCLKP)     
}
DigitMIC_DCLKP_T;

typedef enum {
    DigitMIC_DCLKE_64fsOutput =   (uint8_t)DigitMIC_DCLKE,
    DigitMIC_DCLKE_LOutput    = ~((uint8_t)DigitMIC_DCLKE)     
}
DigitMIC_DCLKE_T;

typedef enum {
    DigitMIC_PMDM_ON  =   (uint8_t)DigitMIC_PMDM,
    DigitMIC_PMDM_OFF = ~((uint8_t)DigitMIC_PMDM)     
}
DigitMIC_PMDM_T;


/* 
 * Timer Select ****************************************************************
 **/
typedef struct {
    __IO uint8_t Select;
}
TimerSelect_T;

//Timer Select  Registers Address
#define TimerSelect_Address          0x09

//Timer_Select Registers Initial Value
#define TimerSelect_InitVal          0x00

//Timer Select Registers Bits Defination
#define Timer_Select_DVTM            0x01
#define Timer_Select_FRN             0x10
#define Timer_Select_RFATT           0x20
#define Timer_Select_ADRST_1059_fs   0x00
#define Timer_Select_ADRST_267_fs    0x40
#define Timer_Select_ADRST_531_fs    0x80
#define Timer_Select_ADRST_135_fs    0xC0

typedef enum {
    TimerSelect_DVTM_204_fs  =   (uint8_t)Timer_Select_DVTM,
    TimerSelect_DVTM_816_fs  = ~((uint8_t)Timer_Select_DVTM)     
}
TimerSelect_DVTM_T;


typedef enum {
    TimerSelect_FRN_Disable =   (uint8_t)Timer_Select_FRN,
    TimerSelect_FRN_Enable  = ~((uint8_t)Timer_Select_FRN)     
}
TimerSelect_FRN_T;

typedef enum {
    TimerSelect_RFATT_16_fs =   (uint8_t)Timer_Select_RFATT,
    TimerSelect_RFATT_4_fs  = ~((uint8_t)Timer_Select_RFATT)     
}
TimerSelect_RFATT_T;


typedef enum {
    TimerSelect_ADRST_1059_fs =   (uint8_t)Timer_Select_ADRST_1059_fs,
    TimerSelect_ADRST_267_fs  =   (uint8_t)Timer_Select_ADRST_267_fs,
    TimerSelect_ADRST_531_fs  =   (uint8_t)Timer_Select_ADRST_531_fs,
    TimerSelect_ADRST_135_fs  =   (uint8_t)Timer_Select_ADRST_135_fs
}
TimerSelect_ADRST_T;


/*
 * ALC *************************************************************************
 **/
typedef struct {
    __IO uint8_t Select;
    __IO uint8_t Control1;
    __IO uint8_t Control2;
    __I uint8_t Volume;
}
ALC_T;

//ALC Registers Address
#define ALC_TimerSelect_Address         0x0A
#define ALC_MdCtrl1_Address             0x0B
#define ALC_MdCtrl2_Address             0x0C
#define ALC_Volume_Address              0X0E


//ALC Registers Initial Value
#define ALC_TimerSelect_InitVal         0x60
#define ALC_MdCtrl1_InitVal             0x00
#define ALC_MdCtrl2_InitVal             0xE1
//#define ALC_Volume_InitVal          //无初值

//ALC Registers Bits Defination
#define ALC_Timer_Select_RFST_0_0032        0x00
#define ALC_Timer_Select_RFST_0_0042        0x01
#define ALC_Timer_Select_RFST_0_0064        0x02
#define ALC_Timer_Select_RFST_0_0127        0x03
#define ALC_Timer_Select_WTM_128_fs         0x00
#define ALC_Timer_Select_WTM_256_fs         0x04
#define ALC_Timer_Select_WTM_512_fs         0x08
#define ALC_Timer_Select_WTM_1024_fs        0x0C
#define ALC_Timer_Select_EQFC_12kHz         0x00
#define ALC_Timer_Select_EQFC_24kHz         0x10
#define ALC_Timer_Select_EQFC_48kHz         0x20
#define ALC_Timer_Select_EQFC_N_A           0x30
#define ALC_Timer_Select_IVTM               0x00

#define ALC_Mode_Control1_LMTH_4_1dB        0x00
#define ALC_Mode_Control1_LMTH_3_3dB        0x01
#define ALC_Mode_Control1_LMTH_6_0dB        0x02
#define ALC_Mode_Control1_LMTH_5_0dB        0x03
#define ALC_Mode_Control1_LMTH_8_5dB        0x40
#define ALC_Mode_Control1_LMTH_7_2dB        0x41
#define ALC_Mode_Control1_LMTH_12_0dB       0x42
#define ALC_Mode_Control1_LMTH_10_1dB       0x43

#define ALC_Mode_Control1_RGAIN_0_00424_1fs            0x00
#define ALC_Mode_Control1_RGAIN_0_00212_1fs            0x04
#define ALC_Mode_Control1_RGAIN_0_00106_1fs            0x08
#define ALC_Mode_Control1_RGAIN_0_00106_2fs            0x0C
#define ALC_Mode_Control1_RGAIN_0_00106_4fs            0x10
#define ALC_Mode_Control1_RGAIN_0_00106_8fs            0x14
#define ALC_Mode_Control1_RGAIN_0_00106_16fs           0x18
#define ALC_Mode_Control1_RGAIN_0_00106_32fs           0x1C

#define ALC_Mode_Control1_ALCEQN            0x80
#define ALC_Mode_Control1_ALC               0x20

typedef enum {
    ALC_TimerSelect_RFST_0_0032  =   (uint8_t)ALC_Timer_Select_RFST_0_0032,
    ALC_TimerSelect_RFST_0_0042  =   (uint8_t)ALC_Timer_Select_RFST_0_0042,
    ALC_TimerSelect_RFST_0_0064  =   (uint8_t)ALC_Timer_Select_RFST_0_0064,
    ALC_TimerSelect_RFST_0_0127  =   (uint8_t)ALC_Timer_Select_RFST_0_0127
}
ALC_TimerSelect_RFST_T;

typedef enum {
    ALC_TimerSelect_WTM_128_fs  =   (uint8_t)ALC_Timer_Select_WTM_128_fs,
    ALC_TimerSelect_WTM_256_fs  =   (uint8_t)ALC_Timer_Select_WTM_256_fs,
    ALC_TimerSelect_WTM_512_fs  =   (uint8_t)ALC_Timer_Select_WTM_512_fs,
    ALC_TimerSelect_WTM_1024_fs =   (uint8_t)ALC_Timer_Select_WTM_1024_fs
}
ALC_TimerSelect_WTM_T;

typedef enum {
    ALC_TimerSelect_EQFC_12kHz  =   (uint8_t)ALC_Timer_Select_EQFC_12kHz,
    ALC_TimerSelect_EQFC_24kHz  =   (uint8_t)ALC_Timer_Select_EQFC_24kHz,
    ALC_TimerSelect_EQFC_48kHz  =   (uint8_t)ALC_Timer_Select_EQFC_48kHz,
    ALC_TimerSelect_EQFC_N_A    =   (uint8_t)ALC_Timer_Select_EQFC_N_A
}
ALC_TimerSelect_EQFC_T;

typedef enum {
    ALC_TimerSelect_IVTM_236_fs  =   (uint8_t)ALC_Timer_Select_IVTM,
    ALC_TimerSelect_IVTM_944_fs  = ~((uint8_t)ALC_Timer_Select_IVTM)     
}
ALC_TimerSelect_IVTM_T;

typedef enum {
    ALC_MdCtrl1_LMTH_4_1dB  =   (uint8_t)ALC_Mode_Control1_LMTH_4_1dB,
    ALC_MdCtrl1_LMTH_3_3dB  =   (uint8_t)ALC_Mode_Control1_LMTH_3_3dB,
    ALC_MdCtrl1_LMTH_6_0dB  =   (uint8_t)ALC_Mode_Control1_LMTH_6_0dB,
    ALC_MdCtrl1_LMTH_5_0dB  =   (uint8_t)ALC_Mode_Control1_LMTH_5_0dB,
    ALC_MdCtrl1_LMTH_8_5dB  =   (uint8_t)ALC_Mode_Control1_LMTH_8_5dB,
    ALC_MdCtrl1_LMTH_7_2dB  =   (uint8_t)ALC_Mode_Control1_LMTH_7_2dB,
    ALC_MdCtrl1_LMTH_12_0dB =   (uint8_t)ALC_Mode_Control1_LMTH_12_0dB,
    ALC_MdCtrl1_LMTH_10_1dB =   (uint8_t)ALC_Mode_Control1_LMTH_10_1dB
}
ALC_MdCtrl1_LMTH_T;

typedef enum {
    ALC_MdCtrl1_RGAIN_0_00424_1fs  =   (uint8_t)ALC_Mode_Control1_RGAIN_0_00424_1fs,
    ALC_MdCtrl1_RGAIN_0_00212_1fs  =   (uint8_t)ALC_Mode_Control1_RGAIN_0_00212_1fs,
    ALC_MdCtrl1_RGAIN_0_00106_1fs  =   (uint8_t)ALC_Mode_Control1_RGAIN_0_00106_1fs,
    ALC_MdCtrl1_RGAIN_0_00106_2fs  =   (uint8_t)ALC_Mode_Control1_RGAIN_0_00106_2fs,
    ALC_MdCtrl1_RGAIN_0_00106_4fs  =   (uint8_t)ALC_Mode_Control1_RGAIN_0_00106_4fs,
    ALC_MdCtrl1_RGAIN_0_00106_8fs  =   (uint8_t)ALC_Mode_Control1_RGAIN_0_00106_8fs,
    ALC_MdCtrl1_RGAIN_0_00106_16fs =   (uint8_t)ALC_Mode_Control1_RGAIN_0_00106_16fs,
    ALC_MdCtrl1_RGAIN_0_00106_32fs =   (uint8_t)ALC_Mode_Control1_RGAIN_0_00106_32fs
}
ALC_MdCtrl1_RGAIN_T;

typedef enum {
    ALC_MdCtrl1_ALCEQN_OFF =   (uint8_t)ALC_Mode_Control1_ALCEQN,
    ALC_MdCtrl1_ALCEQN_ON  = ~((uint8_t)ALC_Mode_Control1_ALCEQN)
}    
ALC_MdCtrl1_ALCEQN_T;

typedef enum {
    ALC_MdCtrl1_ALC_Enable  =   (uint8_t)ALC_Mode_Control1_ALC,
    ALC_MdCtrl1_ALC_Disable = ~((uint8_t)ALC_Mode_Control1_ALC)
}    
ALC_MdCtrl1_ALC_T;


/*
 * Input Volume Control********************************************************
 */
typedef struct{
    __IO uint8_t VolumeControl;
}
InputVolumeControl_T;

//Input Volume Control Registers Address
#define InputVolumeControl_Address                   0x0D

//Input Volume Control Register Initial Value
#define InputVolumeControl_InitVal                   0xE1


/*
 * BEEP Control*****************************************************************
 */
typedef struct{
    __IO uint8_t BEEPControl;
}
BEEPControl_T;

// BEEP Control Registers Address
#define BEEPControl_Address               0x0F

//BEEP Control Register Initial Value
#define BEEPControl_InitVal               0x00

//Bits Defination
#define BEEP_Control_BPLVL_0dB            0x00
#define BEEP_Control_BPLVL_6dB            0x01
#define BEEP_Control_BPLVL_12dB           0x02
#define BEEP_Control_BPLVL_18dB           0x03
#define BEEP_Control_BPLVL_24dB           0x04
#define BEEP_Control_BPLVL_30dB           0x05
#define BEEP_Control_BPLVL_33dB           0x06
#define BEEP_Control_BPLVL_36dB           0x07
#define BEEP_Control_BPLVL_39dB           0x08
#define BEEP_Control_BPLVL_42dB           0x09

#define BEEP_Control_BEEPS                0x20
#define BEEP_Control_BPVCM                0x40

typedef enum {
    BEEPControl_BPLVL_0dB   =  (uint8_t)BEEP_Control_BPLVL_0dB,
    BEEPControl_BPLVL_6dB   =  (uint8_t)BEEP_Control_BPLVL_6dB,
    BEEPControl_BPLVL_12dB  =  (uint8_t)BEEP_Control_BPLVL_12dB,
    BEEPControl_BPLVL_18dB  =  (uint8_t)BEEP_Control_BPLVL_18dB,
    BEEPControl_BPLVL_24dB  =  (uint8_t)BEEP_Control_BPLVL_24dB,
    BEEPControl_BPLVL_30dB  =  (uint8_t)BEEP_Control_BPLVL_30dB,
    BEEPControl_BPLVL_33dB  =  (uint8_t)BEEP_Control_BPLVL_33dB,
    BEEPControl_BPLVL_36dB  =  (uint8_t)BEEP_Control_BPLVL_36dB,
    BEEPControl_BPLVL_39dB  =  (uint8_t)BEEP_Control_BPLVL_39dB,
    BEEPControl_BPLVL_42dB  =  (uint8_t)BEEP_Control_BPLVL_42dB
}
BEEPControl_BPLVL_T;

typedef enum {
    BEEPControl_BEEPS_ON  =   (uint8_t)BEEP_Control_BEEPS,
    BEEPControl_BEEPS_OFF = ~((uint8_t)BEEP_Control_BEEPS)     
}
BEEPControl_BEEPS_T;

typedef enum {
    BEEPControl_BPVCM_1_65V =   (uint8_t)BEEP_Control_BPVCM,
    BEEPControl_BPVCM_1_15V = ~((uint8_t)BEEP_Control_BPVCM)     
}
BEEPControl_BPVCM_T;


/*
 * Digital Volume Control********************************************************
 */
typedef struct{
    __IO uint8_t Volume_Control;
}
Digital_Volume_Control_T;

//Digital Volume Control Registers Address
#define DigitalVolumeControl_Address               0x10

//Digital Volume Control Register Initial Value
#define DigitalVolumeControl_InitVal               0x18


/* 
 * EQ **************************************************************************
 **/
typedef struct {
    __IO uint8_t Select;                     
    __IO uint8_t Setting2;
    __IO uint8_t Setting3;
    __IO uint8_t Setting4;
    __IO uint8_t Setting5;  
}
EQ_T;

//EQ Registers Address
#define EQ_CommonGainSelect_Address       0x11
#define EQ2_GainSetting_Address           0x12
#define EQ3_Gainetting_Address            0x13
#define EQ4_GainSetting_Address           0x14
#define EQ5_GainSetting_Address           0x15

//EQ Registers Initial Value    
#define EQ_CommonGainSelect_InitVal       0x00
#define EQ2_GainSetting_InitVal           0x00
#define EQ3_GainSetting_InitVal           0x00
#define EQ4_GainSetting_InitVal           0x00
#define EQ5_GainSetting_InitVal           0x00

//Bits Defination
#define EQ_Common_Gain_Select_EQC2        0x02
#define EQ_Common_Gain_Select_EQC3        0x04
#define EQ_Common_Gain_Select_EQC4        0x08
#define EQ_Common_Gain_Select_EQC5        0x10

#define EQn_Gain_Setting_256_fs           0x00
#define EQn_Gain_Setting_2048_fs          0x01
#define EQn_Gain_Setting_8192_fs          0x02
#define EQn_Gain_Setting_16384_fs         0x03

typedef enum {
    EQ_CommonGainSelect_EQC2_Enable   =   (uint8_t)EQ_Common_Gain_Select_EQC2,
    EQ_CommonGainSelect_EQC2_Disable  = ~((uint8_t)EQ_Common_Gain_Select_EQC2)     
}
EQ_CommonGainSelect_EQC2_T;

typedef enum {
    EQ_CommonGainSelect_EQC3_Enable   =   (uint8_t)EQ_Common_Gain_Select_EQC3,
    EQ_CommonGainSelect_EQC3_Disable  = ~((uint8_t)EQ_Common_Gain_Select_EQC3)     
}
EQ_CommonGainSelect_EQC3_T;

typedef enum {
    EQ_CommonGainSelect_EQC4_Enable   =   (uint8_t)EQ_Common_Gain_Select_EQC4,
    EQ_CommonGainSelect_EQC4_Disable  = ~((uint8_t)EQ_Common_Gain_Select_EQC4)     
}
EQ_CommonGainSelect_EQC4_T;

typedef enum {
    EQ_CommonGainSelect_EQC5_Enable   =   (uint8_t)EQ_Common_Gain_Select_EQC5,
    EQ_CommonGainSelect_EQC5_Disable  = ~((uint8_t)EQ_Common_Gain_Select_EQC5)     
}
EQ_CommonGainSelect_EQC5_T;

typedef enum {
    EQn_GainSetting_256_fs   =   (uint8_t)EQn_Gain_Setting_256_fs,
    EQn_GainSetting_2048_fs  =   (uint8_t)EQn_Gain_Setting_2048_fs,
    EQn_GainSetting_8192_fs  =   (uint8_t)EQn_Gain_Setting_8192_fs,
    EQn_GainSetting_16384_fs =   (uint8_t)EQn_Gain_Setting_16384_fs
}
EQn_GainSetting_EQnT_T;


/*
 * Digital Filter***************************************************************
 */
typedef struct{
    __IO uint8_t Select1;
    __IO uint8_t Select2;
    __IO uint8_t Select3;
    __IO uint8_t Mode;
}
DigitalFilter_T;

//Digital Filter Registers Address
#define DigitFiltSlct1_Address              0x16
#define DigitFiltSlct2_Address              0x17
#define DigitFiltSlct3_Address              0x21
#define DigitalFilterMode_Address                 0x18

//Digital Filter Initial Value
#define DigitFiltSlct1_InitVal              0x01
#define DigitFiltSlct2_InitVal              0x00
#define DigitFiltSlct3_InitVal              0x00
#define DigitalFilterMode_InitVal                 0x03

//Bits Defination
#define Digital_Filter_Select1_HPFAD              0x00
#define Digital_Filter_Select1_HPFC_3Hz7           0x00
#define Digital_Filter_Select1_HPFC_14Hz8          0x02
#define Digital_Filter_Select1_HPFC_118Hz4         0x04
#define Digital_Filter_Select1_HPFC_236Hz8         0x06

#define Digital_Filter_Select2_HPF                0x01
#define Digital_Filter_Select2_LPF                0x02

#define Digital_Filter_Select3_EQ1                0x01
#define Digital_Filter_Select3_EQ2                0x02
#define Digital_Filter_Select3_EQ3                0x04
#define Digital_Filter_Select3_EQ4                0x08
#define Digital_Filter_Select3_EQ5                0x10

#define Digital_Filter_Mode_PFSDO                 0x00
#define Digital_Filter_Mode_ADCPF                 0x00
#define Digital_Filter_Mode_PFDAC_SDTI            0x00
#define Digital_Filter_Mode_PFDAC_PFVOL           0x04
#define Digital_Filter_Mode_PFDAC_SDTInPFVOL    0x08

#define Digital_Filter_Mode_PFVOL_0dB             0x00
#define Digital_Filter_Mode_PFVOL_6dB             0x10
#define Digital_Filter_Mode_PFVOL_12dB            0x20
#define Digital_Filter_Mode_PFVOL_18dB            0x30

typedef enum {
    DigitFiltSlct1_HPFAD_OFF =   (uint8_t)Digital_Filter_Select1_HPFAD,
    DigitFiltSlct1_HPFAD_ON  = ~((uint8_t)Digital_Filter_Select1_HPFAD)     
}
DigitFiltSlct1_HPFAD_T;

typedef enum {
    DigitFiltSlct1_HPFC_3Hz7   =   (uint8_t)Digital_Filter_Select1_HPFC_3Hz7,
    DigitFiltSlct1_HPFC_14Hz8  =   (uint8_t)Digital_Filter_Select1_HPFC_14Hz8,
    DigitFiltSlct1_HPFC_118Hz4 =   (uint8_t)Digital_Filter_Select1_HPFC_118Hz4,
    DigitFiltSlct1_HPFC_236Hz8 =   (uint8_t)Digital_Filter_Select1_HPFC_236Hz8
}
DigitFiltSlct1_HPFC_T;

typedef enum {
    DigitFiltSlct2_HPF_ON  =   (uint8_t)Digital_Filter_Select2_HPF,
    DigitFiltSlct2_HPF_OFF = ~((uint8_t)Digital_Filter_Select2_HPF)     
}
DigitFiltSlct2_HPF_T;

typedef enum {
    DigitFiltSlct2_LPF_ON  =   (uint8_t)Digital_Filter_Select2_LPF,
    DigitFiltSlct2_LPF_OFF = ~((uint8_t)Digital_Filter_Select2_LPF)     
}
DigitFiltSlct2_LPF_T;

typedef enum {
    DigitFiltSlct3_EQ1_Enable  =   (uint8_t)Digital_Filter_Select3_EQ1,
    DigitFiltSlct3_EQ1_Disable = ~((uint8_t)Digital_Filter_Select3_EQ1)     
}
DigitFiltSlct3_EQ1_T;

typedef enum {
    DigitFiltSlct3_EQ2_Enable  =   (uint8_t)Digital_Filter_Select3_EQ2,
    DigitFiltSlct3_EQ2_Disable = ~((uint8_t)Digital_Filter_Select3_EQ2)     
}
DigitFiltSlct3_EQ2_T;

typedef enum {
    DigitFiltSlct3_EQ3_Enable  =   (uint8_t)Digital_Filter_Select3_EQ3,
    DigitFiltSlct3_EQ3_Disable = ~((uint8_t)Digital_Filter_Select3_EQ3)     
}
DigitFiltSlct3_EQ3_T;

typedef enum {
    DigitFiltSlct3_EQ4_Enable  =   (uint8_t)Digital_Filter_Select3_EQ4,
    DigitFiltSlct3_EQ4_Disable = ~((uint8_t)Digital_Filter_Select3_EQ4)     
}
DigitFiltSlct3_EQ4_T;

typedef enum {
    DigitFiltSlct3_EQ5_Enable  =   (uint8_t)Digital_Filter_Select3_EQ5,
    DigitFiltSlct3_EQ5_Disable = ~((uint8_t)Digital_Filter_Select3_EQ5)     
}
DigitFiltSlct3_EQ5_T;

typedef enum {
    DigitalFilterMode_PFSDO_ADC  =   (uint8_t)Digital_Filter_Mode_PFSDO,
    DigitalFilterMode_PFSDO_DigitBlk  = ~((uint8_t)Digital_Filter_Mode_PFSDO)     
}
DigitalFilterMode_PFSDO_T;

typedef enum {
    DigitalFilterMode_ADCPF_SDTI       =   (uint8_t)Digital_Filter_Mode_ADCPF,
    DigitalFilterMode_ADCPF_ADC = ~((uint8_t)Digital_Filter_Mode_ADCPF)     
}
DigitalFilterMode_ADCPF_T;

typedef enum {
    DigitalFilterMode_PFDAC_SDTI =   (uint8_t)Digital_Filter_Mode_PFDAC_SDTI,
    DigitalFilterMode_PFDAC_PFVOL  =   (uint8_t)Digital_Filter_Mode_PFDAC_PFVOL,
    DigitalFilterMode_PFDAC_SDTInPFVOL  =   (uint8_t)Digital_Filter_Mode_PFDAC_SDTInPFVOL
}
DigitalFilterMode_PFDAC_T;

typedef enum {
    DigitalFilterMode_PFVOL_0dB  =   (uint8_t)Digital_Filter_Mode_PFVOL_0dB,
    DigitalFilterMode_PFVOL_6dB  =   (uint8_t)Digital_Filter_Mode_PFVOL_6dB,
    DigitalFilterMode_PFVOL_12dB =   (uint8_t)Digital_Filter_Mode_PFVOL_12dB,
    DigitalFilterMode_PFVOL_18dB =   (uint8_t)Digital_Filter_Mode_PFVOL_18dB

}
DigitalFilterMode_PFVOL_T;


/*
 * HPF2*************************************************************************
 **/
typedef struct {
    __IO uint8_t Co_efficient0;    
    __IO uint8_t Co_efficient1;    
    __IO uint8_t Co_efficient2;    
    __IO uint8_t Co_efficient3;    
}
HPF2_T;

// HPF2 Registers Address
#define HPF2_Co_efficient0_Address        0x19
#define HPF2_Co_efficient1_Address        0x1A
#define HPF2_Co_efficient2_Address        0x1B
#define HPF2_Co_efficient3_Address        0x1C

//HPF2 Registers Initial Value
#define HPF2_Co_efficient0_InitVal        0xB0
#define HPF2_Co_efficient1_InitVal        0x1F
#define HPF2_Co_efficient2_InitVal        0x9C
#define HPF2_Co_efficient3_InitVal        0x20


/*
 *LPF***************************************************************************
 **/
typedef struct {
    __IO uint8_t Co_efficient0;    
    __IO uint8_t Co_efficient1;    
    __IO uint8_t Co_efficient2;
    __IO uint8_t Co_efficient3;    
}
LPF_T;

//LPF Registers Address
#define LPF_Co_efficient0_Address        0x1D
#define LPF_Co_efficient1_Address        0x1E
#define LPF_Co_efficient2_Address        0x1F
#define LPF_Co_efficient3_Address        0x20

//LPF Registers Initial Value
#define LPF_Co_efficient0_InitVal        0x00
#define LPF_Co_efficient1_InitVal        0x00
#define LPF_Co_efficient2_InitVal        0x00
#define LPF_Co_efficient3_InitVal        0x00


/*
 * E1 / E2 / E3 / E4 / E5   ***************************************************
 */
typedef struct{
    __IO uint8_t Co_efficient0;
    __IO uint8_t Co_efficient1;
    __IO uint8_t Co_efficient2;
    __IO uint8_t Co_efficient3;
    __IO uint8_t Co_efficient4;
    __IO uint8_t Co_efficient5;
}
E_T;

//E1 / E2 / E3 / E4 / E5  Registers Address
#define E1_Co_efficient0_Address        0x22
#define E1_Co_efficient1_Address        0x23
#define E1_Co_efficient2_Address        0x24
#define E1_Co_efficient3_Address        0x25
#define E1_Co_efficient4_Address        0x26
#define E1_Co_efficient5_Address        0x27
#define E2_Co_efficient0_Address        0x28
#define E2_Co_efficient1_Address        0x29
#define E2_Co_efficient2_Address        0x2A
#define E2_Co_efficient3_Address        0x2B
#define E2_Co_efficient4_Address        0x2C
#define E2_Co_efficient5_Address        0x2D
#define E3_Co_efficient0_Address        0x2E
#define E3_Co_efficient1_Address        0x2F
#define E3_Co_efficient2_Address        0x30
#define E3_Co_efficient3_Address        0x31
#define E3_Co_efficient4_Address        0x32
#define E3_Co_efficient5_Address        0x33
#define E4_Co_efficient0_Address        0x34
#define E4_Co_efficient1_Address        0x35
#define E4_Co_efficient2_Address        0x36
#define E4_Co_efficient3_Address        0x37
#define E4_Co_efficient4_Address        0x38
#define E4_Co_efficient5_Address        0x39
#define E5_Co_efficient0_Address        0x3A
#define E5_Co_efficient1_Address        0x3B
#define E5_Co_efficient2_Address        0x3C
#define E5_Co_efficient3_Address        0x3D
#define E5_Co_efficient4_Address        0x3E
#define E5_Co_efficient5_Address        0x3F

// E1 / E2 / E3 / E4 / E5 Registers Initial Value
#define E1_Co_efficient1_InitVal        0x00
#define E1_Co_efficient2_InitVal        0x00
#define E1_Co_efficient3_InitVal        0x00
#define E1_Co_efficient4_InitVal        0x00
#define E1_Co_efficient5_InitVal        0x00
#define E2_Co_efficient0_InitVal        0x00
#define E2_Co_efficient1_InitVal        0x00
#define E2_Co_efficient2_InitVal        0x00
#define E2_Co_efficient3_InitVal        0x00
#define E2_Co_efficient4_InitVal        0x00
#define E2_Co_efficient5_InitVal        0x00
#define E3_Co_efficient0_InitVal        0x00
#define E3_Co_efficient1_InitVal        0x00
#define E3_Co_efficient2_InitVal        0x00
#define E3_Co_efficient3_InitVal        0x00
#define E3_Co_efficient4_InitVal        0x00
#define E3_Co_efficient5_InitVal        0x00
#define E4_Co_efficient0_InitVal        0x00
#define E4_Co_efficient1_InitVal        0x00
#define E4_Co_efficient2_InitVal        0x00
#define E4_Co_efficient3_InitVal        0x00
#define E4_Co_efficient4_InitVal        0x00
#define E4_Co_efficient5_InitVal        0x00
#define E5_Co_efficient0_InitVal        0x00
#define E5_Co_efficient1_InitVal        0x00
#define E5_Co_efficient2_InitVal        0x00
#define E5_Co_efficient3_InitVal        0x00
#define E5_Co_efficient4_InitVal        0x00
#define E5_Co_efficient5_InitVal        0x00


#endif  //_AK4637_Register_h_

/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/