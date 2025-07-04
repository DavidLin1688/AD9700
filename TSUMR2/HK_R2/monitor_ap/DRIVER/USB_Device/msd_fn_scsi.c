#include "ms_config.h"
#include "type.h"
#include "Globalvar.h"
#include "ms_msd_fn_xfer.h"
#include "ms_otg.h"
#include "ms_usb.h"
#include "ms_msd_fn_scsi.h"
#include "ms_drc.h"
#include "sysusbdrv.h"
#include "drvUSBDwld.h"
#ifdef DMA
#include "ms_dma.h"
#endif

#include "board.h"

extern void printMsg( char *str );
extern void printData( char *str, unsigned int value );

#define SCSI_DEBUG    1
#if ENABLE_DEBUG&&SCSI_DEBUG
#define SCSI_printData(str, value)   printData(str, value)
#define SCSI_printMsg(str)           printMsg(str)
#else
#define USB_printData(str, value)
#define USB_printMsg(str)
#endif

#ifndef UNUSED //to avoid compile warnings...
#define UNUSED(var) (void)((var) = (var))
#endif

#ifdef RAMDISK
U8 _RamDisk_R(U8 u8Disk, U32 u32StartSector, U32 u32SectorCount, U32 u32MiuAddr)
{
	if (u32StartSector>=DISKSIZE)
		return 1;
	u32SectorCount*=512;
	u32StartSector*=512;
	memcpy((void *)u32MiuAddr, (void *)(Storage_Mem_Addr+u32StartSector), u32SectorCount);

	return 0;
}

U8 _RamDisk_W(U8 u8Disk, U32 u32StartSector, U32 u32SectorCount, U32 u32MiuAddr)
{
    if (u32StartSector>=DISKSIZE)
        return 1;

    u32SectorCount*=512;
    u32StartSector*=512;
    memcpy((void *)(Storage_Mem_Addr+u32StartSector), (void *)u32MiuAddr, u32SectorCount);

    return 0;
}
#endif
//void Clear_TestUnitReady_Flag(void)	// 20110310
//{
//    TestUnitReadyCMD = 0;
//}

//bool Get_TestUnitReady_Flag(void)	// 20110310
//{
//    return TestUnitReadyCMD;
//}

void Return_CSW_to_Host(MSDFN_BOT_CBW_STRU *cbw,MSDFN_BOT_CSW_STRU *csw,U8 MSDFN_COMMAND,USB_VAR *gUSBStruct)
{
    csw->signature     = MSDFN_BOT_CSW_SIGNATURE;
    csw->tag           = cbw->tag;
    csw->residue       = gUSBStruct->otgfun_residue;
    csw->status        = MSDFN_COMMAND;

    USB_MSDFN_Encode_CSW(csw,(U8 *)gUSBStruct->otgCSW_Addr);
    SDRAM2USB_Bulk(gUSBStruct->otgCSW_Addr,MSDFN_BOT_CSW_LENGTH,gUSBStruct);

	USB_Set_ClrRXMode1();
}

extern void *otg_memset(void *s, int c, unsigned int n);
U8 FnReqSen_Command(MSDFN_BOT_CBW_STRU *cbw,USB_VAR *gUSBStruct)
{
	U8 status;
#if 0
	U8 req_sense[] =
	{
        0x70, /* Error Code */
        0x00,
        0x00, /* ILLEGAL Request */
        0x00, 0x00, 0x00, 0x00,
        0x0A, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00
	};
#else
	U8 req_sense[18];
	otg_memset(req_sense, 0, 18);
	req_sense[0]=0x70;
	req_sense[7]=0x0A;
#endif
	req_sense[2] = gUSBStruct->otgFSenseKey;
	req_sense[12] = gUSBStruct->otgFASC;
	req_sense[13] = gUSBStruct->otgFASCQ;
	gUSBStruct->otgactualXfer_len = REQ_SENS_LEN;
	gUSBStruct->otgdataXfer_dir = DATA_IN;
	if (cbw->dxfer_length < REQ_SENS_LEN)
		gUSBStruct->otgfun_residue = -1;
	else
		gUSBStruct->otgfun_residue = cbw->dxfer_length-REQ_SENS_LEN;

	status=SDRAM2USB_Bulk((U32)&req_sense[0],REQ_SENS_LEN,gUSBStruct);
	return status;
}

