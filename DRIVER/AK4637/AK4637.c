/*******************************************************************************
 * Brief:   Library for AK4637EN, run on STM8L15x
 * Author:  ZhiYe
 * Update:  2017.04.04
 *******************************************************************************/
 
#include "AK4637.h"


/*------------------------------------------------------------------ *
 *                          I2C Command                              *
 *------------------------------------------------------------------ */

/**
  * Brief  Write one byte to one single register
  * Param  Addr: Address of the register
  *         Value: Value you want to write to the register
  * RetVal None:
  */
void AK4637_Write_Reg(uint8_t RegAddr, uint8_t RegVal)
{
    //SDA_IT_DISABLE();
    
    //I2C_IOsim_Send_TwoBytes(AK4637_Address_W, Addr, Value);
    
    I2Csim_START();
    
    I2Csim_Send_Byte(I2C_Address_4637_W, ACK_ENABLE);
    I2Csim_Send_Byte(RegAddr, ACK_ENABLE);
    I2Csim_Send_Byte(RegVal, ACK_ENABLE);
    
    I2Csim_STOP();
    
    //SDA_IT_ENABLE();
}


/**
  * Brief  Read one byte from one single register
  * Param  Addr: Address of the register
  * RetVal Register value
  */
uint8_t AK4637_Read_Reg(uint8_t RegAddr)
{
    //SDA_IT_DISABLE();
    
    uint8_t RegVal = 0;
    
    //RegVal = I2C_IOsim_Receive_OneByte(Addr);
    
    I2Csim_START();
    
    I2Csim_Send_Byte(I2C_Address_4637_W, ACK_ENABLE);
    I2Csim_Send_Byte(RegAddr, ACK_ENABLE);
    
    I2Csim_START();
    
    I2Csim_Send_Byte(I2C_Address_4637_R, ACK_ENABLE);
    RegVal = I2Csim_Receive_Byte(ACK_DISABLE);
    
    I2Csim_STOP();
    
    //SDA_IT_ENABLE();
    
    return RegVal;
}

/* Initialization **************************************************************/

/**
  *
  *
  */
void AK4637_Init()
{
    AK4637_PDN_L();
    Delay_ms(300);
    AK4637_PDN_H();
    
    /* Dummy command, write 0 to 00h, to set all registers to initial value. */
    AK4637_Write_Reg(0x00, 0);
    
    /* System clock configuration. */
    AK4637_SysClk(PwMng2_PMPLL_PowerDown, PwMng2_MS_Slave);
    
    AK4637_AudioFormat(MdCtrl3_DIF_I2S, 
                       MdCtrl2_FS_48kHz,
                       MdCtrl2_CM_512fs,
                       MdCtrl3_MSBS_HalfClk,     // no use in I2S mode
                       MdCtrl3_BCKP_RisingEdge); // no use in I2S mode
    
    AK4637_Mode_Control1(MdCtrl1_PPL_NA, MdCtrl1_CKOUT, MdCtrl1_BCKO_16fs);
    
    /* Power up VCOM and Regulator */
    AK4637_PwMng_VCM(PwMng1_PMVCM_PowerUp);
    Delay_ms(10);
    
    
}


/* Temporary Area **************************************************************/

/**
  * Brief  
  * Param  PMPLL: PLL Power Management
  *            PwMng2_PMPLL_PowerUp
  *            PwMng2_PMPLL_PowerDown (default)
  * Param  M_S: Master/Slave Mode Select
  *            PwMng2_MS_Master
  *            PwMng2_MS_Slave (default)
  * RetVal None
  */ 
void AK4637_SysClk(PwMng2_PMPLL_T PMPLL,
                         PwMng2_MS_T MS)
{
    uint8_t Reg = AK4637_Read_Reg(PwMng2_Address);
    Reg |= ((uint8_t)PMPLL | (uint8_t)MS);
    AK4637_Write_Reg(PwMng2_Address, Reg);
}


/**
  * Brief： 
  * Param:  ADC_DigitalBlock:
  *         DAC_DigitalBlock:
  *         ADC_No_DigitalBlock:
  *         DAC_No_DigitalBlock:
  *         LoopBack: with digital block.
  *                     NOTE:this is not avalible on the prototype board v2
  * TODO:   add mic-in and spk-out options
  */
