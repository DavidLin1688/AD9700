#include "board.h"
#include "Global.h"
#include "Ms_rwreg.h"
#include "Gamma.h"
#include "drv3DLUT_C.h"
#include "COLOR_VERIFY.H"

#if ENABLE_DEBUG && COLORVERIFY_DEBUG
#if CHIP_ID==CHIP_TSUMC || CHIP_ID==CHIP_TSUMD|| CHIP_ID==CHIP_TSUMJ
code RegUnitType tb_FCC_TABLE[] =
{
/*
    {SC7_80, 0x64},     //target 1 cb, 100,     Red
    {SC7_81, 0xd4}, //target 1 cr, 212,     Red
    {SC7_82, 0x48},     //target 2 cb, 72,  Green
    {SC7_83, 0x3a},     //target 2 cr, 58,  Green
    {SC7_84, 0xd4},     //target 3 cb, 212,     Blue
    {SC7_85, 0x72},     //target 3 cr, 114,     Blue
    {SC7_86, 0x9c}, //target 4 cb, 156,     Cyan
    {SC7_87, 0x2c},     //target 4 cr, 44,  Cyan
    {SC7_88, 0xb8},     //target 5 cb, 184,     Magenta
    {SC7_89, 0xc6},     //target 5 cr, 198,     Magenta
    {SC7_8A, 0x2c},     //target 6 cb, 44,  Yellow
    {SC7_8B, 0x8e},     //target 6 cr, 142,     Yellow
    {SC7_8C, 0x80},     //target 7 cb, 128,     White
    {SC7_8D, 0x80},     //target 7 cr, 128,     White
    {SC7_8E, 0x80},     //target 8 cb, 128,     Black
    {SC7_8F, 0x80}, //target 8 cr, 128,     Black
    {SC7_92, 0xff}, //target 1 boundary, [7:6] cb_u, [5:4] cb_d, [3:2] cr_u, [1:0] cr_d
    {SC7_93, 0xff}, //target 2 boundary, [7:6] cb_u, [5:4] cb_d, [3:2] cr_u, [1:0] cr_d
    {SC7_94, 0xff}, //target 3 boundary, [7:6] cb_u, [5:4] cb_d, [3:2] cr_u, [1:0] cr_d
    {SC7_95, 0xff}, //target 4 boundary, [7:6] cb_u, [5:4] cb_d, [3:2] cr_u, [1:0] cr_d
    {SC7_96, 0xff}, //target 5 boundary, [7:6] cb_u, [5:4] cb_d, [3:2] cr_u, [1:0] cr_d
    {SC7_97, 0xff}, //target 6 boundary, [7:6] cb_u, [5:4] cb_d, [3:2] cr_u, [1:0] cr_d
    {SC7_98, 0xff}, //target 7 boundary, [7:6] cb_u, [5:4] cb_d, [3:2] cr_u, [1:0] cr_d
    {SC7_99, 0xff}, //target 8 boundary, [7:6] cb_u, [5:4] cb_d, [3:2] cr_u, [1:0] cr_d
    {SC7_9A, 0xff}, //target 9 boundary, [5:3] cb_ud, [2:0] cr_ud,

    {SC7_9B, 0xff}, //target 1 gain, [7:4], equal 15/16             //target 2 gain, [3:0], equal 15/16
    {SC7_9C, 0xff}, //target 3 gain, [7:4], equal 15/16         //target 4 gain, [3:0], equal 15/16
    {SC7_9D, 0xff}, //target 5 gain, [7:4], equal 15/16         //target 6 gain, [3:0], equal 15/16
    {SC7_9E, 0xff}, //target 7 gain, [7:4], equal 15/16         //target 8 gain, [3:0], equal 15/16

    {SC7_90,0xff},  //target 0~9 enable, [0] for target 1 and 2, [1:7] for target 2~9

    {SC0_00, 0x00},
    */
};
#endif

//>>===========================================

