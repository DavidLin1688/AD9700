////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  [Doxygen]
/// @file msAPI_OSD.h
/// This file includes MStar application interface for OSD
/// @brief API for OSD functions
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_OSD_RESOURCE_C

/********************************************************************************/
/*                    Header Files                                                */
/********************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "datatype.h"
#include "MsTypes.h"

#include "apiGOP.h"
#include "msAPI_OSD_Resource.h"
#include "msAPI_Memory.h"
#include "msAPI_Font.h"
//#include "msAPI_Timer.h"
#include "debug.h"
#include "MsTypes.h"
#include "drvBDMA.h"

#include "sysinfo.h"

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

#define APIOSDSRC_DBG(x) //x
#define SUPPORT_FAST_DRAWTEXT 0

static OSD_RESOURCE_FONT_INFO                _FontTable[E_RES_GROUP_MAX][MAX_FONT];
static OSD_RESOURCE_BITMAP_INFO              _BitmapTable[E_RES_GROUP_MAX][MAX_BITMAP];
static E_RES_GROUP                         _enResGroup = E_RES_GROUP_1ST;
CHAR_CODEMAP_BLOCK  g_au16CodemapBlock ;
OSD_RESOURCE_FONT_INFO GEFontTable;
U8 font_count=0;


static void LoadCodemap(CHAR_CODEMAP_BLOCK  *pCodemapBlock,  U8 *u32Addr)
{
//    GE_GET_ReSource();
    pCodemapBlock->u16StartCode = (u32Addr[1] << 8) + u32Addr[0];
    pCodemapBlock->u16EndCode =   (u32Addr[3] << 8) + u32Addr[2];
    pCodemapBlock->u16StartIndex = (u32Addr[5] << 8) + u32Addr[4];
//    GE_Free_ReSource();
}

/******************************************************************************/
/// API for get font height::
/// Get font height
/// @param font_handle \b IN font handle
/// @return U8: Font height
/******************************************************************************/
U16 msAPI_OSD_RESOURCE_GetFontHeight(FONTHANDLE font_handle)
{
    OSD_RESOURCE_FONT_INFO finfo;
    //GE_GET_ReSource();
    //MDrv_MIU_Get_FontInfo(font_handle, &finfo);
    if ((font_handle < MAX_FONT) && (font_handle >= 0))
    {
        memcpy(&finfo, &_FontTable[_enResGroup][font_handle], sizeof(OSD_RESOURCE_FONT_INFO));
        return finfo.height;
    }


    //GE_Free_ReSource();
    return 0;

}