void AK4637_SignalPath(AK4637_SignalPath_T path)
{
    AK4637_PwMng_PFIL(PwMng1_PMPFIL_PowerDown);
    
    AK4637_DigitMIC_Select(DigitMIC_DMIC_AnalogMIC);
    
    
    switch(path)
    {
        case ADC_DigitalBlock:
            AK4637_PwMng_DAC(PwMng1_PMDAC_PowerDown);
            
            /* Line in */
            AK4637_ADC_Select(SgnlSlct2_MDIF_SingleEnded);
            AK4637_MicGain(SgnlSlct1_MGAIN_18dB);
            AK4637_LD_LineIN();
            
            /* ADC part */
            AK4637_PwMng_ADC(PwMng1_PMADC_PowerUp);
            AK4637_DigitFilt_HPF1(DigitFiltSlct1_HPFAD_ON,
                                  DigitFiltSlct1_HPFC_3Hz7);
            
            AK4637_RecordingPlaybackMode(DigitalFilterMode_ADCPF_ADC,
                                         DigitalFilterMode_PFDAC_SDTI,
                                         DigitalFilterMode_PFSDO_DigitBlk);
            
            AK4637_PwMng_PFIL(PwMng1_PMPFIL_PowerUp);
            break;
            
        case DAC_DigitalBlock:
            AK4637_PwMng_ADC(PwMng1_PMADC_PowerDown);
            
            /* DAC part */
            AK4637_PwMng_DAC(PwMng1_PMDAC_PowerUp);
            // DVOL and SMUTE settings are ignored. the default values are just good.
            AK4637_DAC_to_Line(SgnlSlct3_DACL_ON);
            
            /* Line out */
            // the order of the codes below must be obeyed, to reduce pop noise
            AK4637_MonoOut_Select(PwMng1_LOSEL_LineOut);
            AK4637_PwMng_SpkAmp(PwMng2_PMSL_PowerUp);
            AK4637_SL_PwSave(SgnlSlct1_SLPSN_Normal);
            AK4637_LD_LineOUT();
            
            AK4637_RecordingPlaybackMode(DigitalFilterMode_ADCPF_SDTI,
                                         DigitalFilterMode_PFDAC_PFVOL,
                                         DigitalFilterMode_PFSDO_ADC);
            
            // the setting of PFVOL is ignored. It's just fine by its default value.
                        
            AK4637_PwMng_PFIL(PwMng1_PMPFIL_PowerUp);
            break;
            
        case ADC_No_DigitalBlock:
            AK4637_PwMng_DAC(PwMng1_PMDAC_PowerDown);
            
            /* Line in */
            AK4637_ADC_Select(SgnlSlct2_MDIF_SingleEnded);
            AK4637_MicGain(SgnlSlct1_MGAIN_18dB);
            AK4637_LD_LineIN();
            
            /* ADC part */
            AK4637_PwMng_ADC(PwMng1_PMADC_PowerUp);
            AK4637_DigitFilt_HPF1(DigitFiltSlct1_HPFAD_ON,
                                  DigitFiltSlct1_HPFC_3Hz7);
            
            AK4637_RecordingPlaybackMode(DigitalFilterMode_ADCPF_ADC,
                                         DigitalFilterMode_PFDAC_SDTI,
                                         DigitalFilterMode_PFSDO_ADC);
            
            break;
            
        case DAC_No_DigitalBlock:
            AK4637_PwMng_ADC(PwMng1_PMADC_PowerDown);
        
            /* DAC part */
            AK4637_PwMng_DAC(PwMng1_PMDAC_PowerUp);
            // DVOL and SMUTE settings are ignored. the default values are just good.
            AK4637_DAC_to_Line(SgnlSlct3_DACL_ON);
            
            /* Line out */
            // the order of the codes below must be obeyed, to reduce pop noise
            AK4637_MonoOut_Select(PwMng1_LOSEL_LineOut);
            AK4637_PwMng_SpkAmp(PwMng2_PMSL_PowerUp);
            AK4637_SL_PwSave(SgnlSlct1_SLPSN_Normal);
            AK4637_LD_LineOUT();
            
            AK4637_RecordingPlaybackMode(DigitalFilterMode_ADCPF_SDTI,
                                         DigitalFilterMode_PFDAC_SDTI,
                                         DigitalFilterMode_PFSDO_ADC);
            
            break;
            
        case LoopBack:
            
            /* Line in */
            AK4637_ADC_Select(SgnlSlct2_MDIF_SingleEnded);
            AK4637_MicGain(SgnlSlct1_MGAIN_18dB);
            
            /* ADC part */
            AK4637_PwMng_ADC(PwMng1_PMADC_PowerUp);
            AK4637_DigitFilt_HPF1(DigitFiltSlct1_HPFAD_ON,
                                  DigitFiltSlct1_HPFC_3Hz7);
            
            /* DAC part */
            AK4637_PwMng_DAC(PwMng1_PMDAC_PowerUp);
            // DVOL and SMUTE settings are ignored. the default values are just good.
            AK4637_DAC_to_Line(SgnlSlct3_DACL_ON);
            
            /* Line out */
            // the order of the codes below must be obeyed, to reduce pop noise
            AK4637_MonoOut_Select(PwMng1_LOSEL_LineOut);
            AK4637_PwMng_SpkAmp(PwMng2_PMSL_PowerUp);
            AK4637_SL_PwSave(SgnlSlct1_SLPSN_Normal);
            
            AK4637_RecordingPlaybackMode(DigitalFilterMode_ADCPF_ADC,
                                         DigitalFilterMode_PFDAC_PFVOL,
                                         DigitalFilterMode_PFSDO_DigitBlk);
            
            // the setting of PFVOL is ignored. It's just fine by its default value.
            
            AK4637_PwMng_PFIL(PwMng1_PMPFIL_PowerUp);
            break;
            
        default:
            oPrint(">Error:wrong parameter for AK4637_SignalPath()!");
            break;
    }
}


/* Power Management Functions **************************************************/
// Note: Not all power management functions are here.
 
/**
  * Brief  Microphone Amplifier and ADC Power Management
  * Param  PMADC:
  *            PwMng1_PMADC_PowerUp
  *            PwMng1_PMADC_PowerDown (default)
  * RetVal None
  */ 
void AK4637_PwMng_ADC(PwMng1_PMADC_T PMADC)
{
    uint8_t Reg = AK4637_Read_Reg(PwMng1_Address);
    Reg |= PMADC;
    AK4637_Write_Reg(PwMng1_Address, Reg);                                 
}

/**
  * Brief  DAC Power Management
  * Param  PMDAC:
  *            PwMng1_PMDAC_PowerUp
  *            PwMng1_PMADC_PowerDown (default)
  * RetVal None
  */ 
void AK4637_PwMng_DAC(PwMng1_PMDAC_T PMDAC)
{
    uint8_t Reg = AK4637_Read_Reg(PwMng1_Address);
    Reg |= PMDAC;
    AK4637_Write_Reg(PwMng1_Address, Reg);
}


/**
  * Brief  BEEP Input Select and Power Management
  * Param  PMBP:
  *            PwMng1_PMBP_PowerUp
  *            PwMng1_PMBP_PowerDown (default)
  * RetVal None
  */ 
void AK4637_PwMng_BeepInput(PwMng1_PMBP_T PMBP)
{
    uint8_t Reg = AK4637_Read_Reg(PwMng1_Address);
    Reg |= PMBP;
    AK4637_Write_Reg(PwMng1_Address, Reg);
}


/**
  * Brief  VCOM and Regulator (2.3V) Power Management
  * Param  PMVCM:
  *            PwMng1_PMVCM_PowerUp
  *            PwMng1_PMVCM_PowerDown (default)
  * RetVal None
  */ 
void AK4637_PwMng_VCM(PwMng1_PMVCM_T PMVCM)
{
    uint8_t Reg = AK4637_Read_Reg(PwMng1_Address);
    Reg |= PMVCM;
    AK4637_Write_Reg(PwMng1_Address, Reg);
}

