#define HDMIRX_EFUSE_0_BASE 0x00000000

//Page EFUSE_0
#define REG_0000_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x200)
    #define REG_0000_EFUSE_0_REG_PROG_TRIG Fld(1,0,AC_MSKB0)//[0:0]
    #define REG_0000_EFUSE_0_REG_RWL Fld(1,1,AC_MSKB0)//[1:1]
    #define REG_0000_EFUSE_0_REG_RSB Fld(1,2,AC_MSKB0)//[2:2]
    #define REG_0000_EFUSE_0_REG_MR Fld(1,3,AC_MSKB0)//[3:3]
#define REG_0004_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x204)
    #define REG_0004_EFUSE_0_REG_CLEAR_PWR_LOG Fld(1,0,AC_MSKB0)//[0:0]
    #define REG_0004_EFUSE_0_REG_PWR_NO_GOOD Fld(1,1,AC_MSKB0)//[1:1]
    #define REG_0004_EFUSE_0_REG_PWR_GOOD Fld(1,2,AC_MSKB0)//[2:2]
    #define REG_0004_EFUSE_0_REG_RCP_SRAM_READING Fld(1,8,AC_MSKB1)//[8:8]
    #define REG_0004_EFUSE_0_REG_RCP_SRAM_BUSY Fld(1,9,AC_MSKB1)//[9:9]
    #define REG_0004_EFUSE_0_REG_RCP_RELOAD Fld(1,10,AC_MSKB1)//[10:10]
    #define REG_0004_EFUSE_0_REG_RCP_SRAM_DIRTY Fld(1,11,AC_MSKB1)//[11:11]
    #define REG_0004_EFUSE_0_REG_RCP_CRC_LOG Fld(1,12,AC_MSKB1)//[12:12]
#define REG_0008_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x208)
    #define REG_0008_EFUSE_0_REG_AUTOLOAD_TRIG_LOCK Fld(1,4,AC_MSKB0)//[4:4]
    #define REG_0008_EFUSE_0_REG_AUTOLOAD_TRIG Fld(1,5,AC_MSKB0)//[5:5]
    #define REG_0008_EFUSE_0_REG_FSM_RST_LOCK Fld(1,6,AC_MSKB0)//[6:6]
    #define REG_0008_EFUSE_0_REG_FSM_RST Fld(1,7,AC_MSKB0)//[7:7]
    #define REG_0008_EFUSE_0_REG_SEL_READ Fld(4,8,AC_MSKB1)//[11:8]
    #define REG_0008_EFUSE_0_REG_EFUSE_IDLE Fld(1,14,AC_MSKB1)//[14:14]
    #define REG_0008_EFUSE_0_REG_EFUSE_WD_AUTO_CLEAN Fld(1,15,AC_MSKB1)//[15:15]
#define REG_000C_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x20C)
    #define REG_000C_EFUSE_0_REG_TRCS Fld(1,0,AC_MSKB0)//[0:0]
    #define REG_000C_EFUSE_0_REG_AT Fld(2,1,AC_MSKB0)//[2:1]
    #define REG_000C_EFUSE_0_REG_RF Fld(8,8,AC_FULLB1)//[15:8]
#define REG_0010_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x210)
    #define REG_0010_EFUSE_0_REG_EFUSE_OUTA_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0014_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x214)
    #define REG_0014_EFUSE_0_REG_EFUSE_OUTA_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0018_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x218)
    #define REG_0018_EFUSE_0_REG_EFUSE_OUTA_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_001C_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x21C)
    #define REG_001C_EFUSE_0_REG_EFUSE_OUTA_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0020_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x220)
    #define REG_0020_EFUSE_0_REG_EFUSE_OUTB_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0024_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x224)
    #define REG_0024_EFUSE_0_REG_EFUSE_OUTB_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0028_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x228)
    #define REG_0028_EFUSE_0_REG_EFUSE_OUTB_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_002C_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x22C)
    #define REG_002C_EFUSE_0_REG_EFUSE_OUTB_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0030_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x230)
    #define REG_0030_EFUSE_0_REG_EFUSE_OUTC_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0034_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x234)
    #define REG_0034_EFUSE_0_REG_EFUSE_OUTC_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0038_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x238)
    #define REG_0038_EFUSE_0_REG_EFUSE_OUTC_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_003C_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x23C)
    #define REG_003C_EFUSE_0_REG_EFUSE_OUTC_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0040_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x240)
    #define REG_0040_EFUSE_0_REG_EFUSE_OUTJ_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0044_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x244)
    #define REG_0044_EFUSE_0_REG_EFUSE_OUTJ_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0048_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x248)
    #define REG_0048_EFUSE_0_REG_EFUSE_OUTJ_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_004C_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x24C)
    #define REG_004C_EFUSE_0_REG_EFUSE_OUTJ_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0050_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x250)
    #define REG_0050_EFUSE_0_REG_EFUSE_OUTK_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0054_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x254)
    #define REG_0054_EFUSE_0_REG_EFUSE_OUTK_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0058_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x258)
    #define REG_0058_EFUSE_0_REG_EFUSE_OUTK_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_005C_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x25C)
    #define REG_005C_EFUSE_0_REG_EFUSE_OUTK_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0080_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x280)
    #define REG_0080_EFUSE_0_REG_GPIO_DATA_ADDR Fld(5,0,AC_MSKB0)//[4:0]
