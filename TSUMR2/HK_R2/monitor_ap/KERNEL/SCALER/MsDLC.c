/******************************************************************************
Copyright (c) 2003 MStar Semiconductor, Inc.
All rights reserved.
[Module Name]: MsDLC.c
[Date]:        26-Dec-2003
[Comment]:
MST DLC subroutines.
[Reversion History]:
*******************************************************************************/
#include "board.h"
#if ENABLE_DLC
#include "types.h"
#include "MsDLC.h"
#include "ms_reg.h"
#include "Debug.h"
#include "Common.h"
#include "Global.h"
#include "Adjust.h"
//#include "msADC.h"
//#include "Panel.h"
#include "Ms_rwreg.h"

#include <math.h>

//#include "msACE.h"
//#define LOCAL_TYPE
#define msDoubleBufferStart()
#define msDoubleBufferEnd()

#define MsDLC_DEBUG    1
#if ENABLE_DEBUG && MsDLC_DEBUG
#define DLC_PrintMsg(str) printMsg(str);
#define DLC_PrintData(str, value) printData(str, value)
#endif

extern code short tSRGB[3][3];
extern code short tNormalColorCorrectionMatrix[3][3];

#if DLC_S_MODE
XDATA BYTE g_ucLumaCurve[18];
#else
XDATA BYTE g_ucLumaCurve[16];
#endif
#if ENABLE_DPS
extern xdata BOOL  REG_DPS_RUN_Flag;
#endif
XDATA BOOL REG_UpdateHistogram_Flag = 0;
XDATA WORD g_ucTable[16];
XDATA BYTE g_bLockDlc; // When this bit is true, DLC don't work!!
XDATA DWORD g_dwFactory;
XDATA DWORD g_dwFactory_7;
XDATA DWORD g_dwFactory_9;
XDATA DWORD g_dwLstep;
XDATA DWORD g_dwHstep;
XDATA BYTE g_LowStrength = 120;
XDATA BYTE g_HighStrength = 100;
XDATA BYTE g_bDLCOnOff = 0;
XDATA BYTE g_bNeedRequest = 0;
XDATA BYTE ucDLCCCount = 0;
XDATA BYTE BrightData = 0xff;
XDATA BYTE DarkData = 0x00;
XDATA BYTE PreBrightData = 0xff;
XDATA BYTE ReadFrameDataCnt = 1;
XDATA BYTE SetDarkestFlag = 0;
XDATA BYTE DarkSegmentData;
#define TopLimit_Upper  (0)
#define DownLimit_Upper (((g_sPnlInfo.sPnlTiming.u16Height/2)/8)-1)
#define TopLimit_Lower  ((g_sPnlInfo.sPnlTiming.u16Height/2)/8)
#define DownLimit_Lower ((g_sPnlInfo.sPnlTiming.u16Height/8)-1)
#define DarkestValue    0
#define DarkestRange    ((CURRENT_INPUT_IS_VGA())?(16):(20))
#define BlackWhiteDifference    21    //16      //20081201
//#define TOP_LIMIT       ((WORD)wHeight/64)
//#define DOWN_LIMIT      ((WORD)wHeight*7/64)
/*
#define TOP_LIMIT       (1)// 2004/11/10
#define DOWN_LIMIT      (255)//((WORD)wHeight/8)// 2005/01/21
#define TOTAL_PIXEL     ((DWORD)wHeight*0.04375*wWidth)
*/
#define TOP_LIMIT           ((WORD)g_sPnlInfo.sPnlTiming.u16Height/64)
#define DOWN_LIMIT          ((WORD)g_sPnlInfo.sPnlTiming.u16Height*7/64)
#define TOTAL_PIXEL    ((DWORD)(DOWN_LIMIT-TOP_LIMIT)*0.04375*g_sPnlInfo.sPnlTiming.u16Width/4)
#define FACTORY_7       g_dwFactory_7    // low threshold
#define FACTORY_9       g_dwFactory_9    // high threshold
#define Lstep           g_dwLstep
#define Hstep           g_dwHstep
//#define TOP_LIMIT   (g_wHeight/64)
//#define DOWN_LIMIT  (g_wHeight*7/64)
//#define TOTAL_PIXEL ((DWORD)g_wHeight*0.04375*g_wWidth)
//#define FACTORY     (TOTAL_PIXEL / 8)
//#define FACTORY_7   (FACTORY * 7 / 8)      // low threshold
//#define FACTORY_9   (FACTORY + (FACTORY/8))  // high threshold
//#define Lstep       (FACTORY *1/16)*g_ucLstrength
//#define Hstep       (FACTORY *3/8)*g_ucHstrength
//#define FACTORY_M1  (FACTORY_7 - ((FACTORY *8/16)*g_ucLstrength))
//#define FACTORY_0   (FACTORY_7 - ((FACTORY *7/16)*g_ucLstrength))
//#define FACTORY_1   (FACTORY_7 - ((FACTORY *6/16)*g_ucLstrength))
//#define FACTORY_2   (FACTORY_7 - ((FACTORY *5/16)*g_ucLstrength))
//#define FACTORY_3   (FACTORY_7 - ((FACTORY *4/16)*g_ucLstrength))
//#define FACTORY_4   (FACTORY_7 - ((FACTORY *3/16)*g_ucLstrength))
//#define FACTORY_5   (FACTORY_7 - ((FACTORY *2/16)*g_ucLstrength))
//#define FACTORY_6   (FACTORY_7 - ((FACTORY *1/16)*g_ucLstrength))
//#define FACTORY_11  (FACTORY_9 + ((FACTORY*2/8)*g_ucHstrength))
//#define FACTORY_13  (FACTORY_9 + ((FACTORY*4/8)*g_ucHstrength)
//#define FACTORY_16  (FACTORY_9 + ((FACTORY*7/8)*g_ucHstrength)
//#define FACTORY_19  (FACTORY_9 + (((FACTORY)+(FACTORY*2/8))*g_ucHstrength))
//#define FACTORY_21  (FACTORY_9 + (((FACTORY)+(FACTORY*4/8))*g_ucHstrength))
//#define FACTORY_23  (FACTORY_9 + (((FACTORY)+(FACTORY*6/8))*g_ucHstrength))
//#define FACTORY_27  (FACTORY_9 + (((FACTORY*2)+(FACTORY*2/8))*g_ucHstrength))
//#define FACTORY_30  (FACTORY_9 + (((FACTORY*2)+(FACTORY*5/8))*g_ucHstrength))
//#define FACTORY_32  (FACTORY_9 + (((FACTORY*2)+(FACTORY*7/8))*g_ucHstrength))

BOOL bIsLimitedlRangeFlag =0;
XDATA WORD  u16WeightAvg_Cur;
XDATA BYTE u8BacklightNow=0;
XDATA BYTE u8BacklightPrev=0;
XDATA BYTE u8UpdatedBacklight =0;
XDATA BYTE u8LibReturnFlag=0;
XDATA BYTE u8UpdateStep =1;
#define BACKLIGHT_MAX_DEFAULT   255 
#define BACKLIGHT_MIN_DEFAULT   0
#define WEIGHT_AVG_MAX_DEFAULT  30
#define WEIGHT_AVG_MIN_DEFAULT  4
XDATA BYTE u8Backlight_Max=BACKLIGHT_MAX_DEFAULT;
XDATA BYTE u8Backlight_Min=BACKLIGHT_MIN_DEFAULT;
XDATA BYTE u8WeightAvg_Max= 30;//WEIGHT_AVG_MAX_DEFAULT;
XDATA BYTE u8WeightAvg_Min= 4;//WEIGHT_AVG_MIN_DEFAULT;
BOOL XDATA bDCRStatus=0;