/**
  * Brief  Programmable Filter Block Power Management
  * Param  PMPFIL:
  *            PwMng1_PMPFIL_PowerUp
  *            PwMng1_PMPFIL_PowerDown (default)
  * RetVal None
  */ 
void AK4637_PwMng_PFIL(PwMng1_PMPFIL_T PMPFIL)
{
    uint8_t Reg = AK4637_Read_Reg(PwMng1_Address);
    Reg |= PMPFIL;
    AK4637_Write_Reg(PwMng1_Address, Reg);
}


/**
  * Brief  Speaker Amplifier or Mono Line Output Power Management
  * Param  PMSL:

  *            PwMng2_PMSL_PowerUp
  *            PwMng2_PMSL_PowerDown (default)
  * RetVal None
  */ 
void AK4637_PwMng_SpkAmp(PwMng2_PMSL_T PMSL)
{
    uint8_t Reg = AK4637_Read_Reg(PwMng2_Address);
    Reg |= PMSL;
    AK4637_Write_Reg(PwMng2_Address, Reg);
}




/**
  * Brief  Mono Line Output Select
  * Param  LOSEL:
  *            PwMng1_LOSEL_LineOut
  *            PwMng1_LOSEL_SpeakerOut (default)
  * RetVal None
  */ 
void AK4637_MonoOut_Select(PwMng1_LOSEL_T LOSEL)
{
    uint8_t Reg = AK4637_Read_Reg(PwMng1_Address);
    Reg |= LOSEL;
    AK4637_Write_Reg(PwMng1_Address, Reg);
}




/*---------------------------------------------------------------- *
 *                        02   SgnlSlct1                       *
 *---------------------------------------------------------------- */

/**
  * Brief  Microphone Amplifier Gain Control
  * Param  MAGIN:
  *            SgnlSlct1_MGAIN_0dB
  *            SgnlSlct1_MGAIN_3dB
  *            SgnlSlct1_MGAIN_6dB
  *            SgnlSlct1_MGAIN_9dB
  *            SgnlSlct1_MGAIN_12dB
  *            SgnlSlct1_MGAIN_15dB
  *            SgnlSlct1_MGAIN_18dB (default)
  *            SgnlSlct1_MGAIN_21dB
  *            SgnlSlct1_MGAIN_24dB
  *            SgnlSlct1_MGAIN_27dB
  *            SgnlSlct1_MGAIN_30dB
  * RetVal None
  */ 
void AK4637_MicGain(SgnlSlct1_MGAIN_T MAGIN)
{
    uint8_t Reg = AK4637_Read_Reg(SgnlSlct1_Address);
    Reg |= MAGIN;
    AK4637_Write_Reg(SgnlSlct1_Address, Reg);    
}


/**
  * Brief  MPWR pin Power Managemen
  * Param  PMMP:
  *            SgnlSlct1_PMMP_PowerUp
  *            SgnlSlct1_PMMP_PowerDown (default)
  * RetVal None
  */ 
void AK4637_MPWR_PwMng(SgnlSlct1_PMMP_T PMMP)
{
    uint8_t Reg = AK4637_Read_Reg(SgnlSlct1_Address);
    Reg |= PMMP;
    AK4637_Write_Reg(SgnlSlct1_Address, Reg);                                 
}


/**
  * Brief  Signal Switch Control from DAC to Speaker Amplifier
  * Param  DACS:
  *            SgnlSlct1_DACS_ON
  *            SgnlSlct1_DACS_OFF (default)
  * RetVal None
  */ 
void AK4637_DAC_to_Sperker(SgnlSlct1_DACS_T DACS)
{
    uint8_t Reg = AK4637_Read_Reg(SgnlSlct1_Address);
    Reg |= DACS;
    AK4637_Write_Reg(SgnlSlct1_Address, Reg);                             
}


/**
  * Brief  Speaker Amplifier or Mono Line Output Power-Save Mode
  * Param  SLPSN:
  *            SgnlSlct1_SLPSN_Normal
  *            SgnlSlct1_SLPSN_PowerSave (default)
  * RetVal None
  */ 
void AK4637_SL_PwSave(SgnlSlct1_SLPSN_T SLPSN)
{
    uint8_t Reg = AK4637_Read_Reg(SgnlSlct1_Address);
    Reg |= SLPSN;
    AK4637_Write_Reg(SgnlSlct1_Address, Reg);                                 
}


/*---------------------------------------------------------------- *
 *                        03  Signal Select 2                      *
 *---------------------------------------------------------------- */

/**
  * Brief  MPWR pin Output Voltage Select
  * Param  MICL:
  *            SgnlSlct2_MICL_2_0V
  *            SgnlSlct2_MICL_2_4V (default)
  * RetVal None
  */ 
void AK4637_MPWROutPut(SgnlSlct2_MICL_T MICL)
{
    uint8_t Reg = AK4637_Read_Reg(SgnlSlct2_Address);
    Reg |= MICL;
    AK4637_Write_Reg(SgnlSlct2_Address, Reg); 
}


/**
  * Brief  Speaker Amplifier Output Gain Select
  * Param  SPKG:
  *            SgnlSlct2_SPKG_8_4dB
  *            SgnlSlct2_SPKG_11_1dB
  *            SgnlSlct2_SPKG_6_4dB (default)
  *            SgnlSlct2_SPKG_14_9dB
  * RetVal None
  */ 
void AK4637_SPK_AmpOutputLevel(SgnlSlct2_SPKG_T SPKG)
{
    uint8_t Reg = AK4637_Read_Reg(SgnlSlct2_Address);
    Reg |= SPKG;
    AK4637_Write_Reg(SgnlSlct2_Address, Reg); 
}
 
 
/**
  * Brief  ADC Input Source Select
  * Param  MDIF:
  *            SgnlSlct2_MDIF_SingleEnded (default)
  *            SgnlSlct2_MDIF_Differential
  * RetVal None
  */ 
void AK4637_ADC_Select(SgnlSlct2_MDIF_T MDIF)
{
    uint8_t Reg = AK4637_Read_Reg(SgnlSlct2_Address);
    Reg |= MDIF;
    AK4637_Write_Reg(SgnlSlct2_Address, Reg); 
}
 
 
/*---------------------------------------------------------------- *
 *                    04 Signal Select 3                       *
 *---------------------------------------------------------------- */ 

