#define HDMIRX_P0_PKT_DEC_BASE 0x170a00
//Page P0_HDMIRX_PKT_DEC
#define REG_0000_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x00)//0x170a_00h
    #define REG_0000_P0_HDMIRX_PKT_DEC_REG_RESET_AVMUTE Fld(1,0,AC_MSKB0)//[0:0]
    #define REG_0000_P0_HDMIRX_PKT_DEC_REG_RESET_DC_VAL Fld(1,1,AC_MSKB0)//[1:1]
    #define REG_0000_P0_HDMIRX_PKT_DEC_REG_RESET_STATUS Fld(1,2,AC_MSKB0)//[2:2]
    #define REG_0000_P0_HDMIRX_PKT_DEC_REG_RESET_FRAME_RP Fld(1,3,AC_MSKB0)//[3:3]
    #define REG_0000_P0_HDMIRX_PKT_DEC_REG_RESET_PR Fld(1,4,AC_MSKB0)//[4:4]
    #define REG_0000_P0_HDMIRX_PKT_DEC_REG_RESET_COLOR Fld(1,5,AC_MSKB0)//[5:5]
#define REG_0028_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x14)//0x170a_0ah
    #define REG_0028_P0_HDMIRX_PKT_DEC_REG_DEPACK_DEC_IRQ_MASK_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0030_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x18)//0x170a_0ch
    #define REG_0030_P0_HDMIRX_PKT_DEC_REG_DEPACK_DEC_IRQ_FORCE_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0038_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x1c)//0x170a_0eh
    #define REG_0038_P0_HDMIRX_PKT_DEC_REG_DEPACK_DEC_IRQ_CLR_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0040_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x20)//0x170a_10h
    #define REG_0040_P0_HDMIRX_PKT_DEC_REG_DIS_BCHCORR Fld(1,0,AC_MSKB0)//[0:0]
    #define REG_0040_P0_HDMIRX_PKT_DEC_REG_EN_USRPKT Fld(1,1,AC_MSKB0)//[1:1]
    #define REG_0040_P0_HDMIRX_PKT_DEC_REG_DIS_CHKSUM Fld(1,2,AC_MSKB0)//[2:2]
    #define REG_0040_P0_HDMIRX_PKT_DEC_REG_DIS_BCHCHK Fld(1,3,AC_MSKB0)//[3:3]
    #define REG_0040_P0_HDMIRX_PKT_DEC_REG_PKT_VALID_DELAY_SEL Fld(1,4,AC_MSKB0)//[4:4]
    #define REG_0040_P0_HDMIRX_PKT_DEC_REG_DIS_CHKSUM_RSV Fld(1,5,AC_MSKB0)//[5:5]
    #define REG_0040_P0_HDMIRX_PKT_DEC_REG_DIS_GCP_PKT Fld(1,6,AC_MSKB0)//[6:6]
    #define REG_0040_P0_HDMIRX_PKT_DEC_REG_DIS_AVI_PKT Fld(1,7,AC_MSKB0)//[7:7]
    #define REG_0040_P0_HDMIRX_PKT_DEC_REG_DIS_SPD_PKT Fld(1,8,AC_MSKB1)//[8:8]
    #define REG_0040_P0_HDMIRX_PKT_DEC_REG_DIS_RSV_PKT Fld(1,9,AC_MSKB1)//[9:9]
    #define REG_0040_P0_HDMIRX_PKT_DEC_REG_DIS_NO_GCP_QUIT Fld(1,10,AC_MSKB1)//[10:10]
