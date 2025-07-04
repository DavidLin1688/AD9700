#define HDMIRX_DSCD_BASE 0x173c00
//Page DSCD_1
#define REG_0038_DSCD (HDMIRX_DSCD_BASE +0x1c)//0x173c_0eh
    #define REG_0038_DSCD_REG_BISTFAIL_DSCD_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_003C_DSCD (HDMIRX_DSCD_BASE +0x1e)//0x173c_0fh
    #define REG_003C_DSCD_REG_BISTFAIL_DSCD_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0040_DSCD (HDMIRX_DSCD_BASE +0x20)//0x173c_10h
    #define REG_0040_DSCD_REG_PPS0 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0040_DSCD_REG_PPS1 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0044_DSCD (HDMIRX_DSCD_BASE +0x22)//0x173c_11h
    #define REG_0044_DSCD_REG_PPS2 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0044_DSCD_REG_PPS3 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0048_DSCD (HDMIRX_DSCD_BASE +0x24)//0x173c_12h
    #define REG_0048_DSCD_REG_PPS4 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0048_DSCD_REG_PPS5 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_004C_DSCD (HDMIRX_DSCD_BASE +0x26)//0x173c_13h
    #define REG_004C_DSCD_REG_PPS6 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_004C_DSCD_REG_PPS7 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0050_DSCD (HDMIRX_DSCD_BASE +0x28)//0x173c_14h
    #define REG_0050_DSCD_REG_PPS8 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0050_DSCD_REG_PPS9 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0054_DSCD (HDMIRX_DSCD_BASE +0x2a)//0x173c_15h
    #define REG_0054_DSCD_REG_PPS10 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0054_DSCD_REG_PPS11 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0058_DSCD (HDMIRX_DSCD_BASE +0x2c)//0x173c_16h
    #define REG_0058_DSCD_REG_PPS12 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0058_DSCD_REG_PPS13 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_005C_DSCD (HDMIRX_DSCD_BASE +0x2e)//0x173c_17h
    #define REG_005C_DSCD_REG_PPS14 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_005C_DSCD_REG_PPS15 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0060_DSCD (HDMIRX_DSCD_BASE +0x30)//0x173c_18h
    #define REG_0060_DSCD_REG_PPS16 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0060_DSCD_REG_PPS17 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0064_DSCD (HDMIRX_DSCD_BASE +0x32)//0x173c_19h
    #define REG_0064_DSCD_REG_PPS18 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0064_DSCD_REG_PPS19 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0068_DSCD (HDMIRX_DSCD_BASE +0x34)//0x173c_1ah
    #define REG_0068_DSCD_REG_PPS20 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0068_DSCD_REG_PPS21 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_006C_DSCD (HDMIRX_DSCD_BASE +0x36)//0x173c_1bh
    #define REG_006C_DSCD_REG_PPS22 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_006C_DSCD_REG_PPS23 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0070_DSCD (HDMIRX_DSCD_BASE +0x38)//0x173c_1ch
    #define REG_0070_DSCD_REG_PPS24 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0070_DSCD_REG_PPS25 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0074_DSCD (HDMIRX_DSCD_BASE +0x3a)//0x173c_1dh
    #define REG_0074_DSCD_REG_PPS26 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0074_DSCD_REG_PPS27 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0078_DSCD (HDMIRX_DSCD_BASE +0x3c)//0x173c_1eh
    #define REG_0078_DSCD_REG_PPS28 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0078_DSCD_REG_PPS29 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_007C_DSCD (HDMIRX_DSCD_BASE +0x3e)//0x173c_1fh
    #define REG_007C_DSCD_REG_PPS30 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_007C_DSCD_REG_PPS31 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0080_DSCD (HDMIRX_DSCD_BASE +0x40)//0x173c_20h
    #define REG_0080_DSCD_REG_PPS32 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0080_DSCD_REG_PPS33 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0084_DSCD (HDMIRX_DSCD_BASE +0x42)//0x173c_21h
    #define REG_0084_DSCD_REG_PPS34 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0084_DSCD_REG_PPS35 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0088_DSCD (HDMIRX_DSCD_BASE +0x44)//0x173c_22h
    #define REG_0088_DSCD_REG_PPS36 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0088_DSCD_REG_PPS37 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_008C_DSCD (HDMIRX_DSCD_BASE +0x46)//0x173c_23h
    #define REG_008C_DSCD_REG_PPS38 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_008C_DSCD_REG_PPS39 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0090_DSCD (HDMIRX_DSCD_BASE +0x48)//0x173c_24h
    #define REG_0090_DSCD_REG_PPS40 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0090_DSCD_REG_PPS41 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0094_DSCD (HDMIRX_DSCD_BASE +0x4a)//0x173c_25h
    #define REG_0094_DSCD_REG_PPS42 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0094_DSCD_REG_PPS43 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0098_DSCD (HDMIRX_DSCD_BASE +0x4c)//0x173c_26h
    #define REG_0098_DSCD_REG_PPS44 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0098_DSCD_REG_PPS45 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_009C_DSCD (HDMIRX_DSCD_BASE +0x4e)//0x173c_27h
    #define REG_009C_DSCD_REG_PPS46 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_009C_DSCD_REG_PPS47 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00A0_DSCD (HDMIRX_DSCD_BASE +0x50)//0x173c_28h
    #define REG_00A0_DSCD_REG_PPS48 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00A0_DSCD_REG_PPS49 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00A4_DSCD (HDMIRX_DSCD_BASE +0x52)//0x173c_29h
    #define REG_00A4_DSCD_REG_PPS50 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00A4_DSCD_REG_PPS51 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00A8_DSCD (HDMIRX_DSCD_BASE +0x54)//0x173c_2ah
    #define REG_00A8_DSCD_REG_PPS52 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00A8_DSCD_REG_PPS53 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00AC_DSCD (HDMIRX_DSCD_BASE +0x56)//0x173c_2bh
    #define REG_00AC_DSCD_REG_PPS54 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00AC_DSCD_REG_PPS55 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00B0_DSCD (HDMIRX_DSCD_BASE +0x58)//0x173c_2ch
    #define REG_00B0_DSCD_REG_PPS56 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00B0_DSCD_REG_PPS57 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00B4_DSCD (HDMIRX_DSCD_BASE +0x5a)//0x173c_2dh
    #define REG_00B4_DSCD_REG_PPS58 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00B4_DSCD_REG_PPS59 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00B8_DSCD (HDMIRX_DSCD_BASE +0x5c)//0x173c_2eh
    #define REG_00B8_DSCD_REG_PPS60 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00B8_DSCD_REG_PPS61 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00BC_DSCD (HDMIRX_DSCD_BASE +0x5e)//0x173c_2fh
    #define REG_00BC_DSCD_REG_PPS62 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00BC_DSCD_REG_PPS63 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00C0_DSCD (HDMIRX_DSCD_BASE +0x60)//0x173c_30h
    #define REG_00C0_DSCD_REG_PPS64 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00C0_DSCD_REG_PPS65 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00C4_DSCD (HDMIRX_DSCD_BASE +0x62)//0x173c_31h
    #define REG_00C4_DSCD_REG_PPS66 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00C4_DSCD_REG_PPS67 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00C8_DSCD (HDMIRX_DSCD_BASE +0x64)//0x173c_32h
    #define REG_00C8_DSCD_REG_PPS68 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00C8_DSCD_REG_PPS69 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00CC_DSCD (HDMIRX_DSCD_BASE +0x66)//0x173c_33h
    #define REG_00CC_DSCD_REG_PPS70 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00CC_DSCD_REG_PPS71 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00D0_DSCD (HDMIRX_DSCD_BASE +0x68)//0x173c_34h
    #define REG_00D0_DSCD_REG_PPS72 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00D0_DSCD_REG_PPS73 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00D4_DSCD (HDMIRX_DSCD_BASE +0x6a)//0x173c_35h
    #define REG_00D4_DSCD_REG_PPS74 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00D4_DSCD_REG_PPS75 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00D8_DSCD (HDMIRX_DSCD_BASE +0x6c)//0x173c_36h
    #define REG_00D8_DSCD_REG_PPS76 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00D8_DSCD_REG_PPS77 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00DC_DSCD (HDMIRX_DSCD_BASE +0x6e)//0x173c_37h
    #define REG_00DC_DSCD_REG_PPS78 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00DC_DSCD_REG_PPS79 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00E0_DSCD (HDMIRX_DSCD_BASE +0x70)//0x173c_38h
    #define REG_00E0_DSCD_REG_PPS80 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00E0_DSCD_REG_PPS81 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00E4_DSCD (HDMIRX_DSCD_BASE +0x72)//0x173c_39h
    #define REG_00E4_DSCD_REG_PPS82 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00E4_DSCD_REG_PPS83 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00E8_DSCD (HDMIRX_DSCD_BASE +0x74)//0x173c_3ah
    #define REG_00E8_DSCD_REG_PPS84 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00E8_DSCD_REG_PPS85 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00EC_DSCD (HDMIRX_DSCD_BASE +0x76)//0x173c_3bh
    #define REG_00EC_DSCD_REG_PPS86 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00EC_DSCD_REG_PPS87 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00F0_DSCD (HDMIRX_DSCD_BASE +0x78)//0x173c_3ch
    #define REG_00F0_DSCD_REG_PPS88 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00F0_DSCD_REG_PPS89 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00F4_DSCD (HDMIRX_DSCD_BASE +0x7a)//0x173c_3dh
    #define REG_00F4_DSCD_REG_PPS90 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00F4_DSCD_REG_PPS91 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00F8_DSCD (HDMIRX_DSCD_BASE +0x7c)//0x173c_3eh
    #define REG_00F8_DSCD_REG_PPS92 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00F8_DSCD_REG_PPS93 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_00FC_DSCD (HDMIRX_DSCD_BASE +0x7e)//0x173c_3fh
    #define REG_00FC_DSCD_REG_PPS94 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_00FC_DSCD_REG_PPS95 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0100_DSCD (HDMIRX_DSCD_BASE +0x80)//0x173c_40h
    #define REG_0100_DSCD_REG_PPS96 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0100_DSCD_REG_PPS97 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0104_DSCD (HDMIRX_DSCD_BASE +0x82)//0x173c_41h
    #define REG_0104_DSCD_REG_PPS98 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0104_DSCD_REG_PPS99 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0108_DSCD (HDMIRX_DSCD_BASE +0x84)//0x173c_42h
    #define REG_0108_DSCD_REG_PPS100 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0108_DSCD_REG_PPS101 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_010C_DSCD (HDMIRX_DSCD_BASE +0x86)//0x173c_43h
    #define REG_010C_DSCD_REG_PPS102 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_010C_DSCD_REG_PPS103 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0110_DSCD (HDMIRX_DSCD_BASE +0x88)//0x173c_44h
    #define REG_0110_DSCD_REG_PPS104 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0110_DSCD_REG_PPS105 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0114_DSCD (HDMIRX_DSCD_BASE +0x8a)//0x173c_45h
    #define REG_0114_DSCD_REG_PPS106 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0114_DSCD_REG_PPS107 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0118_DSCD (HDMIRX_DSCD_BASE +0x8c)//0x173c_46h
    #define REG_0118_DSCD_REG_PPS108 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0118_DSCD_REG_PPS109 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_011C_DSCD (HDMIRX_DSCD_BASE +0x8e)//0x173c_47h
    #define REG_011C_DSCD_REG_PPS110 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_011C_DSCD_REG_PPS111 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0120_DSCD (HDMIRX_DSCD_BASE +0x90)//0x173c_48h
    #define REG_0120_DSCD_REG_PPS112 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0120_DSCD_REG_PPS113 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0124_DSCD (HDMIRX_DSCD_BASE +0x92)//0x173c_49h
    #define REG_0124_DSCD_REG_PPS114 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0124_DSCD_REG_PPS115 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0128_DSCD (HDMIRX_DSCD_BASE +0x94)//0x173c_4ah
    #define REG_0128_DSCD_REG_PPS116 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0128_DSCD_REG_PPS117 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_012C_DSCD (HDMIRX_DSCD_BASE +0x96)//0x173c_4bh
    #define REG_012C_DSCD_REG_PPS118 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_012C_DSCD_REG_PPS119 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0130_DSCD (HDMIRX_DSCD_BASE +0x98)//0x173c_4ch
    #define REG_0130_DSCD_REG_PPS120 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0130_DSCD_REG_PPS121 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0134_DSCD (HDMIRX_DSCD_BASE +0x9a)//0x173c_4dh
    #define REG_0134_DSCD_REG_PPS122 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0134_DSCD_REG_PPS123 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0138_DSCD (HDMIRX_DSCD_BASE +0x9c)//0x173c_4eh
    #define REG_0138_DSCD_REG_PPS124 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_0138_DSCD_REG_PPS125 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_013C_DSCD (HDMIRX_DSCD_BASE +0x9e)//0x173c_4fh
    #define REG_013C_DSCD_REG_PPS126 Fld(8,8,AC_FULLB1)//[15:8]
    #define REG_013C_DSCD_REG_PPS127 Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0140_DSCD (HDMIRX_DSCD_BASE +0xa0)//0x173c_50h
    #define REG_0140_DSCD_REG_ENTROPY_SHIFT_BLANKING Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0144_DSCD (HDMIRX_DSCD_BASE +0xa2)//0x173c_51h
    #define REG_0144_DSCD_REG_ENTROPY_SHIFT_BLANKING_SLICE Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0148_DSCD (HDMIRX_DSCD_BASE +0xa4)//0x173c_52h
    #define REG_0148_DSCD_REG_CTXSW_W_TIME Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0148_DSCD_REG_CTXSW_R_TIME Fld(8,8,AC_FULLB1)//[15:8]
