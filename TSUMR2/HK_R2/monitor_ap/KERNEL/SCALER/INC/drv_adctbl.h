// Excel File version:0.4
// Excel File version:0.4
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (; MStar; Confidential; Information; ) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
//****************************************************
// MST8556T _ADC_Driver
// Excel File version:0.4
// 2011/5/23 16:20
//****************************************************


#ifndef _DRVADCTBL_H_
#define _DRVADCTBL_H_

//   ADC initial table CodeGen Version 1.0
#define DRV_ADC_REG(reg) ((reg>>8)&0xFF), (reg&0xFF)
#define REG_ADDR_SIZE       2
#define REG_MASK_SIZE       1
#define REG_DATA_SIZE       2
typedef enum
{
    ADC_TABLE_INIT_All,
    ADC_TABLE_INIT_NUMS
} ADC_INIT_TYPE;

typedef enum
{
    ADC_TABLE_FreeRunEn_All,
    ADC_TABLE_FreeRunEn_NUMS
} ADC_FreeRunEn_TYPE;

typedef enum
{
    ADC_TABLE_FreeRunDis_All,
    ADC_TABLE_FreeRunDis_NUMS
} ADC_FreeRunDis_TYPE;

typedef enum
{
    ADC_TABLE_PorstEn_All,
    ADC_TABLE_PorstEn_NUMS
} ADC_PorstEn_TYPE;

typedef enum
{
    ADC_TABLE_PorstDis_All,
    ADC_TABLE_PorstDis_NUMS
} ADC_PorstDis_TYPE;

typedef enum
{
    ADC_TABLE_MUX_RGB0_Sync,
    ADC_TABLE_MUX_RGB0_Data,
    ADC_TABLE_MUX_NUMS
} ADC_MUX_TYPE;

typedef enum
{
    ADC_TABLE_SOURCE_RGB,
    ADC_TABLE_SOURCE_YUV,
    ADC_TABLE_SOURCE_SOG,
    ADC_TABLE_SOURCE_YUV_HV,
    ADC_TABLE_SOURCE_NUMS
} ADC_SOURCE_TYPE;

typedef enum
{
    ADC_TABLE_AdcCal_ALL,
    ADC_TABLE_AdcCal_NUMS
} ADC_AdcCal_TYPE;

typedef enum
{
    ADC_TABLE_FREQ_SECTION1,
    ADC_TABLE_FREQ_SECTION2,
    ADC_TABLE_FREQ_SECTION3,
    ADC_TABLE_FREQ_SECTION4,
    ADC_TABLE_FREQ_SECTION5,
    ADC_TABLE_FREQ_SECTION6,
    ADC_TABLE_FREQ_SECTION7,
    ADC_TABLE_FREQ_SECTION8,
    ADC_TABLE_FREQ_SECTION9,
    ADC_TABLE_FREQ_SECTION10,
    ADC_TABLE_FREQ_SECTION11,
    ADC_TABLE_FREQ_SECTION12,
    ADC_TABLE_FREQ_SECTION13,
    ADC_TABLE_FREQ_SECTION14,
    ADC_TABLE_FREQ_SECTION15,
    ADC_TABLE_FREQ_SECTION16,
    ADC_TABLE_FREQ_SECTION17,
    ADC_TABLE_SetMode_NUMS
} ADC_SetMode_TYPE;

typedef enum
{
    ADC_TABLE_PowerDown_NUMS
} ADC_PowerDown_TYPE;

typedef struct
{
    WORD FreqHLimit;
    WORD FreqLLimit;
} ADC_FREQ_RANGE;

