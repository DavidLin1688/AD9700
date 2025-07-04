#define _FACTORYALIGN_C_
#include <types.h>
#include <board.h>
#include <mode.h>
#include <UserPrefDef.h>
#include <global.h>
#include <msosd.h>
#include <debug.h>
#include <common.h>
#include <menudef.h>
#include <menufunc.h>
#include <DDC2Bi.h>
#include <NVRam.h>
#include <adjust.h>
#include "Ms_reg.h"
#include <power.h>
#include <ms_rwreg.h>
#include <misc.h>
#include <i2c.h>
#include <userPref.h>
#include <FactoryAlignAOC.h>
#include <FactoryAlignApp.h>

extern BYTE idata rxInputPort;

#if (ODM_NAME==ODM_AOC)

#if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMJ||CHIP_ID==CHIP_TSUM9||CHIP_ID==CHIP_TSUMF
#if D2B_XShared_DDCBuffer
extern BYTE *DDCBuffer;
#else
extern BYTE xdata DDCBuffer[DDC_BUFFER_LENGTH];
#endif
#else
extern BYTE xdata DDCBuffer[DDC_BUFFER_LENGTH];
#endif
extern void DDC2Bi_MessageReady( void );

BYTE XDATA g_ucProductionFlag = 0;
WORD XDATA g_wFDCRCValue = 0;
bit bWriteEnableFlag;
bit DFM_WRITECMD_REPLY_FLAG;

WORD xdata TCRCvalue;
WORD xdata TCRCCounter;