void InitDLCVar(void)
{
    // DLC table initial table
    g_ucLumaCurve[0] = 0x07;
    g_ucLumaCurve[1] = 0x17;
    g_ucLumaCurve[2] = 0x27;
    g_ucLumaCurve[3] = 0x37;
    g_ucLumaCurve[4] = 0x47;
    g_ucLumaCurve[5] = 0x57;
    g_ucLumaCurve[6] = 0x67;
    g_ucLumaCurve[7] = 0x77;
    g_ucLumaCurve[8] = 0x87;
    g_ucLumaCurve[9] = 0x97;
    g_ucLumaCurve[10] = 0xA7;
    g_ucLumaCurve[11] = 0xB7;
    g_ucLumaCurve[12] = 0xC7;
    g_ucLumaCurve[13] = 0xD7;
    g_ucLumaCurve[14] = 0xE7;
    g_ucLumaCurve[15] = 0xF7;
}
#if DLC_S_MODE
typedef enum
{
    DLC_STATIC = 0,
    DLC_MEDIUM = 1,
    DLC_HIGH = 2,

} DLC_MODE_T;

XDATA BYTE DLC_Loop_Cnt;
XDATA BYTE DLC_Loop_Cnt_THD = 32;

XDATA DLC_MODE_T DlcMode;

BYTE code s_CurveH_High[] =
{
    0, 10, 14, 16, 12, 0,
};
BYTE code s_CurveL_High[] =
{
    12, 16, 20, 20, 20, 20, 16, 14,
};
BYTE code s_CurveH_Low[] =
{
    0, 3, 6, 8, 3, 0,
};
BYTE code s_CurveL_Low[] =
{
    0, 2, 4, 6, 4, 2, 0, 0,
};

#endif

//////////////////////////////////////////////////////////////////////////////
// <Name>: msSetDlcStrength
//
// <Description>: This function set DLC strength.
//
// <Parameter>:    -  <Flow>  -  <Description>
// ---------------------------------------------------------------------------
//  ucLowStrength  -    In    -  Strength of low level, from 1 to 255
//  ucHighStrenght -    In    -  Strength of high level from 1 to 255
// The unit is 0.01; the value is small and the effect is strong
// Lstrength :  0.50(strong)   <------------>   1.70 (weak) ; default = 1.20
// Hstrength:   0.50(strong)   <------------>   2.00 (weak) ; default = 1.00
//////////////////////////////////////////////////////////////////////////////
void msSetDlcStrength( BYTE pucLowStrength, BYTE pucHighStrenght )
{
    BYTE LOCAL_TYPE ucLowStrength;
    BYTE LOCAL_TYPE ucHighStrenght;
    ucLowStrength = pucLowStrength;
    ucHighStrenght = pucHighStrenght;
    if( 0 == ucLowStrength )
        ucLowStrength = 1;
    if( 0 == ucHighStrenght )
        ucHighStrenght = 1;
    g_dwLstep = g_dwFactory * 1 / 16 * ucLowStrength / 100;
    g_dwHstep = g_dwFactory * 3 / 8 * ucHighStrenght / 100;
}
void msDlcInit( WORD pwWidth, WORD pwHeight )
{
    //BYTE LOCAL_TYPE ucBank;
    WORD LOCAL_TYPE wWidth;
    WORD LOCAL_TYPE wHeight;
    //WORD LOCAL_TYPE vtotal = 0;
    wWidth = pwWidth;
    wHeight = pwHeight;
    g_bLockDlc = 0;
    g_dwFactory = TOTAL_PIXEL / 8;
    g_dwFactory_7 = ( g_dwFactory * 7 / 8 );
    g_dwFactory_9 = ( g_dwFactory + ( g_dwFactory / 8 ) );
    g_dwLstep = g_dwFactory * 1 / 16 * 12 / 10;
    g_dwHstep = g_dwFactory * 3 / 8;
    //printf("TOP_LIMIT = 0x%x\r\n", TOP_LIMIT);
    //printf("DOWN_LIMIT = 0x%x\r\n", DOWN_LIMIT);
    /*
    printf("TOTAL_PIXEL = 0x%x", dwTotalPixel>>16);
    printf("%x\r\n", dwTotalPixel);
    printf("FACTORY = 0x%x", dwFactory>>16);
    printf("%x\r\n", dwFactory);
    printf("FACTORY7 = 0x%x", g_dwFactory_7>>16);
    printf("%x\r\n", g_dwFactory_7);
    printf("FACTORY9 = 0x%x", g_dwFactory_9>>16);
    printf("%x\r\n", g_dwFactory_9);
    printf("Lstep = 0x%x", g_dwLstep>>16);
    printf("%x\r\n", g_dwLstep);
    printf("Hstep = 0x%x", g_dwHstep>>16);
    printf("%x\r\n", g_dwHstep);
     */
#if 1 // wait for checking
    //msWriteByte(SC03_B6, TOP_LIMIT);
    //msWriteByte(SC03_B7, DOWN_LIMIT);
    //msWriteByteMask(SC03_B5, BIT0, BIT0);
#else
    ucBank = old_msReadByte( BK0_00 );
    // get vtotal// 2005/1/24
    old_msWriteByte( BK0_00, REGBANK0 );
    vtotal = old_msReadByte( BK0_95 ) + ( old_msReadByte( BK0_96 ) & 0x07 ) * 256;
    //
    old_msWriteByte( BK0_00, REGBANK3 );

#ifdef TSUMXXNX     // Rex 100712 for max pixel value is not close to max
    mStar_WriteByteMask( BK3_3B, (BIT6), (BIT6) );
#endif
    //old_msWriteByte(BK3_B6, TOP_LIMIT);
    // old_msWriteByte(BK3_B7, vtotal/8-1);// 2005/1/24
    old_msWriteByte( BK3_BC, 0x00 ); // xxxx 0909
    //    old_msWriteByte(BK3_B5, BIT0);  // Enable range for Histogram
#if ((PanelWidth==1280&&PanelHeight==720)||(PanelWidth==1366&&PanelHeight==768))
    old_msWriteByte( BK3_B6, 0x00 );
    old_msWriteByte( BK3_B7, PanelHeight / 8 ); // 2005/1/24
#else
    old_msWriteByte( BK3_B6, 0x20 );
    old_msWriteByte( BK3_B7, 0x70 ); // 2005/1/24
#endif
    old_msWriteByte( BK3_B5, BIT0 ); // Enable range for Histogram
    old_msWriteByte( BK3_B9, 0x10 );
    //old_msWriteByte(BK3_B8, _BIT6);
    old_msWriteByte( BK0_00, ucBank );
#endif
}

//static XDATA BYTE s_Slope2, s_Slope5;
#define DYNAMIC_DLC 1
BYTE XDATA DLCStatus;
#if DLC_S_MODE
WORD XDATA uwArray[32];
#else
WORD XDATA uwArray[8];
#endif

BYTE XDATA g_u8Ymax, g_u8Ymin;
DWORD XDATA g_u16Total_Weight;
XDATA WORD g_u16Total_Count;

BYTE XDATA ucTmp;

void msDrvSetDLCEnable(BYTE bScalerWin, BYTE En)
{
	if (bScalerWin == MAIN_WINDOW)
		msWriteByteMask ( SC07_B8, En? BIT7: 0 , BIT7);
	else
		msWriteByteMask ( SC07_B8, En? BIT6: 0, BIT6);
}

void msDrvHistogramReportEnable(BYTE bScalerWin, BYTE En)
{
	if (bScalerWin == MAIN_WINDOW)
		msWriteByteMask ( SC07_B8, En? BIT4|BIT1: 0, BIT4|BIT1);
	else
		msWriteByteMask ( SC07_B8, En? BIT4|BIT0: 0, BIT4|BIT0);

    for(ucTmp = 0; ucTmp < 32; ucTmp++)
    	uwArray[ucTmp] = 0x00000000;;

    g_u8Ymax = 0;
    g_u8Ymin = 0;
    g_u16Total_Weight = 0;
    g_u16Total_Count =0;
}

void msDrvHistogramUpDateData(void)
{
	REG_UpdateHistogram_Flag = 0;

	if (msReadByte( SC07_B8 )& BIT3)
	{
        g_u16Total_Count = 0;

	    for(ucTmp = 0; ucTmp < 32; ucTmp++)
        {
			uwArray[ucTmp] = msRead2Byte(SC08_C0 + (2*ucTmp) );
            g_u16Total_Count += uwArray[ucTmp];
        }
        g_u16Total_Weight = msRead2Byte(SC07_36);
        g_u8Ymax = msReadByte ( SC07_3A );
        g_u8Ymin = msReadByte ( SC07_39 );

	if(g_u16Total_Count !=0)	
		u16WeightAvg_Cur = g_u16Total_Weight*255 / g_u16Total_Count;
	
    	msWriteByteMask ( SC07_B8, 0, BIT2 );

		REG_UpdateHistogram_Flag = 1;
	}

	msWriteByteMask ( SC07_B8, BIT2, BIT2 );
}