#if 0
//#ifdef _DRVADC_C_
//****************************************************
// INIT
//****************************************************
code BYTE MST_ADCINIT_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+ADC_TABLE_INIT_NUMS*REG_DATA_SIZE]=
{                 // Reg           Mask Ignore Value
 { DRV_ADC_REG(REG_ADC_ATOP_04_L), 0xFF, 0x00, 0x00/*$All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_04_H), 0x7F, 0x00, 0x00/*$All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_06_L), 0xFF, 0x00, 0x00/*$All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_45_L), 0x03, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_39_H), 0x10, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_22_L), 0xFF, 0x00, 0x38/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_01_L), 0xF7, 0x00, 0x01/*$All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_01_H), 0x73, 0x00, 0x40/*$All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_02_L), 0x01, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_22_H), 0x02, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_20_L), 0x07, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_27_L), 0x1F, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_28_L), 0x0F, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_29_L), 0x3F, 0x00, 0x20/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_29_H), 0x0C, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_30_L), 0x01, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_07_L), 0x38, 0x00, 0x20/*$All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_11_H), 0x04, 0x00, 0x04/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_44_H), 0x70, 0x00, 0x40/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_47_H), 0x70, 0x00, 0x40/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_50_H), 0x70, 0x00, 0x40/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_55_L), 0x3F, 0x00, 0x00/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_0D_H), 0x1F, 0x00, 0x10/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_0D_L), 0xFF, 0x00, 0x01/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_08_H), 0xFF, 0x00, 0x10/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_18_H), 0x07, 0x00, 0x07/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_19_H), 0x1E, 0x00, 0x00/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_1C_L), 0xFF, 0x00, 0x03/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_1C_H), 0x03, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_1D_L), 0xFF, 0x00, 0xD0/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_1D_H), 0x1F, 0x00, 0x07/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_1E_L), 0xFF, 0x00, 0x60/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_1E_H), 0x3F, 0x00, 0x20/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_1F_L), 0xFF, 0x00, 0xA0/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_1F_H), 0x1F, 0x00, 0x03/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_20_L), 0xFF, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_20_H), 0x3F, 0x00, 0x1C/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_21_L), 0xFF, 0x00, 0x40/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_21_H), 0x1F, 0x00, 0x05/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_22_L), 0xFF, 0x00, 0x4A/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_22_H), 0xFF, 0x00, 0x08/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_23_L), 0xFF, 0x00, 0x00/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_23_H), 0x03, 0x00, 0x01/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_27_L), 0xFF, 0x00, 0x03/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_27_H), 0x03, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_28_L), 0xFF, 0x00, 0xD0/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_28_H), 0x1F, 0x00, 0x07/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_29_L), 0xFF, 0x00, 0x60/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_29_H), 0x3F, 0x00, 0x20/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_2A_L), 0xFF, 0x00, 0xA0/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_2A_H), 0x1F, 0x00, 0x03/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_2B_L), 0xFF, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_2B_H), 0x3F, 0x00, 0x1C/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_2C_L), 0xFF, 0x00, 0x40/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_2C_H), 0x1F, 0x00, 0x05/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_2D_L), 0xFF, 0x00, 0x4A/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_2D_H), 0xFF, 0x00, 0x08/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_2E_L), 0xFF, 0x00, 0x00/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_2E_H), 0x03, 0x00, 0x01/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_31_L), 0xFF, 0x00, 0x03/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_31_H), 0x03, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_32_L), 0xFF, 0x00, 0xD0/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_32_H), 0x1F, 0x00, 0x07/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_33_L), 0xFF, 0x00, 0x60/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_33_H), 0x3F, 0x00, 0x20/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_34_L), 0xFF, 0x00, 0xA0/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_34_H), 0x1F, 0x00, 0x03/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_35_L), 0xFF, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_35_H), 0x3F, 0x00, 0x1C/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_36_L), 0xFF, 0x00, 0x40/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_36_H), 0x1F, 0x00, 0x05/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_37_L), 0xFF, 0x00, 0x4A/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_37_H), 0xFF, 0x00, 0x08/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_38_L), 0xFF, 0x00, 0x00/*$All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_38_H), 0x03, 0x00, 0x01/*$All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_11_H), 0x01, 0x00, 0x01/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_11_H), 0x01, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_0D_L), 0xFF, 0x00, 0x09/*All*/, },
 { DRV_ADC_REG(REG_TABLE_END), 0x00, 0x00, 0x00 }
};