//-------------------------------------------------------------------------------------------------
/// load PE font info
/// @param addr   \b IN: address
/// @param len    \b IN: total size of font
/// @param width  \b IN: width
/// @param height \b IN: height
/// @param pBBox  \b IN: pointer to bounding box
/// @image html BoundingBox.jpg "in_line & ini_dis"
/// @param fmt    \b IN: color format (only 3 font mode)
///                      GFX_FMT_I1 :  I1 mode\n
///                      GFX_FMT_I2 :  I2 mode\n
///                      GFX_FMT_I4 :  I4 mode\n
/// @return  font handle (  fail to create handle will return ERR_HANDLE )
//-------------------------------------------------------------------------------------------------
FONTHANDLE msAPI_OSD_RESOURCE_LoadFont (MS_U32 start_addr, MS_U32 glyph_addr, MS_U32 bbox_addr, MS_U32 codemap_addr, MS_U16 u16char_num, MS_U16 codemap_block_num, MS_U8 width, MS_U8 height, MS_U8 bpp, MS_U16 char_glyph_bytes, MS_U32 pitch, MEMTYPE memory_type)
{
//    MS_S8 s8count;
    MS_U8 pitch_bits;

    APIOSDSRC_DBG( printf( "msAPI_OSD_RESOURCE_LoadFont\n" ) );

    pitch_bits = pitch*8;

    GEFontTable.hw_pitch = pitch;
    GEFontTable.start_addr = start_addr;
    GEFontTable.glyph_addr = glyph_addr;
    GEFontTable.bbox_addr = bbox_addr;
    GEFontTable.char_num = u16char_num;
    GEFontTable.width = width;
    GEFontTable.height = height;
    if (bpp == 3)
    {
        // 3 I1
        GEFontTable.pitch = (width + (pitch_bits-1)) / pitch_bits;   // GE hardware is 2-bytes alignment
        if (char_glyph_bytes == 0)
        {
            GEFontTable.char_glyph_bytes = GEFontTable.pitch * (pitch_bits/8) * height * 3; // 3 1-bit tables
        }
        else
        {
            GEFontTable.char_glyph_bytes = char_glyph_bytes;
        }
    }
    else
    {
        //GEFontTable.pitch = (width + (pitch_bits-1)) / pitch_bits * bpp; // GE hardware is 2-bytes alignment
        GEFontTable.pitch = (width*bpp + (pitch_bits-1)) / pitch_bits * pitch; // GE hardware is 2-bytes alignment
        //GEFontTable[font_count].pitch = (width*bpp + 15) / 16; // GE hardware is 2-bytes alignment
        if (char_glyph_bytes == 0)
        {
            GEFontTable.char_glyph_bytes = GEFontTable.pitch * (pitch_bits/8) * height;
        }
        else
        {
            GEFontTable.char_glyph_bytes = char_glyph_bytes;
        }
    }

    GEFontTable.inUsed = TRUE;

    GEFontTable.bpp = bpp;
    GEFontTable.fmt = BMP_FMT_I2;

    if(bpp == 1)
        GEFontTable.fmt = BMP_FMT_I1;
    if(bpp == 2)
        GEFontTable.fmt = BMP_FMT_I2;
    if(bpp == 4)
        GEFontTable.fmt = BMP_FMT_I4;



    GEFontTable.codemap_block_num = codemap_block_num;
    GEFontTable.codemap_addr = codemap_addr;

    GEFontTable.memory_type = memory_type;



//    MDrv_MIU_Set_FontInfo(font_count, &GEFontTable);

    memcpy(&_FontTable[_enResGroup][font_count], &GEFontTable, sizeof(OSD_RESOURCE_FONT_INFO));

 //   printf("LOADTEXT: %x, %x, %x, %x, %x, %x, %x, %x, %x\n", font_count, _FontTable[font_count].glyph_addr, _FontTable[font_count].fmt, _FontTable[font_count].height, _FontTable[font_count].char_glyph_bytes,_FontTable[font_count].char_num,
//       _FontTable[font_count].bbox_addr, _FontTable[font_count].pitch , _FontTable[font_count].width );


    return font_count++;
}

//-------------------------------------------------------------------------------------------------
/// free PE font info
/// @param handle \b IN: font handle
/// @return GFX_SUCCESS - Success
/// @return GFX_INVALID_FONT_HANDLE - Invalid font handle
//-------------------------------------------------------------------------------------------------
OSDSRC_Result msAPI_OSD_RESOURCE_FreeFont(FONTHANDLE handle)
{
    if ((handle < MAX_FONT) && (handle >= 0))
    {
        _FontTable[_enResGroup][handle].inUsed = false;
        _FontTable[_enResGroup][handle].bbox_addr = INVALID_ADDR;
        return OSDSRC_SUCCESS;
    }
    return OSDSRC_INVALID_BMP_HANDLE;
}


OSDSRC_Result MDrv_GE_GetFontInfo(FONTHANDLE handle, FONT_INFO* pinfo)
{
    if ((handle < MAX_FONT) && (handle >= 0))
    {
        memcpy(pinfo, &_FontTable[_enResGroup][handle], sizeof(FONT_INFO));

        return OSDSRC_SUCCESS;
    }
    return OSDSRC_INVALID_BMP_HANDLE;
}