#define REG_0044_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x22)//0x170a_11h
    #define REG_0044_P0_HDMIRX_PKT_DEC_REG_PKT_TYPE Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0044_P0_HDMIRX_PKT_DEC_REG_RSV_PKT_TYPE Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0048_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x24)//0x170a_12h
    #define REG_0048_P0_HDMIRX_PKT_DEC_REG_RCV_GCP_SEL Fld(1,0,AC_MSKB0)//[0:0]
    #define REG_0048_P0_HDMIRX_PKT_DEC_REG_GCP_OUT_SEL Fld(1,1,AC_MSKB0)//[1:1]
    #define REG_0048_P0_HDMIRX_PKT_DEC_REG_AVMUTE_OVERRIDE_TRIGGER Fld(1,2,AC_MSKB0)//[2:2]
    #define REG_0048_P0_HDMIRX_PKT_DEC_REG_AVMUTE_OV Fld(1,3,AC_MSKB0)//[3:3]
    #define REG_0048_P0_HDMIRX_PKT_DEC_REG_MANUAL_COLOR_DEPTH Fld(2,4,AC_MSKB0)//[5:4]
    #define REG_0048_P0_HDMIRX_PKT_DEC_REG_CD_ZERO_UPDATE Fld(1,6,AC_MSKB0)//[6:6]
#define REG_004C_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x26)//0x170a_13h
    #define REG_004C_P0_HDMIRX_PKT_DEC_REG_GCONTROL Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0050_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x28)//0x170a_14h
    #define REG_0050_P0_HDMIRX_PKT_DEC_REG_PIX_REP_OV Fld(4,0,AC_MSKB0)//[3:0]
    #define REG_0050_P0_HDMIRX_PKT_DEC_REG_PIX_REP_OVE Fld(1,4,AC_MSKB0)//[4:4]
    #define REG_0050_P0_HDMIRX_PKT_DEC_REG_VIDEO_FMT_OVE Fld(1,5,AC_MSKB0)//[5:5]
    #define REG_0050_P0_HDMIRX_PKT_DEC_REG_VIDEO_FMT_422_OV Fld(1,6,AC_MSKB0)//[6:6]
    #define REG_0050_P0_HDMIRX_PKT_DEC_REG_VIDEO_FMT_420_OV Fld(1,7,AC_MSKB0)//[7:7]
    #define REG_0050_P0_HDMIRX_PKT_DEC_REG_422_TO_SC_OV_EN Fld(1,8,AC_MSKB1)//[8:8]
    #define REG_0050_P0_HDMIRX_PKT_DEC_REG_422_TO_SC_OV_VALUE Fld(1,9,AC_MSKB1)//[9:9]
    #define REG_0050_P0_HDMIRX_PKT_DEC_REG_420_TO_SC_OV_EN Fld(1,10,AC_MSKB1)//[10:10]
    #define REG_0050_P0_HDMIRX_PKT_DEC_REG_420_TO_SC_OV_VALUE Fld(1,11,AC_MSKB1)//[11:11]
    #define REG_0050_P0_HDMIRX_PKT_DEC_REG_EDR_Q_RANGE Fld(1,12,AC_MSKB1)//[12:12]
    #define REG_0050_P0_HDMIRX_PKT_DEC_REG_SET_DOLBY_EDR11 Fld(1,13,AC_MSKB1)//[13:13]
    #define REG_0050_P0_HDMIRX_PKT_DEC_REG_CLR_DOLBY_EDR11 Fld(1,14,AC_MSKB1)//[14:14]
#define REG_0054_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x2a)//0x170a_15h
    #define REG_0054_P0_HDMIRX_PKT_DEC_REG_HDMI_FRAME_RP Fld(3,0,AC_MSKB0)//[2:0]
    #define REG_0054_P0_HDMIRX_PKT_DEC_REG_FRAME_RP_MODE Fld(4,4,AC_MSKB0)//[7:4]
    #define REG_0054_P0_HDMIRX_PKT_DEC_REG_AVI_PKT_LOSE_THD Fld(4,8,AC_MSKB1)//[11:8]
