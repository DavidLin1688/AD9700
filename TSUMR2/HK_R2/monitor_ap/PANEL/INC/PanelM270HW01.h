#define PanelName   "M270HW01V0"


#define PanelDither     8

#define PanelTTL        0
#define PanelTCON       0
#define PanelLVDS       0xFF
#define PanelRSDS       0

#define LVDS_TIMode         0xff
#define PanelDualPort           0xFF
#define PanelSwapPort            0xFF
#define PanelSwapOddML           0
#define PanelSwapEvenML     0
#define PanelSwapOddRB      0
#define PanelSwapEvenRB     0
#define PanelSwapMLSB       0
#define PanelSwapPlusMinus      0//0xff



#define PanelDClkDelay      0
#define PanelInvDE                  0
#define PanelInvDClk        0
#define PanelInvHSync       0
#define PanelInvVSync       0

// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent    1 // Dclk current
#define PanelDECurrent      1 // DE signal current
#define PanelOddDataCurrent 1 // Odd data current
#define PanelEvenDataCurrent    1 // Even data current

#define PanelOnTiming1    30 // 0//40 // time between panel & data while turn on power
#define PanelOnTiming2    250 // 300//300 //30 // time between data & back light while turn on power

#define PanelOffTiming1  250 // time between back light & data while turn off power
#define PanelOffTiming2  16 // 20 // time between data & panel while turn off power

#define PanelHSyncWidth    35//32
#define PanelHSyncBackPorch  42 //152//24

#define PanelVSyncWidth     3
#define PanelVSyncBackPorch  10 // 46

#define PanelHStart   (PanelHSyncWidth+PanelHSyncBackPorch)
#define PanelVStart   (PanelVSyncWidth+PanelVSyncBackPorch)
#define PanelWidth    1920
#define PanelHeight   1080

#define PanelHTotal     2120//2000 // 1840 // 2240//2256
#define PanelVTotal   1120 // 1080//1200//1250

#define PanelMaxHTotal    4094//2600
#define PanelMinHTotal    2068
#define PanelMaxVTotal    2047//1300 
#define PanelMinVTotal    1088
#define PanelDCLK           150//147 

#define PanelMaxDCLK         180// 166
#define PanelMinDCLK         80//122
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
#define DefCool_RedColor                    97
#define DefCool_GreenColor                105
#define DefCool_BlueColor                   128
#define DefNormal_RedColor               114
#define DefNormal_GreenColor           116
#define DefNormal_BlueColor              128
#define DefWarm_RedColor                 122
#define DefWarm_GreenColor              123
#define DefWarm_BlueColor                128
#define DefsRGB_RedColor                   122
#define DefsRGB_GreenColor               123
#define DefsRGB_BlueColor                  128