//-------------------------------------------------------------------------------------------------
/// Get PE font info
/// @param handle \b IN: font handle
/// @param pinfo \b OUT: font information.
/// @return GFX_SUCCESS - Success
/// @return GFX_INVALID_FONT_HANDLE - Invalid font handle
//-------------------------------------------------------------------------------------------------
OSDSRC_Result msAPI_OSD_RESOURCE_GetFontInfo(FONTHANDLE handle, OSD_RESOURCE_FONT_INFO* pinfo)
{
    if ((handle < MAX_FONT) && (handle >= 0))
    {
#if 0
        pinfo->glyph_addr     = _FontTable[handle].glyph_addr;
        pinfo->height   = _FontTable[handle].height;
        pinfo->len      = _FontTable[handle].len;
        pinfo->offset   = _FontTable[handle].offset;
        pinfo->width    = _FontTable[handle].width;
        pinfo->pitch    = _FontTable[handle].pitch;
        pinfo->fmt      = _FontTable[handle].fmt;
        pinfo->bbox_addr    = _FontTable[handle].bbox_addr;
#endif
        memcpy(pinfo, &_FontTable[_enResGroup][handle], sizeof(OSD_RESOURCE_FONT_INFO));
        return OSDSRC_SUCCESS;
    }
    return OSDSRC_INVALID_FONT_HANDLE;
}

//-------------------------------------------------------------------------------------------------
/// Get PE bitmap info
/// @param handle \b IN: bitmap handle
/// @param pinfo \b OUT: bitmap information.
/// @return GFX_SUCCESS - Success
/// @return GFX_INVALID_BMP_HANDLE - Invalid Bitmap handle
//-------------------------------------------------------------------------------------------------
OSDSRC_Result msAPI_OSD_RESOURCE_GetBitmapInfo(BMPHANDLE handle, OSD_RESOURCE_BITMAP_INFO* pinfo)
{
    if ((handle < MAX_BITMAP) && (handle >= 0))
    {
#if 0
        pinfo->addr    = _BitmapTable[handle].addr;
        pinfo->len     = _BitmapTable[handle].len;
        pinfo->inUsed  = _BitmapTable[handle].inUsed;
        pinfo->width   = _BitmapTable[handle].width;
        pinfo->height  = _BitmapTable[handle].height;
        pinfo->pitch   = _BitmapTable[handle].pitch;
        pinfo->fmt     = _BitmapTable[handle].fmt;
#endif
        memcpy(pinfo, &_BitmapTable[_enResGroup][handle], sizeof(OSD_RESOURCE_BITMAP_INFO));


        return OSDSRC_SUCCESS;
    }
    return OSDSRC_INVALID_BMP_HANDLE;
}

//-------------------------------------------------------------------------------------------------
/// Get PE font info
/// @param handle \b IN: font handle
/// @param pinfo \b OUT: font information.
/// @return GFX_SUCCESS - Success
/// @return GFX_INVALID_FONT_HANDLE - Invalid font handle
//-------------------------------------------------------------------------------------------------
MS_U32 msAPI_OSD_RESOURCE_GetFontInfoGFX(FONTHANDLE handle, GFX_FontInfo* pinfo)
{
    if ((handle < MAX_FONT) && (handle >= 0))
    {
        pinfo->addr     = _FontTable[_enResGroup][handle].glyph_addr;
        pinfo->height   = _FontTable[_enResGroup][handle].height;
        pinfo->offset   = _FontTable[_enResGroup][handle].char_glyph_bytes;
        pinfo->width    = _FontTable[_enResGroup][handle].width;
        pinfo->pitch    = _FontTable[_enResGroup][handle].pitch;
        pinfo->pBBox    = (GFX_GlyphBbox*)_FontTable[_enResGroup][handle].bbox_addr;
        pinfo->len      = _FontTable[_enResGroup][handle].char_glyph_bytes;
        pinfo->inUsed   = _FontTable[_enResGroup][handle].inUsed;

        pinfo->fmt = GFX_FMT_I2;
        if(_FontTable[_enResGroup][handle].fmt == BMP_FMT_I1)
            pinfo->fmt = GFX_FMT_I1;
        else if(_FontTable[_enResGroup][handle].fmt == BMP_FMT_I2)
            pinfo->fmt = GFX_FMT_I2;
        else if(_FontTable[_enResGroup][handle].fmt == BMP_FMT_I4)
            pinfo->fmt = GFX_FMT_I4;
//printf("[Font] Group = %d, width = %d, height = %d\n", _enResGroup, pinfo->width, pinfo->height);
        return OSDSRC_SUCCESS;
    }
    return OSDSRC_INVALID_FONT_HANDLE;
}