/**
  * Brief  Mono Line Output Gain and Common Voltage Setting
  * Param  LVCM:
  *            SgnlSlct3_LVCM_0dB_1_3
  *            SgnlSlct3_LVCM_2dB_1_5 (default)
  *            SgnlSlct3_LVCM_2dB_1_3
  *            SgnlSlct3_LVCM_4dB_1_5
  * RetVal None
  */ 
void AK4637_MonoLineOutput_Volume(SgnlSlct3_LVCM_T LVCM)
{
    uint8_t Reg = AK4637_Read_Reg(SgnlSlct3_Address);
    Reg |= LVCM;
    AK4637_Write_Reg(SgnlSlct3_Address, Reg);
}  


/**
  * Brief  Signal Switch Control from DAC to Mono Line Amplifier
  * Param  DACL:
  *            SgnlSlct3_DACL_ON
  *            SgnlSlct3_DACL_OFF (default)
  * RetVal None
  */ 
void AK4637_DAC_to_Line(SgnlSlct3_DACL_T DACL)
{
    uint8_t Reg = AK4637_Read_Reg(SgnlSlct3_Address);
    Reg |= DACL;
    AK4637_Write_Reg(SgnlSlct3_Address, Reg);                             
}

 
/*------------------------------------------------------------------ *
 *                      05/06   Mode Control                         *
 *------------------------------------------------------------------ */

/**
  * Brief  
  * Param  PllMode: PLL Reference Clock Select
  *            MdCtrl1_PPL_NA:  0x00, used for ext slave mode initialization.
  *            MdCtrl1_PLL_16fs
  *            MdCtrl1_PLL_32fs
  *            MdCtrl1_PLL_64_fs
  *            MdCtrl1_PLL_11M2896Hz
  *            MdCtrl1_PLL_12M288Hz (default)
  *            MdCtrl1_PLL_12MHz
  *            MdCtrl1_PLL_24MHz
  *            MdCtrl1_PLL_13M5Hz
  *            MdCtrl1_PLL_27MHz
  * Param  CKOFF: FCK, BICK, SDTO Output Stop Setting in Master Mode
  *            MdCtrl1_CKOFF
  *            MdCtrl1_CKOUT (default)
  * Param  BckoMode: BICK Output Frequency Setting in Master Mode
  *            MdCtrl1_BCKO_16fs (default)
  *            MdCtrl1_BCKO_32fs
  *            MdCtrl1_BCKO_64fs
  *            MdCtrl1_BCKO_N_A
  * RetVal None
  */ 
void AK4637_Mode_Control1(MdCtrl1_PLL_T PllMode,
                          MdCtrl1_CKOFF_T CKOFF,
                          MdCtrl1_BCKO_T BckoMode)
{
    AK4637_Write_Reg(MdCtrl1_Address, (uint8_t)PllMode | (uint8_t)CKOFF | (uint8_t)BckoMode);
}



/*---------------------------------------------------------------- *
 *                 07   Audio Interface Format                     *
 *---------------------------------------------------------------- */

/**
  * Brief 
  * Param  DIF: Audio Interface Format
  *            MdCtrl3_DIF_DSP
  *            MdCtrl3_DIF_24_16bitMSB
  *            MdCtrl3_DIF_24bitMSB (default)
  *            MdCtrl3_DIF_I2S: 16bit or 24bit compatible
  * Param  fs: Sampling frequency Setting
  *            MdCtrl2_FS_8kHz
  *            MdCtrl2_FS_11k025Hz
  *            MdCtrl2_FS_12kHz
  *            MdCtrl2_FS_16kHz
  *            MdCtrl2_FS_22k05Hz
  *            MdCtrl2_FS_24kHz
  *            MdCtrl2_FS_32kHz
  *            MdCtrl2_FS_44k1Hz
  *            MdCtrl2_FS_48kHz (default)
  * Param  MCLK: MCKI Input Frequency Setting in EXT mode
  *            MdCtrl2_CM_256fs (default)
  *            MdCtrl2_CM_384fs
  *            MdCtrl2_CM_512fs
  *            MdCtrl2_CM_1024fs
  * Param  MSBS: FCK Phase at DSP Mode
  *            MdCtrl3_MSBS_OneClk
  *            MdCtrl3_MSBS_HalfClk (default)
  * Param  BCKP: BICK Polarity at DSP Mode
  *            MdCtrl3_BCKP_FallingEdge
  *            MdCtrl3_BCKP_RisingEdge (default)
  *
  * RetVal None
  */ 
 void AK4637_AudioFormat(MdCtrl3_DIF_T DIF, 
                         MdCtrl2_FS_T fs, 
                         MdCtrl2_CM_T MCLK,
                         MdCtrl3_MSBS_T MSBS,
                         MdCtrl3_BCKP_T BCKP)
{
    uint8_t Reg;
    Reg = AK4637_Read_Reg(MdCtrl3_Address);
    Reg |= (uint8_t)DIF;
    AK4637_Write_Reg(MdCtrl3_Address, Reg);
    
    AK4637_Write_Reg(MdCtrl2_Address, (uint8_t)MCLK | (uint8_t)fs);
    
    if(DIF == MdCtrl3_DIF_DSP)
    {
        Reg = AK4637_Read_Reg(MdCtrl3_Address);
        Reg |= ((uint8_t)MSBS | (uint8_t)BCKP);
        AK4637_Write_Reg(MdCtrl3_Address, Reg);
    }
}


/**
  * Brief  
  * Param  SMUTE: Soft Mute Control
  *            MdCtrl3_SMUTE_SoftMute
  *            MdCtrl3_SMUTE_Normal (default)
  *
  * Param  THDET: Thermal Shutdown Detection Result
  *            MdCtrl3_THDET_ThermalShutDown
  *            MdCtrl3_THDET_Normal (default)
  *
  * Param  TSDSEL: Thermal Shutdown Mode Select
  *            MdCtrl3_TSDSEL_ManualPowerUp
  *            MdCtrl3_TSDSEL_AutomaticPowerUp (default)
  * RetVal None
  */