//****************************************************
// FreeRunEn
//****************************************************
code BYTE MST_ADCFreeRunEn_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+ADC_TABLE_FreeRunEn_NUMS*REG_DATA_SIZE]=
{                 // Reg           Mask Ignore Value
 { DRV_ADC_REG(REG_ADC_DTOP_02_L), 0xFF, 0x00, 0x56/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_02_H), 0xFF, 0x00, 0x66/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_03_L), 0xFF, 0x00, 0x66/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_03_H), 0xFF, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_06_L), 0xFF, 0x00, 0x80/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_06_H), 0xFF, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_0A_L), 0x18, 0x00, 0x10/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_0A_L), 0x07, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_0C_L), 0xFF, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_0C_H), 0xFF, 0x00, 0x01/*All*/, },
 { DRV_ADC_REG(REG_TABLE_END), 0x00, 0x00, 0x00 }
};

//****************************************************
// FreeRunDis
//****************************************************
code BYTE MST_ADCFreeRunDis_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+ADC_TABLE_FreeRunDis_NUMS*REG_DATA_SIZE]=
{                 // Reg           Mask Ignore Value
 { DRV_ADC_REG(REG_ADC_DTOP_06_L), 0xFF, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_06_H), 0xFF, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_02_L), 0xFF, 0x00, 0x82/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_02_H), 0xFF, 0x00, 0x09/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_03_L), 0xFF, 0x00, 0x05/*All*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_03_H), 0xFF, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_TABLE_END), 0x00, 0x00, 0x00 }
};

//****************************************************
// PorstEn
//****************************************************
code BYTE MST_ADCPorstEn_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+ADC_TABLE_PorstEn_NUMS*REG_DATA_SIZE]=
{                 // Reg           Mask Ignore Value
 { DRV_ADC_REG(REG_ADC_ATOP_09_L), 0x20, 0x00, 0x20/*All*/, },
 { DRV_ADC_REG(REG_TABLE_END), 0x00, 0x00, 0x00 }
};

//****************************************************
// PorstDis
//****************************************************
code BYTE MST_ADCPorstDis_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+ADC_TABLE_PorstDis_NUMS*REG_DATA_SIZE]=
{                 // Reg           Mask Ignore Value
 { DRV_ADC_REG(REG_ADC_ATOP_09_L), 0x20, 0x00, 0x00/*All*/, },
 { DRV_ADC_REG(REG_TABLE_END), 0x00, 0x00, 0x00 }
};

//****************************************************
// MUX
//****************************************************
code BYTE MST_ADCMUX_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+ADC_TABLE_MUX_NUMS*REG_DATA_SIZE]=
{                 // Reg           Mask Ignore Value
 { DRV_ADC_REG(REG_ADC_ATOP_01_L), 0x06, 0x00, 0x00/*RGB0_Sync*/,
                                         0x01, 0x00/*RGB0_Data*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_01_H), 0x30, 0x01, 0x00/*RGB0_Sync*/,
                                         0x00, 0x00/*RGB0_Data*/, },
 { DRV_ADC_REG(REG_ADC_ATOP_28_L), 0x0F, 0x00, 0x00/*RGB0_Sync*/,
                                         0x00, 0x00/*RGB0_Data*/, },
 { DRV_ADC_REG(REG_TABLE_END), 0x00, 0x00, 0x00 }
};

