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
// Description: Interrupt Service Routines
//
////////////////////////////////////////////////////////////////////////////////

#define _DRV_ISR_C_

#include <stdio.h>
#include <string.h>
#include "MsTypes.h"

#if defined(__aeon__)
#include "risc32_spr.h"
#endif

//#include "sysinfo.h"
#include "drvCPU.h"
//#include "sysinfo.h"

#include "hwreg.h"

//#include "GPIO.h"
//#include "drvpower_if.h"
#include "drvGlobal.h"
#include "drvUartDebug.h"

//#include "msIR.h"
//#include "msKeypad.h"
#include "drvISR.h"
#include "SysInit.h"
//#include "util_minidump.h"
#include "MsOS.h"
//#include "drvXC_HDMI_if.h"
//#include "apiXC_Hdmi.h"
//#include "Isr.h"
#if (ENABLE_DOLBY_HDR)
#include "drvHDRCommon.h"
#endif

#if (ENABLE_USB_TYPEC)
#include "mailbox.h"
#endif

#if 0//(ENABLE_SECU_R2)
#include "drvHDCPRx.h"
#endif

#include "HdcpHandler.h"

#if DTV_COUNT_DOWN_TIMER_PATCH
extern U8 u8DTVCountDownTimer;
#endif

#ifdef ENABLE_MINI_DUMP
extern void ProcessWDTIsr(MHAL_SavedRegisters *pHalReg, U32 vector);
extern void ProcessMIUIsr(MHAL_SavedRegisters *pHalReg, U32 vector);
#endif

static void ProcessCPU1toCPU0Isr(MHAL_SavedRegisters *pHalReg, U32 vector)
{
    UNUSED(pHalReg);
    UNUSED(vector);

#if (ENABLE_USB_TYPEC)
    drvmbx_receive_cmd_isr();
#endif

    MsOS_EnableInterrupt(E_INT_PM_FIQ_PD51_TO_HKR2);
}

static void ProcessCPU2toCPU0Isr(MHAL_SavedRegisters *pHalReg, U32 vector)
{
    UNUSED(pHalReg);
    UNUSED(vector);

    #if CHIP_ID==CHIP_MT9701 && (ENABLE_DOLBY_HDR)
    //mdrv_Dolby_HKR2_Receive();
    //printf("ProcessCPU2toCPU0Isr\n");
    mdrv_Dolby_SetDVPQR2EventFlag();
    #endif

    MsOS_EnableInterrupt(E_INT_PM_FIQ_HST2_TO_HKR2);
}

static void ProcessCPU3toCPU0Isr(MHAL_SavedRegisters *pHalReg, U32 vector)
{
    UNUSED(pHalReg);
    UNUSED(vector);

    #if (ENABLE_SECU_R2)
    HDCPHandler_SetR2EventFlag();
    #endif

    MsOS_EnableInterrupt(E_INT_PM_FIQ_SECUR2_TO_HKR2);
}

void MDrv_ISR_Init(void)
{
    MsOS_AttachInterrupt(E_INT_PM_FIQ_PD51_TO_HKR2, (InterruptCb)ProcessCPU1toCPU0Isr);
    MsOS_AttachInterrupt(E_INT_PM_FIQ_HST2_TO_HKR2, (InterruptCb)ProcessCPU2toCPU0Isr);
    MsOS_AttachInterrupt(E_INT_PM_FIQ_SECUR2_TO_HKR2, (InterruptCb)ProcessCPU3toCPU0Isr);

#ifdef ENABLE_MINI_DUMP
    MsOS_AttachInterrupt(E_INT_FIQ_WDT, (InterruptCb)ProcessWDTIsr);
    MsOS_AttachInterrupt(E_INT_IRQ_MIU, (InterruptCb)ProcessMIUIsr);
#endif

#if (ENABLE_USB_TYPEC)
    MsOS_EnableInterrupt(E_INT_PM_FIQ_PD51_TO_HKR2);
#endif
}
extern MS_U32 gsystem_time_ms;

//------------------------------------------------------------------------------------
//extern void Timer_Setting_Register(void *ptCb);
extern void Timer_IRQ_Register(void *ptCb);

extern void ms1MsHandler(void);

#ifndef MSOS_TYPE_LINUX
static void TimerISR(void)
{
    ms1MsHandler();

    gTimerCount0++;
    gu8100msTH++;

    // Use a threshold to check the 100 ms. If the threshold
    // is greater or equal than the 100 ms. Increase the 100 ms
    // counter.
    if (gu8100msTH >= 100)
    {
        g100msTimeCount++;
        gu8100msTH = 0;
    }

    if (gTimerCount0%1000==0)
    {
        gSystemTimeCount++;

//        gSystemTimeCount_TCON++;

        #if DTV_COUNT_DOWN_TIMER_PATCH
        if((u8DTVCountDownTimer != 0xFF) && (u8DTVCountDownTimer > 0))
            u8DTVCountDownTimer--;
        #endif
    }

    //--------------------------------
    //down time counter:
    if ( gTimerDownCount0 > 0 )
        gTimerDownCount0--;

    if ( gTimerDownCount1 > 0 )
        gTimerDownCount1--;

    //-------------------------------

#if (!BLOADER)
    #if (ENABLE_MSTV_UART_DEBUG )
    if (g_Uart0CheckTick)
    {
        --g_Uart0CheckTick;
        if ( g_Uart0CheckTick == 0 )
        {
            g_bUart0Detected = FALSE;
            g_UartCommand.Index = 0;
        }
    }
/*
    #elif XMODEM_DWNLD_ENABLE //for xmodem
     if ( g_Uart0CheckTick )
    {
        --g_Uart0CheckTick;
        if ( g_Uart0CheckTick == 0 )
        {
            XModem_Rx_Timeout = TRUE;
        }
    }
*/
    #endif
#endif // #if (!BLOADER)

    //-------------------------------
}

void MDrv_Timer_ISR_Register(void)
{
    MS_U32 check_timer_status;

    check_timer_status = MsOS_CreateTimer( (TimerCb) TimerISR,
                                                  0,
                                                  1,
                                                  TRUE,
                                                  "Check timer");
}
#endif

/**************************
System trap function
 vectors.s assumes that this function will never return
****************************/
char g_strTrapFileLineName[256]={0};
void trapBackUpLocation(const char *filename, unsigned long line)
{
    WORD ret;

    memset(g_strTrapFileLineName, 0, sizeof(g_strTrapFileLineName));
    ret = snprintf(g_strTrapFileLineName, sizeof(g_strTrapFileLineName), "System trap at %s :%u", filename, line);
    if(ret >= sizeof(g_strTrapFileLineName))
    {
        strcpy(g_strTrapFileLineName, "snprintf error");
    }
}
void ProcessSysTrap(MHAL_SavedRegisters *pHalReg, U32 vector)
{
   printf("system trap");

#ifdef ENABLE_MINI_DUMP
   MDrv_Sys_MiniDump(pHalReg, vector, MINI_DUMP_FOR_SYS_TRAP);
#else
   UNUSED(pHalReg);
   UNUSED(vector);
#endif

#if ENABLE_MSTV_UART_DEBUG
   MDrv_Sys_DisableWatchDog();
#endif

   while(1);
}