void msFCCLoader(void)
{
    xdata BYTE  /*ucBank,*/ucTmp;

    //ucBank = old_msReadByte(SC0_00);
#if CHIP_ID==CHIP_TSUMC||CHIP_ID==CHIP_TSUMD|| CHIP_ID==CHIP_TSUMJ
    //old_msWriteByteMask(SCB_A0, BIT4|BIT0   , BIT4|BIT0);
#endif
    for(ucTmp = 0; ucTmp < sizeof( tb_FCC_TABLE ) / sizeof( RegUnitType ); ucTmp++ )
        old_msWriteByte( tb_FCC_TABLE[ucTmp].u16Reg, tb_FCC_TABLE[ucTmp].u8Value );

    //old_msWriteByte(SC0_00, ucBank);

}
//<<===========================================================
//>>===============msHistrogram_Test=============================
void msHistrogram_Test(BYTE bWindow)
{
    xdata BYTE  /*ucBank,*/ucTmp;
    xdata WORD  uwArray32[32];                                  /*use to Story Histrogram32's DLC data*/

    xdata WORD  h_start =   0,  v_start =   0;
    xdata WORD  h_end   = g_sPnlInfo.sPnlTiming.u16Width,  v_end   = g_sPnlInfo.sPnlTiming.u16Height;
    //xdata DWORD Total_Count,Total_Weight;                   /*use to Story Temp.Histrogram DLC data */
    xdata DWORD Total_Weight;                   /*use to Story Temp.Histrogram DLC data */

    //PanelWidth
    //ucBank = old_msReadByte(SC0_00);

    //old_msWriteByteMask(SC7_3B,0x00,_BIT6);                     //RGB mode enable

    //old_msWriteByteMask(SC7_B8,_BIT4,_BIT4);                    //New Y' histogram option enable. 0: Histogram in Y. 1: Histogram in Y'.
    //old_msWriteByteMask(SC7_B5,_BIT1,_BIT1);                //Histogram accelerate mode ON
    //old_msWriteByteMask(SC7_B8, 0, (BIT3|BIT2) );               //clear hand shaking
    if( MAIN_WINDOW == bWindow )
        //old_msWriteByteMask( SC7_B8, BIT1, BIT1|BIT0);              //Main Histrogram window enable
    else
        //old_msWriteByteMask( SC7_B8, BIT0, BIT1|BIT0);              //Sub Histrogram window enable

//>>--------------------Range-------------------------------------------------------
    #if 1 //V range doesnt change , but H range is moved to SC7
    //old_msWriteByte( SC3_B6, v_start/8 );                           // set statistic start range (unit: 8 vertical lines)
    //old_msWriteByte( SC3_B7, v_end  /8 );                            // set statistic end range (uint: 8 vertical lines)
    //old_msWriteByteMask( SC3_B5, BIT0, BIT0 );                      // set statistic vertical range is valid

    //old_msWrite2Byte( SC7_24, h_start);             // set statistic start range (unit: 1 pixel)
    //old_msWrite2Byte( SC7_26, h_end );                          // set statistic start range (unit: 1 pixel)
    //old_msWriteByteMask( SC7_27, (MAIN_WINDOW==bWindow)?(BIT7):(BIT6), BIT7|BIT6 );                 // 1 for set manual H range setting enable in Main window

    //printData("V_Start_(SC3_B6)==[%d]\n\r",old_msReadByte(SC3_B6)*8);
    //printData("V_End_(SC3_B7)==[%d]\n\r",old_msReadByte(SC3_B7)*8);
    printData("H_Start_(SC7_2524)==[%d]\n\r",h_start);
    printData("H_End_(SC7_2726)==[%d]\n\r",h_end);
    #endif
//<<-----------------------------------------------------------------------------------
//>>--------------------Enable Histogram Report----------------
    //old_msWriteByteMask( SC7_B8, ((MAIN_WINDOW==bWindow)?(BIT1):(BIT0))|BIT2, BIT2|BIT1|BIT0 );                 // 1 for set manual H range setting enable in Main window
//<<-----------------------------------------------------------------------------------
//>>--------------------32 Section Histogram report----------------
    //while(!(old_msReadByte(SC7_B8) & _BIT3))  /*SC7_B8[3] HS_REQ:Hand Shaking Acknowledge (Read only) */
    //{
    //}
    printData("111111.(total)==[%x]\n\r",(g_sPnlInfo.sPnlTiming.u16Width/64*g_sPnlInfo.sPnlTiming.u16Height));
    printData("111111.(Weight)==[%x]\n\r",(g_sPnlInfo.sPnlTiming.u16Width/64*g_sPnlInfo.sPnlTiming.u16Height*256));
    for (ucTmp = 0; ucTmp < 32; ucTmp++)
    {
        //uwArray32[ucTmp] = ((WORD) old_msRead2Byte(SC8_C0+ucTmp*2));
        //printData("ADD[]==[%x]\n\r",(SC8_C0+ucTmp*2));

        printData("uwArray32[]==[%x]\n\r",uwArray32[ucTmp]);
    }

//<<-----------------------------------------------------------------------------------
//>>--------------------Total Weight and Count , Min. and Maximum report----------------
    //Total_Count=old_msRead2Byte(SC7_34); //removed in Russell
    //Total_Weight=old_msRead2Byte(SC7_36);
    //printData("222222.minimum pixel value ==[%x]\n\r",old_msReadByte(SC7_39));
    //printData("222222.maximum pixel value ==[%x]\n\r",old_msReadByte(SC7_3A));

    //printData("222222.Sum of pixel count==[%x]\n\r",Total_Count);
    printData("222222.Sum of total weight.==[%x]\n\r",Total_Weight);
//<<-----------------------------------------------------------------------------------
//old_msWriteByte(SC0_00, ucBank);

}
//<<===========================================================
//>>===============Linear Gamma Start=============================
#if Enable_Gamma
void msLinearGammaLoader(void)
{
    //BYTE xdata ucBank;
    BYTE xdata ucTgtChannel;
    WORD xdata uwData = 0;
    WORD xdata i;
    //ucBank = old_scReadByte( SC0_00);
    //old_msWrite2Byte( SC8_20, 0 );

    for( ucTgtChannel = 0; ucTgtChannel < 3; ucTgtChannel++ )
    {
        //old_msWriteByteMask( SC8_22, 0x03,BIT1|BIT0);// Burst write enable
        //old_msWriteByteMask( SC8_22, (ucTgtChannel<<2) , BIT3 | BIT2 ); //Select R/G/B Channel
        for( i = 0; i < 256; ++ i )
        {
            uwData = i<<2; // 10 bit data
            //old_msWrite2Byte( SC8_24, uwData );
        }
        //old_msWriteByteMask( SC8_22, 0, BIT1 | BIT0 );
    }
    //old_msWriteByte( SC0_00, ucBank );
}
//<<===========================================================
//>>===============DeGamma Start=============================
BYTE code DeGammaTbl[] =
{
     0x00,0x0F,0x1E,0x2C,0x3B,0x4A,0x59,0x67
    ,0x76,0x85,0x94,0xA2,0xB1,0xC0,0xCE,0xDD
    ,0x76,0x7D,0x84,0x8B,0x92,0x99,0xA0,0xA7
    ,0xAE,0xB4,0xBB,0xC2,0xC9,0xCF,0xD6,0xDC
    ,0x72,0x75,0x78,0x7B,0x7E,0x82,0x85,0x88
    ,0x8B,0x8E,0x91,0x94,0x97,0x9A,0x9D,0x9F
    ,0xA2,0xA5,0xA8,0xAB,0xAD,0xB0,0xB3,0xB5
    ,0xB8,0xBB,0xBD,0xC0,0xC2,0xC5,0xC7,0xCA
    ,0x4C,0x4E,0x51,0x53,0x55,0x58,0x5A,0x5C
    ,0x5E,0x60,0x63,0x65,0x67,0x69,0x6B,0x6D
    ,0x6F,0x70,0x72,0x74,0x76,0x78,0x79,0x7B
    ,0x7D,0x7E,0x80,0x82,0x83,0x85,0x86,0x88
    ,0x89,0x8A,0x8C,0x8D,0x8E,0x90,0x91,0x92
    ,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A
    ,0x9B,0x9C,0x9D,0x9E,0x9E,0x9F,0xA0,0xA0
    ,0xA1,0xA1,0xA2,0xA2,0xA3,0xA3,0xA4,0xA4
    ,0xA4,0xA4,0xA5,0xA5,0xA5,0xA5,0xA5,0xA5
    ,0xA5,0xA5,0xA5,0xA5,0xA5,0xA5,0xA4,0xA4
    ,0xA4,0xA4,0xA3,0xA3,0xA2,0xA2,0xA1,0xA1
    ,0xA0,0x9F,0x9F,0x9E,0x9D,0x9C,0x9C,0x9B
    ,0x9A,0x99,0x98,0x97,0x96,0x95,0x93,0x92
    ,0x91,0x90,0x8E,0x8D,0x8C,0x8A,0x89,0x87
    ,0x86,0x84,0x82,0x81,0x7F,0x7D,0x7B,0x79
    ,0x77,0x76,0x74,0x72,0x6F,0x6D,0x6B,0x69
    ,0x67,0x64,0x62,0x60,0x5D,0x5B,0x58,0x56
    ,0x53,0x51,0x4E,0x4B,0x48,0x46,0x43,0x40
    ,0x3D,0xBA,0xB7,0xB4,0xB1,0xAE,0xAA,0xA7
    ,0xA4,0xA1,0x9D,0x9A,0x96,0x93,0x8F,0x8C
    ,0x88,0x84,0x81,0x7D,0x79,0x75,0x71,0x6D
    ,0x69,0x65,0x61,0x5D,0x59,0x55,0x50,0x4C
    ,0x48,0x43,0x3F,0x3A,0x36,0x31,0x2C,0x28
    ,0x23,0x1E,0x19,0x14,0x0F,0x0A,0x05,0x00
};

