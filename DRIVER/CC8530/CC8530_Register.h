/*******************************************************************************
 * Brief:   CC8530 driver, run on STM8L15x
 * Author:  ZhiYe
 * Update:  2017.04.08
 *******************************************************************************/

#ifndef _CC8530_Register_h_
#define _CC8530_Register_h_

//#include "MyTypeDefine.h"



/* 
 * 2.2 Bootloader Unlocking*****************************************************
 **/
#define BL_Unlock_SPI       0x2505B007 

 
/* 
 * 2.3 Flash Programming Through SPI Slave Interface*****************************
 **/
#define BL_Flash_Mass_Erase  0x25051337

             //BL_FlASH_PAGE_PROG参数需自己设定 
             //BL_FlASH_VERIFY参数需自己设定
			 

/* 
 * 3.1 Device Information Commands************************************************
 **/

#define Chip_Information                  0x00B0

			 //DI_GET_DEVICE_INFO无写入参数
			 

/* 
 * 3.2 EHIF Control Commands*******************************************************
 **/
 
#define EHIF_IRQ_Low                      0x0000
#define EHIF_IRQ_High                     0x0100
#define MSK_DSC_Rx_Avail_Conf             0x0080
#define MSK_DSC_Tx_Avail_Conf             0x0040
#define MSK_DSC_Reset_Conf                0x0020
#define MSK_SPI_Error_Conf                0x0010
#define MSK_VOL_Chg_Conf                  0x0008
#define MSK_PS_Chg_Conf                   0x0004
#define MSK_NWK_Chg_Conf                  0x0002
#define MSK_SR_Chg_Conf                   0x0001


#define MSK_DSC_Reset_Clr                 0x20
#define MSK_SPI_Error_Clr                 0x10
#define MSK_VOL_Chg_Clr                   0x08
#define MSK_PS_Chg_Clr                    0x04
#define MSK_NWK_Chg_Clr                   0x02
#define MSK_SR_Chg_Clr                    0x01
 
 
/* 
 * 3.3 Audio Network Control and Status Commands*************************************
 **/
 
             //NWM_Do_Scan, NWM_Do_Join, NWM_Ach_Set_Usage的参数需自己设定
			 //NWM_Do_Get_Status无写入参数
			  
#define NWM_Control_Enable                0x0001
#define NWM_Control_Disable               0x0000

#define NWM_Control_Signal                0x0001

#define NWM_Set_RF_CH_Mask                0x00000002   //Enable RF channels 1, 可更改为其他通道


/* 
 * 3.4 Remote Control Commands*******************************************************
 **/
 
             //RC_Set_Data参数需自己设定
             //RC_Get_Data参数待定
			 

/* 
 * 3.5 Data Side-Channel Commands****************************************************
 **/ 
 
#define DSC_Tx_Conn_Reset                 0x0100000000
             //DSC_Tx_Datagram地址参数待定
			 
             //DSC_Rx_Datagram无写入参数	


/* 
 * 3.6 Power Management Commands*****************************************************
 **/

#define PM_Active             0x20
#define PM_Low_Power          0x10
#define PM_Local_Standby      0x08
#define PM_Network_Standby    0x04
#define PM_Off                0x01

             //PM_Get_Data无写入参数

			 
/* 
 * 3.7 Volume Control Commands*******************************************************
 **/
 
#define VC_Set_Input                  0x02000000
#define VC_Set_Output                 0x00000000
#define VC_Local                      0x01000000
#define VC_Remote                     0x00000000 
#define VC_Mute_Op_None               0x00000000 
#define VC_Mute_Op_Mute               0x00400000
#define VC_Mute_Op_Unmute             0x00800000
#define VC_Mute_Op_Toggle             0x00C00000
#define VC_Set_Op_None                0x00000000 
#define VC_Set_Op_Absolute            0x00100000
#define VC_Set_Op_Relative            0x00200000
#define VC_Set_Op_Log_Cha_Offset      0x00300000
             //Log_Channel, Volume参数需自己设定
			 
#define VC_Master_Input               0x02
#define VC_Master_Output              0x00
#define VC_Master_Local               0x01
#define VC_Master_Remote              0x00

             //VC_Slave_Log_Channel参数需自己设定
			 
#define VC_Slave_Input                0x02
#define VC_Slave_Output               0x00
#define VC_Slave_Channel_Offset       0x01
#define VC_Slave_Volume_Setting       0x00


/* 
 * 3.8 RF and Audio Statistics Commands***********************************************
 **/

             //函数均无写入参数
 
/* 
 * 3.9 Calibration Commands***********************************************************
 **/

             //Cal_Set_Data参数需自己设定
			 //Cal_Get_Data无写入参数
 
 
/* 
 * 3.10 Utility Commands***********************************************************
 **/
 
             //IO_Get_Pin_Val无写入参数
