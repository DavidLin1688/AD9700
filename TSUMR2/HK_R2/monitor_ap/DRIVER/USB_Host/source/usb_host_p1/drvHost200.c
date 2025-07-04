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

#if defined(MSOS_TYPE_NOS)

#include "../USBHostConfig.h"
#include <stdlib.h>
//#include <stdarg.h>
#ifndef ATV_SERISE_USE
#include <stdio.h>
#endif
#include <string.h>

//#include "chipset.h"
//#include "flib.h"
#ifndef ATV_SERISE_USE
#include "../../include/datatype.h"
#else
#include "UsbHostDataDef.h"
#endif
#include "../drvHostLib.h"
#include "../drvHost200.h"
//#include "Host20_AP_HID.h"
//#include "Host20_AP_Camera.h"
 #include "../drvUsbMain.h"
#include "../drvscsi.h"
#ifdef ATV_SERISE_USE
#include "uart.h"
#endif

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

#define DRV_HOST_DBG(x)  x;


OTGH_PT_BLK_Struct      *OTGH_PT_BLK;//   __attribute__ ((aligned (16)));
OTGH_PT_BLK_Struct      *sOTGH_PT_BLK;

void OTGH_PT_Bulk_Init(void);


extern void Init_Mass_Storage_Structure(void);

extern qHD_Structure *pHost20_qHD_List_Control0,*pHost20_qHD_List_Control1;
extern qHD_Structure *pHost20_qHD_List_Bulk0,*pHost20_qHD_List_Bulk1;


//====================================================================
// * Function Name: OTGH_AP_Main
// * Description: Main menu of path test
// * Input: none
// * OutPut: none
//====================================================================
BOOLEAN MassStorage_Init(void)
{

  BOOLEAN result;


  if (sAttachDevice->saCD[0].sInterface[0].bInterfaceClass!=0x08)
  {
    DRV_HOST_DBG(printf("not mass storage class!\r\n"));
    return FALSE;
  }
  DRV_HOST_DBG(printf("Mass storage device..\r\n"));
  Init_Mass_Storage_Structure();

  OTGH_PT_Bulk_Init();

  result=bSCSI_Initial();
  if(!result)
  {
    MsOS_DelayTask(500);  //081205 at SEC, disk needs more time for TUR OK
    result=bSCSI_Initial();
  }

  return result;
}




#if 0
//====================================================================
// * Function Name: OTGH_PT_Bulk_Close
// * Description:
// * Input: none
// * OutPut: none
//====================================================================
void OTGH_PT_Bulk_Close(void)
{

  //<5>.Hang the qHD
  if (sAttachDevice->saCD[0].sInterface[0].sED[0].bED_bmAttributes==OTGH_ED_BULK)
  { //<5.1>.stop Asynchronous Schedule
    flib_Host20_Asynchronous_Setting(HOST20_Disable);
    if (Host20_qHD_List_Bulk0.bMaxPacketSize1> 2)           //larger than 512
    {//Support only 2 QHD
      mwHost20_CurrentAsynchronousAddr_Set(Host20_STRUCTURE_qHD_BASE_ADDRESS);
    }
    else
    {
      //<5.2>.Hang the qHD for ED0~ED3
      SetPointer(&(Host20_qHD_List_Control1.bNextQHDPointer3),VirtoPhyAddr((UINT16)&Host20_qHD_List_Control0));

    }

    //<5.2>.Enable Asynchronous Schedule
    flib_Host20_Asynchronous_Setting(HOST20_Enable);
  }

}
#endif
extern void Dump_Data(UINT16 addr,UINT16 sz);
extern BOOLEAN FirstBulkOut,FirstBulkIn;