extern Bool SupportMWE( void );

void msDlcOnOff( BYTE pbSwitch )
{
    //BYTE LOCAL_TYPE ucBank;
    BYTE LOCAL_TYPE bSwitch;
    //WORD LOCAL_TYPE time_out = 0;
    bSwitch = pbSwitch;

    if( bSwitch == _ENABLE )
    {
        g_bDLCOnOff = 1;
        //g_bNeedRequest = 1;
        //DLCStatus = DLC_WAIT;
        #if DLC_S_MODE
        DlcMode = DLC_HIGH;
        #endif
		msDrvSetDLCEnable(MAIN_WINDOW, 1);
		msDrvHistogramReportEnable(MAIN_WINDOW, 1);
        /*
        #if ENABLE_DPS
        REG_DPS_RUN_Flag = 0;
        #endif
        */
    }
    else
    {
		int i;
		for( i = 0; i < 16; i++ )
		{
			msWriteByte( SC08_AE + i, i*16);
		}
	
        msDrvSetDLCEnable(MAIN_WINDOW, 0);
        g_bDLCOnOff = 0;
		msDrvHistogramReportEnable(MAIN_WINDOW, 0);
    }
}

void msDlcHandler(void)
{
    //BYTE LOCAL_TYPE ucBank; //, ucTmp;
    //WORD retry = 2000;
    //BYTE tempvalue = 0;
    //BYTE Backlight_Final;
    #if DLC_S_MODE
    BYTE  i, j;
    BYTE  CurveIdx =0;
    BYTE  CurveWgt=0;
    DWORD TempVar1=0, TempVar2=0;
    BYTE  s_CurveGain = 1;
    const BYTE  *s_CurveH;// = {0, 6, 8, 10, 6, 2};
    const BYTE  *s_CurveL;// = {8, 12, 15, 15, 15, 15, 12, 10};
    #endif
#if 0
    if( !SupportMWE() )
        return ;
#endif

    if( !g_bDLCOnOff )
    {
        return ;
    }

	msDrvHistogramUpDateData();


	if(!REG_UpdateHistogram_Flag)
		return ;

#if DEBUG_DLC_HISTOGRAM
    printData("\r\n ===== (DLC) Histogram Start ======", NULL);
    for ( i = 0; i < 32; i++ )
        printData("\r\n  %x", uwArray[i]);
    printData("\r\n ===== (DLC)Histogram End ======", NULL);
#endif

    //if(!retry)
        //mStar_AdjustDcrBrightness();

#if DLC_S_MODE
 	if( DlcMode == DLC_STATIC )
    {
        for( i = 0; i < 18; i++ )
        {
            msWriteByte( SC08_AE+i, g_ucLumaCurve[i] );
        }
    }
    else
    {
        if( DlcMode == DLC_HIGH)
        {
            s_CurveH = s_CurveH_High;
            s_CurveL = s_CurveL_High;
        }
        else
        {
            s_CurveH = s_CurveH_Low;
            s_CurveL = s_CurveL_Low;
        }

        j = 0;
        for( i = 0; i < 16; i++ )
        {
            g_ucLumaCurve[i] = j;
            j += 0x10;
        }
        g_ucLumaCurve[16] = 0x00;//0xFF;
        g_ucLumaCurve[17] = 0x01;

        TempVar1 = 0;
        TempVar2 = 0;
        for( i = 0; i < 32; i++ )
        {
            TempVar1 += (DWORD)uwArray[i] * (DWORD)(i);
            TempVar2 += (DWORD)uwArray[i];
        }
		if(TempVar1 != 0 && TempVar2 != 0)
        	CurveIdx = TempVar1/TempVar2;
        CurveIdx = CurveIdx>>1;
        //printData("CurveIdx = %d", CurveIdx);

        #if 0
        TempVar1 = 0;
        TempVar2 = 0;
        for( i = 0; i < 31; i++ )
        {
            TempVar1 = DlcTotal>>5;
            TempVar1 = uwArray[i]>TempVar1 ? uwArray[i]-TempVar1 : TempVar1-uwArray[i];
            TempVar2 += TempVar1;
        }
        //printData("DiffSum = %d", TempVar2);
        TempVar2 = TempVar2>>10;
        TempVar2 = TempVar2>10 ? TempVar2-10 : 0;
        CurveWgt = TempVar2>32 ? 32 : TempVar2;
        //printData("CurveWgt = %d", CurveWgt);
        #else
        CurveWgt = 32;
        #endif

        for ( i = 0; i < 17; i++ )
        {
            if (i>CurveIdx)
            {

                TempVar1 = i-CurveIdx;
                TempVar1 = TempVar1>=5 ? 5 : TempVar1;
                TempVar1 = (DWORD)g_ucLumaCurve[i] + ((DWORD)s_CurveH[TempVar1]*s_CurveGain*CurveWgt)/32;
                g_ucLumaCurve[i] = TempVar1 > 0x00FF ? 0xff : TempVar1;
            }
            if (i<=CurveIdx)
            {
                TempVar1 = CurveIdx-i;
                TempVar1 = TempVar1>=7 ? 7 : TempVar1;
                TempVar1 = (DWORD)g_ucLumaCurve[i] - ((DWORD)s_CurveL[TempVar1]*s_CurveGain*CurveWgt)/32;
                g_ucLumaCurve[i] = TempVar1 > 0xF000 ? 0x00 : TempVar1;
            }
        }

#if DEBUG_DLC_CURVE
    printMsg("\r\n ===== (DLC)  ======");
    for ( i = 0; i < 18; i++ )
        printData("\r\n  %x", g_ucLumaCurve[i]);
    printMsg("\r\n ===== (DLC) End ======");
#endif

        if (DLC_Loop_Cnt==0)
        {
            for( i = 0; i < 16; i++ )
            {
                TempVar1 =msReadByte( SC08_AE+i);
                if (g_ucLumaCurve[i]>TempVar1)
                {
                    msWriteByte( SC08_AE+i, TempVar1+1 );
                }
                else if (g_ucLumaCurve[i]<TempVar1)
                {
                    msWriteByte( SC08_AE+i, TempVar1-1 );
                }
            }

			g_ucLumaCurve[16] = 0x00;
        	g_ucLumaCurve[17] = 0x01;
            TempVar1 = msRead2Byte( SC08_AE+16);
            TempVar2 = (((WORD)g_ucLumaCurve[17]<<8)+g_ucLumaCurve[16]);
            if (TempVar2>TempVar1)
            {
                TempVar1 +=1;
                msWriteByte( SC08_AE+17, TempVar1>>8 );
                msWriteByte( SC08_AE+16, TempVar1&0xFF );
            }
            else if (TempVar2<TempVar1)
            {
                TempVar1 -=1;
                msWriteByte( SC08_AE+16, TempVar1&0xFF );
                msWriteByte( SC08_AE+17, TempVar1>>8 );
            }
        }

        if (DLC_Loop_Cnt == DLC_Loop_Cnt_THD)
        {
            DLC_Loop_Cnt = 0;
        }
        else
        {
            DLC_Loop_Cnt++;
        }
    }
#endif
#if 0 // wait for coding
    //bWindow=1;
    ucBank = old_msReadByte( BK0_00 );
    old_msWriteByte( BK0_00, REGBANK3 );
    //if( MAIN_WINDOW == bWindow ) // Main window
    //if( 0 ) // Main window
    //{
    //    old_msWriteByte(BK3_B8, old_msReadByte(BK3_B8) | _BIT2 | _BIT1);
    //}
    //else // Sub window
    {
        if( g_bNeedRequest )            // 2004/11/19
        {
            mStar_WriteByteMask( BK3_B8, (BIT4 | BIT2 | BIT0), (BIT4 | BIT2 | BIT0) );
            g_bNeedRequest = 0;
            //printMsg("request");
        }
    }
    switch( DLCStatus )
    {
        case DLC_WAIT:
            if( UserPrefDcrMode )
            {
                if( ReadFrameDataCnt % 2 == 0 ) // set to lower of panel height
                {
                    old_msWriteByte( BK3_B6, TopLimit_Lower );
                    old_msWriteByte( BK3_B7, DownLimit_Lower );
                }
                else // set to upper of panel height
                {
                    old_msWriteByte( BK3_B6, TopLimit_Upper );
                    old_msWriteByte( BK3_B7, DownLimit_Upper );
                }
            }
            #if DYNAMIC_DLC// 2004/11/10
            if( !( old_msReadByte( BK3_B8 ) &BIT3 ) )                // 2004/11/19
            {
                old_msWriteByte( BK0_00, ucBank );
                return ;
            }
            //while (!(old_msReadByte(BK3_B8) & _BIT3));  // Wait until ready// 2004/11/3
            #endif
            DLCStatus = DLC_READ1;
            old_msWriteByte( BK0_00, ucBank );
            return ;
        case DLC_READ1:
            old_msWriteByte( BK3_B9, 0 );
            #if DYNAMIC_DLC// 2004/11/10
            // 8 segment pixel count extraction
            // Sequencial read
            //=======Define the capture area===========
            // old_msWriteByte(BK3_B5,0x01);
            // old_msWriteByte(BK3_B6,0x030);// start
            // old_msWriteByte(BK3_B6,0x070);// start
            //===================================AutoBacklight function Start=====================
            tempvalue = old_msReadByte( BK3_B8 );
            old_msWriteByte( BK3_B8, 0x16 );
            while( retry-- && !( old_msReadByte( BK3_B8 ) &BIT3 ) )
                ;
            for( ucTmp = 0; ucTmp < 1; ucTmp++ )                // 2004/11/3
                uwArray[ucTmp] = (( WORD )old_msReadByte( BK3_BA ) ) * 0x100 + ( WORD )old_msReadByte( BK3_BA );            // 2004/11/3
            #endif
            {
#if DCRNew

                DWORD PixelCount, LumCount;
                BYTE AveLumi , AveLumi2;


#else //!DCRNew

                WORD reduceAry;
                BYTE CurrentVal;
                BYTE OffsetlVal, OffsetlBL;
                BYTE noise_th = 8;   //8  //20081202
#if 1
                BYTE BL_HIGH = 0xFF;
                BYTE BL_LOW = 0;
#else
                BYTE BL_HIGH = UserprefAutolightHigh; // 0xFF;
                BYTE BL_LOW = UserprefAutolightLow; //0x00;
#endif
                UserprefALha = 60;
                reduceAry = uwArray[0];
                //  printData("uwArray[0]  = 0x%x\r\n", reduceAry);

#endif // end of DCRNew

                // 081117
                if( ReadFrameDataCnt % 2 == 0 ) // get all display data
                {
                    BYTE tempVal;

                    if(( tempVal = old_msReadByte( BK3_3A ) ) > BrightData ) // get max bright data
                        BrightData = tempVal;
                    if(( tempVal = old_msReadByte( BK3_39 ) ) < DarkData ) // get min dark data
                        DarkData = tempVal;
                    if( abs( BrightData - DarkData ) <= BlackWhiteDifference )
                    {
                        if( abs( DarkData - DarkestValue ) <= DarkestRange ) // all display data are dark
                        {
                            SetDarkestFlag = 1;
                        }
                    }

#if DCRNew // 081204
                    PixelCount = mStar_ReadWord( BK3_35 );
                    LumCount = mStar_ReadWord( BK3_37 );
                    AveLumi = ( LumCount * 256 ) / PixelCount;
                    AveLumi = (( WORD )PreAveLumi + AveLumi ) / 2;

                    PixelCount = mStar_ReadWord( BK3_35 );
                    LumCount = mStar_ReadWord( BK3_37 );
                    AveLumi2 = ( LumCount * 256 ) / PixelCount;
                    AveLumi2 = (( WORD )PreAveLumi2 + AveLumi2 ) / 2;
                    if( abs( AveLumi2 - AveLumi ) > 10 ) // read twice to confirm? (not stable)
                    {
                        mStar_WriteByteMask( BK3_B8, 0x00, (BIT3 | BIT2 | BIT1 | BIT0) );
                        g_bNeedRequest = 1;
                        DLCStatus = DLC_WAIT;
                        old_msWriteByte( BK0_00, ucBank );
                        ReadFrameDataCnt ++;
                        break;
                    }

#if DCRMotionTest
                    BackLightTargetValue = AveLumi;

                    if( abs( BackLightTargetValue - BacklightPrev ) >= DCRStep )
                    {
                        bDCRSmoothMotionFlag = 1;
                        DCRStepTransValue = DCRStep / 2; //abs(BackLightTargetValue-BacklightPrev)/DCRStep;
                    }
                    else
                    {
                        bDCRSmoothMotionFlag = 0;
                    }

                    if( bDCRSmoothMotionFlag ) // DCR operating range is over DCRStep
                    {
                        if( BackLightTargetValue >= BacklightPrev ) // increasement
                        {
                            BacklightNow = ( BacklightNow + DCRStepTransValue >= BackLightTargetValue ) ? ( BackLightTargetValue ) : ( BacklightNow + DCRStepTransValue );
                            //BacklightPrev = BacklightNow;//2009-07-29//20091104
                        }
                        else // decreasement
                        {
                            BacklightNow = ( BacklightNow - DCRStepTransValue <= BackLightTargetValue ) ? ( BackLightTargetValue ) : ( BacklightNow - DCRStepTransValue );
                        }
                    }
                    else
                    {
                        BacklightNow = BackLightTargetValue;
                    }

#else // !DCRMotionTest
                    BacklightNow = AveLumi;
#endif

                    if( 0 ) //(abs(BacklightNow - BacklightPrev) < 3)
                    {
                        mStar_WriteByteMask( BK3_B8, 0x00, (BIT3 | BIT2 | BIT1 | BIT0) );
                        g_bNeedRequest = 1;
                        DLCStatus = DLC_WAIT;
                        old_msWriteByte( BK0_00, ucBank );
                        break;
                    }

#else // !DCRNew

                    CurrentVal = ( reduceAry >> 8 ) & 0xFF;
                    CurrentVal = (( WORD )( CurrentVal ) + DarkSegmentData ) / 2;
                    HistogramNow = CurrentVal;
                    HistogramNow = ( WORD )( UserprefALha * HistogramNow + ( 100 - UserprefALha ) * HistogramPrev ) / 100;
                    OffsetlVal = abs( HistogramNow - HistogramPrev ) / 2;
                    if( HistogramNow > HistogramPrev )
                        HistogramNow = HistogramPrev + OffsetlVal;
                    else if( HistogramNow < HistogramPrev )
                        HistogramNow = HistogramPrev - OffsetlVal;
                    //printData("UserprefALha = %d\r\n", UserprefALha);
                    //printData("HistogramNow = %d\r\n",HistogramNow);
                    if( UserprefHistogram1 > HistogramNow )
                        BacklightNow = BL_HIGH;
                    //  LIGHT
                    else if( UserprefHistogram2 < HistogramNow )
                        BacklightNow = BL_LOW;
                    // DARK
                    else
                        BacklightNow = ( WORD )(( UserprefHistogram2 - HistogramNow ) * ( BL_HIGH - BL_LOW ) / abs( UserprefHistogram2 - UserprefHistogram1 ) ) + BL_LOW;
                    OffsetlBL = abs( BacklightNow - BacklightPrev ) / 2; //2         //20081201
                    if( BacklightNow > BacklightPrev )
                        BacklightNow = BacklightPrev + OffsetlBL;
                    else if( BacklightNow < BacklightPrev )
                        BacklightNow = BacklightPrev - OffsetlBL;
                    if(( BacklightNow > BacklightPrev ) && (( BacklightNow - BacklightPrev ) >= noise_th ) )
                        BacklightNow = BacklightNow - noise_th;
                    else if(( BacklightPrev > BacklightNow ) && (( BacklightPrev - BacklightNow ) >= noise_th ) )
                        BacklightNow = BacklightNow + noise_th;
                    else
                        BacklightNow = BacklightPrev;
#endif // end of DCRNew

                    //=====Get the Histogram value=============
#if DCRMotionTest
                    if( !u8DCRStepTransCnt )
#endif
                        if(( BacklightNow != BacklightPrev ) || ( BrightData != PreBrightData ) )
                        {
                            BacklightPrev = BacklightNow;
                            PreBrightData = BrightData;
                            mStar_AdjustDcrBrightness();
#if DCRMotionTest
                            u8DCRStepTransCnt = DCRStepTransPeriod;
#endif
                    }
                    old_msWriteByte( BK0_00, REGBANK3 );
                    HistogramPrev = HistogramNow;
                    //BacklightPrev = BacklightNow;
                    //=============================================================
                }
                else // get upper dark / bright data
                {
#if !DCRNew
                    DarkSegmentData = ( reduceAry >> 8 ) & 0xFF;
#endif

                    DarkData = old_msReadByte( BK3_39 );
                    BrightData = old_msReadByte( BK3_3A );
                    PixelCount = mStar_ReadWord( BK3_35 );
                    LumCount = mStar_ReadWord( BK3_37 );
                    PreAveLumi = ( LumCount * 256 ) / PixelCount;
                    PixelCount = mStar_ReadWord( BK3_35 );
                    LumCount = mStar_ReadWord( BK3_37 );
                    PreAveLumi2 = ( LumCount * 256 ) / PixelCount;
                }

                ReadFrameDataCnt ++;
            }
            // 081109 modified for it's unnecessary to execute others case below when DCR on.
            //DLCStatus = DLC_READ2;
            if( UserPrefDcrMode )
            {
                mStar_WriteByteMask( BK3_B8, 0x00, (BIT3 | BIT2 | BIT1 | BIT0) );
                g_bNeedRequest = 1;
                DLCStatus = DLC_WAIT;
            }
            else
                DLCStatus = DLC_READ2;

            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_READ2:
            old_msWriteByte( BK3_B9, 2 );
#if DYNAMIC_DLC// 2004/11/10
            // 8 segment pixel count extraction
            // Sequencial read
            for( ucTmp = 1; ucTmp < 2; ucTmp++ )
                // 2004/11/3
                uwArray[ucTmp] = (( WORD )old_msReadByte( BK3_BA ) ) * 0x100 + ( WORD )old_msReadByte( BK3_BA );
#endif
            DLCStatus = DLC_READ3;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_READ3:
            old_msWriteByte( BK3_B9, 4 );
#if DYNAMIC_DLC// 2004/11/10
            // 8 segment pixel count extraction
            // Sequencial read
            for( ucTmp = 2; ucTmp < 3; ucTmp++ )
                uwArray[ucTmp] = (( WORD )old_msReadByte( BK3_BA ) ) * 0x100 + ( WORD )old_msReadByte( BK3_BA );
#endif
            DLCStatus = DLC_READ4;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_READ4:
            old_msWriteByte( BK3_B9, 6 );
#if DYNAMIC_DLC// 2004/11/10
            // 8 segment pixel count extraction
            // Sequencial read
            for( ucTmp = 3; ucTmp < 4; ucTmp++ )
                uwArray[ucTmp] = (( WORD )old_msReadByte( BK3_BA ) ) * 0x100 + ( WORD )old_msReadByte( BK3_BA );
#endif
            DLCStatus = DLC_READ5;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_READ5:
            old_msWriteByte( BK3_B9, 8 );
#if DYNAMIC_DLC// 2004/11/10
            // 8 segment pixel count extraction
            // Sequencial read
            for( ucTmp = 4; ucTmp < 5; ucTmp++ )
                uwArray[ucTmp] = (( WORD )old_msReadByte( BK3_BA ) ) * 0x100 + ( WORD )old_msReadByte( BK3_BA );
#endif
            DLCStatus = DLC_READ6;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_READ6:
            old_msWriteByte( BK3_B9, 10 );
#if DYNAMIC_DLC// 2004/11/10
            // 8 segment pixel count extraction
            // Sequencial read
            for( ucTmp = 5; ucTmp < 6; ucTmp++ )
                uwArray[ucTmp] = (( WORD )old_msReadByte( BK3_BA ) ) * 0x100 + ( WORD )old_msReadByte( BK3_BA );
#endif
            DLCStatus = DLC_READ7;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_READ7:
            old_msWriteByte( BK3_B9, 12 );
#if DYNAMIC_DLC// 2004/11/10
            // 8 segment pixel count extraction
            // Sequencial read
            for( ucTmp = 6; ucTmp < 7; ucTmp++ )
                uwArray[ucTmp] = (( WORD )old_msReadByte( BK3_BA ) ) * 0x100 + ( WORD )old_msReadByte( BK3_BA );
#endif
            DLCStatus = DLC_READ8;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_READ8:
            old_msWriteByte( BK3_B9, 14 );
#if DYNAMIC_DLC// 2004/11/10
            // 8 segment pixel count extraction
            // Sequencial read
            for( ucTmp = 7; ucTmp < 8; ucTmp++ )
                uwArray[ucTmp] = (( WORD )old_msReadByte( BK3_BA ) ) * 0x100 + ( WORD )old_msReadByte( BK3_BA );
#endif
            DLCStatus = DLC_CAL1;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_CAL1:
            uwArray[3] = (( uwArray[0] / 2 ) + ( uwArray[1] / 4 ) + ( uwArray[2] / 4 ) );
            uwArray[4] = (( uwArray[5] / 4 ) + ( uwArray[6] / 4 ) + ( uwArray[7] / 2 ) );
            //if ((uwArray[3]>tpArray[8]) && ((uwArray[3]-uwArray[8])> FACTORY_19))
            //    g_fcount=2;
            // g_ucTable[5] value LUT
            //if (g_ucTable[5] == 0)        // this line should be removed!
            //    g_ucTable[5] = 0x57;
            if( uwArray[3] < FACTORY_7 )
            {
                ucTmp = (( FACTORY_7 - uwArray[3] ) / Lstep ) + 1;
                if( ucTmp > 10 )
                    ucTmp = 10;
                g_ucTable[5] = 0x57 - ucTmp;
            }
            else if( uwArray[3] > FACTORY_9 )
            {
                ucTmp = (( uwArray[3] - FACTORY_9 ) / Hstep ) + 1;
                if( ucTmp > 10 )
                    ucTmp = 10;
                g_ucTable[5] = 0x57 + ucTmp;
            }
            else
                g_ucTable[5] = 0x57;
            //flicker avoid
            if( s_Slope5 == 0 )
                s_Slope5 = 0x57;
            DLCStatus = DLC_CAL2;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_CAL2:
            if(( g_ucTable[5] > s_Slope5 ) && (( g_ucTable[5] - s_Slope5 ) >= 2 ) )
                g_ucTable[5] = g_ucTable[5] - 1;
            else if(( s_Slope5 > g_ucTable[5] ) && (( s_Slope5 - g_ucTable[5] ) >= 2 ) )
                g_ucTable[5] = g_ucTable[5] + 1;
            else
                g_ucTable[5] = s_Slope5;
            //uwArray[8] =  uwArray[3];
            // g_ucTable[2] value LUT
            uwArray[3] = uwArray[0];
            //if (g_ucTable[2] == 0)  // Can this line be removed
            //    g_ucTable[2] = 0x27;// Can this line be removed
            g_ucTable[2] = (( g_ucTable[5] - 0x07 ) * 2 / 5 ) + 0x07;
            if( uwArray[3] < FACTORY_7 )
            {
                ucTmp = (( FACTORY_7 - uwArray[3] ) / Lstep ) + 1;
                if( ucTmp > 10 )
                    ucTmp = 10;
                g_ucTable[2] = g_ucTable[2] - ucTmp;
            }
            else if( uwArray[3] > FACTORY_9 )
            {
                ucTmp = (( uwArray[3] - FACTORY_9 ) / Hstep ) + 1;
                if( ucTmp > 10 )
                    ucTmp = 10;
                g_ucTable[2] = g_ucTable[2] + ucTmp;
            }
            //else
            //    g_ucTable[2] = g_ucTable[2];
            //flicker avoid
            if( s_Slope2 == 0 )
                s_Slope2 = 0x27;
            DLCStatus = DLC_CAL3;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_CAL3:
            if(( g_ucTable[2] > s_Slope2 ) && (( g_ucTable[2] - s_Slope2 ) >= 2 ) )
                g_ucTable[2] = g_ucTable[2] - 1;
            else if(( s_Slope2 > g_ucTable[2] ) && (( s_Slope2 - g_ucTable[2] ) >= 2 ) )
                g_ucTable[2] = g_ucTable[2] + 1;
            else
                g_ucTable[2] = s_Slope2;

            // g_ucTable[10] value LUT
            //if (g_ucTable[10] == 0)       // this line should be removed
            //    g_ucTable[10] = 0xA7;
            if( uwArray[4] < FACTORY_7 )
            {
                ucTmp = (( FACTORY_7 - uwArray[4] ) / Lstep ) + 1;
                if( ucTmp > 8 )
                    ucTmp = 8;
                g_ucTable[10] = 0xA7 + ucTmp;
            }
            else if( uwArray[4] > FACTORY_9 )
            {
                ucTmp = (( uwArray[4] - FACTORY_9 ) / Hstep ) + 1;
                if( ucTmp > 8 )
                    ucTmp = 8;
                g_ucTable[10] = 0xA7 - ucTmp;
            }
            else
                g_ucTable[10] = 0xA7;

            // g_ucTable[13] value LUT
            uwArray[4] = uwArray[7];
            //if (g_ucTable[13] == 0)       // this line should be removed
            //    g_ucTable[13] = 0xd7;
            DLCStatus = DLC_CAL4;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_CAL4:
            g_ucTable[13] = 0xf7 - (( 0xf7 - g_ucTable[10] ) * 2 / 5 );
            if( uwArray[4] < FACTORY_7 )
            {
                ucTmp = (( FACTORY_7 - uwArray[4] ) / Lstep ) + 1;
                if( ucTmp > 8 )
                    ucTmp = 8;
                g_ucTable[13] = g_ucTable[13] + ucTmp;
            }
            else if( uwArray[4] > FACTORY_9 )
            {
                ucTmp = (( uwArray[4] - FACTORY_9 ) / Hstep ) + 1;
                if( ucTmp > 8 )
                    ucTmp = 8;
                g_ucTable[13] = g_ucTable[13] - ucTmp;
            }
            //else
            //    g_ucTable[13] =g_ucTable[13];
            s_Slope5 = g_ucTable[5];
            s_Slope2 = g_ucTable[2];
            DLCStatus = DLC_CAL5;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_CAL5:
#if 0
            if( g_bLockDlc == 1 )
                // For test
            {
                g_ucTable[2] = 0x27;
                g_ucTable[5] = 0x57;
                g_ucTable[10] = 0xA7;
                g_ucTable[13] = 0xd7;
            }
#endif
            g_ucTable[1] = ( 0x07 + g_ucTable[2] ) / 2;
            g_ucTable[3] = g_ucTable[5] - (( g_ucTable[5] - g_ucTable[2] ) * 2 / 3 );
            g_ucTable[4] = g_ucTable[2] + (( g_ucTable[5] - g_ucTable[2] ) * 2 / 3 );
            g_ucTable[7] = g_ucTable[5] + (( g_ucTable[10] - g_ucTable[5] ) * 2 / 5 );
            g_ucTable[6] = ( g_ucTable[5] / 2 ) + ( g_ucTable[7] / 2 );
            g_ucTable[8] = g_ucTable[10] - (( g_ucTable[10] - g_ucTable[5] ) * 2 / 5 );
            g_ucTable[9] = ( g_ucTable[8] / 2 ) + ( g_ucTable[10] / 2 );
            g_ucTable[11] = g_ucTable[13] - (( g_ucTable[13] - g_ucTable[10] ) * 2 / 3 );
            g_ucTable[14] = ( g_ucTable[13] / 2 ) + ( 0xf7 / 2 );
            g_ucTable[12] = g_ucTable[10] + (( g_ucTable[13] - g_ucTable[10] ) * 2 / 3 );
            DLCStatus = DLC_CAL6;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_CAL6:
            g_ucTable[0] = ( 0x07 + ( g_ucTable[1] / 3 ) ) / 2; // fine tune lowest level
            //if(DLCMode==MODE2_DLC)  // xxxx 0909
            //   g_ucTable[0] = 0x05;
            g_ucTable[15] = 0xff - (( 0xff - g_ucTable[14] ) / 3 );
            g_ucTable[15] = (( g_ucTable[15] ) / 2 ) + ( 0xff / 2 ); // fine tune highest level
            g_ucTable[0] = g_ucTable[0] + g_ucLumaCurve[0] - 0x07;
            g_ucTable[1] = g_ucTable[1] + g_ucLumaCurve[1] - 0x17;
            g_ucTable[2] = g_ucTable[2] + g_ucLumaCurve[2] - 0x27;
            g_ucTable[3] = g_ucTable[3] + g_ucLumaCurve[3] - 0x37;
            g_ucTable[4] = g_ucTable[4] + g_ucLumaCurve[4] - 0x47;
            g_ucTable[5] = g_ucTable[5] + g_ucLumaCurve[5] - 0x57;
            g_ucTable[6] = g_ucTable[6] + g_ucLumaCurve[6] - 0x67;
            g_ucTable[7] = g_ucTable[7] + g_ucLumaCurve[7] - 0x77;
            g_ucTable[8] = g_ucTable[8] + g_ucLumaCurve[8] - 0x87;
            g_ucTable[9] = g_ucTable[9] + g_ucLumaCurve[9] - 0x97;
            g_ucTable[10] = g_ucTable[10] + g_ucLumaCurve[10] - 0xa7;
            g_ucTable[11] = g_ucTable[11] + g_ucLumaCurve[11] - 0xb7;
            g_ucTable[12] = g_ucTable[12] + g_ucLumaCurve[12] - 0xc7;
            g_ucTable[13] = g_ucTable[13] + g_ucLumaCurve[13] - 0xd7;
            g_ucTable[14] = g_ucTable[14] + g_ucLumaCurve[14] - 0xe7;
            g_ucTable[15] = g_ucTable[15] + g_ucLumaCurve[15] - 0xf7;

            for( ucTmp = 0; ucTmp < 16; ucTmp++ )
            {
                if( g_ucTable[ucTmp] > 0x1FF )
                    g_ucTable[ucTmp] = 0x00;
                else if( g_ucTable[ucTmp] > 0xFF )
                    g_ucTable[ucTmp] = 0xFF;
            }
#if !DYNAMIC_DLC// 2004/11/10
            g_ucTable[0] = g_ucLumaCurve[0];
            g_ucTable[1] = g_ucLumaCurve[1];
            g_ucTable[2] = g_ucLumaCurve[2];
            g_ucTable[3] = g_ucLumaCurve[3];
            g_ucTable[4] = g_ucLumaCurve[4];
            g_ucTable[5] = g_ucLumaCurve[5];
            g_ucTable[6] = g_ucLumaCurve[6];
            g_ucTable[7] = g_ucLumaCurve[7];
            g_ucTable[8] = g_ucLumaCurve[8];
            g_ucTable[9] = g_ucLumaCurve[9];
            g_ucTable[10] = g_ucLumaCurve[10];
            g_ucTable[11] = g_ucLumaCurve[11];
            g_ucTable[12] = g_ucLumaCurve[12];
            g_ucTable[13] = g_ucLumaCurve[13];
            g_ucTable[14] = g_ucLumaCurve[14];
            g_ucTable[15] = g_ucLumaCurve[15];
#endif
            DLCStatus = DLC_WRITE1;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_WRITE1:
            old_msWriteByte( BK0_00, REGBANK3 ); // bank 3
            old_msWriteByte( BK3_B9, 0x10 );
            for( ucTmp = 0; ucTmp <= 1; ucTmp++ )
            {
                old_msWriteByte( BK3_BA, g_ucTable[ucTmp] );
            }
            //old_msWriteByte(BK3_BA, g_ucLumaCurve[ucTmp][uc2]);
            DLCStatus = DLC_WRITE2;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_WRITE2:
            old_msWriteByte( BK0_00, REGBANK3 ); // bank 3
            old_msWriteByte( BK3_B9, 0x12 );
            for( ucTmp = 2; ucTmp <= 3; ucTmp++ )
            {
                old_msWriteByte( BK3_BA, g_ucTable[ucTmp] );
            }
            //old_msWriteByte(BK3_BA, g_ucLumaCurve[ucTmp][uc2]);
            DLCStatus = DLC_WRITE3;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_WRITE3:
            old_msWriteByte( BK0_00, REGBANK3 ); // bank 3
            old_msWriteByte( BK3_B9, 0x14 );
            for( ucTmp = 4; ucTmp <= 5; ucTmp++ )
            {
                old_msWriteByte( BK3_BA, g_ucTable[ucTmp] );
            }
            //old_msWriteByte(BK3_BA, g_ucLumaCurve[ucTmp][uc2]);
            DLCStatus = DLC_WRITE4;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_WRITE4:
            old_msWriteByte( BK0_00, REGBANK3 ); // bank 3
            old_msWriteByte( BK3_B9, 0x16 );
            for( ucTmp = 6; ucTmp <= 7; ucTmp++ )
            {
                old_msWriteByte( BK3_BA, g_ucTable[ucTmp] );
            }
            //old_msWriteByte(BK3_BA, g_ucLumaCurve[ucTmp][uc2]);
            DLCStatus = DLC_WRITE5;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_WRITE5:
            old_msWriteByte( BK0_00, REGBANK3 ); // bank 3
            old_msWriteByte( BK3_B9, 0x18 );
            for( ucTmp = 8; ucTmp <= 9; ucTmp++ )
            {
                old_msWriteByte( BK3_BA, g_ucTable[ucTmp] );
            }
            //old_msWriteByte(BK3_BA, g_ucLumaCurve[ucTmp][uc2]);
            DLCStatus = DLC_WRITE6;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_WRITE6:
            old_msWriteByte( BK0_00, REGBANK3 ); // bank 3
            old_msWriteByte( BK3_B9, 0x1A );
            for( ucTmp = 0x0a; ucTmp <= 0x0b; ucTmp++ )
            {
                old_msWriteByte( BK3_BA, g_ucTable[ucTmp] );
            }
            //old_msWriteByte(BK3_BA, g_ucLumaCurve[ucTmp][uc2]);
            DLCStatus = DLC_WRITE7;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_WRITE7:
            old_msWriteByte( BK0_00, REGBANK3 ); // bank 3
            old_msWriteByte( BK3_B9, 0x1C );
            for( ucTmp = 0x0c; ucTmp <= 0x0d; ucTmp++ )
            {
                old_msWriteByte( BK3_BA, g_ucTable[ucTmp] );
            }
            //old_msWriteByte(BK3_BA, g_ucLumaCurve[ucTmp][uc2]);
            DLCStatus = DLC_WRITE8;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        case DLC_WRITE8:
            if( ucDLCCCount < 255 )
                ucDLCCCount++;
            old_msWriteByte( BK0_00, REGBANK3 ); // bank 3
            old_msWriteByte( BK3_B9, 0x1E );
            for( ucTmp = 0x0e; ucTmp <= 0x0f; ucTmp++ )
            {
                old_msWriteByte( BK3_BA, g_ucTable[ucTmp] );
            }
            //old_msWriteByte(BK3_BA, g_ucLumaCurve[ucTmp][uc2]);
            old_msWriteByte( BK0_00, REGBANK3 );
            mStar_WriteByteMask( BK3_B8, 0x00, (BIT3 | BIT2 | BIT1 | BIT0) );
            //printMsg("reset");
            g_bNeedRequest = 1; // 2004/11/19
            old_msWriteByte( BK0_00, ucBank );
            DLCStatus = DLC_WAIT;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
        default:
            g_bNeedRequest = 1;
            DLCStatus = DLC_WAIT;
            old_msWriteByte( BK0_00, ucBank );
            return ;
            break;
    }
#endif
}
void LoadDLCTable( const BYTE *pDLCtable ) // 2004/10/15
{
    BYTE LOCAL_TYPE index;
    LOCAL_TYPE const BYTE *DLCtable;
    DLCtable = pDLCtable;
    // dlc function
    for( index = 0; index < 16; index++ )
    {
        g_ucLumaCurve[index] = DLCtable[index];
    }
    g_LowStrength = DLCtable[16];
    g_HighStrength = DLCtable[17];
    msSetDlcStrength( g_LowStrength, g_HighStrength );
    msDlcOnOff( _ENABLE );
}