#define REG_014C_DSCD (HDMIRX_DSCD_BASE +0xa6)//0x173c_53h
    #define REG_014C_DSCD_REG_SLICE_NUM Fld(5,0,AC_MSKB0)//[4:0]
    #define REG_014C_DSCD_REG_IN_BUF_BYPASS Fld(1,7,AC_MSKB0)//[7:7]
    #define REG_014C_DSCD_REG_IN_BUF_ACC_BYPASS Fld(1,8,AC_MSKB1)//[8:8]
    #define REG_014C_DSCD_REG_SHIFT_EN_TRIG_SEL Fld(1,9,AC_MSKB1)//[9:9]
    #define REG_014C_DSCD_REG_INI_DEC_LINE_DELAY_Q1M Fld(1,10,AC_MSKB1)//[10:10]
    #define REG_014C_DSCD_REG_READ_BACK_AUTO_VSYNC_RST Fld(1,14,AC_MSKB1)//[14:14]
    #define REG_014C_DSCD_REG_READ_BACK_RST Fld(1,15,AC_MSKB1)//[15:15]
#define REG_0150_DSCD (HDMIRX_DSCD_BASE +0xa8)//0x173c_54h
    #define REG_0150_DSCD_REG_INI_DEC_DELAY_USER Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0154_DSCD (HDMIRX_DSCD_BASE +0xaa)//0x173c_55h
    #define REG_0154_DSCD_REG_INI_DEC_LINE_DELAY Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0158_DSCD (HDMIRX_DSCD_BASE +0xac)//0x173c_56h
    #define REG_0158_DSCD_REG_RB_EMPTY_READ_BACK Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0158_DSCD_REG_IN_BUF_FULL_READ_BACK Fld(8,8,AC_FULLB1)//[15:8]