#define REG_0084_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x284)
    #define REG_0084_EFUSE_0_REG_GPIO_PD Fld(1,0,AC_MSKB0)//[0:0]
    #define REG_0084_EFUSE_0_REG_GPIO_PS Fld(1,1,AC_MSKB0)//[1:1]
    #define REG_0084_EFUSE_0_REG_GPIO_PG Fld(1,2,AC_MSKB0)//[2:2]
    #define REG_0084_EFUSE_0_REG_GPIO_LD Fld(1,3,AC_MSKB0)//[3:3]
    #define REG_0084_EFUSE_0_REG_GPIO_CSB Fld(1,4,AC_MSKB0)//[4:4]
    #define REG_0084_EFUSE_0_REG_GPIO_STB Fld(1,5,AC_MSKB0)//[5:5]
#define REG_008C_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x28C)
    #define REG_008C_EFUSE_0_REG_GPIO_PROG_EN Fld(1,0,AC_MSKB0)//[0:0]
    #define REG_008C_EFUSE_0_REG_GPIO_MODE_EN Fld(1,1,AC_MSKB0)//[1:1]
    #define REG_008C_EFUSE_0_REG_GPIO_LATCH_EN Fld(1,2,AC_MSKB0)//[2:2]
    #define REG_008C_EFUSE_0_REG_RE_PROG_PROT Fld(1,8,AC_MSKB1)//[8:8]
#define REG_0090_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x290)
    #define REG_0090_EFUSE_0_REG_WDATA_LO Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0094_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x294)
    #define REG_0094_EFUSE_0_REG_WDATA_HI Fld(16,0,AC_FULLW10)//[15:0]
#define REG_00A0_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2A0)
    #define REG_00A0_EFUSE_0_REG_READ_TRIG Fld(1,13,AC_MSKB1)//[13:13]
    #define REG_00A0_EFUSE_0_REG_ADDR Fld(8,2,AC_MSKW10)//[9:2]
    #define REG_00A0_EFUSE_0_REG_PROG_ENABLE Fld(1,15,AC_MSKB1)//[15:15]
#define REG_00A8_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2A8)
    #define REG_00A8_EFUSE_0_REG_PROG_PD_PS Fld(5,0,AC_MSKB0)//[4:0]
    #define REG_00A8_EFUSE_0_REG_PROG_STB_H Fld(10,6,AC_MSKW10)//[15:6]
#define REG_00AC_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2AC)
    #define REG_00AC_EFUSE_0_REG_MR_READ_STB_H Fld(4,0,AC_MSKB0)//[3:0]
    #define REG_00AC_EFUSE_0_REG_READ_STB_H Fld(3,5,AC_MSKB0)//[7:5]
    #define REG_00AC_EFUSE_0_REG_READ_LATCH Fld(3,10,AC_MSKB1)//[12:10]
#define REG_00B0_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2B0)
    #define REG_00B0_EFUSE_0_REG_RDATA_15_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_00B4_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2B4)
    #define REG_00B4_EFUSE_0_REG_RDATA_31_16 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_00B8_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2B8)
    #define REG_00B8_EFUSE_0_REG_EFUSE_INIT_DEBUG_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_00BC_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2BC)
    #define REG_00BC_EFUSE_0_REG_EFUSE_INIT_DEBUG_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_00C0_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2C0)
    #define REG_00C0_EFUSE_0_REG_EFUSE_OUT_TOP_OVERWRITE_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_00C4_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2C4)
    #define REG_00C4_EFUSE_0_REG_EFUSE_OUT_TOP_OVERWRITE_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_00C8_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2C8)
    #define REG_00C8_EFUSE_0_REG_EFUSE_OUT_TOP_OVERWRITE_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_00CC_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2CC)
    #define REG_00CC_EFUSE_0_REG_EFUSE_OUT_TOP_OVERWRITE_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_00D0_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2D0)
    #define REG_00D0_EFUSE_0_REG_EFUSE_OUT_TOP_FINAL_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_00D4_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2D4)
    #define REG_00D4_EFUSE_0_REG_EFUSE_OUT_TOP_FINAL_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_00D8_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2D8)
    #define REG_00D8_EFUSE_0_REG_EFUSE_OUT_TOP_FINAL_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_00DC_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x2DC)
    #define REG_00DC_EFUSE_0_REG_EFUSE_OUT_TOP_FINAL_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0140_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x340)
    #define REG_0140_EFUSE_0_REG_EFUSE_OUTB_FINAL_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0144_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x344)
    #define REG_0144_EFUSE_0_REG_EFUSE_OUTB_FINAL_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0148_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x348)
    #define REG_0148_EFUSE_0_REG_EFUSE_OUTB_FINAL_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_014C_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x34C)
    #define REG_014C_EFUSE_0_REG_EFUSE_OUTB_FINAL_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0150_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x350)
    #define REG_0150_EFUSE_0_REG_EFUSE_SW_FINAL_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0154_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x354)
    #define REG_0154_EFUSE_0_REG_EFUSE_SW_FINAL_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0158_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x358)
    #define REG_0158_EFUSE_0_REG_EFUSE_SW_FINAL_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_015C_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x35C)
    #define REG_015C_EFUSE_0_REG_EFUSE_SW_FINAL_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0160_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x360)
    #define REG_0160_EFUSE_0_REG_EFUSE_OUTB_OVERWRITE_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0164_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x364)
    #define REG_0164_EFUSE_0_REG_EFUSE_OUTB_OVERWRITE_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0168_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x368)
    #define REG_0168_EFUSE_0_REG_EFUSE_OUTB_OVERWRITE_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_016C_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x36C)
    #define REG_016C_EFUSE_0_REG_EFUSE_OUTB_OVERWRITE_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0170_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x370)
    #define REG_0170_EFUSE_0_REG_EFUSE_OUTB_OVERWRITE_EN Fld(1,0,AC_MSKB0)//[0:0]
    #define REG_0170_EFUSE_0_REG_EFUSE_OUT_TOP_OVERWRITE_EN Fld(1,1,AC_MSKB0)//[1:1]