#define DCRNew  1   // 081204
#define DCRMotionTest   1 // 081205
#if DCRNew
WORD xdata PreAveLumi, PreAveLumi2;
#endif
#if DCRMotionTest
#define DCRStep     8 // DCR increasement/decreasement step
#define DCRStepTransPeriod  2 // unit: 10ms
BYTE xdata DCRStepTransValue; //
BYTE xdata BackLightTargetValue; //
BYTE xdata u8DCRStepTransCnt; // unit: DCRStepTransPeriod*10ms
bit bDCRSmoothMotionFlag = 0;
#endif

void msDCROnOff( BYTE ucSwitch, BYTE win)
{
    if(ucSwitch)
    {
        BrightData = 0xff;
        PreBrightData = 0xff;
        DarkData = 0x00;
        ReadFrameDataCnt = 1;
        SetDarkestFlag = 0;
        HISTOGRAM_WHOLE_VERTICAL_RANGE_EN(1);//old_msWriteByteMask(SC3_B5, 0, BIT0); // whole DE range
        HISTOGRAM_RGB_TO_Y_EN(IsColorspaceRGB());//old_msWriteByteMask(SC7_40, BIT2, BIT2); // enable R2Y       //A008 item
        if(win == 0) // 0: main win
        {
            MWE_FUNCTION_EN(0);//old_msWriteByteMask(SC0_5C, 0, BIT3);
            STATISTIC_REQUEST_MAIN_ENABLE();//old_msWriteByte(SC7_B8, (BIT2|BIT1));
        }
        else // 1: sub win
        {
            MWE_FUNCTION_EN(1);//old_msWriteByteMask(SC0_5C, BIT3, BIT3);
            STATISTIC_REQUEST_SUB_ENABLE();//old_msWriteByte(SC7_B8, (BIT2|BIT0));
        }
    }
    else
    {
        STATISTIC_REQUEST_EN(0);//old_msWriteByte(SC7_B8, 0);
    }

     SetDCRStatus(ucSwitch);
     msAPIDCR_Inital(UserPrefBrightness);	

}


