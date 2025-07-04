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
// (��MStar Confidential Information��) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// @file
// @brief
// @author MStarSemi Inc.
//
//-
//-
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_FS_SYSINFO_C
#include <string.h>
#include "MsCommon.h"

#include "msAPI_FS_SysInfo.h"

#include "sysinfo.h"

#include "hwreg.h"

#include "Debug.h"
#include "SysInit.h"

#include "msAPI_Timer.h"
#include "msAPI_Memory.h"

#include "msAPI_FCtrl.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_FSEnv.h"

#include "MsTypes.h"
//#include "drvBDMA.h"
#include "drvIMI.h"

#define  MSAPI_FS_DBG(flag,x)         {if(flag){x;}}


#define FS_MEM_CTRL_ID BUF_ID_FILECNTL

#define MAX_SUPPORT_FS_WIN1_LOCK_COUNT 4

#define DEFAULT_MJD     44239 //51544

//Aeon add by Eric-PH Lee
void FS_MEM_Dump(void *ptr,U8 *str)
{
    U16 i;
    UNUSED(ptr);
    UNUSED(str);
    MS_DEBUG_MSG(printf("\nFS_MEM_Dump %s",str));
    for(i=0;i<0x30;i++)
    {
        if(i%16==0)
        {
            MS_DEBUG_MSG(printf("\n"));
        }
        MS_DEBUG_MSG(printf("%02x ",*(((U8 *)ptr)+i)));
    }
    MS_DEBUG_MSG(printf("\n"));
}

void msAPI_FS_Init(void)
{
    //msAPI_FSEnv_Init must be called at first to initialize file system memory map.
    //if(!msAPI_FSEnv_Init(_PA2VA(((FILE_SYSTEM_POOL_MEMORY_TYPE & MIU1) ? (FILE_SYSTEM_POOL_ADR | MIU_INTERVAL) : (FILE_SYSTEM_POOL_ADR))),FILE_SYSTEM_POOL_LEN))
    if(!msAPI_FSEnv_Init(FILE_SYSTEM_POOL_ADR, FILE_SYSTEM_POOL_LEN))
    {
        __ASSERT(0);
        MS_DEBUG_MSG(printf("Init File System Error!!!\n"));
    }
    msAPI_MSDCtrl_Init();
    msAPI_FCtrl_Init();
}


void * msAPI_FS_Memory_Allocate(U16 u16Number_of_bytes)
{
    return msAPI_Memory_Allocate(u16Number_of_bytes, FS_MEM_CTRL_ID);
}

void msAPI_FS_Memory_Free(void * pMem)
{
    msAPI_Memory_Free(pMem, FS_MEM_CTRL_ID);
}


void msAPI_FS_MIU_Copy(U32 srcaddr, U32 dstaddr, U32 len)
{
    memcpy((U8 *)dstaddr,(U8 *)srcaddr,len);

}


void msAPI_FS_MIU_Copy_I(U32 srcaddr, U32 dstaddr, U32 len)
{
    memcpy((U8 *)dstaddr,(U8 *)srcaddr,len);
    //Leo-temp, need to use different BDMA drivers.
    //MDrv_BDMA_CopyHnd(srcaddr, dstaddr, len, E_BDMA_SDRAM2SDRAM, BDMA_OPCFG_INV_COPY);
}

void FS_RESET_WDT()
{
    MDrv_Sys_ClearWatchDog();
}

#undef MSAPI_FS_SYSINFO_C