//****************************************************
// SOURCE
//****************************************************
code BYTE MST_ADCSOURCE_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+ADC_TABLE_SOURCE_NUMS*REG_DATA_SIZE]=
{                 // Reg           Mask Ignore Value
 { DRV_ADC_REG(REG_ADC_DTOP_07_L), 0x40, 0x00, 0x00/*RGB*/,
                                         0x00, 0x40/*YUV*/,
                                         0x00, 0x40/*SOG*/,
                                         0x00, 0x00/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_1B_L), 0xFF, 0x00, 0x20/*RGB*/,
                                         0x00, 0x00/*YUV*/,
                                         0x00, 0x20/*SOG*/,
                                         0x00, 0x00/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_1B_H), 0x03, 0x00, 0x00/*RGB*/,
                                         0x00, 0x02/*YUV*/,
                                         0x00, 0x00/*SOG*/,
                                         0x00, 0x02/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_26_L), 0xFF, 0x00, 0x20/*RGB*/,
                                         0x00, 0x20/*YUV*/,
                                         0x00, 0x20/*SOG*/,
                                         0x00, 0x20/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_26_H), 0x03, 0x00, 0x00/*RGB*/,
                                         0x00, 0x00/*YUV*/,
                                         0x00, 0x00/*SOG*/,
                                         0x00, 0x00/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_30_L), 0xFF, 0x00, 0x20/*RGB*/,
                                         0x00, 0x00/*YUV*/,
                                         0x00, 0x20/*SOG*/,
                                         0x00, 0x00/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_30_H), 0x03, 0x00, 0x00/*RGB*/,
                                         0x00, 0x02/*YUV*/,
                                         0x00, 0x00/*SOG*/,
                                         0x00, 0x02/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_44_L), 0xFF, 0x00, 0x20/*RGB*/,
                                         0x00, 0x00/*YUV*/,
                                         0x00, 0x20/*SOG*/,
                                         0x00, 0x00/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_44_H), 0x03, 0x00, 0x00/*RGB*/,
                                         0x00, 0x02/*YUV*/,
                                         0x00, 0x00/*SOG*/,
                                         0x00, 0x02/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_47_L), 0xFF, 0x00, 0x20/*RGB*/,
                                         0x00, 0x00/*YUV*/,
                                         0x00, 0x20/*SOG*/,
                                         0x00, 0x00/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_47_H), 0x03, 0x00, 0x00/*RGB*/,
                                         0x00, 0x00/*YUV*/,
                                         0x00, 0x00/*SOG*/,
                                         0x00, 0x00/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_50_L), 0xFF, 0x00, 0x20/*RGB*/,
                                         0x00, 0x00/*YUV*/,
                                         0x00, 0x20/*SOG*/,
                                         0x00, 0x00/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_50_H), 0x03, 0x00, 0x00/*RGB*/,
                                         0x00, 0x02/*YUV*/,
                                         0x00, 0x00/*SOG*/,
                                         0x00, 0x02/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_46_L), 0xFF, 0x00, 0x00/*RGB*/,
                                         0x00, 0x00/*YUV*/,
                                         0x00, 0x00/*SOG*/,
                                         0x00, 0x00/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_46_H), 0x67, 0x00, 0x20/*$RGB*/,
                                         0x00, 0x22/*$YUV*/,
                                         0x00, 0x20/*$SOG*/,
                                         0x00, 0x22/*$YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_49_L), 0xFF, 0x00, 0x00/*RGB*/,
                                         0x00, 0x40/*YUV*/,
                                         0x00, 0x00/*SOG*/,
                                         0x00, 0x40/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_49_H), 0x67, 0x00, 0x20/*$RGB*/,
                                         0x00, 0x20/*$YUV*/,
                                         0x00, 0x20/*$SOG*/,
                                         0x00, 0x20/*$YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_52_L), 0xFF, 0x00, 0x00/*RGB*/,
                                         0x00, 0x00/*YUV*/,
                                         0x00, 0x00/*SOG*/,
                                         0x00, 0x00/*YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_52_H), 0x67, 0x00, 0x20/*$RGB*/,
                                         0x00, 0x22/*$YUV*/,
                                         0x00, 0x20/*$SOG*/,
                                         0x00, 0x22/*$YUV_HV*/, },
 { DRV_ADC_REG(REG_ADC_DTOP_FE_L), 0xFF, 0x00, 0x05/*RGB*/,
                                         0x00, 0x05/*YUV*/,
                                         0x00, 0x05/*SOG*/,
                                         0x00, 0x05/*YUV_HV*/, },
 { DRV_ADC_REG(REG_TABLE_END), 0x00, 0x00, 0x00 }
};

