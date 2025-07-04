#ifndef _PanelLTM230HT3_
#define _PanelLTM230HT3_
#define PanelName               "LTM230HT3"

#define _PANEL_NORMALLY_BLACK_
#define PanelDither     8

#define PanelTTL            0
#define PanelTCON       0
#define PanelLVDS       0xFF
#define PanelRSDS       0

#define LVDS_TIMode     0xff
#define PanelDualPort       0xFF
#define PanelSwapPort       0xFF
#define PanelSwapOddML      0
#define PanelSwapEvenML     0
#define PanelSwapOddRB      0//xFF
#define PanelSwapEvenRB     0//xFF
#define PanelSwapMLSB       0

#define PanelDClkDelay          0
#define PanelInvDE              0
#define PanelInvDClk            0
#define PanelInvHSync           0
#define PanelInvVSync           0
// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent        1 // Dclk current
#define PanelDECurrent              1 // DE signal current
#define PanelOddDataCurrent         1 // Odd data current
#define PanelEvenDataCurrent    1 // Even data current

#define PanelOnTiming1          20//60//20 // time between panel & data while turn on power
#define PanelOnTiming2          550//350//220 // time between data & back light while turn on power
#define PanelOffTiming1         150//350//220 // 2005/5/3// time between back light & data while turn off power 
#define PanelOffTiming2         20//20//25 // 2005/5/3//10 // time between data & panel while turn off power 

#define PanelHSyncWidth         20
#define PanelHSyncBackPorch     28

#define PanelVSyncWidth         3
#define PanelVSyncBackPorch     12

#define PanelHStart                 (PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart                 (PanelVSyncWidth+PanelVSyncBackPorch)

#define PanelWidth      1920
#define PanelHeight     1080
#define PanelHTotal     2020
#define PanelVTotal     1111

#define PanelMaxHTotal      2080
#define PanelMinHTotal      2000
#define PanelMaxVTotal      1118
#define PanelMinVTotal          1105

#define PanelDCLK               135
#define PanelMaxDCLK            175
#define PanelMinDCLK            108
//=================================================================
// TCON  setting for LVDS
//PVS / FSYNC
#define GPO9_VStart     0x7
#define GPO9_VEnd       0x705
#define GPO9_HStart     0x0
#define GPO9_HEnd       0x0
#define GPO9_Control        0x7

//HSYNC
#define GPOA_VStart     0x006
#define GPOA_VEnd       0x408
#define GPOA_HStart     0
#define GPOA_HEnd       0
#define GPOA_Control        0x4

//=================================================================
//Color Temp
#define DefCool_RedColor                    105
#define DefCool_GreenColor                113
#define DefCool_BlueColor                   130
#define DefNormal_RedColor               116
#define DefNormal_GreenColor           122
#define DefNormal_BlueColor              130
#define DefWarm_RedColor                 130
#define DefWarm_GreenColor              130
#define DefWarm_BlueColor                130
#define DefsRGB_RedColor                   130
#define DefsRGB_GreenColor               130
#define DefsRGB_BlueColor                  130
#endif