#define REG_0058_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x2c)//0x170a_16h
    #define REG_0058_P0_HDMIRX_PKT_DEC_REG_SUPPORT_PKT_HEADER_H Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0058_P0_HDMIRX_PKT_DEC_REG_SUPPORT_PKT_HEADER_L Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0060_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x30)//0x170a_18h
    #define REG_0060_P0_HDMIRX_PKT_DEC_REG_AVI_PKT_DIFF_EN_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0064_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x32)//0x170a_19h
    #define REG_0064_P0_HDMIRX_PKT_DEC_REG_AVI_PKT_DIFF_EN_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0068_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x34)//0x170a_1ah
    #define REG_0068_P0_HDMIRX_PKT_DEC_REG_GCP_PKT_DIFF_EN_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_006C_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x36)//0x170a_1bh
    #define REG_006C_P0_HDMIRX_PKT_DEC_REG_GCP_PKT_DIFF_EN_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0070_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x38)//0x170a_1ch
    #define REG_0070_P0_HDMIRX_PKT_DEC_REG_SPD_PKT_DIFF_EN_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0074_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x3a)//0x170a_1dh
    #define REG_0074_P0_HDMIRX_PKT_DEC_REG_SPD_PKT_DIFF_EN_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_007C_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x3e)//0x170a_1fh
    #define REG_007C_P0_HDMIRX_PKT_DEC_REG_DEPACK_DEC_TSTBUS_SEL Fld(4,0,AC_MSKB0)//[3:0]
    #define REG_007C_P0_HDMIRX_PKT_DEC_REG_PHASE_DIFF_8P Fld(3,4,AC_MSKB0)//[6:4]