//****************************************************
// AdcCal
//****************************************************
code BYTE MST_ADCAdcCal_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+ADC_TABLE_AdcCal_NUMS*REG_DATA_SIZE]=
{                 // Reg           Mask Ignore Value
 { DRV_ADC_REG(REG_TABLE_END), 0x00, 0x00, 0x00 }
};

//****************************************************
// SetMode
//****************************************************
code ADC_FREQ_RANGE MST_ADC_FreqRange_TBL[]=
{
    //H-Limit,  L-Limit
    { 0x1000,   0x012C},/*ADC_FREQ_SECTION1*/
    { 0x012C,   0x00FA},/*ADC_FREQ_SECTION2*/
    { 0x00FA,   0x00C8},/*ADC_FREQ_SECTION3*/
    { 0x00C8,   0x00B4},/*ADC_FREQ_SECTION4*/
    { 0x00B4,   0x00A0},/*ADC_FREQ_SECTION5*/
    { 0x00A0,   0x008C},/*ADC_FREQ_SECTION6*/
    { 0x008C,   0x0078},/*ADC_FREQ_SECTION7*/
    { 0x0078,   0x0064},/*ADC_FREQ_SECTION8*/
    { 0x0064,   0x0050},/*ADC_FREQ_SECTION9*/
    { 0x0050,   0x0046},/*ADC_FREQ_SECTION10*/
    { 0x0046,   0x003C},/*ADC_FREQ_SECTION11*/
    { 0x003C,   0x002D},/*ADC_FREQ_SECTION12*/
    { 0x002D,   0x0028},/*ADC_FREQ_SECTION13*/
    { 0x0028,   0x001E},/*ADC_FREQ_SECTION14*/
    { 0x001E,   0x0014},/*ADC_FREQ_SECTION15*/
    { 0x0014,   0x000F},/*ADC_FREQ_SECTION16*/
    { 0x000F,   0x0005},/*ADC_FREQ_SECTION17*/
};

code BYTE MST_ADCSetModeYUV_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+ADC_TABLE_SetMode_NUMS*REG_DATA_SIZE]=
{                 // Reg           Mask Ignore Value
 { DRV_ADC_REG(REG_ADC_ATOP_23_L), 0x0F, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x02/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x04/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x05/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x06/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x07/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x09/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x0A/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x0A/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x0B/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x0B/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x0C/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x0C/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x0D/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x0E/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_23_L), 0xF0, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x50/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x60/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x70/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x80/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x90/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0xA0/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0xA0/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0xB0/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0xB0/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0xC0/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0xC0/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0xD0/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0xE0/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_23_H), 0x0F, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x02/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x04/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x05/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x06/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x07/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x09/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x0A/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x0A/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x0B/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x0B/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x0C/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x0C/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x0D/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x0E/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_23_H), 0xF0, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x50/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x60/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x70/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x80/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x90/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0xA0/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0xA0/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0xB0/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0xB0/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0xC0/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0xC0/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0xD0/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0xE0/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_24_L), 0x0F, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x02/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x04/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x05/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x06/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x07/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x09/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x0A/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x0A/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x0B/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x0B/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x0C/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x0C/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x0D/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x0E/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_24_L), 0xF0, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x50/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x60/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x70/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x80/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x90/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0xA0/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0xA0/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0xB0/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0xB0/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0xC0/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0xC0/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0xD0/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0xE0/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_DTOP_17_H), 0x0F, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_DTOP_17_L), 0xFF, 0x00, 0x45/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x45/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x45/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x45/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x45/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x45/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x45/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x45/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x45/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x45/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x45/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_DTOP_18_L), 0xFF, 0x00, 0x40/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_DTOP_19_H), 0x60, 0x00, 0x40/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_0A_L), 0x07, 0x00, 0x01/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_0A_L), 0x18, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x18/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x18/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x18/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_0A_L), 0x20, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_09_H), 0x03, 0x00, 0x03/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x02/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x02/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x02/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_TABLE_END), 0x00, 0x00, 0x00 }
};