#define REG_0180_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x380)
    #define REG_0180_EFUSE_0_REG_EFUSE_DUMMY_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0184_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x384)
    #define REG_0184_EFUSE_0_REG_EFUSE_DUMMY_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0188_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x388)
    #define REG_0188_EFUSE_0_REG_EFUSE_RW_DEBUG Fld(16,0,AC_FULLW10)//[15:0]
#define REG_018C_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x38C)
    #define REG_018C_EFUSE_0_REG_TEE_ONEWAY_LOCK Fld(16,0,AC_FULLW10)//[15:0]
#define REG_0190_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x390)
    #define REG_0190_EFUSE_0_REG_EFUSE_DEBUG_BUS Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01A0_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3A0)
    #define REG_01A0_EFUSE_0_REG_EFUSE_SW_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01A4_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3A4)
    #define REG_01A4_EFUSE_0_REG_EFUSE_SW_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01A8_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3A8)
    #define REG_01A8_EFUSE_0_REG_EFUSE_SW_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01AC_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3AC)
    #define REG_01AC_EFUSE_0_REG_EFUSE_SW_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01B0_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3B0)
    #define REG_01B0_EFUSE_0_REG_EFUSE_OUT_ANA_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01B4_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3B4)
    #define REG_01B4_EFUSE_0_REG_EFUSE_OUT_ANA_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01B8_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3B8)
    #define REG_01B8_EFUSE_0_REG_EFUSE_OUT_ANA_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01BC_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3BC)
    #define REG_01BC_EFUSE_0_REG_EFUSE_OUT_ANA_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01C0_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3C0)
    #define REG_01C0_EFUSE_0_REG_EFUSE_OUTM_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01C4_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3C4)
    #define REG_01C4_EFUSE_0_REG_EFUSE_OUTM_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01C8_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3C8)
    #define REG_01C8_EFUSE_0_REG_EFUSE_OUTM_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01CC_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3CC)
    #define REG_01CC_EFUSE_0_REG_EFUSE_OUTM_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01D0_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3D0)
    #define REG_01D0_EFUSE_0_REG_EFUSE_OUTN_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01D4_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3D4)
    #define REG_01D4_EFUSE_0_REG_EFUSE_OUTN_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01D8_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3D8)
    #define REG_01D8_EFUSE_0_REG_EFUSE_OUTN_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01DC_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3DC)
    #define REG_01DC_EFUSE_0_REG_EFUSE_OUTN_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01E0_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3E0)
    #define REG_01E0_EFUSE_0_REG_EFUSE_OUTO_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01E4_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3E4)
    #define REG_01E4_EFUSE_0_REG_EFUSE_OUTO_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01E8_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3E8)
    #define REG_01E8_EFUSE_0_REG_EFUSE_OUTO_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01EC_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3EC)
    #define REG_01EC_EFUSE_0_REG_EFUSE_OUTO_3 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01F0_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3F0)
    #define REG_01F0_EFUSE_0_REG_EFUSE_OUTY_0 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01F4_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3F4)
    #define REG_01F4_EFUSE_0_REG_EFUSE_OUTY_1 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01F8_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3F8)
    #define REG_01F8_EFUSE_0_REG_EFUSE_OUTY_2 Fld(16,0,AC_FULLW10)//[15:0]
#define REG_01FC_EFUSE_0 (HDMIRX_EFUSE_0_BASE + 0x3FC)
    #define REG_01FC_EFUSE_0_REG_EFUSE_OUTY_3 Fld(16,0,AC_FULLW10)//[15:0]

