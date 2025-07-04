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
    //************************************************************
    //***             RIU Base address of each IP              ***
    //***                (Byte address [23:0])                 ***
    //************************************************************

#define    RIUBASE_VD_MHEG5            0x100300    //0x100300 ~ 0x1003ff
#define    RIUBASE_MAU0                0x100400    //0x100400 ~ 0x10047f
#define    RIUBASE_MAU1                0x100480    //0x100480 ~ 0x1004ff
#define    RIUBASE_POR_STATUS          0x100500    //0x100500 ~ 0x10053f
#define    RIUBASE_INTR_CPUINT         0x100540    //0x100540 ~ 0x10057f
#define    RIUBASE_BDMA                0x100900    //0x100900 ~ 0x10097f
#define    RIUBASE_UART0               0x100980    //0x100980 ~ 0x1009bf
#define    RIUBASE_UART1               0x1009C0    //0x1009C0 ~ 0x1009ff
#define    RIUBASE_MHEG5               0x100f00    //0x100f00 ~ 0x100fff
#define    RIUBASE_MIU_ATOP            0x101100    //0x101100 ~ 0x1011ff
#define    RIUBASE_MIU                 0x101200    //0x101200 ~ 0x1012ff
#define    RIUBASE_MIU_ARB             0x101300    //0x101300 ~ 0x1013ff
#define    RIUBASE_NEC                 0x101500    //0x101500 ~ 0x1015ff
#define    RIUBASE_SEMAPH              0x101800    //0x101800 ~ 0x10183f      
#define    RIUBASE_INTR_CTRL           0x101900    //0x101900 ~ 0x1019ff
#define    RIUBASE_OSD                 0x101c00    //0x101c00 ~ 0x101cff      
#define    RIUBASE_OSD2                0x101d00    //0x101d00 ~ 0x101dff
#define    RIUBASE_CHIP                0x101e00    //0x101e00 ~ 0x101eff
#define    RIUBASE_GOP                 0x101f00    //0x101f00 ~ 0x101fff
#define    RIUBASE_ADC_ATOP            0x102500    //0x102500 ~ 0x1025ff
#define    RIUBASE_ADC_DTOP            0x102600    //0x102600 ~ 0x1026ff
#define    RIUBASE_ADC_DTOPB           0x102700    //0x102700 ~ 0x1027ff
#define    RIUBASE_GE0                 0x102800    //0x102800 ~ 0x1028ff
#define    RIUBASE_MAILBOX             0x103380    //0x103380 ~ 0x1033ff
#define    RIUBASE_PATGEN              0x103980    //0x103980 ~ 0x1039ff
#define    RIUBASE_TOP_MISC            0x103A80    //0x103A80 ~ 0x103Aff
#define    RIUBASE_PIU_NONPM           0x103C00    //0x103C00 ~ 0x103Cff
#define    RIUBASE_DIQ_PWM             0x103D00    //0x103D00 ~ 0x103Dff
#define    RIUBASE_MIIC2               0x103E00    //0x103E00 ~ 0x103Eff
#define    RIUBASE_GE1                 0x110700    //0x110700 ~ 0x1107ff
#define    RIUBASE_MIIC0               0x111800    //0x111800 ~ 0x1118ff
#define    RIUBASE_MIIC1               0x111900    //0x111900 ~ 0x1119ff
#define    RIUBASE_CLKGEN0             0x120f00    //0x120f00 ~ 0x120fff