#if ENABLE_HDCP&&HDCPKEY_IN_Flash
#if (HDCPKEY_USE_CODE==0 || ENABLE_NEWDFM_REQUEST)
#if 0
WORD CRC16( BYTE nData, WORD nCRC )
{
    BYTE nMask;
    Bool fFeedback;

    for( nMask = 0x80; nMask; nMask >>= 1 )
    {
        fFeedback = ( Bool )((( nCRC & 0x8000 ) ? 1 : 0 ) ^(( nMask & nData ) ? 1 : 0 ) );
        nCRC <<= 1;
        if( fFeedback )
        {
            nCRC ^= 0x1021;
        }
    }

    return nCRC;
}
#endif
#endif
#endif
#if 0
//////////////////////////////////////////////////////////////////////////////
// <Name>: drvFactoryAlignAOC
//
// <Description>: This function set AOC FactoryAlignment.
//
// <Parameter>:    -  <Flow>  -  <Description>
// ---------------------------------------------------------------------------
//  S-6Ea-51a-8Aa-03a-FEa-57a-39a-38a-30a-31a-XXa-XXa-XXa-CHKa-P
//
//////////////////////////////////////////////////////////////////////////////
BYTE drvFactoryAlignAOC( void )
{
    Bool result = FALSE;
    BYTE XDATA ucLen, ucPre1, ucCmd, ucExt, ucData1, ucData2, ucData3;
    WORD XDATA WordValue;

    ucLen = DDC2BI_PKTSIZE & ( ~0x80 );
    ucPre1 = DDC2BI_PRE1;
    ucCmd = DDC2BI_CMD;
    ucExt = DDC2BI_EXT;
    ucData1 = DDC2BI_DATA1;
    ucData2 = DDC2BI_DATA2;
    ucData3 = DDC2BI_DATA3;
    WordValue = (( DDC2BI_DATA1 << 8 ) | DDC2BI_DATA2 );

    if( ucPre1 == TPV_GETVCP )
    {
        if( ucCmd == ADJ_Brightness )
        {
            g_wFDCRCValue = appFactoryGetBrightness();
        }
        else if( ucCmd == ADJ_Contrast )
        {
            g_wFDCRCValue = appFactoryGetContrast();
        }
        else if( ucCmd == ADJ_Red_Gain )
        {
            g_wFDCRCValue = appFactoryGetRedGain();
        }
        else if( ucCmd == ADJ_Green_Gain )
        {
            g_wFDCRCValue = appFactoryGetGreenGain();
        }
        else if( ucCmd == ADJ_Blue_Gain )
        {
            g_wFDCRCValue = appFactoryGetBlueGain();
        }
        else if( ucCmd == TPV_FCode01 )                                     //110913 Rick's confuse
        {
            if( ucExt == 0xE2 )
            {
#if HDCPKEY_IN_Flash
                g_wFDCRCValue = appFactoryGetHdcpCRC();
                DDC2BI_TPVALUE = 0;
                DDC2BI_VALUEH = g_wFDCRCValue / 256;
                DDC2BI_VALUEL = g_wFDCRCValue % 256;
                DDC2BI_RETVALUEH = 0x88;
                DDC2BI_RETVALUEL = 0x02;
                Clr_WriteHDCPcodeFlag();
#endif
            }
#if ENABLE_NEWDFM_REQUEST
            else
            {
                DDC2BI_REPLYBYTE = 0x05;
            }
#endif
        }
        else if( ucCmd == TPV_FCode02 )
        {
            if( ucExt == 0x01 )           // ADC R Gain
            {
                g_wFDCRCValue = appFactoryGetAdcRedGain();
            }
            else if( ucExt == 0x02 )  // ADC G Gain
            {
                g_wFDCRCValue = appFactoryGetAdcGreenGain();
            }
            else if( ucExt == 0x03 )  // ADC B Gain
            {
                g_wFDCRCValue = appFactoryGetAdcBlueGain();
            }
            else if( ucExt == 0x04 )          // ADC R Offset
            {
                g_wFDCRCValue = appFactoryGetAdcRedOffset();
            }
            else if( ucExt == 0x05 )          // ADC G Offset
            {
                g_wFDCRCValue = appFactoryGetAdcGreenOffset();
            }
            else if( ucExt == 0x06 )      // ADC B Offset
            {
                g_wFDCRCValue = appFactoryGetAdcBlueOffset();
            }
        }
#ifdef UseVGACableReadWriteAllPortsEDID
#if ENABLE_NEWDFM_REQUEST
        else if( ucCmd == TPV_FCode0F )
        {
            WORD xdata wAddr;

            wAddr = (( WORD )ucData1 << 8 ) + ucData2;
            ucLen = ucData3;

            appFactoryGetEDID( ucExt, wAddr, ( BYTE* )&DDC2BI_PRE1, ucLen );
            DDC2BI_PKTSIZE = ucLen | 0x80;
            SET_DFM_WRITECMD_REPLY_FLAG();
        }
#endif
#endif
    }
    //====================================================
    else if( ucPre1 == TPV_SETVCP )
    {
#if ENABLE_NEWDFM_REQUEST && ENABLE_HDCP&&HDCPKEY_IN_Flash
        BYTE ucCount;


        if(( ucCmd == TPV_FCode01 && ucExt == 0xE0 ) || ( ucCmd == TPV_FCode0A ) )
        {

        }
        else
        {
            g_wFDCRCValue = 0;
            if( ucCmd == TPV_FCode0F )
            {
                ucLen = DDC2BI_PKTSIZE - 0x86;

                DDC2BI_FDCRCHI = ucData2;
                DDC2BI_FDCRCLO = ucLen;
                DDC2BI_REPLYBYTE = ucData1;
                DDC2BI_PKTSIZE = 0x83;
            }
            else
            {
                for( ucCount = 0; ucCount < ( ucLen - 0x02 ) ; ucCount++ )
                    g_wFDCRCValue = CRC16( *( &DDC2BI_CMD + ucCount ), g_wFDCRCValue );


                DDC2BI_FDCRCHI = g_wFDCRCValue >> 8;
                DDC2BI_FDCRCLO = g_wFDCRCValue & 0xFF;
                DDC2BI_REPLYBYTE = 0x03;
                DDC2BI_PKTSIZE = 0x83;
            }

            DDC2Bi_MessageReady();
            if(INPUT_IS_VGA(rxInputPort))//( rxInputPort == 0 )
                DDCADC_RBUF_WDP = DDC2B_DEST_ADDRESS;
            else
#if CHIP_ID != CHIP_TSUMC
                DDCDVI_RBUF_WDP = DDC2B_DEST_ADDRESS;
#else
            {
                DDCDVI0_RBUF_WDP = DDC2B_DEST_ADDRESS;
                DDCDVI1_RBUF_WDP = DDC2B_DEST_ADDRESS;
                DDCDVI2_RBUF_WDP = DDC2B_DEST_ADDRESS;
            }
#endif

            SET_DFM_WRITECMD_REPLY_FLAG();
        }
#endif

        if( ucCmd == TPV_FCode01 )
        {
            if( ucExt == TPV_FactoryMode )
            {
                if( ucData1 == 0x00 )
                {
                    appFactorySetFactoryFlag( ucData2 );
#if ENABLE_NEWDFM_REQUEST
                    DDC2BI_REPLYBYTE = 0x02;
#endif
                }
            }
            else if( ucExt == 0xA2 )
            {
                if( ucData1 == 0x00 )
                {
                    appFactorySetBurninFlag( ucData2 );
#if ENABLE_NEWDFM_REQUEST
                    DDC2BI_REPLYBYTE = 0x02;
#endif
                }
#ifdef UseVGACableReadWriteAllPortsEDID
#if ENABLE_NEWDFM_REQUEST
                else if( ucData1 == 0x01 )
                {
                    g_wFDCRCValue = appFactorySetEdidWriteStart( ucData2 );
                    DDC2BI_FDCRCHI = g_wFDCRCValue >> 8;
                    DDC2BI_FDCRCLO = g_wFDCRCValue & 0xFF;
                    DDC2BI_REPLYBYTE = 0x02;
                }
#endif
#endif
            }
            else if( ucExt == 0xA3 ) // Clear backlight hours
            {
            #if USEFLASH
                BlacklitTime = 0;
                UserprefBacklighttime = 0;
                UserPref_EnableFlashSaveBit( bFlashSaveMonitor2Bit );
            #else
                BlacklitTime = 0;
                SaveBlacklitTime();
            #endif
            }
            else if( ucExt == 0xA5 )
            {
                if( DDC2BI_DATA1 == 0x00 )
                {
                    appFactorySetProductModeFlag( ucData2 );
#if ENABLE_NEWDFM_REQUEST
                    DDC2BI_REPLYBYTE = 0x02;
#endif
                }
            }
#if PanelRSDS||PANEL_MINI_LVDS
            else if( ucExt == 0xA9 )
            {
                appFactoryAdjVcomValue( WordValue );
#if ENABLE_NEWDFM_REQUEST
                DDC2BI_REPLYBYTE = 0x02;
#endif
            }
#endif
#if HDCPKEY_IN_Flash
            else if( ucExt == 0xE0 ) //for HDCP Write start or EDID write start
            {
                appFactorySetHdcpWriteStart();
#if ENABLE_NEWDFM_REQUEST
                DDC2BI_REPLYBYTE = 0x02;
#endif
            }
#endif
        }
        else if( ucCmd == 0xD6 ) //for DFM Power saving
        {
            if( ucExt == 0x00 && ucData1 == 0x00 )
            {
                appFactorySetForcePowerSaving();
#if ENABLE_NEWDFM_REQUEST
                DDC2BI_REPLYBYTE = 0x02;
#endif
            }
        }
        else if( ucCmd == TPV_FCode08 )
        {

        }
#if HDCPKEY_IN_Flash
        else if( ucCmd == TPV_FCode0A )
        {
        #if 1
            if(( TCRCCounter + ucExt ) > 304 )
                ucLen = ( 304 % ucExt );
            else
                ucLen = ucExt;
            appFactoryHdcpWrite( ucData1, ucExt, ( BYTE * )&DDC2BI_DATA2, ucLen );
        #else
            appFactoryHdcpWrite( ucData1, HDCP_BLOCK_LENGTH, ( BYTE * )&DDC2BI_DATA2, HDCP_BLOCK_LENGTH );
        #endif
        }
#endif
#ifdef UseVGACableReadWriteAllPortsEDID
#if ENABLE_NEWDFM_REQUEST
        else if( ucCmd == TPV_FCode0F )
        {
            appFactoryWriteEDID( ucExt, (( WORD )ucData1 << 8 ) + ucData2, ( BYTE * )&DDC2BI_DATA3, ucLen );
        }
#endif
#endif
        else if( ucCmd == ADJ_Brightness )
        {
            appFactoryAdjBrightness( WordValue );
#if ENABLE_NEWDFM_REQUEST
            DDC2BI_REPLYBYTE = 0x02;
#endif
        }
        else if( ucCmd == ADJ_Contrast )   // contrast
        {
            appFactoryAdjContrast( WordValue );
#if ENABLE_NEWDFM_REQUEST
            DDC2BI_REPLYBYTE = 0x02;
#endif
        }
        else if( ucCmd == ADJ_Red_Gain )        // Red Color
        {
            appFactoryAdjRedGain( WordValue );
#if ENABLE_NEWDFM_REQUEST
            DDC2BI_REPLYBYTE = 0x02;
#endif

        }
        else if( ucCmd == ADJ_Green_Gain )  // Green Color
        {
            appFactoryAdjGreenGain( WordValue );
#if ENABLE_NEWDFM_REQUEST
            DDC2BI_REPLYBYTE = 0x02;
#endif

        }
        else if( ucCmd == ADJ_Blue_Gain )            // Blue Color
        {
            appFactoryAdjBlueGain( WordValue );
#if ENABLE_NEWDFM_REQUEST
            DDC2BI_REPLYBYTE = 0x02;
#endif
        }
        else if( ucCmd == Select_Color_Preset ) //Save or Recall ColorTemp //110120 Modify
        {
            if( ucData2 )
            {
                appFactoryRecallColorPreset( ucExt );
            }
            else
            {
                appFactorySaveColorPreset( ucExt );
            }
#if ENABLE_NEWDFM_REQUEST
            DDC2BI_REPLYBYTE = 0x02;
#endif

        }
        else if( ucCmd == 0xCC )        // Language
        {
            if( ucExt == 0x00 && ucData1 == 0x00 )
            {
                result = appFactoryAdjLanguage( DDC2BI_DATA2 );
#if ENABLE_NEWDFM_REQUEST
                DDC2BI_REPLYBYTE = 0x02;
#endif

            }
            else
            {
#if ENABLE_NEWDFM_REQUEST
                DDC2BI_REPLYBYTE = 0x05;
#endif
            }

        }
        else if( ucCmd == Auto_Color ) // Auto Color
        {
            if( ucData1 == 0x00 && ucData2 == 0x00 )
            {
                if (appFactoryAutoColor())
                    DDC2BI_REPLYBYTE = 0x02;
                else
                    DDC2BI_REPLYBYTE = 0x04;
            }
        }
        else if( ucCmd == Auto_Setup ) // Auto Config
        {
            if( DDC2BI_DATA1 == 0x00 && DDC2BI_DATA2 == 0x00 )
            {
                if (appFactoryAutoSetup())
                    DDC2BI_REPLYBYTE = 0x02;
                else
                    DDC2BI_REPLYBYTE = 0x04;
            }
        }
        else if( ucCmd == ALL_Reset )  // Factory All Reset
        {
            if( DDC2BI_DATA1 == 0x00 && DDC2BI_DATA2 == 0x00 )
            {
               if (appFactoryAllReset())
                   DDC2BI_REPLYBYTE = 0x02;
               else
                   DDC2BI_REPLYBYTE = 0x04;
            }
        }
#if ENABLE_NEWDFM_REQUEST
        else
        {
            DDC2BI_REPLYBYTE = 0x05;
        }
#endif
    }

    return 0;
}
#endif
#endif