#if 1//RAMDISK
U8 FnRD_FMT_CAPC_Command(MSDFN_BOT_CBW_STRU *cbw,U32 nBlkNo, U32 nBlkSize,USB_VAR *gUSBStruct)
{
	u8 status;

	u8 aRdCapacity[] = {
		0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
	};

    // fix coverity error-No_EFFECT
	//*cbw = *cbw;
	//nBlkNo = nBlkNo;
	//nBlkSize = nBlkSize;
	//*gUSBStruct = *gUSBStruct;
	UNUSED(*cbw);
    UNUSED(nBlkNo);
    UNUSED(nBlkSize);

#if (DISKSIZE == 0)

#else
	nBlkNo--;
	aRdCapacity[3] = (u8) (nBlkNo & 0x00FF);
	aRdCapacity[2] = (u8) ((nBlkNo >> 8) & 0x00FF);
	aRdCapacity[1] = (u8) ((nBlkNo >> 16) & 0x00FF);
	aRdCapacity[0] = (u8) ((nBlkNo >> 24) & 0x00FF);

	aRdCapacity[7] = (u8) (nBlkSize & 0x00FF);
	aRdCapacity[6] = (u8) ((nBlkSize >> 8) & 0x00FF);
	aRdCapacity[5] = (u8) ((nBlkSize >> 16) & 0x00FF);
	aRdCapacity[4] = (u8) ((nBlkSize >> 24) & 0x00FF);

	gUSBStruct->otgactualXfer_len = RD_CAPCY_LEN;
	gUSBStruct->otgdataXfer_dir = DATA_IN;

	if (cbw->dxfer_length < RD_CAPCY_LEN)
		gUSBStruct->otgfun_residue = -1;
	else
		gUSBStruct->otgfun_residue = cbw->dxfer_length - RD_CAPCY_LEN;
#endif
	status=SDRAM2USB_Bulk((U32)&aRdCapacity[0],INQ_DATA_LEN,gUSBStruct);

	return status;
}
#endif

U8 FnInquiry_Command(MSDFN_BOT_CBW_STRU *cbw,USB_VAR *gUSBStruct)
{
    U8 status;
    U8 inquiry[] =
    {
		0x00, /* Device is connected to LUN	 : Disk Drive */
#if NON_REMOVABLE_DRIVE
#message "Non removable disk"
		0x01, /* Non-Removable */
		0x02, /* Device supports SCSI-2 */
		0x02, /* Data Format  : SCSI-2 */
#else
		0x80, /* Removable */
		0x00, /* Device supports SCSI-2 */
		0x00, /* Data Format  : SCSI-2 */
#endif
		31, /* Number of additional Bytes to Follow */
		0x00, /* Reserved */
		0x00, /* Reserved  : Some fields suported in SCSI-3 */
		0x00, /* Device Supports Synchronus Transfer */
		/* These 8-bytes describe the Manufacturer */
		'G','C','R','E','A','D','E','R',
		/* These 16 bytes describe Product */
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0
	};
	//printf("FnInquiry_Command\n");
	gUSBStruct->otgactualXfer_len = INQ_DATA_LEN;
	gUSBStruct->otgdataXfer_dir = DATA_IN;
	if (cbw->dxfer_length < INQ_DATA_LEN)
		gUSBStruct->otgfun_residue = -1; // TODO: set CSW residue to "-1" is unique?
	else
		gUSBStruct->otgfun_residue = cbw->dxfer_length - INQ_DATA_LEN;

	status=SDRAM2USB_Bulk((U32)&inquiry[0],INQ_DATA_LEN,gUSBStruct);

	return status;
}

#if 0
U8 CheckDevice(MSDFN_BOT_CBW_STRU *cbw,MSDFN_BOT_CSW_STRU *csw,USB_VAR *gUSBStruct)
{
	U8  u8status = 0;
#ifdef RAMDISK
	csw->status = MSDFN_BOT_COMMAND_PASSED;
	gUSBStruct->otgFSenseKey = KEY_NO_SENSE;
	gUSBStruct->otgFASC = 0;
	gUSBStruct->otgFASCQ = 0;
	u8status = 1;
#else
	//do nothing
#endif
	return  u8status;
}

U8 FnRdCap_Command(MSDFN_BOT_CBW_STRU *cbw,U32 noblk,U32 blksize,USB_VAR *gUSBStruct)
{
    U8 status;
    U8 rd_capacity[] =
    {
      0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
    };
    noblk--;
#if (DISKSIZE == 0)


#else
    rd_capacity[3] = (U8) (noblk & 0x00FF);
    rd_capacity[2] = (U8) ((noblk >> 8) & 0x00FF);
    rd_capacity[1] = (U8) ((noblk >> 16) & 0x00FF);
    rd_capacity[0] = (U8) ((noblk >> 24) & 0x00FF);
    rd_capacity[7] = (U8) (blksize & 0x00FF);
    rd_capacity[6] = (U8) ((blksize >> 8) & 0x00FF);
    rd_capacity[5] = (U8) ((blksize >> 16) & 0x00FF);
    rd_capacity[4] = (U8) ((blksize >> 24) & 0x00FF);
#endif
    gUSBStruct->otgactualXfer_len = RD_CAPCY_LEN;
    gUSBStruct->otgdataXfer_dir = DATA_IN;
    if (cbw->dxfer_length < RD_CAPCY_LEN)
        gUSBStruct->otgfun_residue = -1;
    else
        gUSBStruct->otgfun_residue = cbw->dxfer_length-RD_CAPCY_LEN;
    status=SDRAM2USB_Bulk((U32)&rd_capacity[0],RD_CAPCY_LEN,gUSBStruct);
    //    printf("ReadCapacity_status:%x \n",status);
    return status;
}