//====================================================================
// * Function Name: OTGH_PT_Bulk_Init
// * Description:
// * Input: none
// * OutPut: none
//====================================================================
void OTGH_PT_Bulk_Init(void)
{

  UINT16 wMaxPacketSize;

  // UINT8 *wTemp;

  wMaxPacketSize=sAttachDevice->saCD[0].sInterface[0].sED[0].bED_wMaxPacketSizeHighByte;
  wMaxPacketSize=(wMaxPacketSize<<8)+(sAttachDevice->saCD[0].sInterface[0].sED[0].bED_wMaxPacketSizeLowByte);



  //<5>.Hook the qHD
  if (sAttachDevice->saCD[0].sInterface[0].sED[0].bED_bmAttributes==OTGH_ED_BULK)
  { //<5.1>.stop Asynchronous Schedule
    //flib_Host20_Asynchronous_Setting(HOST20_Disable);
    //mbHost20_USBCMD_AsynchronousEnable_Clr();

    mbHost20_USBCMD_AsynchronousEnable_Clr();
    while(mwHost20_USBSTS_AsynchronousStatus_Rd()>0);


      //<5.2>.Hook the qHD for ED0~ED3
     pHost20_qHD_List_Control1->bNextQHDPointer=(VirtoPhyAddr((U32)pHost20_qHD_List_Bulk0)>>5);
     pHost20_qHD_List_Bulk0->bNextQHDPointer=(VirtoPhyAddr((U32)pHost20_qHD_List_Bulk1)>>5);
     pHost20_qHD_List_Bulk1->bNextQHDPointer=(VirtoPhyAddr((U32)pHost20_qHD_List_Control0)>>5);




    //<5.2>.Enable Asynchronous Schedule
    //flib_Host20_Asynchronous_Setting(HOST20_Enable);

  }


  FirstBulkIn=TRUE;
  FirstBulkOut=TRUE;

  //Setting Max Packet Size and print message
  wMaxPacketSize=sAttachDevice->saCD[0].sInterface[0].sED[0].bED_wMaxPacketSizeHighByte;
  wMaxPacketSize=(wMaxPacketSize<<8)+(sAttachDevice->saCD[0].sInterface[0].sED[0].bED_wMaxPacketSizeLowByte);
    pHost20_qHD_List_Bulk0->bMaxPacketSize=wMaxPacketSize;
    pHost20_qHD_List_Bulk1->bMaxPacketSize=wMaxPacketSize; //Suppose In/Out have the same Max packet Size
    pHost20_qHD_List_Bulk0->bDeviceAddress=sAttachDevice->bAdd;
    pHost20_qHD_List_Bulk1->bDeviceAddress=sAttachDevice->bAdd;
    pHost20_qHD_List_Bulk0->bEdNumber=(sAttachDevice->saCD[0].sInterface[0].sED[0].bED_EndpointAddress) & 0x0f; //set endpoint address
    pHost20_qHD_List_Bulk1->bEdNumber=(sAttachDevice->saCD[0].sInterface[0].sED[1].bED_EndpointAddress) & 0x0f; //set endpoint address

  //printf("add:%02bx\r\n",psDevice_AP->bAdd);
  //printf("Endpoint 1 addr: %02bx\r\n", Host20_qHD_List_Bulk0.bEdNumber);
  //printf("Endpoint 2 addr: %02bx\r\n", Host20_qHD_List_Bulk1.bEdNumber);


  //printf(">>> Bulk In/Out Max Packet Size = %x\r\n",wMaxPacketSize);

  //For Bulk Structure
  //sOTGH_PT_BLK=( OTGH_PT_BLK_Struct *)flib_Host20_GetStructure(Host20_MEM_TYPE_4K_BUFFER);//2=>4kBuffer;
  //sOTGH_PT_BLK=(OTGH_PT_BLK_Struct xdata *)OTGH_PT_BLK_DATA;            //bulk QH data structure
  //printf("PT_BLK:%x\r\n",(U16)&OTGH_PT_BLK);
  //printf("OTGH_PT_BLK_DATA:%x\r\n",OTGH_PT_BLK_DATA);
  //OTGH_PT_BLK->wDataRange=2*1024*1; ////2k


  if (((sAttachDevice->saCD[0].sInterface[0].sED[0].bED_EndpointAddress)&BIT7)>0)
  { OTGH_PT_BLK->bInQHDArrayNum=0;//Array 0           //for in 0, for out,1
    OTGH_PT_BLK->bOutQHDArrayNum=1;//Array 0
  }
  else
  {
    OTGH_PT_BLK->bInQHDArrayNum=1;//Array 0            //for in 1 for out,0
    OTGH_PT_BLK->bOutQHDArrayNum=0;//Array 0
  }

  OTGH_PT_BLK->bStatus = HOST20_OK;
}
#endif //#if defined(MSOS_TYPE_NOS)