#define REG_0080_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x40)//0x170a_20h
    #define REG_0080_P0_HDMIRX_PKT_DEC_REG_AVI_HDR1 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0080_P0_HDMIRX_PKT_DEC_REG_AVI_HDR2 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0084_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x42)//0x170a_21h
    #define REG_0084_P0_HDMIRX_PKT_DEC_REG_AVI_PB00 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0084_P0_HDMIRX_PKT_DEC_REG_AVI_PB01 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0088_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x44)//0x170a_22h
    #define REG_0088_P0_HDMIRX_PKT_DEC_REG_AVI_PB02 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0088_P0_HDMIRX_PKT_DEC_REG_AVI_PB03 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_008C_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x46)//0x170a_23h
    #define REG_008C_P0_HDMIRX_PKT_DEC_REG_AVI_PB04 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_008C_P0_HDMIRX_PKT_DEC_REG_AVI_PB05 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0090_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x48)//0x170a_24h
    #define REG_0090_P0_HDMIRX_PKT_DEC_REG_AVI_PB06 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0090_P0_HDMIRX_PKT_DEC_REG_AVI_PB07 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0094_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x4a)//0x170a_25h
    #define REG_0094_P0_HDMIRX_PKT_DEC_REG_AVI_PB08 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0094_P0_HDMIRX_PKT_DEC_REG_AVI_PB09 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0098_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x4c)//0x170a_26h
    #define REG_0098_P0_HDMIRX_PKT_DEC_REG_AVI_PB10 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0098_P0_HDMIRX_PKT_DEC_REG_AVI_PB11 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_009C_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x4e)//0x170a_27h
    #define REG_009C_P0_HDMIRX_PKT_DEC_REG_AVI_PB12 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_009C_P0_HDMIRX_PKT_DEC_REG_AVI_PB13 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00A0_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x50)//0x170a_28h
    #define REG_00A0_P0_HDMIRX_PKT_DEC_REG_AVI_PB14 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00A0_P0_HDMIRX_PKT_DEC_REG_AVI_PB15 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00A4_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x52)//0x170a_29h
    #define REG_00A4_P0_HDMIRX_PKT_DEC_REG_AVI_PB16 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00A4_P0_HDMIRX_PKT_DEC_REG_AVI_PB17 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00A8_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x54)//0x170a_2ah
    #define REG_00A8_P0_HDMIRX_PKT_DEC_REG_AVI_PB18 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00A8_P0_HDMIRX_PKT_DEC_REG_AVI_PB19 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00AC_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x56)//0x170a_2bh
    #define REG_00AC_P0_HDMIRX_PKT_DEC_REG_AVI_PB20 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00AC_P0_HDMIRX_PKT_DEC_REG_AVI_PB21 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00B0_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x58)//0x170a_2ch
    #define REG_00B0_P0_HDMIRX_PKT_DEC_REG_AVI_PB22 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00B0_P0_HDMIRX_PKT_DEC_REG_AVI_PB23 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00B4_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x5a)//0x170a_2dh
    #define REG_00B4_P0_HDMIRX_PKT_DEC_REG_AVI_PB24 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00B4_P0_HDMIRX_PKT_DEC_REG_AVI_PB25 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00B8_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x5c)//0x170a_2eh
    #define REG_00B8_P0_HDMIRX_PKT_DEC_REG_AVI_PB26 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00B8_P0_HDMIRX_PKT_DEC_REG_AVI_PB27 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00C0_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x60)//0x170a_30h
    #define REG_00C0_P0_HDMIRX_PKT_DEC_REG_GCP_HDR1 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00C0_P0_HDMIRX_PKT_DEC_REG_GCP_HDR2 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00C4_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x62)//0x170a_31h
    #define REG_00C4_P0_HDMIRX_PKT_DEC_REG_GCP_PB00 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00C4_P0_HDMIRX_PKT_DEC_REG_GCP_PB01 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00C8_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x64)//0x170a_32h
    #define REG_00C8_P0_HDMIRX_PKT_DEC_REG_GCP_PB02 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00C8_P0_HDMIRX_PKT_DEC_REG_GCP_PB03 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00CC_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x66)//0x170a_33h
    #define REG_00CC_P0_HDMIRX_PKT_DEC_REG_GCP_PB04 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00CC_P0_HDMIRX_PKT_DEC_REG_GCP_PB05 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00D0_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x68)//0x170a_34h
    #define REG_00D0_P0_HDMIRX_PKT_DEC_REG_GCP_PB06 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00D0_P0_HDMIRX_PKT_DEC_REG_GCP_PB07 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00D4_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x6a)//0x170a_35h
    #define REG_00D4_P0_HDMIRX_PKT_DEC_REG_GCP_PB08 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00D4_P0_HDMIRX_PKT_DEC_REG_GCP_PB09 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00D8_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x6c)//0x170a_36h
    #define REG_00D8_P0_HDMIRX_PKT_DEC_REG_GCP_PB10 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00D8_P0_HDMIRX_PKT_DEC_REG_GCP_PB11 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00DC_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x6e)//0x170a_37h
    #define REG_00DC_P0_HDMIRX_PKT_DEC_REG_GCP_PB12 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00DC_P0_HDMIRX_PKT_DEC_REG_GCP_PB13 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00E0_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x70)//0x170a_38h
    #define REG_00E0_P0_HDMIRX_PKT_DEC_REG_GCP_PB14 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00E0_P0_HDMIRX_PKT_DEC_REG_GCP_PB15 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00E4_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x72)//0x170a_39h
    #define REG_00E4_P0_HDMIRX_PKT_DEC_REG_GCP_PB16 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00E4_P0_HDMIRX_PKT_DEC_REG_GCP_PB17 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00E8_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x74)//0x170a_3ah
    #define REG_00E8_P0_HDMIRX_PKT_DEC_REG_GCP_PB18 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00E8_P0_HDMIRX_PKT_DEC_REG_GCP_PB19 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00EC_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x76)//0x170a_3bh
    #define REG_00EC_P0_HDMIRX_PKT_DEC_REG_GCP_PB20 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00EC_P0_HDMIRX_PKT_DEC_REG_GCP_PB21 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00F0_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x78)//0x170a_3ch
    #define REG_00F0_P0_HDMIRX_PKT_DEC_REG_GCP_PB22 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00F0_P0_HDMIRX_PKT_DEC_REG_GCP_PB23 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00F4_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x7a)//0x170a_3dh
    #define REG_00F4_P0_HDMIRX_PKT_DEC_REG_GCP_PB24 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00F4_P0_HDMIRX_PKT_DEC_REG_GCP_PB25 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_00F8_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x7c)//0x170a_3eh
    #define REG_00F8_P0_HDMIRX_PKT_DEC_REG_GCP_PB26 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_00F8_P0_HDMIRX_PKT_DEC_REG_GCP_PB27 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0100_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x80)//0x170a_40h
    #define REG_0100_P0_HDMIRX_PKT_DEC_REG_SPD_HDR1 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0100_P0_HDMIRX_PKT_DEC_REG_SPD_HDR2 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0104_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x82)//0x170a_41h
    #define REG_0104_P0_HDMIRX_PKT_DEC_REG_SPD_PB00 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0104_P0_HDMIRX_PKT_DEC_REG_SPD_PB01 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0108_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x84)//0x170a_42h
    #define REG_0108_P0_HDMIRX_PKT_DEC_REG_SPD_PB02 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0108_P0_HDMIRX_PKT_DEC_REG_SPD_PB03 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_010C_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x86)//0x170a_43h
    #define REG_010C_P0_HDMIRX_PKT_DEC_REG_SPD_PB04 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_010C_P0_HDMIRX_PKT_DEC_REG_SPD_PB05 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0110_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x88)//0x170a_44h
    #define REG_0110_P0_HDMIRX_PKT_DEC_REG_SPD_PB06 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0110_P0_HDMIRX_PKT_DEC_REG_SPD_PB07 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0114_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x8a)//0x170a_45h
    #define REG_0114_P0_HDMIRX_PKT_DEC_REG_SPD_PB08 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0114_P0_HDMIRX_PKT_DEC_REG_SPD_PB09 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0118_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x8c)//0x170a_46h
    #define REG_0118_P0_HDMIRX_PKT_DEC_REG_SPD_PB10 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0118_P0_HDMIRX_PKT_DEC_REG_SPD_PB11 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_011C_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x8e)//0x170a_47h
    #define REG_011C_P0_HDMIRX_PKT_DEC_REG_SPD_PB12 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_011C_P0_HDMIRX_PKT_DEC_REG_SPD_PB13 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0120_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x90)//0x170a_48h
    #define REG_0120_P0_HDMIRX_PKT_DEC_REG_SPD_PB14 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0120_P0_HDMIRX_PKT_DEC_REG_SPD_PB15 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0124_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x92)//0x170a_49h
    #define REG_0124_P0_HDMIRX_PKT_DEC_REG_SPD_PB16 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0124_P0_HDMIRX_PKT_DEC_REG_SPD_PB17 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0128_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x94)//0x170a_4ah
    #define REG_0128_P0_HDMIRX_PKT_DEC_REG_SPD_PB18 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0128_P0_HDMIRX_PKT_DEC_REG_SPD_PB19 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_012C_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x96)//0x170a_4bh
    #define REG_012C_P0_HDMIRX_PKT_DEC_REG_SPD_PB20 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_012C_P0_HDMIRX_PKT_DEC_REG_SPD_PB21 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0130_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x98)//0x170a_4ch
    #define REG_0130_P0_HDMIRX_PKT_DEC_REG_SPD_PB22 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0130_P0_HDMIRX_PKT_DEC_REG_SPD_PB23 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0134_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x9a)//0x170a_4dh
    #define REG_0134_P0_HDMIRX_PKT_DEC_REG_SPD_PB24 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0134_P0_HDMIRX_PKT_DEC_REG_SPD_PB25 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0138_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0x9c)//0x170a_4eh
    #define REG_0138_P0_HDMIRX_PKT_DEC_REG_SPD_PB26 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0138_P0_HDMIRX_PKT_DEC_REG_SPD_PB27 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0140_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xa0)//0x170a_50h
    #define REG_0140_P0_HDMIRX_PKT_DEC_REG_RSV_HDR1 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0140_P0_HDMIRX_PKT_DEC_REG_RSV_HDR2 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0144_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xa2)//0x170a_51h
    #define REG_0144_P0_HDMIRX_PKT_DEC_REG_RSV_PB00 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0144_P0_HDMIRX_PKT_DEC_REG_RSV_PB01 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0148_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xa4)//0x170a_52h
    #define REG_0148_P0_HDMIRX_PKT_DEC_REG_RSV_PB02 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0148_P0_HDMIRX_PKT_DEC_REG_RSV_PB03 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_014C_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xa6)//0x170a_53h
    #define REG_014C_P0_HDMIRX_PKT_DEC_REG_RSV_PB04 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_014C_P0_HDMIRX_PKT_DEC_REG_RSV_PB05 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0150_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xa8)//0x170a_54h
    #define REG_0150_P0_HDMIRX_PKT_DEC_REG_RSV_PB06 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0150_P0_HDMIRX_PKT_DEC_REG_RSV_PB07 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0154_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xaa)//0x170a_55h
    #define REG_0154_P0_HDMIRX_PKT_DEC_REG_RSV_PB08 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0154_P0_HDMIRX_PKT_DEC_REG_RSV_PB09 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0158_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xac)//0x170a_56h
    #define REG_0158_P0_HDMIRX_PKT_DEC_REG_RSV_PB10 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0158_P0_HDMIRX_PKT_DEC_REG_RSV_PB11 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_015C_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xae)//0x170a_57h
    #define REG_015C_P0_HDMIRX_PKT_DEC_REG_RSV_PB12 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_015C_P0_HDMIRX_PKT_DEC_REG_RSV_PB13 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0160_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xb0)//0x170a_58h
    #define REG_0160_P0_HDMIRX_PKT_DEC_REG_RSV_PB14 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0160_P0_HDMIRX_PKT_DEC_REG_RSV_PB15 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0164_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xb2)//0x170a_59h
    #define REG_0164_P0_HDMIRX_PKT_DEC_REG_RSV_PB16 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0164_P0_HDMIRX_PKT_DEC_REG_RSV_PB17 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0168_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xb4)//0x170a_5ah
    #define REG_0168_P0_HDMIRX_PKT_DEC_REG_RSV_PB18 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0168_P0_HDMIRX_PKT_DEC_REG_RSV_PB19 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_016C_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xb6)//0x170a_5bh
    #define REG_016C_P0_HDMIRX_PKT_DEC_REG_RSV_PB20 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_016C_P0_HDMIRX_PKT_DEC_REG_RSV_PB21 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0170_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xb8)//0x170a_5ch
    #define REG_0170_P0_HDMIRX_PKT_DEC_REG_RSV_PB22 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0170_P0_HDMIRX_PKT_DEC_REG_RSV_PB23 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0174_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xba)//0x170a_5dh
    #define REG_0174_P0_HDMIRX_PKT_DEC_REG_RSV_PB24 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0174_P0_HDMIRX_PKT_DEC_REG_RSV_PB25 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0178_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xbc)//0x170a_5eh
    #define REG_0178_P0_HDMIRX_PKT_DEC_REG_RSV_PB26 Fld(8,0,AC_FULLB0)//[7:0]
    #define REG_0178_P0_HDMIRX_PKT_DEC_REG_RSV_PB27 Fld(8,8,AC_FULLB1)//[15:8]