#define REG_015C_DSCD (HDMIRX_DSCD_BASE +0xae)//0x173c_57h
    #define REG_015C_DSCD_REG_IN_AFF_FULL_READ_BACK Fld(1,0,AC_MSKB0)//[0:0]
    #define REG_015C_DSCD_REG_OUT_BUF_FULL_READ_BACK Fld(3,1,AC_MSKB0)//[3:1]
    #define REG_015C_DSCD_REG_I_CKSZ_ERR_READ_BACK Fld(1,4,AC_MSKB0)//[4:4]
    #define REG_015C_DSCD_REG_F_CKSZ_ERR_READ_BACK Fld(1,5,AC_MSKB0)//[5:5]
    #define REG_015C_DSCD_REG_RB_FULL_READ_BACK Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0160_DSCD (HDMIRX_DSCD_BASE +0xb0)//0x173c_58h
    #define REG_0160_DSCD_REG_PPS_RB_SEL Fld(2,0,AC_MSKB0)//[1:0]
#define REG_0164_DSCD (HDMIRX_DSCD_BASE +0xb2)//0x173c_59h
    #define REG_0164_DSCD_REG_PPS128OR4BYTE_IN Fld(1,0,AC_MSKB0)//[0:0]
#define REG_0168_DSCD (HDMIRX_DSCD_BASE +0xb4)//0x173c_5ah
    #define REG_0168_DSCD_REG_READ_BACK_MASK Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0168_DSCD_REG_RB_SLICE_ID Fld(5,8,AC_MSKB1)//[12:8]
    #define REG_0168_DSCD_REG_RB_MODE Fld(1,15,AC_MSKB1)//[15:15]
