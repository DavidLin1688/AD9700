#include "types.h"

#define NULLBYTE_1  0xFF,//you can define as 0x00 or 0xFF 
#define NULLBYTE_2  NULLBYTE_1 NULLBYTE_1
#define NULLBYTE_4  NULLBYTE_2 NULLBYTE_2
#define NULLBYTE_8  NULLBYTE_4 NULLBYTE_4
#define NULLBYTE_16 NULLBYTE_8 NULLBYTE_8
#define NULLBYTE_32 NULLBYTE_16 NULLBYTE_16
#define NULLBYTE_64 NULLBYTE_32 NULLBYTE_32
#define NULLBYTE_128    NULLBYTE_64 NULLBYTE_64
#define NULLBYTE_256    NULLBYTE_128 NULLBYTE_128
#define NULLBYTE_512    NULLBYTE_256 NULLBYTE_256
#define NULLBYTE_1024   NULLBYTE_512 NULLBYTE_512
#define NULLBYTE_2048   NULLBYTE_1024 NULLBYTE_1024
#define NULLBYTE_4096   NULLBYTE_2048 NULLBYTE_2048

BYTE code PDUpdateReserved[] =//Reserved for PD RT7880.rrf, 0xAC000~0xAFFFF, 16KB
{
    NULLBYTE_4096//sector 1 0xAC000
    NULLBYTE_4096//sector 2 0xAD000
    NULLBYTE_4096//sector 3 0xAE000
    NULLBYTE_4096//sector 4 0xAF000
};

void PDUpdateReservedDummy(void)
{
    BYTE i = PDUpdateReserved[0];
    i = i;
}