void msLinearDeGammaLoader(void)
{
    //BYTE xdata ucBank;
    BYTE xdata ucTgtChannel;
    WORD xdata uwData = 0;
    WORD xdata i;
    //ucBank = old_scReadByte( SC0_00);
    //old_msWrite2Byte( SCE_C0, 0 );
    //old_msWriteByteMask( SCE_02, BIT0, BIT0 );//DE-Gamma enable

    for( ucTgtChannel = 0; ucTgtChannel < 3; ucTgtChannel++ )
    {
        //old_msWriteByteMask( SCE_C2, 0x03,BIT1|BIT0);// Burst write enable
        //old_msWriteByteMask( SCE_C2, (ucTgtChannel<<2) , BIT3 | BIT2 ); //Select R/G/B Channel
        for( i = 0; i < 256; ++ i )
        {
            uwData =( i<<4); // 15 bit data
            printData("DeGamma Data==[%x]\n\r",i<<4);

            //old_msWrite2Byte( SCE_C4, uwData );
            //old_msWrite2Byte(SCE_C4, DeGammaTbl[i]);
            printData("DeGamma Data==[%x]\n\r",uwData);

        }
        //old_msWriteByteMask( SCE_C2, 0, BIT1 | BIT0 );
    }
    //old_msWriteByteMask( SCE_02, BIT0, BIT0 );
    //old_msWriteByte( SC0_00, ucBank );
}

void msLinearFixGammaLoader(void)
{
    //BYTE xdata ucBank;
    BYTE xdata ucTgtChannel;
    WORD xdata uwData = 0;
    WORD xdata i;
    //ucBank = old_scReadByte( SC0_00);
    //old_msWriteByte( SCE_E0, 0 );
    //old_msWriteByteMask( SCE_02, BIT2, BIT2 ); //Fixed Gamma enable

    for( ucTgtChannel = 0; ucTgtChannel < 3; ucTgtChannel++ )
    {
        //old_msWriteByteMask( SCE_E2, 0x03,BIT1|BIT0);// Burst write enable
        //old_msWriteByteMask( SCE_E2, (ucTgtChannel<<2) , BIT3 | BIT2 ); //Select R/G/B Channel
        for( i = 0; i < 256; ++ i )
        {
            uwData = i<<2; // 10 bit data
            //old_msWrite2Byte( SCE_E4, uwData );
            //old_msWrite2Byte(SCE_E4, DeGammaTbl[i]);
            printData("FixGamma Data==[%x]\n\r",uwData);

        }
        //old_msWriteByteMask( SCE_E2, 0, BIT1 | BIT0 );
    }
    //old_msWriteByteMask( SCE_02, BIT2, BIT2 );
    //old_msWriteByte( SC0_00, ucBank );
}
#endif

void ms2DHPeakingTest(BYTE bScalerWin ,BYTE ucSharpness, BYTE ucStep )
{
#define NO_CHANGE_STEP      0x80
#define NO_CHANGE_SHARPNESS 0xFF


    BYTE xdata uci = 0;

    //Over/Under shoort Setting  //main and sub use the same setting
    for( uci = 0; uci < 8; uci ++ )
    {
         //old_msWriteByteMask(SCB_40+uci, 0x00,0xFF);        //overshoort：SCB_40~SCB_47
         //old_msWriteByteMask(SCB_48+uci, 0xFF,0xFF);        //undershoort：SCB_48~SCB_4F
    }
    if(bScalerWin == MAIN_WINDOW)
    {
        //>>----main win H peaking initial------------------
        //Enable
        //old_msWriteByteMask( SCB_20, BIT0   , BIT0 );   //main post peaking enable
        //old_msWriteByteMask( SCB_21, 0xFF   , 0xFF );   //main Bank1~8 peaking enable
        //Term Setting
        #if 0
        old_msWrite2ByteMask( SCB_38, 0x0123    , 0x7777 ); //main win peaking term1~4 select
        old_msWrite2ByteMask( SCB_3A, 0x0123    , 0x7777 ); //main win peaking term5~8 select
        old_msWrite2ByteMask( SCB_3C, 0x4567    , 0x7777 ); //main win peaking term9~12 select
        old_msWrite2ByteMask( SCB_3E, 0x4567    , 0x7777 ); //main win peaking term13~16 select
        #else
        for( uci = 0; uci < 4; uci ++ )
        {   //Term Setting for main win
             //old_msWriteByteMask(SCB_38+uci*2   , (uci*2<<4)|(uci*2+1)  ,0x77);
             //old_msWriteByteMask(SCB_38+uci*2+1, (uci*2<<4)|(uci*2+1) ,0x77);
        }
        #endif

        //Post Coring Setting
        //old_msWriteByteMask( SCB_26, 0x42   , 0xFF );           //[7:4]:Coring_TH_2 ,[3:0]:Coring_TH_1
        for( uci = 0; uci < 8; uci ++ )
        {
             //old_msWriteByteMask(SCB_30+uci, 0x20,0x3F);        //main win band 1~8 peaking coef
        }
        //<<--------------------------
        if( NO_CHANGE_SHARPNESS == ucSharpness )
            ucSharpness = 0;//old_msReadByte(SCB_27)&0x3F;    // MAIN window user sharpness adjust
        else
            ucSharpness&=0x3F;

        //old_msWriteByte(SCB_27,  ucSharpness);
        //printData("111 ucSharpness===%x",old_msReadByte(SCB_27));

        if( NO_CHANGE_STEP == ucStep )
            ucStep = 0;//(old_msReadByte(SCB_22)&0x03);                 // MAIN window peaking step
        else
            ucStep&=0x03;

        printData("111 ucStep===%x",ucStep);
        //old_msWriteByte(SCB_22,  (ucStep<<6 |ucStep<<4|ucStep<<2|ucStep));  //for band1~4
        //old_msWriteByte(SCB_23,  (ucStep<<6 |ucStep<<4|ucStep<<2|ucStep));  //for band5~8
        //printData("111 ucStep===%x",old_msReadByte(SCB_22));
    }
    else
    {

        //>>----sub win H peaking initial------------------
        //Enable
        //old_msWriteByteMask( SCB_28, BIT0   , BIT0 );   //sub post peaking enable
        //old_msWriteByteMask( SCB_29, 0xFF   , 0xFF );   //sub Bank1~8 peaking enable
        //Term Setting
        #if 0
        old_msWrite2ByteMask( SCB_58, 0x0123    , 0x7777 ); //main win peaking term1~4 select
        old_msWrite2ByteMask( SCB_5A, 0x0123    , 0x7777 ); //main win peaking term5~8 select
        old_msWrite2ByteMask( SCB_5C, 0x4567    , 0x7777 ); //main win peaking term9~12 select
        old_msWrite2ByteMask( SCB_5E, 0x4567    , 0x7777 ); //main win peaking term13~16 select
        #else
        for( uci = 0; uci < 4; uci ++ )
        {
             //old_msWriteByteMask(SCB_58+uci*2   , (uci*2<<4)|(uci*2+1)  ,0x77);
             //old_msWriteByteMask(SCB_59+uci*2+1, (uci*2<<4)|(uci*2+1) ,0x77);
        }
        #endif
        //Post Coring Setting
        //old_msWriteByteMask( SCB_2E, 0x42   , 0xFF );           //[7:4]:Coring_TH_2 ,[3:0]:Coring_TH_1
        for( uci = 0; uci < 8; uci ++ )
        {
             //old_msWriteByteMask(SCB_50+uci, 0x20,0x3F);        //sub win band 1~8 peaking coef
        }

        //<<--------------------------
        if( NO_CHANGE_SHARPNESS == ucSharpness )
            ucSharpness = 0;//old_msReadByte(SCB_2F)&0x3F;    // MWE window user sharpness adjust
        else
            ucSharpness&=0x3F;
        //old_msWriteByte(SCB_2F,  ucSharpness);

        if( NO_CHANGE_STEP == ucStep )
            ucStep = 0;//(old_msReadByte(SCB_2A)&0x03);                 // MWE window peaking step
        else
            ucStep&=0x03;

        printData("222 ucStep===%x",ucStep);
        //old_msWriteByte(SCB_2A,  (ucStep<<6 |ucStep<<4|ucStep<<2|ucStep));  //for band1~4
        //old_msWriteByte(SCB_2B,  (ucStep<<6 |ucStep<<4|ucStep<<2|ucStep));  //for band5~8
        //printData("222 SCB_2B===%x",old_msReadByte(SCB_2B));
    }
    //old_msWriteByte(SC0_00, ucBank);
}