#define DCRAdjustStep 1
#define DCRMinTarget 4
#define DCRMaxTarget 30

void SetDCRStatus(BYTE En)
{
	bDCRStatus = En;
}

BOOL GetDCRStatus(void)
{
	return bDCRStatus;
}

void SetDCR_OFF_Backlight(BYTE u8BL)
{
	u8UpdatedBacklight = u8BL;
}

void SetColorRangeStatus(BOOL En)
{
	bIsLimitedlRangeFlag = En;
}


BOOL GetColorRangeStatus(void)
{
	return bIsLimitedlRangeFlag;
}

void msDCR_InitalSetting(BYTE u8Step, BYTE u8TargetMax, BYTE u8TargetMin)
{   
	u8UpdateStep = u8Step;
	u8WeightAvg_Max = u8TargetMax;
	u8WeightAvg_Min = u8TargetMin;
}

WORD msExtendRealBL(WORD min , WORD max, BYTE cur)
{
	WORD u16Value =0;
	if((max-min) > 0 || (u8Backlight_Max - u8Backlight_Min) > 0)
		u16Value  = (DWORD)((max * max/(max-min)) * cur / (u8Backlight_Max - u8Backlight_Min)) ;
	return u16Value;
}

void msAPIDCR_Enable(Bool bEn)
{
	SetDCRStatus(bEn);
}