//-------------------------------------------------------------------------------------------------
/// Get PE bitmap info
/// @param handle \b IN: bitmap handle
/// @param pinfo \b OUT: bitmap information.
/// @return GFX_SUCCESS - Success
/// @return GFX_INVALID_BMP_HANDLE - Invalid Bitmap handle
//-------------------------------------------------------------------------------------------------
MS_U32 msAPI_OSD_RESOURCE_GetBitmapInfoGFX(BMPHANDLE handle, GFX_BitmapInfo* pinfo)
{

    if ((handle < MAX_BITMAP) && (handle >= 0))
    {
        pinfo->addr    = _BitmapTable[_enResGroup][handle].addr;
        pinfo->len     = _BitmapTable[_enResGroup][handle].len;
        pinfo->inUsed  = _BitmapTable[_enResGroup][handle].inUsed;
        pinfo->width   = _BitmapTable[_enResGroup][handle].width;
        pinfo->height  = _BitmapTable[_enResGroup][handle].height;
        pinfo->pitch   = _BitmapTable[_enResGroup][handle].pitch;
        pinfo->fmt     = (GFX_Buffer_Format)_BitmapTable[_enResGroup][handle].fmt;
        return OSDSRC_SUCCESS;
    }
    return OSDSRC_INVALID_BMP_HANDLE;
}



/******************************************************************************/
/// Get X-tuple of the glyph bounding box: (x0, width)
/// @param handle \b IN Font handle
/// @param u16Unicode \b IN Character Unicode
/// @param *pGlyphBBox_X \b IN Pointer to FONT_BBOX_X to return the X-direction font bounding box
/******************************************************************************/
OSDSRC_Result msAPI_OSD_RESOURCE_GetBBox_X(FONTHANDLE handle, MS_U16 u16Unicode, OSDSRC_GLYPH_BBOX_X *pGlyphBBox_X)
{
    MS_U16 u16GlyphIndex;
    OSDSRC_GLYPH_BBOX *pBoxX;

//    GE_GET_ReSource();

    u16GlyphIndex = msAPI_OSD_RESOURCE_UnicodeToIndex(handle, u16Unicode);

    pBoxX = (OSDSRC_GLYPH_BBOX*)_PA2VA(_FontTable[_enResGroup][handle].bbox_addr);
//    MDrv_MIU_Get_FontInfo(handle, &GEFontTable);

    if (u16GlyphIndex != ERR_NULL_INDEX)
    {
       // pBoxX = (GFX_GlyphBbox_X *)(GEFontTable.bbox_addr + (u16GlyphIndex << 2));
        //pGlyphBBox_X->u8X0 = pBoxX->u8X0;
        pGlyphBBox_X->u8Width = pBoxX[u16GlyphIndex].u8Width;
        pGlyphBBox_X->u8X0 =  pBoxX[u16GlyphIndex].u8X0;
    }
    else
    {
        pGlyphBBox_X->u8X0 = 0;
        pGlyphBBox_X->u8Width = 0;
    }

//    GE_Free_ReSource();
    return OSDSRC_SUCCESS;
}