void msNoiseMasking(BYTE bScalerWin ,BYTE u8Strength, BYTE u8THRD )
{
	//Command1(BIT0:Main/Sub win, BIT1:NM enable, BIT2:LowY enable, BIT3:STD enable)
	//Command2: NM gain coef
	//Command3:THRD
	//EX:normal mode: 49 03 3f ff (main win,NM enable gain=0x3F)
	//EX:Low Y mode:  49 07 3f 20 (main win,NM enable ,LowY mode enable, gain=0x3F/2 and LowY's gain=0x3F,THRD=0x20)

	//1.Normal mode
	if(_bit0_(bScalerWin))
	{
		printData("111.Main window (bScalerWin&BIT0)==>%x",(bScalerWin&BIT0));

		//H direction Noise masking
		//old_msWriteByteMask(SCB_C0, (_bit1_(bScalerWin)?(BIT7):(0x00))		,BIT7);  	// Y noise-masking enable
		//old_msWriteByteMask(SCB_C0, (_bit2_(bScalerWin)?((u8Strength<=0x3F? u8Strength/2:0x3F/2)):((u8Strength<=0x3F? u8Strength:0x3F))) 	,0x3F);  	//BIT5~BIT0:4.2 format
		//old_msWriteByteMask(SCB_C2, 0xFF 	,0xFF); 									//Max/Min value threshold
		//old_msWriteByteMask(SCB_C1, (_bit1_(bScalerWin)?(BIT7):(0x00))		,BIT7);  	//C noise-masking enable
		//old_msWriteByteMask(SCB_C1, (_bit2_(bScalerWin)?((u8Strength<=0x3F? u8Strength/2:0x3F/2)):((u8Strength<=0x3F? u8Strength:0x3F))) 	,0x3F);  	//BIT5~BIT0:4.2 format
		//old_msWriteByteMask(SCB_C3, 0xFF 	,0xFF); 									//Max/Min value threshold
		//V direction Noise masking
		//old_msWriteByteMask(SCB_24, (_bit1_(bScalerWin)?(BIT7):(0x00))			,BIT7);  	// Y noise-masking enable
		//old_msWriteByteMask(SCB_24, (_bit2_(bScalerWin)?((u8Strength<=0x3F? u8Strength/2:0x3F/2)):((u8Strength<=0x3F? u8Strength:0x3F))) 	,0x3F);  	//BIT5~BIT0:4.2 format
		//old_msWriteByteMask(SCB_72, 0xFF 	,0xFF); 									//Max/Min value threshold
		if (_bit1_(bScalerWin))
			printMsg("111.Enable NM");
		else
			printMsg("111. disable NM");
		//2.LOW Y mode
		{
			//H direction:
 			//Y
			{
				if (_bit2_(bScalerWin))
					printMsg("111. Enable Low Y mode");
				else
					printMsg("111. disable Low Y mode");

				//old_msWriteByteMask(SCB_E0, (_bit2_(bScalerWin)?(BIT0):(0x00))	,BIT0); 		//reg_main_nm_low_y_en
				//old_msWriteByteMask(SCB_E2, u8THRD	,0xFF);								//reg_main_nm_low_y_th
				//old_msWriteByteMask(SCB_E4, (u8Strength<=0x3F? u8Strength:0x3F),0x3F);		//reg_main_nm_low_y_gain
				//old_msWriteByteMask(SCB_E5, (0x00),BIT1|BIT0); 								//reg_main_nm_low_y_step
				//printData("111.SCB_E0==%x",old_msReadByte(SCB_E0));
				//C
				//old_msWriteByteMask(SCB_EA, (_bit2_(bScalerWin)?(BIT0):(0x00))	,BIT0); 		//reg_main_nm_low_y_en
				//old_msWriteByteMask(SCB_EC, u8THRD	,0xFF);								//reg_main_nm_low_y_th
				//old_msWriteByteMask(SCB_EE, (u8Strength<=0x3F? u8Strength:0x3F),0x3F);		//reg_main_nm_low_y_gain
				//old_msWriteByteMask(SCB_EF, (0x00)	,BIT1|BIT0); 								//reg_main_nm_low_y_step
				//printData("111.SCB_EA==%x",old_msReadByte(SCB_EA));
				//V direction:
				//old_msWriteByteMask(SCB_F4,(_bit2_(bScalerWin)?(BIT0):(0x00))		,BIT0); 		//reg_main_v_nm_low_y_en
				//old_msWriteByteMask(SCB_F6, u8THRD	,0xFF);								//reg_main_v_nm_low_y_th
				//old_msWriteByteMask(SCB_E8, (u8Strength<=0x3F? u8Strength:0x3F),0x3F);		//reg_main_v_nm_low_y_gain
				//old_msWriteByteMask(SCB_E9, (0x00),BIT1|BIT0); 								//reg_main_v_nm_low_y_step
				//printData("111.SCB_F4==%x",old_msReadByte(SCB_F4));
			}
		}
		#if CHIP_ID==CHIP_TSUMD
		//3.STD mode
		{
			if (_bit3_(bScalerWin))
				printMsg("111. Enable STD mode");
			else
				printMsg("111. Disable STD mode");
			//H direction
			//old_msWriteByteMask(SCB_E0, (_bit3_(bScalerWin)?(BIT1):(0x00))	,BIT1); 	//reg_main_nm_low_y_en
			//old_msWriteByteMask(SCB_E1, (0x00),BIT1|BIT0); 								//reg_main_nm_std_step
			//old_msWriteByteMask(SCB_E3, u8THRD,0xFF); 								//reg_main_nm_std_th
			//V direction
			//old_msWriteByteMask(SCB_F4, (_bit3_(bScalerWin)?(BIT1):(0x00))	,BIT1); 		//reg_main_v_nm_std_en
			//old_msWriteByteMask(SCB_F5, (0x00),BIT1|BIT0); 								//reg_main_v_nm_std_step
		}
		#endif
	}
	else
	{

		printMsg("222.Sub window");
		//H direction Noise masking
		/*
		old_msWriteByteMask(SCB_C8, (_bit1_(bScalerWin)?(BIT7):(0x00))		,BIT7);  	// Y noise-masking enable
		old_msWriteByteMask(SCB_C8, (_bit2_(bScalerWin)?((u8Strength<=0x3F? u8Strength/2:0x3F/2)):((u8Strength<=0x3F? u8Strength:0x3F))) 	,0x3F);  	//BIT5~BIT0:4.2 format
		old_msWriteByteMask(SCB_CA, 0xFF 	,0xFF); 			//Max/Min value threshold
		old_msWriteByteMask(SCB_C9, (_bit1_(bScalerWin)?(BIT7):(0x00))		,BIT7);  	//C noise-masking enable
		old_msWriteByteMask(SCB_C9, (_bit2_(bScalerWin)?((u8Strength<=0x3F? u8Strength/2:0x3F/2)):((u8Strength<=0x3F? u8Strength:0x3F))) 	,0x3F);  	//BIT5~BIT0:4.2 format
		old_msWriteByteMask(SCB_CB, 0xFF 	,0xFF); 			//Max/Min value threshold
		//V direction Noise masking
		old_msWriteByteMask(SCB_2C, (_bit1_(bScalerWin)?(BIT7):(0x00))		,BIT7);  	// Y noise-masking enable
		old_msWriteByteMask(SCB_2C, (_bit2_(bScalerWin)?((u8Strength<=0x3F? u8Strength/2:0x3F/2)):((u8Strength<=0x3F? u8Strength:0x3F))) 	,0x3F);  	//BIT5~BIT0:4.2 format
		old_msWriteByteMask(SCB_73, 0xFF 	,0xFF); 			//Max/Min value threshold
		*/
		if (_bit1_(bScalerWin))
			printMsg("222. Enable NM");
		else
			printMsg("222. Disable NM");

		//2.LOW Y mode
		{
			//Y
			{
				if (_bit2_(bScalerWin))
					printMsg("222. Enable LowY mode");
				else
					printMsg("222. Disable LowY mode");
				/*
				old_msWriteByteMask(SCB_E0, (_bit2_(bScalerWin)?(BIT4):(0x00))	,BIT4); 		//reg_sub_nm_low_y_en
				old_msWriteByteMask(SCB_E6, u8THRD	,0xFF);								//reg_sub_nm_low_y_th
				old_msWriteByteMask(SCB_E8, (u8Strength<=0x3F? u8Strength:0x3F),0x3F);		//reg_sub_nm_low_y_gain
				old_msWriteByteMask(SCB_E9, (0x00)	,BIT1|BIT0); 								//reg_sub_nm_low_y_step
				printData("2222.SCB_E0==%x",old_msReadByte(SCB_E0));
				//C
				old_msWriteByteMask(SCB_EA,(_bit2_(bScalerWin)?(BIT4):(0x00))	,BIT4); 		//reg_sub_nm_low_c_en
				old_msWriteByteMask(SCB_F0, u8THRD	,0xFF);								//reg_sub_nm_low_c_th
				old_msWriteByteMask(SCB_F2, (u8Strength<=0x3F? u8Strength:0x3F),0x3F);		//reg_sub_nm_low_c_gain
				old_msWriteByteMask(SCB_F3, (0x00)	,BIT1|BIT0); 								//reg_sub_nm_low_c_step
				printData("2222.SCB_EA==%x",old_msReadByte(SCB_EA));
				//V direction:
				old_msWriteByteMask(SCB_F4, (_bit2_(bScalerWin)?(BIT4):(0x00))	,BIT4); 		//reg_sub_v_nm_low_y_en
				old_msWriteByteMask(SCB_FA, u8THRD	,0xFF);								//reg_sub_v_nm_low_y_th
				old_msWriteByteMask(SCB_EC, (u8Strength<=0x3F? u8Strength:0x3F),0x3F);		//reg_sub_v_nm_low_y_gain
				old_msWriteByteMask(SCB_ED, (0x00)	,BIT1|BIT0); 								//reg_sub_v_nm_low_y_step
				printData("2222.SCB_F4==%x",old_msReadByte(SCB_F4));
				*/
			}
		}
		#if CHIP_ID==CHIP_TSUMD
		//3.STD mode
		{
			if (_bit3_(bScalerWin))
				printMsg("111. Enable STD mode");
			else
				printMsg("111. Disable STD mode");
			/*
			//H direction
			old_msWriteByteMask(SCB_E0, (_bit3_(bScalerWin)?(BIT5):(0x00))	,BIT5); 		//reg_sub_nm_low_y_en
			old_msWriteByteMask(SCB_E1, (0x00),BIT3|BIT2); 								//reg_sub_nm_std_step
			old_msWriteByteMask(SCB_E7, u8THRD,0xFF); 									//reg_main_nm_std_th
			//V direction
			old_msWriteByteMask(SCB_F4, (_bit3_(bScalerWin)?(BIT5):(0x00))	,BIT5); 		//reg_sub_v_nm_std_en
			old_msWriteByteMask(SCB_F5, (0x00),BIT3|BIT2); 								//reg_sub_v_nm_std_step
			*/
		}
		#endif
	}
}


