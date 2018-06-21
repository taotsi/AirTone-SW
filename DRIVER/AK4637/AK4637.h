/*******************************************************************************
 * Brief:   Library for AK4637EN, run on STM8L15x
 * Author:  ZhiYe
 * Update:  2017.04.04
 *******************************************************************************/
#ifndef _AK4637_H_
#define _AK4637_H_

#include "stm8l15x_conf.h"
#include "AK4637_Register.h"
#include "BSP.h"

/* Macros ---------------------------------------------------------------------*/
#define PORT_STM8_4637          GPIOD
#define PIN_STM8_4637_PDN       GPIO_Pin_7
#define PIN_STM8_4637_LD        GPIO_Pin_6 // line direction, for ADG849 the CMOS switch

#define AK4637_Addr    0x12

/* AK4637EN Controling Pin Macros */
#define AK4637_PDN_H()          PORT_STM8_4637->ODR |= (uint8_t)  PIN_STM8_4637_PDN
#define AK4637_PDN_L()          PORT_STM8_4637->ODR &= (uint8_t)(~PIN_STM8_4637_PDN)

#define AK4637_LD_LineIN()      PORT_STM8_4637->ODR |= (uint8_t)  PIN_STM8_4637_LD  // high
#define AK4637_LD_LineOUT()     PORT_STM8_4637->ODR &= (uint8_t)(~PIN_STM8_4637_LD) // low


/* Type Defination ------------------------------------------------------------*/
typedef enum
{  
    ADC_DigitalBlock    = (uint8_t)0x01 ,
    DAC_DigitalBlock    = (uint8_t)0x02 ,
    ADC_No_DigitalBlock = (uint8_t)0x03 ,
    DAC_No_DigitalBlock = (uint8_t)0x04 ,
    LoopBack            = (uint8_t)0x05
}
AK4637_SignalPath_T;


/* Functions ------------------------------------------------------------------*/
/* I2C Command *****************************************************************/
void AK4637_Write_Reg(uint8_t RegAddr, uint8_t Value);
uint8_t AK4637_Read_Reg(uint8_t RegAddr);

/* Initialization **************************************************************/
void AK4637_Init();

/* temp area *******************************************************************/
void AK4637_SysClk(PwMng2_PMPLL_T PMPLL,
                   PwMng2_MS_T MS);
                   
void AK4637_SignalPath(AK4637_SignalPath_T path);


/* Power management ************************************************************/

void AK4637_PwMng_ADC(PwMng1_PMADC_T PMADC);
void AK4637_PwMng_DAC(PwMng1_PMDAC_T PMDAC);
void AK4637_PwMng_BeepInput(PwMng1_PMBP_T PMBP);
void AK4637_PwMng_VCM(PwMng1_PMVCM_T PMVCM);
void AK4637_PwMng_PFIL(PwMng1_PMPFIL_T PMPFIL);
void AK4637_PwMng_SpkAmp(PwMng2_PMSL_T PMSL);

void AK4637_MonoOut_Select(PwMng1_LOSEL_T LOSEL);


/* Signal Select ***************************************************************/
void AK4637_MicGain(SgnlSlct1_MGAIN_T MAGIN);
void AK4637_MPWR_PwMng(SgnlSlct1_PMMP_T PMMP);
void AK4637_DAC_to_Sperker(SgnlSlct1_DACS_T DACS);
void AK4637_SL_PwSave(SgnlSlct1_SLPSN_T SLPSN);
void AK4637_MPWROutPut(SgnlSlct2_MICL_T MICL);
void AK4637_SPK_AmpOutputLevel(SgnlSlct2_SPKG_T SPKG);
void AK4637_ADC_Select(SgnlSlct2_MDIF_T MDIF);
void AK4637_MonoLineOutput_Volume(SgnlSlct3_LVCM_T LVCM);
void AK4637_DAC_to_Line(SgnlSlct3_DACL_T DACL);


/* Mode Control ****************************************************************/

void AK4637_Mode_Control1(MdCtrl1_PLL_T PllMode,
                          MdCtrl1_CKOFF_T CKOFF,
                          MdCtrl1_BCKO_T BckoMode);
/*
void AK4637_AudioClk(MdCtrl2_CM_T CMMode,
                     MdCtrl2_FS_T FSMode);
void AK4637_AudioFormat(MdCtrl3_MSBS_T MSBS, 
                        MdCtrl3_MSBS_T MSBS,
                        MdCtrl3_DIF_T DIF);
*/
void AK4637_Mode_Control3_1(MdCtrl3_SMUTE_T SMUTE,
                            MdCtrl3_THDET_T THDET,
                            MdCtrl3_TSDSEL_T TSDSEL);

