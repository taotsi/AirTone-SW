/*******************************************************************************
 * Brief:   Memory Management Library.
 * Author:  taotsi
 * Update:  2017.04.30
 *******************************************************************************/
#ifndef _MemManage_H_
#define _MemManage_H_

#include "BSP.h"
/* Macros ---------------------------------------------------------------------*/
/* M25P128 Address Index */
#define FIndx_CCIMG_Master_Origin_SW        0xFFFFFF
#define FIndx_CCIMG_Master_Origin           0xFC0000
#define FIndx_CCIMG_Master_Processed_SW     0xFBFFFF
#define FIndx_CCIMG_Master_Processed        0xF80000
// The data size is stored in tow bytes at address 0x801E of the fireware image data.
#define FIndx_CCIMG_Master_Size             FIndx_CCIMG_Master_Processed+0x1E

#define FIndx_CCIMG_Slave_Origin_SW         0xF7FFFF
#define FIndx_CCIMG_Slave_Origin            0xF40000
#define FIndx_CCIMG_Slave_Processed_SW      0xF3FFFF
#define FIndx_CCIMG_Slave_Processed         0xF00000
// The data size is stored in tow bytes at address 0x801E of the fireware image data.
#define FIndx_CCIMG_Slave_Size              FIndx_CCIMG_Slave_Processed+0x1E


/* Data Size */
#define DtSz_CCIMG_Origin           0x01580B    // 88075 chars


/* Logic Switch */
#define FSW_CCIMG_Master_Origin_Written         0x00
#define FSW_CCIMG_Master_Origin_Empty           0xFF
#define FSW_CCIMG_Master_Processed_Written      0x00
#define FSW_CCIMG_Master_Processed_Empty        0xFF

#define FSW_CCIMG_Slave_Origin_Written          0x00
#define FSW_CCIMG_Slave_Origin_Empty            0xFF
#define FSW_CCIMG_Slave_Processed_Written       0x00
#define FSW_CCIMG_Slave_Processed_Empty         0xFF



/* Functions ------------------------------------------------------------------*/
//void MemMng_DataTrans_PC_M25P(uint32_t addr, uint16_t nPages);
void MemMng_Config(void);
void MemMng_DataTrans_PC_M25P(uint32_t addr, uint32_t nBytes);
void MemMng_DataTrans_M25P_CC8530_IMG(uint32_t addr_src);
void MemMng_DataProc_Char_HEX(uint32_t addr_origin, uint32_t addr_new, uint16_t nRows);

#endif // _MemManage_H_
/* ----------------------------- End of file --------------------------------- */
/*******************************************************************************/