void AK4637_Mode_Control3_1(MdCtrl3_SMUTE_T SMUTE,
                          MdCtrl3_THDET_T THDET,
                          MdCtrl3_TSDSEL_T TSDSEL)
{
    uint8_t Reg = AK4637_Read_Reg(MdCtrl3_Address);
    Reg |= ((uint8_t)SMUTE | (uint8_t)THDET | (uint8_t)TSDSEL);
     AK4637_Write_Reg(MdCtrl3_Address, Reg);                                 
}


/*---------------------------------------------------------------- *
 *                         08   DigitMIC                         *
 *---------------------------------------------------------------- */

/**
  * Brief  Digital Microphone Connection Select
  * Param  DMIC:

  *            DigitMIC_DMIC_DigitMIC
  *            DigitMIC_DMIC_AnalogMIC (default)
  * RetVal None
  */ 
void AK4637_DigitMIC_Select(DigitMIC_DMIC_T DMIC)
{
    uint8_t Reg = AK4637_Read_Reg(DigitMIC_Address);
    Reg |= DMIC;
    AK4637_Write_Reg(DigitMIC_Address, Reg);
}


/**
  * Brief  Data Latching Edge Select
  * Param  DCLKP:

  *            DigitMIC_DCLKP_FallingEdge
  *            DigitMIC_DCLKP_RisingEdge (default)
  * RetVal None
  */ 
void AK4637_DigitMIC_CPOL(DigitMIC_DCLKP_T DCLKP)
{
     uint8_t Reg = AK4637_Read_Reg(DigitMIC_Address);
    Reg |= DCLKP;
    AK4637_Write_Reg(DigitMIC_Address, Reg);                             
}


/**
  * Brief  DMCLK pin Output Clock Control
  * Param  DCLKE:

  *            DigitMIC_DCLKE_64fsOutput
  *            DigitMIC_DCLKE_LOutput (default)
  * RetVal None
  */ 
void AK4637_DigitMIC_MCLK(DigitMIC_DCLKE_T DCLKE)
{
    uint8_t Reg = AK4637_Read_Reg(DigitMIC_Address);
    Reg |= DCLKE;
    AK4637_Write_Reg(DigitMIC_Address, Reg);                             
}


/**
  * Brief  Input Signal Select with Digital Microphone
  * Param  PMDM:

  *            DigitMIC_PMDM_ON
  *            DigitMIC_PMDM_OFF (default)
  * RetVal None
  */ 
void AK4637_PwMng_DigitMIC(DigitMIC_PMDM_T PMDM)
{
    uint8_t Reg = AK4637_Read_Reg(DigitMIC_Address);
    Reg |= PMDM;
    AK4637_Write_Reg(DigitMIC_Address, Reg);                             
}


/*---------------------------------------------------------------- *
 *                   09 Output Digital Volume                      *
 *---------------------------------------------------------------- */

/**
  * Brief  Output Digital Volume Soft Transition Time Setting
  * Param  DVTM:

  *            TimerSelect_DVTM_204_fs
  *            TimerSelect_DVTM_816_fs (default)
  * RetVal None
  */ 
void AK4637_OutputTransitionTime(TimerSelect_DVTM_T DVTM)
{
    uint8_t Reg = AK4637_Read_Reg(TimerSelect_Address);
    Reg |= DVTM;
    AK4637_Write_Reg(TimerSelect_Address, Reg);
}


/*---------------------------------------------------------------- *
 *                     09/0A/0B ALC Operation                      *
 *---------------------------------------------------------------- */

/**
  * Brief  
  * Param  FRN: ALC Fast Recovery Function Enable

  *            TimerSelect_FRN_Disable
  *            TimerSelect_FRN_Enable (default)
  *
  * Param  RFATT: Fast Recovery Reference Volume Attenuation Amount

  *            TimerSelect_RFATT_16_fs
  *            TimerSelect_RFATT_4_fs (default)
  *
  * Param  ADRST: ADC Initialization Cycle Setting

  *            TimerSelect_ADRST_1059_fs (default)
  *            TimerSelect_ADRST_267_fs
  *            TimerSelect_ADRST_531_fs
  *            TimerSelect_ADRST_135_fs
  * RetVal None
  */ 
void AK4637_TimerSelect(TimerSelect_FRN_T FRN,
                           TimerSelect_RFATT_T RFATT,
                           TimerSelect_ADRST_T ADRST)
{
    uint8_t Reg = AK4637_Read_Reg(TimerSelect_Address);
    Reg |= ((uint8_t)FRN | (uint8_t)RFATT | (uint8_t)ADRST);
    AK4637_Write_Reg(TimerSelect_Address, Reg);                                 
}


/**
  * Brief  
  * Param  IVTM: Input Digital Volume Soft Transition Time Setting
  *            ALC_TimerSelect_IVTM_236_fs
  *            ALC_TimerSelect_IVTM_944_fs (default)
  *
  * Param  EQFC: ALCEQ Frequency Setting
  *            ALC_TimerSelect_EQFC_12kHz
  *            ALC_TimerSelect_EQFC_24kHz
  *            ALC_TimerSelect_EQFC_48kHz (default)
  *            ALC_TimerSelect_EQFC_N_A
  *
  * Param  WTM: ALC Recovery Waiting Period
  *            ALC_TimerSelect_WTM_128_fs (default)
  *            ALC_TimerSelect_WTM_256_fs
  *            ALC_TimerSelect_WTM_512_fs
  *            ALC_TimerSelect_WTM_1024_fs
  *
  * Param  RFST: ALC First Recovery Speed
  *            ALC_TimerSelect_RFST_0_0032 (default)
  *            ALC_TimerSelect_RFST_0_0042
  *            ALC_TimerSelect_RFST_0_0064
  *            ALC_TimerSelect_RFST_0_0127
  * RetVal None
  */ 
void AK4637_ALC_TimerSelect(ALC_TimerSelect_IVTM_T IVTM,
                          ALC_TimerSelect_EQFC_T EQFC,
                          ALC_TimerSelect_WTM_T WTM,
                          ALC_TimerSelect_RFST_T RFST)
{
    AK4637_Write_Reg(ALC_TimerSelect_Address, (uint8_t)IVTM | (uint8_t)EQFC | (uint8_t)WTM | (uint8_t)RFST);
}