#if CHIP_ID==CHIP_TSUMD
void msDeMosquito(BYTE u8Enable, BYTE u8Strength ,BYTE u8THRD)
{
/*
	1.開一張有字幕的圖，用來消除字旁邊雜訊
	2.關SPF bypass mode（SC2_70[3]=0)
	3.設定reg_spf_rgb2y_en(SC2_70[7]=1)
	4.開debug mode（SC4_10[7]=1)
	5.開deMosquito（SC4_10[0]=1)
	6.把gain設大（SC4_10[12:8]=0x1F）
	7.設定THRD1（SC4_11[7:0]值愈小愈明顯）
	8.設定THRD2（SC4_12[7:0]值愈大愈明顯）
*/
/*
    old_msWriteByteMask(SC2_E0,	0x00		,BIT3|BIT2|BIT1|BIT0);
    old_msWriteByteMask(SC2_E0,	(IsColorspaceRGB()? 0x00:BIT7)		,BIT7);

    old_msWriteByteMask(SC4_20,	BIT1			,BIT1);  //Alpha LPF enable

    old_msWriteByteMask(SC4_20,	u8Enable	,BIT7|BIT0);  //BIT0:enable ,BIT7：debug mode

    old_msWriteByteMask(SC4_21,	(u8Strength<=0x1F? u8Strength:0x1F) 	,0x1F);  //BIT12~BIT8
    old_msWriteByteMask(SC4_22,	abs(0xFF-u8THRD) 		,0xFF);  //DMS threshold 1
    old_msWriteByteMask(SC4_24,	u8THRD 		,0xFF);  //DMS threshold 2
*/

    //old_msWriteByteMask(SC4_23, BIT1|BIT0		,BIT1|BIT0);  //reg_lut_step_hor_f2
    //old_msWriteByteMask(SC4_25, BIT2|BIT1|BIT0		,BIT2|BIT1|BIT0);  //reg_lut_step_cen_f2

}