#define REG_016C_DSCD (HDMIRX_DSCD_BASE +0xb6)//0x173c_5bh
    #define REG_016C_DSCD_REG_RATE_BUF_LVL Fld(8,0,AC_FULLB0)//[7:0]
#define REG_0170_DSCD (HDMIRX_DSCD_BASE +0xb8)//0x173c_5ch
    #define REG_0170_DSCD_REG_RB_LINE_ID Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0174_DSCD (HDMIRX_DSCD_BASE +0xba)//0x173c_5dh
    #define REG_0174_DSCD_REG_RB_LINE_COST Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0178_DSCD (HDMIRX_DSCD_BASE +0xbc)//0x173c_5eh
    #define REG_0178_DSCD_REG_FULLNESS_RB_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_017C_DSCD (HDMIRX_DSCD_BASE +0xbe)//0x173c_5fh
    #define REG_017C_DSCD_REG_FULLNESS_RB_1 Fld(4,0,AC_MSKB0)//[3:0]
    #define REG_017C_DSCD_REG_VIRTUAL_BUF_EMPTY Fld(1,5,AC_MSKB0)//[5:5]
    #define REG_017C_DSCD_REG_VIRTUAL_BUF_FULL Fld(1,6,AC_MSKB0)//[6:6]
#define REG_0180_DSCD (HDMIRX_DSCD_BASE +0xc0)//0x173c_60h
    #define REG_0180_DSCD_REG_PPS_RB_32BYTE_0 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0180_DSCD_REG_PPS_RB_32BYTE_1 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0184_DSCD (HDMIRX_DSCD_BASE +0xc2)//0x173c_61h
    #define REG_0184_DSCD_REG_PPS_RB_32BYTE_2 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0184_DSCD_REG_PPS_RB_32BYTE_3 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0188_DSCD (HDMIRX_DSCD_BASE +0xc4)//0x173c_62h
    #define REG_0188_DSCD_REG_PPS_RB_32BYTE_4 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0188_DSCD_REG_PPS_RB_32BYTE_5 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_018C_DSCD (HDMIRX_DSCD_BASE +0xc6)//0x173c_63h
    #define REG_018C_DSCD_REG_PPS_RB_32BYTE_6 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_018C_DSCD_REG_PPS_RB_32BYTE_7 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0190_DSCD (HDMIRX_DSCD_BASE +0xc8)//0x173c_64h
    #define REG_0190_DSCD_REG_PPS_RB_32BYTE_8 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0190_DSCD_REG_PPS_RB_32BYTE_9 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0194_DSCD (HDMIRX_DSCD_BASE +0xca)//0x173c_65h
    #define REG_0194_DSCD_REG_PPS_RB_32BYTE_10 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0194_DSCD_REG_PPS_RB_32BYTE_11 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0198_DSCD (HDMIRX_DSCD_BASE +0xcc)//0x173c_66h
    #define REG_0198_DSCD_REG_PPS_RB_32BYTE_12 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0198_DSCD_REG_PPS_RB_32BYTE_13 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_019C_DSCD (HDMIRX_DSCD_BASE +0xce)//0x173c_67h
    #define REG_019C_DSCD_REG_PPS_RB_32BYTE_14 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_019C_DSCD_REG_PPS_RB_32BYTE_15 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_01A0_DSCD (HDMIRX_DSCD_BASE +0xd0)//0x173c_68h
    #define REG_01A0_DSCD_REG_PPS_RB_32BYTE_16 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_01A0_DSCD_REG_PPS_RB_32BYTE_17 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_01A4_DSCD (HDMIRX_DSCD_BASE +0xd2)//0x173c_69h
    #define REG_01A4_DSCD_REG_PPS_RB_32BYTE_18 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_01A4_DSCD_REG_PPS_RB_32BYTE_19 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_01A8_DSCD (HDMIRX_DSCD_BASE +0xd4)//0x173c_6ah
    #define REG_01A8_DSCD_REG_PPS_RB_32BYTE_20 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_01A8_DSCD_REG_PPS_RB_32BYTE_21 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_01AC_DSCD (HDMIRX_DSCD_BASE +0xd6)//0x173c_6bh
    #define REG_01AC_DSCD_REG_PPS_RB_32BYTE_22 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_01AC_DSCD_REG_PPS_RB_32BYTE_23 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_01B0_DSCD (HDMIRX_DSCD_BASE +0xd8)//0x173c_6ch
    #define REG_01B0_DSCD_REG_PPS_RB_32BYTE_24 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_01B0_DSCD_REG_PPS_RB_32BYTE_25 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_01B4_DSCD (HDMIRX_DSCD_BASE +0xda)//0x173c_6dh
    #define REG_01B4_DSCD_REG_PPS_RB_32BYTE_26 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_01B4_DSCD_REG_PPS_RB_32BYTE_27 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_01B8_DSCD (HDMIRX_DSCD_BASE +0xdc)//0x173c_6eh
    #define REG_01B8_DSCD_REG_PPS_RB_32BYTE_28 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_01B8_DSCD_REG_PPS_RB_32BYTE_29 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_01BC_DSCD (HDMIRX_DSCD_BASE +0xde)//0x173c_6fh
    #define REG_01BC_DSCD_REG_PPS_RB_32BYTE_30 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_01BC_DSCD_REG_PPS_RB_32BYTE_31 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_01C0_DSCD (HDMIRX_DSCD_BASE +0xe0)//0x173c_70h
    #define REG_01C0_DSCD_REG_DSCD_OUTPUT_DELAY Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01C4_DSCD (HDMIRX_DSCD_BASE +0xe2)//0x173c_71h
    #define REG_01C4_DSCD_REG_DSCD_OUTPUT_DELAY_SEL Fld(1,0,AC_MSKB0)//[0:0]
    #define REG_01C4_DSCD_REG_DSCD_SELFGEN_DE_EN Fld(1,1,AC_MSKB0)//[1:1]
    #define REG_01C4_DSCD_REG_DSCD_SELFGEN_TRIG_EN Fld(1,2,AC_MSKB0)//[2:2]
    #define REG_01C4_DSCD_REG_TRIG_BLANK_SEL Fld(1,3,AC_MSKB0)//[3:3]
    #define REG_01C4_DSCD_REG_DB_OFF Fld(1,4,AC_MSKB0)//[4:4]
    #define REG_01C4_DSCD_REG_TEST_SINK_START_SW_SEL Fld(1,5,AC_MSKB0)//[5:5]
    #define REG_01C4_DSCD_REG_TEST_SINK_START_SW Fld(1,6,AC_MSKB0)//[6:6]
    #define REG_01C4_DSCD_REG_OUTPUT_CRC_COLOR_FORMAT_SW_SEL Fld(1,7,AC_MSKB0)//[7:7]
    #define REG_01C4_DSCD_REG_OUTPUT_CRC_COLOR_FORMAT_SW Fld(5,8,AC_MSKB1)//[12:8]