U8 FnTestRdy_Command(MSDFN_BOT_CBW_STRU *cbw,USB_VAR *gUSBStruct)
{
    U8 status = USB_ST_NOERROR;
    gUSBStruct->otgactualXfer_len = 0;
    gUSBStruct->otgdataXfer_dir = 0;
    gUSBStruct->otgfun_residue = 0;
    if (gUSBStruct->otgStop)
    {
        status = MSDFN_BOT_COMMAND_FAILED;
        gUSBStruct->otgFSenseKey = KEY_NOT_READY;
        gUSBStruct->otgFASC = ADDKEY_MEDIUM_NOT_PRESENT;
        gUSBStruct->otgFASCQ = 0;
    }
    return  status;
}

U8 FnStartStop_Command(MSDFN_BOT_CBW_STRU *cbw,USB_VAR *gUSBStruct)
{
    gUSBStruct->otgactualXfer_len = 0;
    gUSBStruct->otgdataXfer_dir = 0;
    gUSBStruct->otgfun_residue = 0;
    if (cbw->cmd_bytes[4] & 0x02)   // stop
        gUSBStruct->otgStop = 1;
    else
        gUSBStruct->otgStop = 0;
    return  USB_ST_NOERROR;
}

U8 FnVerify_Command(MSDFN_BOT_CBW_STRU *cbw,USB_VAR *gUSBStruct)
{
    gUSBStruct->otgactualXfer_len = 0;
    gUSBStruct->otgdataXfer_dir = 0;
    gUSBStruct->otgfun_residue = 0;
    return  USB_ST_NOERROR;
}

U8 FnModeSense_Command(MSDFN_BOT_CBW_STRU *cbw,USB_VAR *gUSBStruct)
{
    U8 status;
    U8 mode_sense[] = {0x03,0x00,0x00,0x00};
    gUSBStruct->otgactualXfer_len = MODE_SEN_LEN;
    gUSBStruct->otgdataXfer_dir = DATA_IN;
    if (cbw->dxfer_length < MODE_SEN_LEN)
        gUSBStruct->otgfun_residue = -1;
    else
        gUSBStruct->otgfun_residue = cbw->dxfer_length-MODE_SEN_LEN;
    status=SDRAM2USB_Bulk((U32)&mode_sense[0],MODE_SEN_LEN,gUSBStruct);
    return status;
}

U8 FnPrevent_Command(MSDFN_BOT_CBW_STRU *cbw,USB_VAR *gUSBStruct)
{
    U8 status;
    gUSBStruct->otgactualXfer_len = 0;
    gUSBStruct->otgdataXfer_dir = 0;
    gUSBStruct->otgfun_residue = 0;
    if (cbw->cmd_bytes[4]!=0)
    {
        status = MSDFN_BOT_COMMAND_FAILED;
        gUSBStruct->otgFSenseKey = 0x05;
        gUSBStruct->otgFASC= 0x24;
        gUSBStruct->otgFASCQ = 0x00;
    }
    else
        status = USB_ST_NOERROR;
    return status;
}
#endif

U8 FnRdCap_Command(MSDFN_BOT_CBW_STRU *cbw,U32 noblk,U32 blksize,USB_VAR *gUSBStruct)
{
    U8 status;
    U8 rd_capacity[] =
    {
      0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
    };
    noblk--;

	//*cbw = *cbw;
	//blksize = blksize;
	UNUSED(blksize);
#if (DISKSIZE == 0)


#else
    rd_capacity[3] = (U8) (noblk & 0x00FF);
    rd_capacity[2] = (U8) ((noblk >> 8) & 0x00FF);
    rd_capacity[1] = (U8) ((noblk >> 16) & 0x00FF);
    rd_capacity[0] = (U8) ((noblk >> 24) & 0x00FF);
    rd_capacity[7] = (U8) (blksize & 0x00FF);
    rd_capacity[6] = (U8) ((blksize >> 8) & 0x00FF);
    rd_capacity[5] = (U8) ((blksize >> 16) & 0x00FF);
    rd_capacity[4] = (U8) ((blksize >> 24) & 0x00FF);
#endif
    gUSBStruct->otgactualXfer_len = RD_CAPCY_LEN;
    gUSBStruct->otgdataXfer_dir = DATA_IN;
    if (cbw->dxfer_length < RD_CAPCY_LEN)
        gUSBStruct->otgfun_residue = -1;
    else
        gUSBStruct->otgfun_residue = cbw->dxfer_length-RD_CAPCY_LEN;
    status=SDRAM2USB_Bulk((U32)&rd_capacity[0],RD_CAPCY_LEN,gUSBStruct);
    //    printf("ReadCapacity_status:%x \n",status);
    return status;
}