/******************************************************************************/
/// Get glyph display information
/// @param handle \b IN Font handle
/// @param u16Unicode \b IN Character Unicode
/// @param *pGlyphDispInfo \b IN Pointer to GLYPH_DISP_INFO to return the glyph display information
/******************************************************************************/
void msAPI_OSD_RESOURCE_GetGlyphDispInfo(FONTHANDLE handle, U16 u16Unicode, OSDSRC_GLYPH_DISP_INFO *pGlyphDispInfo)
{
    OSDSRC_GLYPH_BBOX_X *pBoxX;

    pGlyphDispInfo->u16Index = msAPI_OSD_RESOURCE_UnicodeToIndex(handle, u16Unicode);


    if (_FontTable[_enResGroup][handle].bbox_addr == INVALID_ADDR)
    {
        pGlyphDispInfo->u8X0 = 0;
        pGlyphDispInfo->u8Width = _FontTable[_enResGroup][handle].width;
    }
    else if(pGlyphDispInfo->u16Index == ERR_NULL_INDEX)
    {
        pGlyphDispInfo->u8X0 = 0;
        pGlyphDispInfo->u8Width = 0;
    }
    else
    {
        pBoxX = (OSDSRC_GLYPH_BBOX_X *)(_PA2VA((U32)(_FontTable[_enResGroup][handle].bbox_addr)) + ((U32)pGlyphDispInfo->u16Index * 4));
        pGlyphDispInfo->u8X0 = pBoxX->u8X0;
        pGlyphDispInfo->u8Width = pBoxX->u8Width;
    }

    #if (SUPPORT_S4_OVERLAY_FONT)
    pGlyphDispInfo->overlap_info.s8Xoffset=0;
    pGlyphDispInfo->overlap_info.s8Yoffset=0;
    #endif
}
/******************************************************************************/
/// Conversion of Unicode to glyph index
/// @param handle \b IN Font handle
/// @param u16Unicode \b IN Character Unicode
/// @return Glyph index
/******************************************************************************/
U16 msAPI_OSD_RESOURCE_UnicodeToIndex(FONTHANDLE handle, MS_U16 u16Unicode)
{
    MS_U16 u16CodemapBlockNum;
    MS_U16 u16CodemapBlock_left, u16CodemapBlock_right, u16CodemapBlock_middle;
    MS_U16 u16GlyphIndex;
    MS_U32 u32CodemapAddr;
    MS_U32 u32AddrTemp;
    MS_U8  u8MaxLoop;  // To advoid infinite while-loop

//    GE_GET_ReSource();

    //MDrv_MIU_Get_FontInfo(handle, &GEFontTable);
    u32CodemapAddr =  _PA2VA(_FontTable[_enResGroup][handle].codemap_addr); //GEFontTable.codemap_addr;
    u16CodemapBlockNum =  _FontTable[_enResGroup][handle].codemap_block_num;

    if (u32CodemapAddr == 0 || u16CodemapBlockNum == 0)
    {
        u16GlyphIndex = u16Unicode;
//        GE_Free_ReSource();
        return u16GlyphIndex;
    }
    else
    {
        // Binary search

        u8MaxLoop = 0;
        u16GlyphIndex = 0;

       #if SUPPORT_FAST_DRAWTEXT
        if (u16Unicode >=g_au16CodemapBlock.u16StartCode && u16Unicode <= g_au16CodemapBlock.u16EndCode && handle==g_u8PreFontHandle) {
                u16GlyphIndex = u16Unicode - g_au16CodemapBlock.u16StartCode + g_au16CodemapBlock.u16StartIndex;
//                 GE_Free_ReSource();
                return u16GlyphIndex;
        }
        else if (u16Unicode <= 255)
    #else
    if (u16Unicode <= 255)
    #endif
        {
            // Special check for ASCII-255 to see if in the first block
            LoadCodemap(&g_au16CodemapBlock, (U8 *)u32CodemapAddr);
            //MDrv_MIU_SDRAM2VARCopy(u32CodemapAddr  ,(U8*)&g_au16CodemapBlock , sizeof(c) );
            //printf("\n unicode<255");
             #if SUPPORT_FAST_DRAWTEXT
            u32AddrTemp = u32CodemapAddr + (1 * sizeof(CHAR_CODEMAP_BLOCK));
             #else
            //u32AddrTemp = u32CodemapAddr + (0 * sizeof(CHAR_CODEMAP_BLOCK));
            //u32AddrTemp >>= 3;
            u32AddrTemp = u32CodemapAddr + (1 * sizeof(CHAR_CODEMAP_BLOCK));

            // Start copy
//            XBYTE[FLH2MIU_CMD] = MIU_DMA_SDRAM2SRAM;
             //printf("\n  1st g_au16CodemapBlock.u16StartCode : %u",g_au16CodemapBlock.u16StartCode);
             //printf("\n  1st g_au16CodemapBlock.u16EndCode : %u",g_au16CodemapBlock.u16EndCode);
             #endif
            if (u16Unicode >= g_au16CodemapBlock.u16StartCode && u16Unicode <= g_au16CodemapBlock.u16EndCode)
            {
                // Found
                u16GlyphIndex = u16Unicode - g_au16CodemapBlock.u16StartCode + g_au16CodemapBlock.u16StartIndex;
                // Make "left" be greater that "right" since we have found
                u16CodemapBlock_left = u16CodemapBlockNum;
          //g_u16PreFontBlockStartCode=g_au16CodemapBlock.u16StartCode;
          //g_u16PreFontBlockEndCode=g_au16CodemapBlock.u16EndCode;
          #if SUPPORT_FAST_DRAWTEXT
          g_u8PreFontHandle=handle;
          #endif
//                GE_Free_ReSource();
                return u16GlyphIndex;
            }
        else
        {
            //LoadCodemap(&g_au16CodemapBlock, (U8 *)u32CodemapAddr);
            LoadCodemap(&g_au16CodemapBlock, (U8 *)u32AddrTemp);
             //MDrv_MIU_SDRAM2VARCopy(u32AddrTemp  ,(U8*)&g_au16CodemapBlock , sizeof(CHAR_CODEMAP_BLOCK) );

            if (u16Unicode >= g_au16CodemapBlock.u16StartCode && u16Unicode <= g_au16CodemapBlock.u16EndCode)
            {
             //printf("\n  2nd g_au16CodemapBlock.u16StartCode : %u",g_au16CodemapBlock.u16StartCode);
             //printf("\n  2nd g_au16CodemapBlock.u16EndCode : %u",g_au16CodemapBlock.u16EndCode);
                // Found
                u16GlyphIndex = u16Unicode - g_au16CodemapBlock.u16StartCode + g_au16CodemapBlock.u16StartIndex;
                // Make "left" be greater that "right" since we have found
                u16CodemapBlock_left = u16CodemapBlockNum;
          //g_u16PreFontBlockStartCode=g_au16CodemapBlock.u16StartCode;
         // g_u16PreFontBlockEndCode=g_au16CodemapBlock.u16EndCode;
         #if SUPPORT_FAST_DRAWTEXT
          g_u8PreFontHandle=handle;
         #endif
//                 GE_Free_ReSource();
                return u16GlyphIndex;
            }

            else
            {
                // Not found
                u16CodemapBlock_left = 1;
            }

        }
    /*
            else
            {
                // Not found
                u16CodemapBlock_left = 1;
            }*/
        }
        else
        {
            u16CodemapBlock_left = 0;
        }
        //printf("\n u16CodemapBlockNum : %u",u16CodemapBlockNum);
        u16CodemapBlock_right = u16CodemapBlockNum - 1; // u16CodemapBlockNum >= 1 here

        while (u16CodemapBlock_left <= u16CodemapBlock_right)
        {


            u16CodemapBlock_middle = (u16CodemapBlock_left + u16CodemapBlock_right)/2;
            //MDrv_MIU_Copy(u32CodemapAddr + ((U32)u16CodemapBlock_middle * sizeof(CHAR_CODEMAP_BLOCK)), (U16)&g_au16CodemapBlock, sizeof(CHAR_CODEMAP_BLOCK), MIU_SDRAM2SRAM);

            // Destination SDRAM address
            u32AddrTemp = u32CodemapAddr + ((U32)u16CodemapBlock_middle * sizeof(CHAR_CODEMAP_BLOCK));
            LoadCodemap(&g_au16CodemapBlock, (U8 *)u32AddrTemp);
            //MDrv_MIU_SDRAM2VARCopy(u32AddrTemp  ,(U8*)&g_au16CodemapBlock , sizeof(CHAR_CODEMAP_BLOCK) );
            // printf("\n in while loop");
            // printf("\n  g_au16CodemapBlock.u16StartCode : %u",g_au16CodemapBlock.u16StartCode);
             //printf("\n  g_au16CodemapBlock.u16EndCode : %u",g_au16CodemapBlock.u16EndCode);

            #if SUPPORT_FAST_DRAWTEXT
         #else
             u32AddrTemp >>= 3;
          #endif

            // Start copy
//            XBYTE[FLH2MIU_CMD] = MIU_DMA_SDRAM2SRAM;

            if (u16Unicode < g_au16CodemapBlock.u16StartCode)
            {
                if (u16CodemapBlock_middle == 0)
                {
                    // Not found
                    break;
                }
                u16CodemapBlock_right = u16CodemapBlock_middle - 1;
            }
            else if (u16Unicode <= g_au16CodemapBlock.u16EndCode)
            {
                // Found
                u16GlyphIndex = u16Unicode - g_au16CodemapBlock.u16StartCode + g_au16CodemapBlock.u16StartIndex;
          //g_u16PreFontBlockStartCode=g_au16CodemapBlock.u16StartCode;
          //g_u16PreFontBlockEndCode=g_au16CodemapBlock.u16EndCode;
          #if SUPPORT_FAST_DRAWTEXT
          g_u8PreFontHandle=handle;
          #endif
//                GE_Free_ReSource();
                return u16GlyphIndex;
            }
            else
            {
                u16CodemapBlock_left = u16CodemapBlock_middle + 1;
            }

            if (u8MaxLoop++ >= 16)
            {
                // Over max while-loop. Should be something wrong with the codemap blocks
                break;
            }
        }
    }

    APIOSDSRC_DBG(printf("[codemap not found]\n"));
//     GE_Free_ReSource();
    return ERR_NULL_INDEX;
}

