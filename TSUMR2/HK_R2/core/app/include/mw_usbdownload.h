//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!��MStar Confidential Information!�L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MW_USBDOWNLOAD_H
#define MW_USBDOWNLOAD_H

#include "default_option_define.h"

///////////////////////////////////////////////////
#ifdef MW_USBDOWNLOAD_C
#define INTERFACE
#else
#define INTERFACE extern
#endif
// search latest bin file by file name
#define ENABLE_USB_DOWNLOAD_USE_VERSION_BY_FILENAME (0)
#define MAX_FILENAME_LEN 32

typedef void (* pZUIDrawCB)(U8);

////////////////////////////////////////////////////////////////////////////////
INTERFACE void MW_UsbDownload_Init(U8 u8USBPortNo, U8 u8FlashID, U32 u32DRAMAddr, U32 u32DRAMLen, U32 u32FlashSize, U8 u8UpgradeMode, U8 u8MemType, U8 * u8FileName, pZUIDrawCB ZUIDrawPercentage, BOOLEAN bAPBinFlag);
INTERFACE BOOLEAN MW_UsbDownload_Search(void);
INTERFACE BOOLEAN MW_UsbDownload_Start(void);
INTERFACE U32 MW_UsbDownload_GetDualImageOffset(void);
INTERFACE BOOLEAN Dump_DRAM_To_USB(U32 u32Address, U32 u32Length);

#if (ENABLE_SZ_FACTORY_USB_SAVE_DATABASE_FUNCTION == ENABLE ||ENABLE_SZ_FACTORY_USB_SAVE_MAP_FUNCTION == ENABLE)
INTERFACE void MApp_UsbSaveData_SetPort(U8 u8USBPortNo);
INTERFACE U8 MApp_UsbSaveData_OpenNewFileForWrite(U16* pString,U8 charLen);
INTERFACE BOOLEAN MApp_UsbSaveData_InitFileSystem(void);
INTERFACE void MApp_UsbSaveData_Exit(void);
#endif

#if( ENABLE_USB_DOWNLOAD_BIN )

typedef enum
{
    E_USB_DL__OK,

    E_USB_DL__USB_PORT_IS_NOT_DETECTED,

    E_USB_DL__MEMORY_BUFFER_SIZE_ERROR,
    E_USB_DL__MEMORY_PROTECT_HIT_HAPPEN,

    E_USB_DL__INIT_FILE_SYSTEM_FAILED,
    E_USB_DL__SEARCH_FILE_FAILED,
    E_USB_DL__OPEN_FILE_FAILED,
    E_USB_DL__FILE_SIZE_IS_ERROR,
    E_USB_DL__READ_FILE_FAILED,

    E_USB_DL__GET_BIN_INFO_FAILED,
    E_USB_DL__FILE_SIZE_IS_BIG_THEN_BIN_SIZE,

    E_USB_DL__BDMA_FLASH_TO_DRAM_FAILED,
    E_USB_DL__BDMA_DRAM_TO_DRAM_FAILED,

    E_USB_DL__PARAMETER_ERROR,
    E_USB_DL__MEMORY_ALLOC_FAILED,

    E_USB_DL__FLASH_WRITE_PROTECT_FAILED,
    E_USB_DL__ERASE_FLASH_FAILED,

} EnuUsbDlErrCode;


EnuUsbDlErrCode MW_Usb_Download_Bin(U8 u8USBPortNo, U8* pu8FileName, U32 u32DramBufAddr, U32 u32DramBufSize, U16 u16BinId);
#endif

extern U32 g_u32DownloadSize;
extern U32 g_u32FileSize;

#undef INTERFACE

#endif  //#ifndef MW_USBDOWNLOAD_H