U8 FnVendor_XROM_Command(MSDFN_BOT_CBW_STRU *cbw, USB_VAR *gUSBStruct)
{
    U32             u32tmpVal, u32ReqLen, buf_len=0;
    U8              status = 0;
    vendorCmdStruct *pCmdStruct = (vendorCmdStruct *)gUSBStruct->ptrVCmdStruct;
	buf_len = buf_len;

#if 0//defined(INTEL_8051)
	*((U8 *)&u32ReqLen + 0) = cbw->cmd_bytes[6];
    *((U8 *)&u32ReqLen + 1) = cbw->cmd_bytes[7];
    *((U8 *)&u32ReqLen + 2) = cbw->cmd_bytes[8];
    *((U8 *)&u32ReqLen + 3) = cbw->cmd_bytes[9];
#else
	*((U8 *)&u32ReqLen + 0) = cbw->cmd_bytes[9];
    *((U8 *)&u32ReqLen + 1) = cbw->cmd_bytes[8];
    *((U8 *)&u32ReqLen + 2) = cbw->cmd_bytes[7];
    *((U8 *)&u32ReqLen + 3) = cbw->cmd_bytes[6];
#endif
	//printData("@@@FnVendor_XROM_Command:0x%x, len:0x%x\n",cbw->cmd_bytes[1],u32ReqLen);

#if 0
	SCSI_printData("@@@cmd_bytes[0]:0x%x\n",cbw->cmd_bytes[0]);
	SCSI_printData("@@@cmd_bytes[1]:0x%x\n",cbw->cmd_bytes[1]);
	SCSI_printData("@@@cmd_bytes[2]:0x%x\n",cbw->cmd_bytes[2]);
	SCSI_printData("@@@cmd_bytes[3]:0x%x\n",cbw->cmd_bytes[3]);
	SCSI_printData("@@@cmd_bytes[4]:0x%x\n",cbw->cmd_bytes[4]);
	SCSI_printData("@@@cmd_bytes[5]:0x%x\n",cbw->cmd_bytes[5]);
	SCSI_printData("@@@cmd_bytes[6]:0x%x\n",cbw->cmd_bytes[6]);
	SCSI_printData("@@@cmd_bytes[7]:0x%x\n",cbw->cmd_bytes[7]);
	SCSI_printData("@@@cmd_bytes[8]:0x%x\n",cbw->cmd_bytes[8]);
	SCSI_printData("@@@cmd_bytes[9]:0x%x\n",cbw->cmd_bytes[9]);
	SCSI_printData("@@@cmd_bytes[10]:0x%x\n",cbw->cmd_bytes[10]);
	SCSI_printData("@@@cmd_bytes[11]:0x%x\n",cbw->cmd_bytes[11]);
	SCSI_printData("@@@cmd_bytes[12]:0x%x\n",cbw->cmd_bytes[12]);
	SCSI_printData("@@@cmd_bytes[13]:0x%x\n",cbw->cmd_bytes[13]);
	SCSI_printData("@@@cmd_bytes[14]:0x%x\n",cbw->cmd_bytes[14]);
	SCSI_printData("@@@cmd_bytes[15]:0x%x\n",cbw->cmd_bytes[15]);
	SCSI_printData("u32ReqLen_L:0x%x\n",u32ReqLen);
	SCSI_printData("u32ReqLen_H:0x%x\n",u32ReqLen>>16);
#endif

    switch(cbw->cmd_bytes[1])
    {
        case XROM_USB_DOWNLOAD_KEEP:    /* USB Download */
        case XROM_USB_DOWNLOAD_END:     /* Last packet */
            /* Inhibit interleaving download and upload operations. */
            //if (pCmdStruct->currUpldBytes || pCmdStruct->currDwldBytes)
            //{
            //   return  USB_ST_NORESPONSE;
            //}
            pCmdStruct->currDwldBytes = u32ReqLen;
            /* Actual USB_DOWNLOAD vendor command packet length must be the multiple of CYGHWR_HAL_MIPS_MSTAR_HIFBUF_SIZE */
            u32ReqLen += 512 - 1;
            u32ReqLen &= ~(512 - 1);
#ifdef DMA
			//SCSI_printData("u32ReqLen:0x%x\n",u32ReqLen);
			status = USB2SDRAM_BulkDMA((U32)pCmdStruct->ucptrDataBuf, u32ReqLen, gUSBStruct);
#else
            status = USB2SDRAM_Bulk((U32)pCmdStruct->ucptrDataBuf, u32ReqLen, gUSBStruct);
#endif
            //hal_dcache_invalidate(pCmdStruct->ucptrDataBuf, u32ReqLen);

#if 1 // fix early ping, 20110919
            USB_Set_ClrRXMode1();
			USB_REG_WRITE8(M_REG_DMA_MODE_CTL+1, (USB_REG_READ8(M_REG_DMA_MODE_CTL+1)) | 0x20); //jimy patch
#endif
            if(cbw->cmd_bytes[1] == XROM_USB_DOWNLOAD_END)  /* Last packet */
                pCmdStruct->bDwldEnd = 1;
            break;
        case XROM_USB_UPLOAD_SIZE:
#if 1 // fix early ping, 20110919
            USB_Set_ClrRXMode1();
#endif
            status = SDRAM2USB_Bulk((U32)pCmdStruct->ptrPPB2Buf, u32ReqLen, gUSBStruct);
			otg_memset(pCmdStruct->ptrPPB2Buf,0x0,0x4);
            break;
        case XROM_USB_UPLOAD_FIXEDLEN:
        case XROM_USB_UPLOAD_VARLEN:    /* USB upload (Variable Length) */
#if 1 // fix early ping, 20110919
            USB_Set_ClrRXMode1();
#endif
            /* Inhibit interleaving download and upload operations. */
            if (pCmdStruct->currDwldBytes)
                return  USB_ST_NORESPONSE;
            status = SDRAM2USB_Bulk((U32)pCmdStruct->ucptrDataBuf + pCmdStruct->currUpldOffset,
                                    u32ReqLen, gUSBStruct);
            pCmdStruct->currUpldOffset += u32ReqLen;
            if (pCmdStruct->currUpldBytes > u32ReqLen)
                pCmdStruct->currUpldBytes -= u32ReqLen;
            else
                pCmdStruct->currUpldBytes = 0;
            break;
        case XROM_USB_ERR_CODE:
            u32tmpVal = pCmdStruct->errCode;
            status = SDRAM2USB_Bulk((U32)&u32tmpVal, u32ReqLen, gUSBStruct);
            break;
		//case XROM_USB_UPLOAD_LOG:
		//	buf_len = USB_GET_LOG(u32ReqLen);
		//	status = SDRAM2USB_Bulk((U32)pCmdStruct->ptrTmpHifBuf, buf_len, gUSBStruct);
		//	break;

        case XROM_USB_GET_DP_SYNC_CNT:
            pCmdStruct->ptrPPB2Buf[0] = 1; // fix return 1 device
            pCmdStruct->ptrPPB2Buf[1] = 0;
            USB_Set_ClrRXMode1();
            status = SDRAM2USB_Bulk((U32)pCmdStruct->ptrPPB2Buf, u32ReqLen, gUSBStruct);
            otg_memset(pCmdStruct->ptrPPB2Buf,0x0,0x4);
        break;

        case XROM_USB_GET_UPDATE_STATUS:
            if(MST_FW_Update_Bitmap > 1)
            {
                U8 Tx_Update_Status = 0;

                if((MST_UpdateStatus == MST_UPDATE_STATUS_FAIL) || (Tx_Update_Status == MST_UPDATE_STATUS_FAIL))
                     pCmdStruct->ptrPPB2Buf[0] = MST_UPDATE_STATUS_FAIL;
                else if((MST_UpdateStatus == MST_UPDATE_STATUS_SUCCESS) && (Tx_Update_Status == MST_UPDATE_STATUS_SUCCESS))
                     pCmdStruct->ptrPPB2Buf[0] = MST_UPDATE_STATUS_SUCCESS;
                else
                    pCmdStruct->ptrPPB2Buf[0] = MST_UPDATE_STATUS_INPROGRESS;
            }
            else
            {
                pCmdStruct->ptrPPB2Buf[0] = MST_UpdateStatus;
            }

            pCmdStruct->ptrPPB2Buf[1] = 0;
            USB_Set_ClrRXMode1();
            status = SDRAM2USB_Bulk((U32)pCmdStruct->ptrPPB2Buf, u32ReqLen, gUSBStruct);
            otg_memset(pCmdStruct->ptrPPB2Buf,0x0,0x4);
        break;

        case XROM_USB_SET_UPDATE_BITMAP:
            MST_FW_Update_Bitmap = ((U16)cbw->cmd_bytes[2]<<8)|cbw->cmd_bytes[3];
        break;

        case XROM_USB_SET_DELAY_TIME:
            MST_FW_Update_DealyTime = ((U16)cbw->cmd_bytes[2]<<8)|cbw->cmd_bytes[3];
        break;

#if ENABLE_USB_DEVICE_UPDATE_CODE
        case XROM_USB_GET_PROGRAMMED_SIZE:
            pCmdStruct->ptrPPB2Buf[0] = (U8)((SPIWCnt >> 24 ) & 0xFF);
            pCmdStruct->ptrPPB2Buf[1] = (U8)((SPIWCnt >> 16 ) & 0xFF);
            pCmdStruct->ptrPPB2Buf[2] = (U8)((SPIWCnt >> 8 ) & 0xFF);;
            pCmdStruct->ptrPPB2Buf[3] = (U8)(SPIWCnt & 0xFF);
            USB_Set_ClrRXMode1();
            status = SDRAM2USB_Bulk((U32)pCmdStruct->ptrPPB2Buf, u32ReqLen, gUSBStruct);
            otg_memset(pCmdStruct->ptrPPB2Buf,0x0,0x4);
        break;
#endif

		case XROM_USB_INVALID_FILE:
			break;

        case XROM_USB_FILE_SIZE:
#if 0
//			UploadFileSize = (U32)(cbw->cmd_bytes[2]<<8|cbw->cmd_bytes[3])*1024;
			SCSI_printData("UploadFileSize: H:0x%x  ",((U32)(cbw->cmd_bytes[2]<<8|cbw->cmd_bytes[3])*1024)>>16);
			SCSI_printData("L:0x%x\n",((U32)(cbw->cmd_bytes[2]<<8|cbw->cmd_bytes[3])*1024));
#endif
			break;

		case XROM_USB_REBOOT_SYS:
			break;

		case XROM_USB_WRITE_SC_REG:
			break;

		case XROM_USB_READ_SC_REG:
			break;

		case XROM_USB_WRITE_NM_REG:
			break;

		case XROM_USB_READ_NM_REG:
			break;

        default:
            break;
    }
    gUSBStruct->otgfun_residue -= u32ReqLen; // 20100811 G1 U02
    if (gUSBStruct->otgfun_residue < 0)
    {
        gUSBStruct->otgfun_residue = -1;
    }
    return  status;
}