/**
  * Brief  
  * Param  ALCEQ: ALC EQ Enable 
  *            ALC_MdCtrl1_ALCEQN_OFF
  *            ALC_MdCtrl1_ALCEQN_ON (default)
  *
  * Param  LMTH: ALC Limiter Detection Level / Recovery Counter Reset Level
  *            ALC_MdCtrl1_LMTH_4_1dB (default)
  *            ALC_MdCtrl1_LMTH_3_3dB
  *            ALC_MdCtrl1_LMTH_6_0dB
  *            ALC_MdCtrl1_LMTH_5_0dB
  *            ALC_MdCtrl1_LMTH_8_5dB
  *            ALC_MdCtrl1_LMTH_7_2dB
  *            ALC_MdCtrl1_LMTH_12_0dB
  *            ALC_MdCtrl1_LMTH_10_1dB
  *
  * Param  RGAIN: ALC Recovery Gain Step
  *            ALC_MdCtrl1_RGAIN_0_00424_1fs (default)
  *            ALC_MdCtrl1_RGAIN_0_00212_1fs
  *            ALC_MdCtrl1_RGAIN_0_00106_1fs
  *            ALC_MdCtrl1_RGAIN_0_00106_2fs
  *            ALC_MdCtrl1_RGAIN_0_00106_4fs
  *            ALC_MdCtrl1_RGAIN_0_00106_8fs
  *            ALC_MdCtrl1_RGAIN_0_00106_16fs
  *            ALC_MdCtrl1_RGAIN_0_00106_32fs
  * RetVal None
  */ 
void AK4637_ALC_MdCtrl1(ALC_MdCtrl1_ALCEQN_T ALCEQ,
                           ALC_MdCtrl1_LMTH_T LMTH,
                           ALC_MdCtrl1_RGAIN_T RGAIN)
{
    uint8_t Reg = AK4637_Read_Reg(ALC_MdCtrl1_Address);
    Reg |= ((uint8_t)ALCEQ | (uint8_t)LMTH | (uint8_t)RGAIN);
    AK4637_Write_Reg(ALC_MdCtrl1_Address, Reg);
}


/**
  * Brief  ALC Enable
  * Param  ALC:
  *            ALC_MdCtrl1_ALC_Enable
  *            ALC_MdCtrl1_ALC_Disable (default)
  * RetVal None
  */ 
void AK4637_ALC_Enable(ALC_MdCtrl1_ALC_T ALC)
{
    uint8_t Reg = AK4637_Read_Reg(ALC_MdCtrl1_Address);
    Reg |= ALC;
    AK4637_Write_Reg(ALC_MdCtrl1_Address, Reg);
}


/*---------------------------------------------------------------- *
 *                      0C ALC Mode Control 2                      *
 *---------------------------------------------------------------- */

/**
  * Brief  Reference Value at ALC Recovery Operation.
            0.375dB step, 242 Level
  * Param  REF: default:"E1H"(+30.0dB)
  * RetVal None
  */ 
void AK4637_ALC_MdCtrl2(uint8_t REF)
{
    AK4637_Write_Reg(ALC_MdCtrl2_Address, REF);
} 
 
 
/*---------------------------------------------------------------- *
 *                      0D Input Volume Control                    *
 *---------------------------------------------------------------- */

/**
  * Brief  Digital Input Volume;
            0.375dB step, 242 Level
  * Param  IVOL: default:"E1H"(+30.0dB)
  * RetVal None
  */  
void AK4637_Input_VolumeControl(uint8_t IVOL)
{
    AK4637_Write_Reg(InputVolumeControl_Address, IVOL);
}  
 
 
/*---------------------------------------------------------------- *
 *                          0E ALC Volume                          *
 *---------------------------------------------------------------- */

/**
  * Brief  Current ALC volume value;
            0.375dB step, 242 Level. 
            Read operation only.
  * Param  None:
  * RetVal Current ALC volume value
  */  
uint8_t AK4637_ALC_Volume(void)
{
    return ((uint8_t)AK4637_Read_Reg(ALC_Volume_Address));
}

 
/*---------------------------------------------------------------- *
 *                      0F  BEEP Control                           *
 *---------------------------------------------------------------- */

/**
  * Brief  
  * Param  BPVCM: Common Voltage Setting of BEEP Input Amplifier

  *            BEEPControl_BPVCM_1_65V
  *            BEEPControl_BPVCM_1_15V (default)
  *
  * Param  BEEPS: Signal Switch Control from the BEEP pin to Speaker Amplifier

  *            BEEPControl_BEEPS_ON
  *            BEEPControl_BEEPS_OFF (default)
  *
  * Param  BPLVL: BEEP Output Level Setting

  *            BEEPControl_BPLVL_0dB (default)
  *            BEEPControl_BPLVL_6dB
  *            BEEPControl_BPLVL_12dB
  *            BEEPControl_BPLVL_18dB
  *            BEEPControl_BPLVL_24dB
  *            BEEPControl_BPLVL_30dB
  *            BEEPControl_BPLVL_33dB
  *            BEEPControl_BPLVL_36dB
  *            BEEPControl_BPLVL_39dB
  *            BEEPControl_BPLVL_42dB
  * RetVal None
  */  
void AK4637_Beep_AmpCommonVoltage(BEEPControl_BPVCM_T BPVCM,
                                BEEPControl_BEEPS_T BEEPS,
                                BEEPControl_BPLVL_T BPLVL)
{
    AK4637_Write_Reg(BEEPControl_Address, (uint8_t)BPVCM | (uint8_t)BEEPS | (uint8_t)BPLVL);
} 


/*---------------------------------------------------------------- *
 *                    10 Digital Volume Control                    *
 *---------------------------------------------------------------- */

/**
  * Brief  Reference Value at ALC Recovery Operation.
            0.375dB step, 242 Level
  * Param  DVOL: default:"18H"(0dB)
  * RetVal None
  */  