code BYTE MST_ADCSetModeRGB_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+ADC_TABLE_SetMode_NUMS*REG_DATA_SIZE]=
{                 // Reg           Mask Ignore Value
 { DRV_ADC_REG(REG_ADC_ATOP_23_L), 0x0F, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x02/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x04/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x05/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x06/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x07/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x09/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x0A/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x0B/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x0C/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x0C/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x0D/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_23_L), 0xF0, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x50/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x60/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x70/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x80/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x90/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0xA0/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0xB0/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0xC0/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0xC0/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0xD0/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_23_H), 0x0F, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x02/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x04/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x05/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x06/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x07/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x09/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x0A/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x0B/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x0C/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x0C/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x0D/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_23_H), 0xF0, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x50/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x60/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x70/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x80/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x90/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0xA0/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0xB0/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0xC0/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0xC0/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0xD0/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_24_L), 0x0F, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x02/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x04/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x05/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x06/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x07/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x09/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x0A/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x0B/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x0C/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x0C/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x0D/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_24_L), 0xF0, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x50/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x60/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x70/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x80/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x90/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0xA0/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0xB0/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0xC0/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0xC0/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0xD0/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_DTOP_17_H), 0x0F, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_DTOP_17_L), 0xFF, 0x00, 0x30/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x30/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_DTOP_18_L), 0xFF, 0x00, 0x40/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_DTOP_19_H), 0x60, 0x00, 0x40/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x40/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_0A_L), 0x07, 0x00, 0x01/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_0A_L), 0x18, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x10/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x18/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x18/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x18/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_0A_L), 0x20, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x20/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_ADC_ATOP_09_H), 0x03, 0x00, 0x03/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x02/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x02/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x02/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_TABLE_END), 0x00, 0x00, 0x00 }
};

code BYTE MST_ADCSetModeYUV_Y_TBL[][REG_ADDR_SIZE+REG_MASK_SIZE+ADC_TABLE_SetMode_NUMS*REG_DATA_SIZE]=
{                 // Reg           Mask Ignore Value
 { DRV_ADC_REG(REG_ADC_ATOP_23_H), 0x0F, 0x00, 0x00/*ADC_TABLE_FREQ_SECTION1*/,
                                         0x00, 0x00/*ADC_TABLE_FREQ_SECTION2*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION3*/,
                                         0x00, 0x01/*ADC_TABLE_FREQ_SECTION4*/,
                                         0x00, 0x02/*ADC_TABLE_FREQ_SECTION5*/,
                                         0x00, 0x03/*ADC_TABLE_FREQ_SECTION6*/,
                                         0x00, 0x04/*ADC_TABLE_FREQ_SECTION7*/,
                                         0x00, 0x05/*ADC_TABLE_FREQ_SECTION8*/,
                                         0x00, 0x06/*ADC_TABLE_FREQ_SECTION9*/,
                                         0x00, 0x07/*ADC_TABLE_FREQ_SECTION10*/,
                                         0x00, 0x08/*ADC_TABLE_FREQ_SECTION11*/,
                                         0x00, 0x09/*ADC_TABLE_FREQ_SECTION12*/,
                                         0x00, 0x0A/*ADC_TABLE_FREQ_SECTION13*/,
                                         0x00, 0x0B/*ADC_TABLE_FREQ_SECTION14*/,
                                         0x00, 0x0C/*ADC_TABLE_FREQ_SECTION15*/,
                                         0x00, 0x0C/*ADC_TABLE_FREQ_SECTION16*/,
                                         0x00, 0x0D/*ADC_TABLE_FREQ_SECTION17*/,},
 { DRV_ADC_REG(REG_TABLE_END), 0x00, 0x00, 0x00 }
};

//****************************************************
// PowerDown
//****************************************************


#endif //_MSDAC_C_


#endif