U8 FnVendor_Cmds(void *pcbw, void *pcsw, void *pUsbStruct)
{
	MSDFN_BOT_CBW_STRU  *cbwPtr = (MSDFN_BOT_CBW_STRU *)pcbw;
	USB_VAR *gUSBStruct = (USB_VAR *)pUsbStruct;
	U8  status = USB_ST_NOERROR;
	U8  cmdByte = cbwPtr->cmd_bytes[0];
    pcsw = pcsw;

	if (cmdByte == SCSI_VENDOR_XROM )
		status = FnVendor_XROM_Command(cbwPtr,gUSBStruct);
    else
    {
        /* Command Not Support */
        if (cbwPtr->dxfer_length != 0)
        {
            if (cbwPtr->dir_flag & 0x80)
                USB_Endpoint_Bulk_In_Stall(gUSBStruct);
            else
                USB_Endpoint_Bulk_Out_Stall(gUSBStruct);
        }
        gUSBStruct->otgFSenseKey = 0x05;
        gUSBStruct->otgFASC = 0x24;
        gUSBStruct->otgFASCQ = 0x00;
    }
    return  status;
}
#if 0
U8 FnRd10_Command(MSDFN_BOT_CBW_STRU *cbw,USB_VAR *gUSBStruct)
{
	U8      status = USB_ST_NOERROR, CRSts = 0x00, *databuf;
	U16     nblocks = 0x00;
	U32     block_num = 0x00, XferSize, tmpactXfer;
	if (cbw->cmd_bytes[0] & 0x20)
    {
        *((U8 *)&block_num+0)=cbw->cmd_bytes[5];
        *((U8 *)&block_num+1)=cbw->cmd_bytes[4];
        *((U8 *)&block_num+2)=cbw->cmd_bytes[3];
        *((U8 *)&block_num+3)=cbw->cmd_bytes[2];
        *((U8 *)&nblocks+1)=cbw->cmd_bytes[7];
        *((U8 *)&nblocks+0)=cbw->cmd_bytes[8];
    }
	gUSBStruct->otgactualXfer_len = (U32)nblocks * SCSI_BLOCK_SIZE;
	tmpactXfer = gUSBStruct->otgactualXfer_len;  //wayne add
	gUSBStruct->otgdataXfer_dir = DATA_IN;
	if (cbw->dxfer_length < gUSBStruct->otgactualXfer_len)
		gUSBStruct->otgfun_residue = -1;
	else
        gUSBStruct->otgfun_residue = cbw->dxfer_length-gUSBStruct->otgactualXfer_len;
	databuf = (U8 *)gUSBStruct->ucptrDataBuf;
    //--------------add data read from device here-------------------------------------------
    //cut them into a lot of 4K buffers
    while (tmpactXfer)
    {
		if (tmpactXfer>USB_BUFSIZE)
			XferSize=USB_BUFSIZE;
		else
			XferSize=tmpactXfer;
#ifdef RAMDISK
		CRSts = _RamDisk_R(0, block_num, XferSize/0x200, (U32)databuf);
#endif
		status = SDRAM2USB_Bulk((U32)databuf,XferSize,gUSBStruct);  //wayne added
		block_num+=XferSize/0x200;
		tmpactXfer-=XferSize;
    }
	return status;
}