void msSpikeNR(BYTE u8Enable, BYTE u8Strength ,BYTE u8THRD)
{
/*
	開一張有雜點的圖，用來消除圖片上的雜點：
	1.關SPF bypass mode（SC2_70[3]=0)
	2.設定reg_spf_rgb2y_en(SC2_70[7]=0)
	3.關SPK_NR motion mode（SC4_50[3]=0）
	4.開SPK_NR開關（SC4_50[0]=1）
	5.設定SPK_NR強度（SC4_50[11:8]=0x0f)
	6.設定SPK_NR THRD1（SC4_51[12:8]，值愈大效果愈強）
	7.設定SPK_NR THRD0（SC4_51[7:0]，值愈大效果愈強）
	8.設定SPK_NR THRD2（SC4_52[7:0]，值愈小效果愈強）
	9.設定SPK_NR PTH1 Step（SC4_53[6:4]，值愈大效果愈強）
	10.設定SPK_NR PTH0 Step（SC4_53[2:0]，值愈大效果愈強）
	11.設定SPK_NR PTH2 Step（SC4_53[10:8]，值愈大效果愈強）
*/
/*
    old_msWriteByteMask(SC2_E0,	0x00		,BIT3|BIT2|BIT1|BIT0);
    old_msWriteByteMask(SC2_E0,	(IsColorspaceRGB()? 0x00:BIT7)		,BIT7);

    old_msWriteByteMask(SC4_A0,	u8Enable&BIT0	,BIT3|BIT0);  //BIT0:enable ,BIT3 motion mode

    old_msWriteByteMask(SC4_A1,	(u8Strength<=0x0F? u8Strength:0x0F) 	,0x0F);  //BIT11~BIT8

    old_msWriteByteMask(SC4_A2,	u8THRD 		,0xFF);  // threshold 0  BIT7~0
    old_msWriteByteMask(SC4_A3,	u8THRD&0x1F 		,0xFF);  // threshold 1  BIT12~8
    old_msWriteByteMask(SC4_A4,	abs(0xFF-u8THRD) 		,0xFF);  // threshold 2 BIT7~0
*/

    //old_msWriteByteMask(SC4_A6, BIT6|BIT5|BIT4|BIT2|BIT1|BIT0 		,BIT6|BIT5|BIT4|BIT2|BIT1|BIT0);  // STEP11 21 31
    //old_msWriteByteMask(SC4_A7, BIT2|BIT1|BIT0	,BIT2|BIT1|BIT0);  // STEP22
}

