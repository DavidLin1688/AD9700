
#include "Global.h"
#if ENABLE_TOUCH_PANEL || ENABLE_TOUCH_PANEL_CTRL_OSD
#define TOUCH_PANEL_C

sTouchPanelDataType xdata TPL_Data;
//BYTE xdata FingerLiftCounter; // if finger lift, send lift status to htc 3 times for reducing dummy work

extern Bool ElandWriteWordMask(WORD reg, WORD val, WORD mask);

#define DEBUG_TOUCH_PANEL  0

#if DEBUG_TOUCH_PANEL && ENABLE_DEBUG
#define TPL_DPUTSTR(str)    	printMsg(str)
#define TPL_DPRINTF(str, x) 	printData(str, x)
#else
#define TPL_DPUTSTR(str)
#define TPL_DPRINTF(str, x)
#endif

#if 0//ENABLE_TOUCH_PANEL
//extern BYTE GetMenuItemCount(BYTE menupage);
extern BYTE GetMenuItemPosiX(BYTE menupage, BYTE item);
//extern BYTE GetMenuItemPosiY(BYTE menupage, BYTE item);
//extern BYTE GetMenuItemNextMenu(BYTE menupage, BYTE item);
extern WORD GetMenuItemFlag(BYTE menupage, BYTE item);

BYTE xdata TouchPanelPowerFlag;

extern BYTE xdata MenuPageIndex;
extern BYTE xdata MenuItemIndex;
extern BYTE xdata PrevMenuItemIndex;
#endif


#define SPI_DELAY() {_nop_(); _nop_(); _nop_(); _nop_();} // 4 nop-> clock around 650KHz

Bool SPI_WriteByte(BYTE val)
{
    BYTE i;

    Clr_SPI_SEL();
    SPI_DELAY();

    for(i=0; i<8; i++)
    {
        Clr_SPI_SCK();
        if(val&_BIT7)
        {
            Set_SPI_MOSI();
        }
        else
        {
            Clr_SPI_MOSI();
        }
        val <<= 1;
        SPI_DELAY();
        Set_SPI_SCK();
        SPI_DELAY();
    }

    Set_SPI_MOSI();
    Set_SPI_SEL();
    SPI_DELAY();

    return TRUE;
}

Bool SPI_ReadByte(BYTE *val)
{
    BYTE i;
    BYTE value = 0;

    Clr_SPI_SEL();
    SPI_DELAY();

    for(i=0; i<8; i++)
    {
        value <<= 1;
        Clr_SPI_SCK();
        SPI_DELAY();
        if(SPI_MISO_Pin)
            value |= _BIT0;
        Set_SPI_SCK();
        SPI_DELAY();
    }

    *val = value;
    Set_SPI_SEL();
    SPI_DELAY();

    return TRUE;
}

Bool SPI_WriteRegister(BYTE addr, BYTE val)
{
    SPI_WriteByte(addr);
    SPI_WriteByte(val);
    return TRUE;
}

Bool SPI_ReadRegister(BYTE addr, BYTE *val)
{
    SPI_WriteByte(addr);
    SPI_ReadByte(val);
    return TRUE;
}

Bool SPI_WaitBusReady(BYTE count)
{
    BYTE i = 0;
    BYTE tempcount = 0;

    do{
        SPI_ReadRegister(ARC_SPICMD_ACCESS_STATUS, &i);
        if(i == ACCESS_STATUS_READY)
            return TRUE;

        Delay1ms(5);
    }while(tempcount++ < count); // wait for bus ready

    if(i == ACCESS_STATUS_READY)
        return TRUE;
    else
        return FALSE;

}

Bool SPI_Write32Bit(DWORD addr, DWORD val)
{
    uDWBuffer dw_temp;

    // wait for bus ready
    if(SPI_WaitBusReady(WAIT_BUS_READY_COUNT) == FALSE)
    {
        #if 0//DEBUG_TOUCH_PANEL
            TPL_DPRINTF(" W_BusBusy", 0);
        #endif
        return FALSE;
    }

    // set to write mode
    SPI_WriteRegister(ARC_SPICMD_SET_ACCESS_MODE, ACCESS_MODE_WRITE);

    // set write address 32bit
    dw_temp.valDW = addr;
    SPI_WriteRegister(ARC_SPICMD_ADDR_BYTE3, dw_temp.valB[0]);
    SPI_WriteRegister(ARC_SPICMD_ADDR_BYTE2, dw_temp.valB[1]);
    SPI_WriteRegister(ARC_SPICMD_ADDR_BYTE1, dw_temp.valB[2]);
    SPI_WriteRegister(ARC_SPICMD_ADDR_BYTE0, dw_temp.valB[3]);

    // set write data 32bit
    dw_temp.valDW = val;
    SPI_WriteRegister(ARC_SPICMD_WRDATA_BYTE3, dw_temp.valB[0]);
    SPI_WriteRegister(ARC_SPICMD_WRDATA_BYTE2, dw_temp.valB[1]);
    SPI_WriteRegister(ARC_SPICMD_WRDATA_BYTE1, dw_temp.valB[2]);
    SPI_WriteRegister(ARC_SPICMD_WRDATA_BYTE0, dw_temp.valB[3]);

    // set data length 32bit
    SPI_WriteRegister(ARC_SPICMD_DATALEN_SELECT, DATALEN_SELECT_32BIT);

    // start to access SRAM
    SPI_WriteRegister(ARC_SPICMD_ACCESS_START, 0);

    return TRUE;
}