void AK4637_Digital_VolumeControl(uint8_t DVOL)
{
    AK4637_Write_Reg(ALC_Volume_Address, DVOL);
}
 
 
/*------------------------------------------------------------------ *
 *                  11   EQ CommenGain Select                        *
 *------------------------------------------------------------------ */
/**
  * Brief 
  * Param  EQC2: Equalizer 2 Common Gain Selector

  *            EQ_CommonGainSelect_EQC2_Enable
  *            EQ_CommonGainSelect_EQC2_Disable (default)
  *
  * Param  EQC3: Equalizer 3 Common Gain Selector

  *            EQ_CommonGainSelect_EQC3_Enable
  *            EQ_CommonGainSelect_EQC3_Disable (default)
  *
  * Param  EQC4: Equalizer 4 Common Gain Selector

  *            EQ_CommonGainSelect_EQC4_Enable
  *            EQ_CommonGainSelect_EQC4_Disable (default)
  *
  * Param  EQC5: Equalizer 5 Common Gain Selector

  *            EQ_CommonGainSelect_EQC5_Enable
  *            EQ_CommonGainSelect_EQC5_Disable (default)
  * RetVal None
  */ 
void AK4637_EQ_CommenGain_Select(EQ_CommonGainSelect_EQC2_T EQC2,
                               EQ_CommonGainSelect_EQC3_T EQC3,
                               EQ_CommonGainSelect_EQC4_T EQC4,
                               EQ_CommonGainSelect_EQC5_T EQC5)
{
     AK4637_Write_Reg(EQ_CommonGainSelect_Address,
                           (uint8_t)EQC2 | (uint8_t)EQC3 | (uint8_t)EQC4 | (uint8_t)EQC5);                                 
}


/*------------------------------------------------------------------ *
 *                      12   EQ2 Gain Setting                        *
 *------------------------------------------------------------------ */

/**
  * Brief  
  * Param  EQ2G: Gain Setting 
                  default:"00H"(Mute)
  *
  * Param  EQnT: Transition Time

  *            EQn_GainSetting_256_fs (default)
  *            EQn_GainSetting_2048_fs
  *            EQn_GainSetting_8192_fs
  *            EQn_GainSetting_16384_fs
  * RetVal None
  */ 
void AK4637_EQ2_GainSetting(uint8_t EQ2G,
                          EQn_GainSetting_EQnT_T EQnT)
{
    AK4637_Write_Reg(EQ3_Gainetting_Address, EQ2G | EQnT);
} 
 
 
/*------------------------------------------------------------------ *
 *                      13  EQ3 Gain Setting                         *
 *------------------------------------------------------------------ */

/**
  * Brief  
  * Param  EQ3G: Gain Setting 
                  default:"00H"(Mute)
  *
  * Param  EQnT: Transition Time

  *            EQn_GainSetting_256_fs (default)
  *            EQn_GainSetting_2048_fs
  *            EQn_GainSetting_8192_fs
  *            EQn_GainSetting_16384_fs
  * RetVal None
  */  
void AK4637_EQ3_GainSetting(uint8_t EQ3G,
                          EQn_GainSetting_EQnT_T EQnT)
{
    AK4637_Write_Reg(EQ3_Gainetting_Address, EQ3G | EQnT);
} 
 
 
/*------------------------------------------------------------------ *
 *                      14   EQ4 Gain Setting                         *
 *------------------------------------------------------------------ */

/**
  * Brief  
  * Param  EQ4G: Gain Setting 
                  default:"00H"(Mute)
  *
  * Param  EQnT: Transition Time

  *            EQn_GainSetting_256_fs (default)
  *            EQn_GainSetting_2048_fs
  *            EQn_GainSetting_8192_fs
  *            EQn_GainSetting_16384_fs
  * RetVal None
  */  
void AK4637_EQ4_GainSetting(uint8_t EQ4G,
                          EQn_GainSetting_EQnT_T EQnT)
{
    AK4637_Write_Reg(EQ4_GainSetting_Address, EQ4G | EQnT);
}  
 
 
/*------------------------------------------------------------------ *
 *                      15   EQ5 Gain Setting                        *
 *------------------------------------------------------------------ */

/**
  * Brief  
  * Param  EQ5G: Gain Setting 
                  default:"00H"(Mute)
  *
  * Param  EQnT: Transition Time

  *            EQn_GainSetting_256_fs (default)
  *            EQn_GainSetting_2048_fs
  *            EQn_GainSetting_8192_fs
  *            EQn_GainSetting_16384_fs
  * RetVal None
  */  
void AK4637_EQ5_GainSetting(uint8_t EQ5G,
                          EQn_GainSetting_EQnT_T EQnT)
{
    AK4637_Write_Reg(EQ5_GainSetting_Address, EQ5G | EQnT);
} 
 
 
/*---------------------------------------------------------------- *
 *        16/17/21 Programmable Filter ON/OFF Setting              *
 *---------------------------------------------------------------- */
/**
  * Brief  
  * Param  HPFAD: HPF1 Control after ADC
  *            DigitFiltSlct1_HPFAD_OFF
  *            DigitFiltSlct1_HPFAD_ON (default)
  * Param  HPFC: Cut-off Frequency Setting of HPF1
  *              The is based on the fs of 48kHz. For situations based on other fs,
  *                see table 25 on P45 of the datasheet.
  *            DigitFiltSlct1_HPFC_3Hz7 (default)
  *            DigitFiltSlct1_HPFC_14Hz8
  *            DigitFiltSlct1_HPFC_118Hz4
  *            DigitFiltSlct1_HPFC_236Hz8
  * RetVal None
  */ 
  void AK4637_DigitFilt_HPF1(DigitFiltSlct1_HPFAD_T HPFAD,
                             DigitFiltSlct1_HPFC_T HPFC)
{
    AK4637_Write_Reg(DigitFiltSlct1_Address, (uint8_t)HPFC | (uint8_t)HPFAD);
}
/**
  * Brief  
  * Param  HPF: HPF2 Coefficient Setting Enable

  *            DigitFiltSlct2_HPF_ON
  *            DigitFiltSlct2_HPF_OFF (default)
  *
  * Param  LPF: LPF Coefficient Setting Enable

  *            DigitFiltSlct2_LPF_ON
  *            DigitFiltSlct2_LPF_OFF (default)
  * RetVal None
  */ 