void msAPIDCR_Inital(BYTE PreBL)
{
	SetColorRangeStatus(0); 
	msDCR_InitalSetting(DCRAdjustStep,  DCRMaxTarget , DCRMinTarget);
	u8BacklightPrev = PreBL;
	SetDCR_OFF_Backlight(PreBL);
}

void msAPIBL_Handler(void)
{
    WORD u16PWM =0;


    if(u8BacklightPrev != u8BacklightNow)
    {
        u16PWM = msExtendRealBL(BRIGHTNESS_REAL_MIN, BRIGHTNESS_REAL_MAX, u8BacklightNow ); //  u16PWM = msExtendRealBL(u16Backlight_Min, u16Backlight_Max, u8BacklightNow ); 

	#if DEBUG_DCR
	printData("\r\n u16PWM=%x",u16PWM);
	#endif
	mStar_AdjustBrightness( u16PWM ); 
    }
    u8BacklightPrev = u8BacklightNow;

}

void msDCR_OFF_Fading(void)
{
     u8BacklightNow = u8UpdatedBacklight;  	
   
     if (u8BacklightNow > (u8BacklightPrev))
        u8BacklightNow = u8BacklightPrev + u8UpdateStep;
    else if ((u8BacklightNow) < u8BacklightPrev)
        u8BacklightNow = u8BacklightPrev - u8UpdateStep;
}