void msDeBlocking(BYTE u8Enable, /*BYTE u8Strength ,*/BYTE u8THRD)
{
/*
	畫面因為壓縮會有線的雜訊，用來消線的雜訊
	1.關SPF bypass mode（SC2_70[3:0]=0)
	2.設定reg_spf_rgb2y_en(SC2_70[7]=0)

	2.開de blocking 開關：SC2_10[0]=1
	3.開debug mode（SC2_40[7]=1)
	4.關iir mode（SC2_40[6]=0)
	5.開enable (SC2_40[0]=1)
	6.設定THRD（SC2_40[15:8]=0x00)
	7.設定STEP（SC2_40[3:2]=0~3)
*/
/*
    old_msWriteByteMask(SC2_E0,	0x00		,BIT3|BIT2|BIT1|BIT0);
    old_msWriteByteMask(SC2_E0,	(IsColorspaceRGB()? 0x00:BIT7)		,BIT7);

    old_msWriteByteMask(SC2_20,	u8Enable&BIT0	,BIT0);  //BIT0:enable
    old_msWriteByteMask(SC2_80,	u8Enable&(BIT7|BIT6|BIT0)	,BIT7|BIT6|BIT0);  //BIT7:debug mode ,BIT6: iir mode BIT0:blockiness_en_f2
    //old_msWriteByteMask(SC2_80,	BIT3|BIT2	,BIT3|BIT2);  //De-blocking coarse detect step F2

    old_msWriteByteMask(SC2_81,	u8THRD	,0xFF);  //De-blocking coarse active threshold F2
*/


}
void msSNR(BYTE u8Enable, BYTE u8Strength ,BYTE u8THRD)
{
/*
	指的是APN裡的SNR：一樣可以達到消除雜訊的功能，打糊畫面（打dot pattern試）
	1.關SPF bypass mode（SC2_70[3:0]=0)
	2.設定reg_spf_rgb2y_en(SC2_70[7]=1)

	3.開SNR開關：SC2_30[0]=1
	4.關SNR motion mode：SC2_30[1]=0
	5.設定SNR active THRD：SC2_30[15:8]=0xFF（作用？）
	6.設定SNR 強度：SC2_31[3:0]
	7.設定SNR Alpha Step：SC2_31[7:5]（作用？）
	8.設定SNR LUT：SC2_34/35/36/37為最大值（0xFFFF）
*/

    //old_msWriteByteMask(SC2_E0,	0x00		,BIT3|BIT2|BIT1|BIT0);
    //old_msWriteByteMask(SC2_E0,	/*(IsColorspaceRGB()? 0x00:BIT7)*/BIT7		,BIT7);
/*
    old_msWriteByteMask(SC2_60,	u8Enable&BIT0		,BIT1|BIT0);  //BIT0: enable   BIT1:motion mode
    old_msWriteByteMask(SC2_62,	(u8Strength<=0x0F? u8Strength:0x0F) 	,0x0F);  //BIT3~BIT0
    old_msWriteByteMask(SC2_61,	u8THRD	,0xFF);  	//SNR active threshold

    old_msWrite2ByteMask( SC2_68, 0xFFFF , 0xFFFF );
    old_msWrite2ByteMask( SC2_6A, 0xFFFF , 0xFFFF );
    old_msWrite2ByteMask( SC2_6C, 0xFFFF , 0xFFFF );
    old_msWrite2ByteMask( SC2_6E, 0xFFFF , 0xFFFF );
	*/
}

void msPreNoiseMasking(BYTE u8Enable, BYTE u8Strength ,BYTE u8THRD)
{
/*
	和noise masking一樣的作用，但該function是在scaling前（把畫面打糊）
	例如開64灰階，階與階的分界設定完後會變模糊
	1.關SPF bypass mode（SC2_70[3:0]=0)
	2.設定reg_spf_rgb2y_en(SC2_70[7]=1)

	3.關閉motion ：SC2_50[1]=0
	4.開pre-Y noise masking：SC2_50[0]=1
	5.設定Y NM Gain：SC2_54[5:0]
	6.設定Y NM max THRD：SC2_55[3:0]
	7.設定Y NM min THRD：SC2_55[7:4]

*/
    //old_msWriteByteMask(SC2_E0,	0x00		,BIT3|BIT2|BIT1|BIT0);
    //old_msWriteByteMask(SC2_E0,	/*(IsColorspaceRGB()? 0x00:BIT7)*/BIT7		,BIT7);
/*
    old_msWriteByteMask(SC2_A0,	u8Enable&BIT0		,BIT1|BIT0);  //BIT0: enable   BIT1:motion mode
    old_msWriteByteMask(SC2_A8,	(u8Strength<=0x3F? u8Strength:0x3F) 	,0x3F);  //BIT5~BIT0
    old_msWriteByteMask(SC2_AA,	u8THRD	,0xFF);  	//max/min THRD
*/
}

void msHcoring(BYTE u8Enable, BYTE u8Strength)
{
/*
	New function in Jnior
	main
	1.SCB_08[1:0]=11b		   Y Band1,2 enable
	2.SCB_08[6:4]=111b		  Step=MAX
	3.SCB_08[7]=1				   Highpass enable HPF 開關（0：coring，1：sharpness)
	sub
	4.SCB_08[9:8]=11b			Y Band1,2 enable
	5.SCB_08[14:12]=111b	  Step=MAX
	6.SCB_08[15]=1				   Highpass enable
	7.SCB_09~0C=FFFF		Gain table MAX
*/
    //old_msWriteByteMask(SCB_A0,	(IsColorspaceRGB()? 0x00:BIT4|BIT0)		,BIT4|BIT0);

	//main window
    //old_msWriteByteMask(SCB_10,	u8Enable&(BIT7|BIT1|BIT0)		,BIT7|BIT1|BIT0); //BIT1&BIT0: y_band1&band2_h_coring_en BIT7:HPF mode
    //old_msWriteByteMask(SCB_10,	BIT2		,BIT2); //dither
    //old_msWriteByteMask(SCB_10,	(u8Strength<=0x07? u8Strength:0x07)<<4 	,BIT6|BIT5|BIT4);  //BIT6~BIT4
    //old_msWrite2ByteMask( SCB_12, 0xFFFF , 0xFFFF );
    //old_msWrite2ByteMask( SCB_14, 0xFFFF , 0xFFFF );
    //old_msWrite2ByteMask( SCB_16, 0xFFFF , 0xFFFF );
    //old_msWrite2ByteMask( SCB_18, 0xFFFF , 0xFFFF );

	//sub window
    //old_msWriteByteMask(SCB_04,	u8Enable&(BIT7|BIT1|BIT0)		,BIT7|BIT1|BIT0); //reg_main_y_band1&band2_h_coring_en
    //old_msWriteByteMask(SCB_04,	BIT2		,BIT2); //dither
    //old_msWriteByteMask(SCB_04,	(u8Strength<=0x07? u8Strength:0x07)<<4 	,BIT6|BIT5|BIT4);  //BIT6~BIT4
    //old_msWrite2ByteMask( SCB_06, 0xFFFF , 0xFFFF );
    //old_msWrite2ByteMask( SCB_08, 0xFFFF , 0xFFFF );
    //old_msWrite2ByteMask( SCB_0A, 0xFFFF , 0xFFFF );
    //old_msWrite2ByteMask( SCB_0C, 0xFFFF , 0xFFFF );

}