//-------------------------------------------------------------------------------------------------
/// load PE bitmap info
/// @param addr   \b IN: address
/// @param len    \b IN: total size of bitmap
/// @param width  \b IN: width
/// @param height \b IN: height
/// @param fmt    \b IN: color format (only support 6 color format)
///                     GFX_FMT_I8    \n
///                     GFX_FMT_RGB565\n
///                     GFX_FMT_ARGB1555\n
///                     GFX_FMT_ARGB4444\n
///                     GFX_FMT_1BAAFGBG123433\n
///                     GFX_FMT_ARGB8888\n
/// @return  bitmap handle (  fail to create handle will return ERR_HANDLE )
//-------------------------------------------------------------------------------------------------
BMPHANDLE msAPI_OSD_RESOURCE_LoadBitmap(MS_U32 addr, MS_U32 len, MS_U32 width, MS_U32 height, BMP_Buffer_Format fmt)
{
    int count;


    APIOSDSRC_DBG( printf( "msAPI_OSD_RESOURCE_LoadBitmap\n" ) );


    if (addr & 0x7)         // 64 bits aligned check
    {
        return ERR_HANDLE;
    }

    if( ( (GFX_Buffer_Format)fmt == GFX_FMT_I1 ) || ( (GFX_Buffer_Format)fmt == GFX_FMT_I2 ) || ( (GFX_Buffer_Format)fmt == GFX_FMT_I4 ) )
    {
        return ERR_HANDLE;
    }

    for (count = 0; count<MAX_BITMAP; count++ )
    {
        if (_BitmapTable[_enResGroup][count].inUsed == false)
            break;
    }

    if ( count == MAX_BITMAP)
    {
        return ERR_HANDLE;
    }

    if( (GFX_Buffer_Format)fmt == GFX_FMT_ARGB8888 ) //E_GOP_COLOR_ARGB8888 16-bit align
    {
        _BitmapTable[_enResGroup][count].pitch = width << 2;
    }
    else if( (GFX_Buffer_Format)fmt == GFX_FMT_I8 ) //E_GOP_COLOR_I8
    {
        _BitmapTable[_enResGroup][count].pitch = width ;
    }
    else // E_GOP_COLOR_RGB555 , E_GOP_COLOR_RGB565, E_GOP_COLOR_ARGB4444, E_GOP_COLOR_BLINK
    {
        _BitmapTable[_enResGroup][count].pitch = width << 1;
    }
//printf("LoadBMP pre: %d, %x %x %x %x\n", count, _BitmapTable[count].width, _BitmapTable[count].height, _BitmapTable[count].addr, _BitmapTable[count].pitch);
//    _BitmapTable[count].pitch = (((_BitmapTable[count].pitch + 15)>>4)<<4);

    _BitmapTable[_enResGroup][count].addr = addr;
    _BitmapTable[_enResGroup][count].len = len;
    _BitmapTable[_enResGroup][count].width = width;
    _BitmapTable[_enResGroup][count].height = height;
    _BitmapTable[_enResGroup][count].fmt = fmt;
    _BitmapTable[_enResGroup][count].inUsed = true;
//printf("LoadBMP: %d, %x %x %x %x\n", count, _BitmapTable[count].width, _BitmapTable[count].height, _BitmapTable[count].addr, _BitmapTable[count].pitch);
    return  count;
}