#define NVS_Get_Autonomous              0x00
#define NVS_Get_Host_Control            0x01     // 1/2/3都行?

#define NVS_Set_Autonomous              0x0000000000
#define NVS_Set_Host_Control            0x0100000000   //1/2/3都行?
#define NVS_Set_Data                    //需自己设定


/* 
 * 3.11 RF Test Commands***********************************************************
 **/
#define RFT_Txtst_CW_Enable             0x010000
#define RFT_Txtst_CW_Disable            0x000000
#define RFT_Txtst_CW_Freq_Offset        //需自己设定
#define RFT_Txtst_CW_Tx_Pow             //需自己设定

#define RFT_Txtst_PN_Enable             0x010000
#define RFT_Txtst_PN_Disable            0x000000
#define RFT_Txtst_PN_Freq_Offset        //需自己设定
#define RFT_Txtst_PN_Tx_Pow             //需自己设定

#define RFT_Rxtst_Cont_Enable           0x0100
#define RFT_Rxtst_Cont_Disable          0x0000
#define RFT_Rxtst_Cont_Freq_Offset      //需自己设定

#define RFT_Rxtst_RSSI_Freq_Offset      //需自己设定

             //Rft_Txper, Rft_Rxper, Rft_Nwksim参数需自己设定
			 
			 
/* 
 * 3.12 Audio Test Commands***********************************************************
 **/

             //AT_Gen_Yone, AT_Det_Tone参数需自己设定
 
 
/* 
 * 3.13 IO Test Commands***********************************************************
 **/
#define IO_Input_Xant_Usb_Sel            {0x00, 0x01, 0x00, 0x00} // 这样可以吗？
#define IO_Input_GIO15                   0x00004000
#define IO_Input_GIO14                   0x00002000
#define IO_Input_GIO13                   0x00001000
#define IO_Input_GIO12                   0x00000800
#define IO_Input_GIO11                   0x00000400
#define IO_Input_GIO10                   0x00000200
#define IO_Input_GIO9                    0x00000100
#define IO_Input_GIO8                    0x00000080
#define IO_Input_GIO7                    0x00000040
#define IO_Input_GIO6                    0x00000020
#define IO_Input_GIO5                    0x00000010
#define IO_Input_GIO4                    0x00000008
#define IO_Input_GIO3                    0x00000004
#define IO_Input_GIO2                    0x00000002
#define IO_Input_GIO1                    0x00000001        

//向选中的IO写1
#define IO_Output_Xant_Usb_Diff_Set          0x0002000000040000
#define IO_Output_Xant_Usb_P_Set             0x0001000000020000
#define IO_Output_Xant_Usb_N_Set             0x0001000000010000
#define IO_Output_GIO15_Set                  0x0000400000004000
#define IO_Output_GIO14_Set                  0x0000200000002000
#define IO_Output_GIO13_Set                  0x0000100000001000
#define IO_Output_GIO12_Set                  0x0000080000000800
#define IO_Output_GIO11_Set                  0x0000040000000400
#define IO_Output_GIO10_Set                  0x0000020000000200
#define IO_Output_GIO9_Set                   0x0000010000000100
#define IO_Output_GIO8_Set                   0x0000008000000080
#define IO_Output_GIO7_Set                   0x0000004000000040
#define IO_Output_GIO6_Set                   0x0000002000000020
#define IO_Output_GIO5_Set                   0x0000001000000010
#define IO_Output_GIO4_Set                   0x0000000800000008
#define IO_Output_GIO3_Set                   0x0000000400000004
#define IO_Output_GIO2_Set                   0x0000000200000002
#define IO_Output_GIO1_Set                   0x0000000100000001

//向选中的IO写0
#define IO_Output_Xant_Usb_Diff_Low          0x0002000000000000
#define IO_Output_Xant_Usb_P_Low             0x0001000000000000
#define IO_Output_Xant_Usb_N_Low             0x0001000000000000
#define IO_Output_GIO15_Low                  0x0000400000000000
#define IO_Output_GIO14_Low                  0x0000200000000000
#define IO_Output_GIO13_Low                  0x0000100000000000
#define IO_Output_GIO12_Low                  0x0000080000000000
#define IO_Output_GIO11_Low                  0x0000040000000000
#define IO_Output_GIO10_Low                  0x0000020000000000
#define IO_Output_GIO9_Low                   0x0000010000000000
#define IO_Output_GIO8_Low                   0x0000008000000000
#define IO_Output_GIO7_Low                   0x0000004000000000
#define IO_Output_GIO6_Low                   0x0000002000000000
#define IO_Output_GIO5_Low                   0x0000001000000000
#define IO_Output_GIO4_Low                   0x0000000800000000
#define IO_Output_GIO3_Low                   0x0000000400000000
#define IO_Output_GIO2_Low                   0x0000000200000000
#define IO_Output_GIO1_Low                   0x0000000100000000
             
#endif  // _CC8530_Register_h_

/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/