Bool SPI_Read32Bit(DWORD addr, DWORD *val)
{
    uDWBuffer dw_temp;

    // wait for bus ready
    if(SPI_WaitBusReady(WAIT_BUS_READY_COUNT) == FALSE)
    {
        #if DEBUG_TOUCH_PANEL
            TPL_DPRINTF(" R_BusBusy", 0);
        #endif
        return FALSE;
    }

    // set to read mode
    SPI_WriteRegister(ARC_SPICMD_SET_ACCESS_MODE, ACCESS_MODE_READ);

    // set read address 32bit
    dw_temp.valDW = addr;
    SPI_WriteRegister(ARC_SPICMD_ADDR_BYTE3, dw_temp.valB[0]);
    SPI_WriteRegister(ARC_SPICMD_ADDR_BYTE2, dw_temp.valB[1]);
    SPI_WriteRegister(ARC_SPICMD_ADDR_BYTE1, dw_temp.valB[2]);
    SPI_WriteRegister(ARC_SPICMD_ADDR_BYTE0, dw_temp.valB[3]);

    // set data length 32bit
    SPI_WriteRegister(ARC_SPICMD_DATALEN_SELECT, DATALEN_SELECT_32BIT);

    // start to access SRAM
    SPI_WriteRegister(ARC_SPICMD_ACCESS_START, 0);

    // wait for bus ready
    if(SPI_WaitBusReady(WAIT_BUS_READY_COUNT) == FALSE)
    {
        #if 0//DEBUG_TOUCH_PANEL
            TPL_DPRINTF(" R_BusBusy-1", 0);
        #endif
        return FALSE;
    }

    // read data 32bit
    SPI_ReadRegister(ARC_SPICMD_RDDATA_BYTE3, &dw_temp.valB[0]);
    SPI_ReadRegister(ARC_SPICMD_RDDATA_BYTE2, &dw_temp.valB[1]);
    SPI_ReadRegister(ARC_SPICMD_RDDATA_BYTE1, &dw_temp.valB[2]);
    SPI_ReadRegister(ARC_SPICMD_RDDATA_BYTE0, &dw_temp.valB[3]);

    #if 0//DEBUG_TOUCH_PANEL
        TPL_DPRINTF(" ARC_SPICMD_RDDATA_BYTE3:%x", dw_temp.valB[0]);
        TPL_DPRINTF(" ARC_SPICMD_RDDATA_BYTE2:%x", dw_temp.valB[1]);
        TPL_DPRINTF(" ARC_SPICMD_RDDATA_BYTE1:%x", dw_temp.valB[2]);
        TPL_DPRINTF(" ARC_SPICMD_RDDATA_BYTE0:%x", dw_temp.valB[3]);
    #endif

    *val = dw_temp.valDW;

    return TRUE;

}

void SPI_Init(void)
{
    Set_TOCUCH_PANEL_POWER();
    //Delay1ms(5);//Delay1ms(8); 2011.11.01 cc
    Set_SPI_SEL();
    Set_SPI_MOSI();
    Set_SPI_SCK();

    Delay1ms(70);// tpv touch team
}

void TPL_InitVariables(void)
{
    //GetXYMappingOffsetValue();
    //TPL_FingerStatus = FINGER_LIFT;
    TPL_PollingCounter = SPI_POLLING_INTERVAL;
    TPL_StatusFlag = 0;
}