#define REG_01C8_DSCD (HDMIRX_DSCD_BASE +0xe4)//0x173c_72h
    #define REG_01C8_DSCD_REG_CKSZ_READ_BACK_SEL Fld(3,0,AC_MSKB0)//[2:0]
#define REG_01CC_DSCD (HDMIRX_DSCD_BASE +0xe6)//0x173c_73h
    #define REG_01CC_DSCD_REG_I_CKUNK_SIZE_READ_BACK Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01D0_DSCD (HDMIRX_DSCD_BASE +0xe8)//0x173c_74h
    #define REG_01D0_DSCD_REG_F_CHUNK_SIZE_READ_BACK Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01DC_DSCD (HDMIRX_DSCD_BASE +0xee)//0x173c_77h
    #define REG_01DC_DSCD_REG_CRC_TEST_CONFIG Fld(13,0,AC_MSKW10)//[12:0]
    #define REG_01DC_DSCD_REG_ECO_DSC_OUT_CRC_420 Fld(2,13,AC_MSKB1)//[14:13]
#define REG_01E0_DSCD (HDMIRX_DSCD_BASE +0xf0)//0x173c_78h
    #define REG_01E0_DSCD_REG_SW_RST Fld(1,0,AC_MSKB0)//[0:0]
    #define REG_01E0_DSCD_REG_SW_RST_VSYNC Fld(1,1,AC_MSKB0)//[1:1]
    #define REG_01E0_DSCD_REG_AUTO_SLICE_ID_CHG Fld(1,2,AC_MSKB0)//[2:2]
    #define REG_01E0_DSCD_REG_INI_DEC_DELAY_SEL Fld(1,3,AC_MSKB0)//[3:3]
    #define REG_01E0_DSCD_REG_SLICE_WIDTH_AUTO_SEL Fld(1,4,AC_MSKB0)//[4:4]
    #define REG_01E0_DSCD_REG_USE_STR_PPS Fld(1,5,AC_MSKB0)//[5:5]
    #define REG_01E0_DSCD_REG_422_OUT_SEL Fld(1,6,AC_MSKB0)//[6:6]
    #define REG_01E0_DSCD_REG_CRC_EN Fld(1,7,AC_MSKB0)//[7:7]
    #define REG_01E0_DSCD_REG_INPUT_CRC_WRAP_CNT Fld(4,8,AC_MSKB1)//[11:8]
    #define REG_01E0_DSCD_REG_OUTPUT_CRC_WRAP_CNT Fld(4,12,AC_MSKB1)//[15:12]