#define REG_017C_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xbe)//0x170a_5fh
    #define REG_017C_P0_HDMIRX_PKT_DEC_REG_RSV_PKT_DIFF_EN Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0180_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xc0)//0x170a_60h
    #define REG_0180_P0_HDMIRX_PKT_DEC_REG_PKT_DEC_RESERVED_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0184_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xc2)//0x170a_61h
    #define REG_0184_P0_HDMIRX_PKT_DEC_REG_PKT_DEC_RESERVED_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0188_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xc4)//0x170a_62h
    #define REG_0188_P0_HDMIRX_PKT_DEC_REG_PKT_DEC_RESERVED_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_018C_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xc6)//0x170a_63h
    #define REG_018C_P0_HDMIRX_PKT_DEC_REG_PKT_DEC_RESERVED_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01A0_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xd0)//0x170a_68h
    #define REG_01A0_P0_HDMIRX_PKT_DEC_REG_PKT_DEC_RESERVED_RD_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01A4_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xd2)//0x170a_69h
    #define REG_01A4_P0_HDMIRX_PKT_DEC_REG_PKT_DEC_RESERVED_RD_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01A8_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xd4)//0x170a_6ah
    #define REG_01A8_P0_HDMIRX_PKT_DEC_REG_PKT_DEC_RESERVED_RD_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01AC_P0_HDMIRX_PKT_DEC (HDMIRX_P0_PKT_DEC_BASE +0xd6)//0x170a_6bh
    #define REG_01AC_P0_HDMIRX_PKT_DEC_REG_PKT_DEC_RESERVED_RD_3 Fld(16,0,AC_FULLW10)//[15:0]