U8 FnWt10_Command(MSDFN_BOT_CBW_STRU *cbw,USB_VAR *gUSBStruct)
{
	U8      status = USB_ST_NOERROR, CRSts = 0x00, *databuf;
	U16     nblocks = 0x00;
	U32     block_num = 0x00, XferSize, tmpactXfer;

    if (cbw->cmd_bytes[0] & 0x20)
    {
        *((U8 *)&block_num+0)=cbw->cmd_bytes[5];
        *((U8 *)&block_num+1)=cbw->cmd_bytes[4];
        *((U8 *)&block_num+2)=cbw->cmd_bytes[3];
        *((U8 *)&block_num+3)=cbw->cmd_bytes[2];
        *((U8 *)&nblocks+1)=cbw->cmd_bytes[7];
        *((U8 *)&nblocks+0)=cbw->cmd_bytes[8];
    }
	gUSBStruct->otgactualXfer_len = (U32)nblocks * SCSI_BLOCK_SIZE;
	tmpactXfer = gUSBStruct->otgactualXfer_len;   //wayne add
	gUSBStruct->otgdataXfer_dir = DATA_OUT;
    if (cbw->dxfer_length < gUSBStruct->otgactualXfer_len)
        gUSBStruct->otgfun_residue = -1;
    else
        gUSBStruct->otgfun_residue = cbw->dxfer_length-gUSBStruct->otgactualXfer_len;

	databuf = (U8 *)gUSBStruct->ucptrDataBuf;
	while (tmpactXfer)
	{
		if (tmpactXfer>USB_BUFSIZE)
			XferSize=USB_BUFSIZE;
		else
			XferSize=tmpactXfer;
		status = USB2SDRAM_Bulk((U32)databuf,XferSize,gUSBStruct);
#ifdef RAMDISK
		CRSts = _RamDisk_W(0, block_num, XferSize/0x200,(U32)databuf);
#endif
		block_num+=XferSize/0x200;
		tmpactXfer-=XferSize;
	}
	return status;
}
#endif
U8 FnDisk_Cmds_Rom(void *pcbw, void *pcsw, void *pUsbStruct)
{
    MSDFN_BOT_CBW_STRU  *cbwPtr = (MSDFN_BOT_CBW_STRU *)pcbw;
    MSDFN_BOT_CSW_STRU  *cswPtr = (MSDFN_BOT_CSW_STRU *)pcsw;
    USB_VAR *gUSBStruct = (USB_VAR *)pUsbStruct;
    /* Not support standard SCSI disk related commands in ROM */
    cswPtr->status = MSDFN_BOT_COMMAND_FAILED;
    gUSBStruct->otgFSenseKey = KEY_NOT_READY;
    gUSBStruct->otgFASC = ADDKEY_MEDIUM_NOT_PRESENT;
    gUSBStruct->otgFASCQ = 0;
    if (cbwPtr->dxfer_length != 0)
    {
        if (cbwPtr->dir_flag & 0x80)
            USB_Endpoint_Bulk_In_Stall(gUSBStruct);
        else
            USB_Endpoint_Bulk_Out_Stall(gUSBStruct);
    }

    return  USB_ST_STALL;
}