void msDCR_Handler(void)
{
   if(!GetDCRStatus())
   {	
	msDCR_OFF_Fading();
	return;
   }
   
   msDrvHistogramUpDateData();
    if(!REG_UpdateHistogram_Flag)
	return ;
	
    if(GetColorRangeStatus())//if (u8DLCFlags&DLCF_VIDEO_LVL_MODE_LIMITED) //YUV domain
    {
        u16WeightAvg_Cur=(u16WeightAvg_Cur<=16 ? 0 :\
            (u16WeightAvg_Cur>=235? 255: ((WORD)255*(u16WeightAvg_Cur-16)+109)/219)); //mapping 16~235 to 0~255
    }

    if( u16WeightAvg_Cur > u8WeightAvg_Max)
        u8BacklightNow=u8Backlight_Max;  //  LIGHT
    else if( u16WeightAvg_Cur < u8WeightAvg_Min )
        u8BacklightNow=u8Backlight_Min; // DARK
    else
        u8BacklightNow=(WORD)((u16WeightAvg_Cur-u8WeightAvg_Min)*(u8Backlight_Max-u8Backlight_Min)/(u8WeightAvg_Max-u8WeightAvg_Min))+u8Backlight_Min;

#if DEBUG_DCR
	if(u8BacklightPrev != u8BacklightNow)
	{
	        printData("\r\n u16WeightAvgNow'=%x",u16WeightAvg_Cur);
	        printData("u8BacklightNow=%x",u8BacklightNow);
	}
#endif

    if (u8BacklightNow > (u8BacklightPrev))
        u8BacklightNow = u8BacklightPrev + u8UpdateStep;
    else if ((u8BacklightNow) < u8BacklightPrev)
        u8BacklightNow = u8BacklightPrev - u8UpdateStep;

}