void AK4637_DigitFiltSlct2(DigitFiltSlct2_HPF_T HPF,
                           DigitFiltSlct2_LPF_T LPF)
{
     AK4637_Write_Reg(DigitFiltSlct2_Address, (uint8_t)HPF | (uint8_t)LPF);                                 
}

/**
  * Brief  
  * Param  EQ1: Equalizer 1 Coefficient Setting Enable

  *            DigitFiltSlct3_EQ1_Enable
  *            DigitFiltSlct3_EQ1_Disable (default)
  *
  * Param  EQ2: Equalizer 2 Coefficient Setting Enable

  *            DigitFiltSlct3_EQ2_Enable
  *            DigitFiltSlct3_EQ2_Disable (default)
  *
  * Param  EQ3: Equalizer 3 Coefficient Setting Enable

  *            DigitFiltSlct3_EQ3_Enable
  *            DigitFiltSlct3_EQ3_Disable (default)
  *
  * Param  EQ4: Equalizer 4 Coefficient Setting Enable

  *            DigitFiltSlct3_EQ4_Enable
  *            DigitFiltSlct3_EQ4_Disable (default)
  *
  * Param  EQ5: Equalizer 5 Coefficient Setting Enable

  *            DigitFiltSlct3_EQ5_Enable
  *            DigitFiltSlct3_EQ5_Disable (default)
  * RetVal None
  */  
void AK4637_Digital_Filter_Select3(DigitFiltSlct3_EQ1_T EQ1,
                                   DigitFiltSlct3_EQ2_T EQ2,
                                   DigitFiltSlct3_EQ3_T EQ3,
                                   DigitFiltSlct3_EQ4_T EQ4,
                                   DigitFiltSlct3_EQ5_T EQ5)
{
     AK4637_Write_Reg(DigitFiltSlct3_Address,
                           (uint8_t)EQ1 | (uint8_t)EQ2 | (uint8_t)EQ3 | (uint8_t)EQ4 | (uint8_t)EQ5);                                 
}


/*---------------------------------------------------------------- *
 *               18  Programmable Filter Path                      *
 *---------------------------------------------------------------- */

/**
  * Brief  
  * Param  ADCPF: Programmable Filter / ALC Input Signal Select
  *            DigitalFilterMode_ADCPF_SDTI
  *            DigitalFilterMode_ADCPF_ADC (default)
  * Param  PFDAC: DAC Input Signal Select
  *            DigitalFilterMode_PFDAC_SDTI (default)
  *            DigitalFilterMode_PFDAC_PFVOL
  *            DigitalFilterMode_PFDAC_SDTInPFVOL
  * Param  PFSDO: SDTO Output Signal Select
  *            DigitalFilterMode_PFSDO_ADC
  *            DigitalFilterMode_PFSDO_DigitBlk (default)
  * RetVal None
  */
void AK4637_RecordingPlaybackMode(DigitalFilterMode_ADCPF_T ADCPF,
                                  DigitalFilterMode_PFDAC_T PFDAC,
                                  DigitalFilterMode_PFSDO_T PFSDO)
{
    uint8_t Reg = AK4637_Read_Reg(DigitalFilterMode_Address);
    Reg |= ((uint8_t)ADCPF | (uint8_t)PFDAC | (uint8_t)PFSDO);
    AK4637_Write_Reg(DigitalFilterMode_Address, Reg); 
}


/*---------------------------------------------------------------- *
 *                   18 Sidetone Digital Volume                    *
 *---------------------------------------------------------------- */
/**
  * Brief  Sidetone Digital Volume
  * Param  PFVOL:

  *            DigitalFilterMode_PFVOL_0dB (default)
  *            DigitalFilterMode_PFVOL_6dB
  *            DigitalFilterMode_PFVOL_12dB
  *            DigitalFilterMode_PFVOL_18dB
  * RetVal None
  */ 
void AK4637_SidetoneDigitalVolume(DigitalFilterMode_PFVOL_T PFVOL)
{
    uint8_t Reg = AK4637_Read_Reg(DigitalFilterMode_Address);
    Reg |= PFVOL;
    AK4637_Write_Reg(DigitalFilterMode_Address, Reg); 
}


/*---------------------------------------------------------------- *
 *                      19-1C   HPF2 Co-efficient                  *
 *---------------------------------------------------------------- */

/**
  * Brief  HPF2 Coefficient
  * Param  HPF2_Cofficient[4]:
  * @note   Default: F1A13-0 bits = 0x1FB0,
                     F1B13-0 bits = 0x209F (fc = 150Hz@fs=48kHz)
  * RetVal None
  */ 
void AK4637_HPF2_Coefficient(uint8_t HPF2_Cofficient[4])
{
    uint8_t addr = HPF2_Co_efficient0_Address;
    for(int i=0; i<4; i++)
    {
        AK4637_Write_Reg(addr++, HPF2_Cofficient[i]); 
    }
} 
 
 
/*---------------------------------------------------------------- *
 *                   1D-20   LPF Co-efficient                      *
 *---------------------------------------------------------------- */

/**
  * Brief  LPF Co-efficient
  * Param  LPF_Cofficient[4]:
  * @note   Default: 0000H
  * RetVal None
  */  
void AK4637_LPF_Coefficient(uint8_t LPF_Cofficient[4])
{
    uint8_t addr = LPF_Co_efficient0_Address;
    for(int i=0; i<4; i++)
    {
        AK4637_Write_Reg(addr++, LPF_Cofficient[i]); 
    }
}  
 
 
/*---------------------------------------------------------------- *
 *                  22-3F   E1/2/3/4/5 Co-efficient                *
 *---------------------------------------------------------------- */

/**
  * Brief  E1/2/3/4/5 Co-efficient
  * Param  E_Cofficient[30]:
  * @note   Default: 0000H
  * RetVal None
  */  
void AK4637_EQ_Coefficient(uint8_t EQ_Cofficient[30])
{
    uint8_t addr = E1_Co_efficient0_Address;
    for(int i=0; i<30; i++)
    {
        AK4637_Write_Reg(addr++, EQ_Cofficient[i]); 
    }
} 

/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/