#if 0
U8 FnDisk_Cmds_Ram(void *pcbw, void *pcsw, void *pUsbStruct)
{
	MSDFN_BOT_CBW_STRU  *cbwPtr = (MSDFN_BOT_CBW_STRU *)pcbw;
	MSDFN_BOT_CSW_STRU  *cswPtr = (MSDFN_BOT_CSW_STRU *)pcsw;
	USB_VAR *gUSBStruct = (USB_VAR *)pUsbStruct;
    U8  status = USB_ST_NOERROR;
	U8  cmdByte = cbwPtr->cmd_bytes[0];
	if (CheckDevice(cbwPtr, cswPtr, gUSBStruct) == 0)
	{
		status = USB_ST_STALL;
		if (cbwPtr->dxfer_length != 0)
		{
			if (cbwPtr->dir_flag & 0x80)
				USB_Endpoint_Bulk_In_Stall(gUSBStruct);
			else
				USB_Endpoint_Bulk_Out_Stall(gUSBStruct);
		}
	}
	else if (cmdByte == SCSI_FN_READ_CAPACITY)
	{
		status = FnRdCap_Command(cbwPtr, DISKSIZE-1,
                                     SCSI_BLOCK_SIZE, gUSBStruct);
	}
	else if (cmdByte == SCSI_FN_STARTSTOP)
		status = FnStartStop_Command(cbwPtr, gUSBStruct);
	else if (cmdByte == SCSI_FN_TEST_UNIT_READY)
		status = FnTestRdy_Command(cbwPtr, gUSBStruct);
	else if (cmdByte == SCSI_FN_VERIFY)
		status = FnVerify_Command(cbwPtr, gUSBStruct);
	else if (cmdByte == SCSI_FN_MODE_SENSE)
		status = FnModeSense_Command(cbwPtr, gUSBStruct);
    else if (cmdByte == SCSI_FN_READ10)
        status = FnRd10_Command(cbwPtr, gUSBStruct);
    else if (cmdByte == SCSI_FN_WRITE10)
        status = FnWt10_Command(cbwPtr, gUSBStruct);
	else if (cmdByte == SCSI_FN_PREVENT)
		status = FnPrevent_Command(cbwPtr, gUSBStruct);
	else
	{
        /* Command Not Support */
        if (cbwPtr->dxfer_length != 0)
        {
            if (cbwPtr->dir_flag & 0x80)
                USB_Endpoint_Bulk_In_Stall(gUSBStruct);
            else
                USB_Endpoint_Bulk_Out_Stall(gUSBStruct);
        }
        gUSBStruct->otgFSenseKey = 0x05;
        gUSBStruct->otgFASC = 0x24;
        gUSBStruct->otgFASCQ = 0x00;
	}
	return  status;
}
#endif