void msAPIDCR_Handler(void)
{
	msAPIBL_Handler();
	//msMultiWinData_Handler();
	msDCR_Handler();
}

void msDCRHandler(void)
{
    msAPIDCR_Handler();
    return;
    DWORD xdata TotalPixelCount;
    WORD xdata AveLumi , AveLumi2;

    if(!UserPrefDcrMode)
        return;

    if(!STATISTIC_ACKNOWLEDGE())//(!(old_msReadByte(SC7_B8)&BIT3)) // histogram is not ready
        return;

    if( ReadFrameDataCnt % 2 == 0 ) // get all display data
    {
        BYTE tempVal;

        if(( tempVal = Y_CHANNEL_MAX_PIXEL() ) > BrightData )//(( tempVal = old_msReadByte( SC7_3A ) ) > BrightData ) // get max bright data
            BrightData = tempVal;
        if(( tempVal = Y_CHANNEL_MIN_PIXEL() ) < DarkData )//(( tempVal = old_msReadByte( SC7_39 ) ) < DarkData ) // get min dark data
            DarkData = tempVal;
        if( abs( BrightData - DarkData ) <= BlackWhiteDifference )
        {
            if( abs( DarkData - DarkestValue ) <= DarkestRange ) // all display data are dark
            {
                SetDarkestFlag = 1;
            }
        }

        TotalPixelCount = TOTAL_PIXEL_COUNT();
        AveLumi = TOTAL_PIXEL_WEIGHT();//old_msRead2Byte(SC7_36);  //weight
        AveLumi = AVERAGE_LUMINANCE(AveLumi, TotalPixelCount);//((((DWORD)AveLumi)*16384 +(u16HistogramHR>>1))/u16HistogramHR +(u16HistogramVR>>1))/ u16HistogramVR; //average
        AveLumi = (( DWORD )PreAveLumi + AveLumi ) / 2;

        AveLumi2 = TOTAL_PIXEL_WEIGHT();//old_msRead2Byte(SC7_36);  //weight
        AveLumi2 = AVERAGE_LUMINANCE(AveLumi2, TotalPixelCount);//((((DWORD)AveLumi2)*16384 +(u16HistogramHR>>1))/u16HistogramHR +(u16HistogramVR>>1))/ u16HistogramVR; //average
        AveLumi2 = (( DWORD )PreAveLumi + AveLumi2 ) / 2;

        if( abs( AveLumi2 - AveLumi ) > 10 ) // read twice to confirm? (not stable)
        {
            ReadFrameDataCnt ++;
            STATISTIC_REQUEST_EN(0);//old_msWriteByteMask(SC7_B8, 0, BIT2);
            STATISTIC_REQUEST_EN(1);//old_msWriteByteMask(SC7_B8, BIT2, BIT2);
            return;
        }

        BackLightTargetValue = (AveLumi > 0x100)?(0xff):((BYTE)AveLumi);

        if( abs( BackLightTargetValue - BacklightPrev ) >= DCRStep )
        {
            bDCRSmoothMotionFlag = 1;
            DCRStepTransValue = DCRStep / 2; //abs(BackLightTargetValue-BacklightPrev)/DCRStep;
        }
        else
        {
            bDCRSmoothMotionFlag = 0;
        }

        if( bDCRSmoothMotionFlag ) // DCR operating range is over DCRStep
        {
            if( BackLightTargetValue >= BacklightPrev ) // increasement
            {
                BacklightNow = ( BacklightNow + DCRStepTransValue >= BackLightTargetValue ) ? ( BackLightTargetValue ) : ( BacklightNow + DCRStepTransValue );
            }
            else // decreasement
            {
                BacklightNow = ( BacklightNow - DCRStepTransValue <= BackLightTargetValue ) ? ( BackLightTargetValue ) : ( BacklightNow - DCRStepTransValue );
            }
        }
        else
        {
            BacklightNow = BackLightTargetValue;
        }

#if DCRMotionTest
        if( !u8DCRStepTransCnt )
#endif
            if(( BacklightNow != BacklightPrev ) || ( BrightData != PreBrightData ) )
            {
                BacklightPrev = BacklightNow;
                PreBrightData = BrightData;
                mStar_AdjustDcrBrightness();
#if DCRMotionTest
                u8DCRStepTransCnt = DCRStepTransPeriod;
#endif
        }
        HistogramPrev = HistogramNow;
    }
    else // get upper dark / bright data
    {
        DarkData = Y_CHANNEL_MIN_PIXEL();//old_msReadByte( SC7_39 );
        BrightData = Y_CHANNEL_MAX_PIXEL();//old_msReadByte( SC7_3A );

        TotalPixelCount = TOTAL_PIXEL_COUNT();
        AveLumi = TOTAL_PIXEL_WEIGHT();//old_msRead2Byte(SC7_36);  //weight
        PreAveLumi = AVERAGE_LUMINANCE(AveLumi, TotalPixelCount);//((((DWORD)AveLumi)*16384 +(u16HistogramHR>>1))/u16HistogramHR +(u16HistogramVR>>1))/ u16HistogramVR; //average
        AveLumi = TOTAL_PIXEL_WEIGHT();//old_msRead2Byte(SC7_36);  //weight
        PreAveLumi2 = AVERAGE_LUMINANCE(AveLumi, TotalPixelCount);//((((DWORD)AveLumi)*16384 +(u16HistogramHR>>1))/u16HistogramHR +(u16HistogramVR>>1))/ u16HistogramVR; //average
    }

    ReadFrameDataCnt ++;

    STATISTIC_REQUEST_EN(0);//old_msWriteByteMask(SC7_B8, 0, BIT2);
    STATISTIC_REQUEST_EN(1);//old_msWriteByteMask(SC7_B8, BIT2, BIT2);

}
#endif