void AK4637_AudioFormat(MdCtrl3_DIF_T DIF, 
                        MdCtrl2_FS_T fs, 
                        MdCtrl2_CM_T MCLK,
                        MdCtrl3_MSBS_T MSBS,
                        MdCtrl3_BCKP_T BCKP);

    
    
/* DigitMIC ******************************************************************/                          
void AK4637_DigitMIC_Select(DigitMIC_DMIC_T DMIC);
void AK4637_DigitMIC_CPOL(DigitMIC_DCLKP_T DCLKP);
void AK4637_DigitMIC_MCLK(DigitMIC_DCLKE_T DCLKE);
void AK4637_PwMng_DigitMIC(DigitMIC_PMDM_T PMDM);


/* ALC Operation ***************************************************************/
void AK4637_OutputTransitionTime(TimerSelect_DVTM_T DVTM);
void AK4637_TimerSelect(TimerSelect_FRN_T FRN,
                        TimerSelect_RFATT_T RFATT,
                        TimerSelect_ADRST_T ADRST);                   
void AK4637_ALC_TimerSelect(ALC_TimerSelect_IVTM_T IVTM,
                            ALC_TimerSelect_EQFC_T EQFC,
                            ALC_TimerSelect_WTM_T WTM,
                            ALC_TimerSelect_RFST_T RFST);
void AK4637_ALC_MdCtrl1(ALC_MdCtrl1_ALCEQN_T ALCEQ,
                             ALC_MdCtrl1_LMTH_T LMTH,
                             ALC_MdCtrl1_RGAIN_T RGAIN);
void AK4637_ALC_Enable(ALC_MdCtrl1_ALC_T ALC);
void AK4637_ALC_MdCtrl2(uint8_t REF);
void AK4637_Input_VolumeControl(uint8_t IVOL);
uint8_t AK4637_ALC_Volume(void);


/* BEEP Control ***************************************************************/
void AK4637_Beep_AmpCommonVoltage(BEEPControl_BPVCM_T BPVCM,
                                  BEEPControl_BEEPS_T BEEPS,
                                  BEEPControl_BPLVL_T BPLVL);
                                
/* Digital_Volume *************************************************************/                                
void AK4637_Digital_VolumeControl(uint8_t DVOL);


/* EQ *************************************************************************/
void AK4637_EQ_CommenGain_Select(EQ_CommonGainSelect_EQC2_T EQC2,
                                 EQ_CommonGainSelect_EQC3_T EQC3,
                                 EQ_CommonGainSelect_EQC4_T EQC4,
                                 EQ_CommonGainSelect_EQC5_T EQC5);
void AK4637_EQ2_GainSetting(uint8_t EQ2G,
                            EQn_GainSetting_EQnT_T EQnT);
void AK4637_EQ3_GainSetting(uint8_t EQ3G,
                            EQn_GainSetting_EQnT_T EQnT);
void AK4637_EQ4_GainSetting(uint8_t EQ4G,
                            EQn_GainSetting_EQnT_T EQnT);
void AK4637_EQ5_GainSetting(uint8_t EQ5G,
                            EQn_GainSetting_EQnT_T EQnT);
                          
                          
/*Programmable Filter *********************************************************/                          
void AK4637_DigitFilt_HPF1(DigitFiltSlct1_HPFAD_T HPFAD,
                           DigitFiltSlct1_HPFC_T HPFC);
void AK4637_DigitFiltSlct2(DigitFiltSlct2_HPF_T HPF,
                           DigitFiltSlct2_LPF_T LPF);
void AK4637_Digital_Filter_Select3(DigitFiltSlct3_EQ1_T EQ1,
                                   DigitFiltSlct3_EQ2_T EQ2,
                                   DigitFiltSlct3_EQ3_T EQ3,
                                   DigitFiltSlct3_EQ4_T EQ4,
                                   DigitFiltSlct3_EQ5_T EQ5);
void AK4637_RecordingPlaybackMode(DigitalFilterMode_ADCPF_T ADCPF,
                                  DigitalFilterMode_PFDAC_T PFDAC,
                                  DigitalFilterMode_PFSDO_T PFSDO);
void AK4637_SidetoneDigitalVolume(DigitalFilterMode_PFVOL_T PFVOL);
void AK4637_HPF2_Coefficient(uint8_t HPF2_Cofficient[4]);
void AK4637_LPF_Coefficient(uint8_t LPF_Cofficient[4]);
void AK4637_EQ_Coefficient(uint8_t E_Cofficient[30]);

#endif
/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/