void MSDFNCMDloop(USB_VAR *gUSBStruct, U8 *VendorCMD)
{
	MSDFN_BOT_CBW_STRU  cbw;
	MSDFN_BOT_CSW_STRU  csw;
	U8  status = USB_ST_NOERROR;
	U8  ep, i;

#ifdef RAMDISK
	RamDisk_Init();
#endif

	if (gUSBStruct->otgMassCmdRevFlag == 1)
	{
		gUSBStruct->otgResetComplete=0; // 20100819 G1 U02
		ep = USB_Ret_Blt_EP_Object(EP_TX);
		//USB_DRC_Index_Select(gUSBStruct->otgUSB_EP[ep].BltEP);
		gUSBStruct->otgMassCmdRevFlag = 0;
		USB_MSDFN_Decode_CBW((U8 *)gUSBStruct->otgCBWCB_Addr, &cbw);

		if (gUSBStruct->otgUSB_EP[ep].BytesProcessed == MSDFN_BOT_CBW_LENGTH)
		{
            if ((cbw.signature == MSDFN_BOT_CBW_SIGNATURE) && !(cbw.max_lun & MSDFN_BOT_LUN_MASK) &&
                (cbw.max_lun <= gUSBStruct->otgPerMassmax_Lun))
                gUSBStruct->otgfun_residue = cbw.dxfer_length;
			else
            {
                if (cbw.dxfer_length != 0)
                {
                    if (cbw.dir_flag & 0x80)
                        USB_Endpoint_Bulk_In_Stall(gUSBStruct);
                    else
                        USB_Endpoint_Bulk_Out_Stall(gUSBStruct);
                }
                if (gUSBStruct->otgResetComplete == 0) // 20100819 G1 U02
                {
                    Return_CSW_to_Host(&cbw, &csw, MSDFN_BOT_PHASE_ERROR, gUSBStruct);
                }
                return;
            }
		}
		else
		{
			if (cbw.dxfer_length != 0)
			{
				if (cbw.dir_flag & 0x80)
					USB_Endpoint_Bulk_In_Stall(gUSBStruct);
				else
					USB_Endpoint_Bulk_Out_Stall(gUSBStruct);
			}
			if (gUSBStruct->otgResetComplete == 0) // 20100819 G1 U02
				Return_CSW_to_Host(&cbw, &csw, MSDFN_BOT_PHASE_ERROR, gUSBStruct);
			return;
		}
		USB_REG_WRITE8(M_REG_INTRUSBE, 0x0); // 20100812, disable reset int, G1 U02
		/* Parse SCSI command */
		//*(volatile unsigned int *)(0x1f206700)=(cbw.cmd_bytes[0]);
		if (cbw.cmd_bytes[0]==  SCSI_FN_REQUEST_SENSE)
			status = FnReqSen_Command(&cbw, gUSBStruct);
		else if (cbw.cmd_bytes[0]== SCSI_FN_INQUIRY )
			status = FnInquiry_Command(&cbw, gUSBStruct);
#if 1//RAMDISK
		else if (cbw.cmd_bytes[0]== SCSI_FN_RD_FMT_CAPC )
		{
			status = FnRD_FMT_CAPC_Command(&cbw, 0,SCSI_BLOCK_SIZE, gUSBStruct);
		}
#endif
		else if (cbw.cmd_bytes[0] >= SCSI_1STID_VENDOR)
		{
			status = FnVendor_Cmds(&cbw, &csw, gUSBStruct);//fpSCSI_vendor(&cbw, &csw, gUSBStruct);

            for(i=0; i<16; i++)
                VendorCMD[i] = cbw.cmd_bytes[i];
		}
		else if (cbw.cmd_bytes[0] == SCSI_FN_READ_CAPACITY)
		{
			status = FnRdCap_Command(&cbw, DISKSIZE-1,
                                     SCSI_BLOCK_SIZE, gUSBStruct);
		}
		else
        {
            status = FnDisk_Cmds_Rom(&cbw, &csw, gUSBStruct);//fpSCSI_disk(&cbw, &csw, gUSBStruct);
            if (cbw.cmd_bytes[0] ==  SCSI_FN_TEST_UNIT_READY)	// 20110310
            {
                 //TestUnitReadyCMD = 1;	// 20110310
            }
        }
		USB_REG_WRITE8(M_REG_INTRUSBE, 0xf7); // 20100812, enable reset int, G1 U02
		if (gUSBStruct->otgResetComplete == 1) // 20100819, G1 U02
			return;

		/* Return command operation result */
		if (status == USB_ST_NOERROR)
			Return_CSW_to_Host(&cbw, &csw, MSDFN_BOT_COMMAND_PASSED, gUSBStruct);
		else
		{
			Return_CSW_to_Host(&cbw, &csw, MSDFN_BOT_COMMAND_FAILED, gUSBStruct);
		}
	}
	//gprintf("end msdloop\n");

	return;
}