#define SPI_SYS_CTRL_MODE	(SPI_SYS_SPI_MODE|SPI_SYS_USB_MODE)
Bool TPL_InitSetting(void)
{
    BYTE i = 0;
    DWORD dwvalue = 0;

    SPI_Init();
    TPL_InitVariables();

    for(i=0; i<READ_STATUS_RETRY_COUNT; i++)
    {
        if(SPI_Read32Bit(SPI_SYS_CHK_CODE, &dwvalue) == TRUE)
        {
            if(dwvalue == SPI_SYS_CHK_CODE_DEFAULT)
                break;
        }
        //Delay1ms(2);
    }

    if(i<READ_STATUS_RETRY_COUNT)
    {
        SPI_Write32Bit(SPI_SYS_CTRL, SPI_SYS_CTRL_MODE);
        dwvalue = 0;
        for(i=0; i<READ_STATUS_RETRY_COUNT; i++)
        {
            SPI_Read32Bit(SPI_SYS_STATUS, &dwvalue);
            if(dwvalue == SPI_SYS_CTRL_MODE)
            {
                #if DEBUG_TOUCH_PANEL
                    TPL_DPRINTF(" TPL_Init ok", 1);
                #endif
                TPL_Set_InitPassFlag();
                return TRUE;
            }
        }
    }
    else
    {
        #if DEBUG_TOUCH_PANEL
            TPL_DPRINTF(" TPL_Init fail", 1);
        #endif
        return FALSE;
    }

    return TRUE;
}

void Swap4(BYTE * databuf)
{
    BYTE temp;

    temp = databuf[0];
    databuf[0] = databuf[3];
    databuf[3] = temp;

    temp = databuf[1];
    databuf[1] = databuf[2];
    databuf[2] = temp;
}

Bool TPL_ReadSurface(void)
{
    BYTE i;
    DWORD dw_temp = 0;

    if(SPI_Write32Bit(SPI_DATA_CTRL, SPI_DATA_START_READING) == FALSE)
    {
    #if DEBUG_TOUCH_PANEL
        TPL_DPRINTF(" SPI_DATA_START_READING fail", 1);
    #endif
        return FALSE;
    }

    for(i = 0; i<READ_STATUS_RETRY_COUNT; i++)
    {
        SPI_Read32Bit(SPI_DATA_STATUS, &dw_temp);
        dw_temp &= SPI_DATA_START_READING;
        if(dw_temp == SPI_DATA_START_READING)
            break;
        Delay1ms(2);
    }

    if(dw_temp != SPI_DATA_START_READING)
    {
    #if DEBUG_TOUCH_PANEL
        TPL_DPRINTF(" DATA_START_READING false", 1);
    #endif
        return FALSE;
    }

    // get data index
    if(SPI_Read32Bit(SPI_DATA_INDEX, &dw_temp) == FALSE)
    {
    #if DEBUG_TOUCH_PANEL
        TPL_DPRINTF(" ReadIndexFail", 1);
    #endif
        return FALSE;
    }

    dw_temp &= 0x01;

    SPI_Read32Bit(SPI_DATA0_3_0+dw_temp*0x10, &TPL_Data.OutputData.dwBuffer[0].valDW);
    SPI_Read32Bit(SPI_DATA0_7_4+dw_temp*0x10, &TPL_Data.OutputData.dwBuffer[1].valDW);
    SPI_Read32Bit(SPI_DATA0_11_8+dw_temp*0x10, &TPL_Data.OutputData.dwBuffer[2].valDW);
    SPI_Read32Bit(SPI_DATA0_15_12+dw_temp*0x10, &TPL_Data.OutputData.dwBuffer[3].valDW);

    SPI_Write32Bit(SPI_DATA_CTRL, SPI_DATA_STOP_READING);

    // to meet the allocation of uOutputData
    Swap4(TPL_Data.OutputData.dwBuffer[0].valB);
    Swap4(TPL_Data.OutputData.dwBuffer[1].valB);
    Swap4(TPL_Data.OutputData.dwBuffer[2].valB);
    Swap4(TPL_Data.OutputData.dwBuffer[3].valB);

    #if DEBUG_TOUCH_PANEL && 0
    if(FINGER_ON)
    {
        printData("   TPL_Conatct0_X:%x", TPL_Conatct0_X);
        printData("   TPL_Conatct0_Y:%x", TPL_Conatct0_Y);
    }
    #endif

    return TRUE;

}

void TouchPanelHandler(void)
{
    if(!BackLightActiveFlag || InputTimingChangeFlag || SyncLossState() || TPL_PollingCounter)
        return;

    TPL_PollingCounter = SPI_POLLING_INTERVAL;

    if(TPL_ReadSurface() == FALSE)
        return;

#if ENABLE_MHL
    if(FINGER_ON)
    {
        mdrv_mhl_CbusWriteBurst(0x40, 0x10, &TPL_Data.OutputData.dwBuffer[0].valB[0]);
    }
#endif
}

#endif