void msShinnyColor(BYTE u8Enable, BYTE u8Strength ,BYTE u8THRD)
{
/*
	SC9_4A[11]：main開關
	SC9_4A[15:12]：main gain
	SC9_4A[10]：main Rounding

	SC9_4B[11]：main開關
	SC9_4B[15:12]：main gain
	SC9_4B[10]：main Rounding

	SC9_4C[14]： 在計算過程中gain可能會過大這個register可以用來卡overflow用的
	SC9_4C[13]： HBC gain mode（選gain的模式）
*/
    //old_msWriteByteMask(SC9_98,	u8THRD		,0xFF);  //hbc gain1 threshold
    //old_msWriteByteMask(SC9_99,	BIT6		,BIT6);  //clamp function for HBC gain

	//main window
    //old_msWriteByteMask(SC9_95,	( u8Enable > 0 ) ? ( 1<<3 ) : ( 0 )		,BIT3);  //enable
    //old_msWriteByteMask(SC9_95,	(u8Strength<=0x0F? u8Strength:0x0F)<<4 	,BIT7|BIT6|BIT5|BIT4);  //BIT7~BIT4 gain
    //old_msWriteByteMask(SC9_95,	BIT2		,BIT2);  //Rounding

	//sub window
    //old_msWriteByteMask(SC9_97,	( u8Enable > 0 ) ? ( 1<<3 ) : ( 0 )		,BIT3);  //enable
    //old_msWriteByteMask(SC9_97,	(u8Strength<=0x0F? u8Strength:0x0F)<<4 	,BIT7|BIT6|BIT5|BIT4);  //BIT7~BIT4 gain
    //old_msWriteByteMask(SC9_97,	BIT2		,BIT2);  //Rounding

}


void Peaking_PostSNR(BYTE u8Enable, BYTE u8THRD)
{
	/*   2d Peaking- Post SNR
	// Post-SNR is non motion adaptive . The user can use port-snr to reduce noise in spatial (2D) domain.
	1.Main win：
	   SCB_58[0]：Main window Gaussian SNR enable
	   SCB_58[1]：Main window Gaussian SNR adaptive factor enable
	   SCB_58[2]：Main window Gaussian SNR Mean selection :
						 0: 3x3  1: 5x5 （設1 LPF效果比較強）
	   SCB_58[5:4]：Main window Gaussian SNR LUT step
	   SCB_58[12:8]：Main window Gaussian SNR threshold
	2.Sub win：
	   SCB_59[0]：Main window Gaussian SNR enable
	   SCB_59[1]：Main window Gaussian SNR adaptive factor enable
	   SCB_59[2]：Main window Gaussian SNR Mean selection :
						 0: 3x3  1: 5x5
	   SCB_59[5:4]：Main window Gaussian SNR LUT step
	   SCB_59[12:8]：Main window Gaussian SNR threshold

	3.LUT table：（由小到大）
	   SCB_59~5F：Gaussian SNR Table 0~7
	*/

	//main window
    //old_msWriteByteMask(SCB_B0,	BIT2|BIT1	,BIT2|BIT1);  		//[2]: SNR Mean selection  [1]:adaptive factor enable
    //old_msWriteByteMask(SCB_B0,	BIT5|BIT4	,BIT5|BIT4);  		//[2]: SNR LUT step
    //old_msWriteByteMask(SCB_B0,	( u8Enable > 0 ) ? (BIT0 ) : ( 0 )		,BIT0);  //enable
    //old_msWriteByteMask(SCB_B1,	u8THRD&0x0F	,0x0F);  			//[3:0]:Gaussian SNR threshold

	//sub window
    //old_msWriteByteMask(SCB_B2,	BIT2|BIT1	,BIT2|BIT1);  		//[2]: SNR Mean selection  [1]:adaptive factor enable
    //old_msWriteByteMask(SCB_B2,	BIT5|BIT4	,BIT5|BIT4);  		//[2]: SNR LUT step
    //old_msWriteByteMask(SCB_B2,	( u8Enable > 0 ) ? (BIT0 ) : ( 0 )		,BIT0);  //enable
    //old_msWriteByteMask(SCB_B3,	u8THRD&0x0F	,0x0F);  			//[3:0]:Gaussian SNR threshold

	//LUT table
    //old_msWrite2ByteMask(SCB_B8,	0x0608	,0xFFFF);
    //old_msWrite2ByteMask(SCB_BA,	0x0204	,0xFFFF);
    //old_msWrite2ByteMask(SCB_BC,	0x0000	,0xFFFF);
    //old_msWrite2ByteMask(SCB_BE,	0x0000	,0xFFFF);
}
#endif


//<<===========================================================
//>>===========================================================

void msColor_Test_Funct(BYTE tb1, BYTE tb2)
{
    BYTE xdata uncallvalue = tb2;
    switch(tb1)
    {
        case 1:
            msHistrogram_Test(tb2);   // 01 ,01, 0 or 1  0-> main; 1->sub
            break;

        #if Enable_Gamma
        case 2:
            {
                extern void drvGammaLoadTbl( BYTE GamaMode );
                drvGammaLoadTbl(tb2);  //01 02 N
            }
            break;
        case 3:
            msLinearGammaLoader();
            break;
        case 4:
            {
                extern void drvGammaOnOff(BYTE u8Switch, BYTE u8Window);
                drvGammaOnOff(tb2,0);
                drvGammaOnOff(tb2,1);
            }
            break;
        case 5:
            printMsg("msLinearDeGammaLoader");
            msLinearDeGammaLoader();
            break;
    case 6:
        printMsg("msLinearFixGammaLoader");
        msLinearFixGammaLoader();
        break;
#endif
    case 7:
        printMsg("msFCCLoader");
        msFCCLoader();
            //old_msWriteByte(SC7_90, ( tb2 ==0 ) ? ( 0x00 ) : ( 0xFF ) );
            //old_msWriteByte(SC0_00, 0x00 );
        break;

#if 0//ENABLE_3DLUT
#if ENABLE_3DLUT_Test
    case 8:
        {
            extern void mStar_Setup3DLUT( void );
            printMsg("mStar_Setup3DLUT");
            mStar_Setup3DLUT();
        }
        break;
    case 9:
        {
            extern void void ms3DLutLoadTbl(BYTE ColorMode);
             ms3DLutLoadTbl(0);
         }
         break;
     case 0x0A:
         {
             extern void drv3DLutWriteReadTest(void);
              drv3DLutWriteReadTest();
          }
          break;
     case 0x0B:
         {
             extern  void drv3DLutEnable(BYTE ucSrcIdx, BYTE enable) ;
              drv3DLutEnable(0, tb2);
              drv3DLutEnable(1, tb2);
          }
          break;
#endif
#endif




    }
}
#else
BYTE code msColorVerifyNullData[] = {0};
void msColorVerifyDummy()
{
    BYTE xdata x = msColorVerifyNullData[0];
    x = x;
}

#endif