//-------------------------------------------------------------------------------------------------
/// free PE bitmap info
/// @param handle \b IN: bitmap handle
/// @return GFX_SUCCESS - Success
/// @return GFX_INVALID_BMP_HANDLE - Invalid bitmap handle
//-------------------------------------------------------------------------------------------------
OSDSRC_Result msAPI_OSD_RESOURCE_FreeBitmap(BMPHANDLE handle)
{
    if ((handle < MAX_BITMAP) && (handle >= 0))
    {
        _BitmapTable[_enResGroup][handle].inUsed = false;
        return OSDSRC_SUCCESS;
    }
    return OSDSRC_INVALID_BMP_HANDLE;
}


//-------------------------------------------------------------------------------------------------
/// Set FB info to GE (For GOP callback)
/// @param pitch \b IN: pitch of the framebuffer
/// @param addr \b IN: address of the framebuffer
/// @param fmt \b IN: format of the framebuffer in GFX_Buffer_Format enum
/// @return OSDSRC_SUCCESS - Success
//-------------------------------------------------------------------------------------------------
MS_U32 msAPI_OSD_RESOURCE_SetFBFmt(MS_U16 pitch,MS_U32 addr , MS_U16 fmt )
{

    GFX_BufferInfo dstbuf;

    dstbuf.u32ColorFmt = (GFX_Buffer_Format)(fmt&0xff);
    dstbuf.u32Addr = addr;
    dstbuf.u32Pitch = pitch;
    //printf("SetFBFmt: %x, %x, %x\n",dstbuf.u32ColorFmt,dstbuf.u32Addr,dstbuf.u32Pitch  );
    MApi_GFX_SetDstBufferInfo(&dstbuf, 0);

    return (MS_U32)OSDSRC_SUCCESS;
}

#ifdef DVBT_MMBOX
void msAPI_OSD_RESOURCE_SetResGroup(E_RES_GROUP enResGroup)
{
    _enResGroup = enResGroup;
}

E_RES_GROUP msAPI_OSD_RESOURCE_GetResGroup(void)
{
    return _enResGroup;
}
#endif

void msAPI_OSD_RESOURCE_ResetFontVar(void)
{
    font_count = 0;
}

#undef MSAPI_OSD_RESOURCE_C