//Page DSCD_2
#define REG_01E4_DSCD (HDMIRX_DSCD_BASE +0xf2)//0x173c_79h
    #define REG_01E4_DSCD_REG_INPUT_CRC_R_CR Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01E8_DSCD (HDMIRX_DSCD_BASE +0xf4)//0x173c_7ah
    #define REG_01E8_DSCD_REG_INPUT_CRC_G_Y Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01EC_DSCD (HDMIRX_DSCD_BASE +0xf6)//0x173c_7bh
    #define REG_01EC_DSCD_REG_INPUT_CRC_B_CB Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01F0_DSCD (HDMIRX_DSCD_BASE +0xf8)//0x173c_7ch
    #define REG_01F0_DSCD_REG_OUTPUT_CRC_R_CR Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01F4_DSCD (HDMIRX_DSCD_BASE +0xfa)//0x173c_7dh
    #define REG_01F4_DSCD_REG_OUTPUT_CRC_G_Y Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01F8_DSCD (HDMIRX_DSCD_BASE +0xfc)//0x173c_7eh
    #define REG_01F8_DSCD_REG_OUTPUT_CRC_B_CB Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01FC_DSCD (HDMIRX_DSCD_BASE +0xfe)//0x173c_7fh
    #define REG_01FC_DSCD_REG_OUTPUT_CRC_TEST_CONFIG Fld(13,0,AC_MSKW10)//[12:0]

