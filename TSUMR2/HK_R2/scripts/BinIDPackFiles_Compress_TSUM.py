#!/usr/bin/python

import os
import sys
import re
import struct
import crcmod

CHUNK_HEADER_SIZE = 0x80                      # The size of chunk header is 128 bytes.
BOOTLOADER_SIZE   = 0						  # The size of sboot+chunk_header_size = 64K*n bytes.
CHUNK_HEADER_BASE = 0				       	  # chunk_header_base is at the end of sboot
UNCOMPRESSED_LEN  = 0x3800                    # The size of uncompressed part is 14K bytes.

bLittleEndian = False
bCRC16Enable  = True
bMultiFlash   = False
PM_CODE_SIZE  = 0             # The size of PM code is supposed to be passed by argument.
AP_BASE       = 0             # AP base is at the end of sboot+chunk_header+PM
UNCOMP_LEN    = 0             # Uncompressed length of AP.bin

CRC16 = crcmod.mkCrcFun(0x18005, 0, 0)
CRC32 = crcmod.mkCrcFun(0x104C11DB7, 0, 0)
LZSS = "./scripts/lzss/lzss.exe c "
MSCOMP = "./scripts/util/mscompress -c -u 0 -9 "
MSCOMP7 = "./scripts/util/mscompress7 e 0 "

FLAG_COMPRESS = 0x01
FLAG_FLASH2   = 0x02
FLAG_MSCOMPRESS = 0x04
FLAG_MSCOMPRESS7 = 0x08

def getFlashTable2(data):
    magic = struct.pack("BBBB", 0x39, 0xB6, 0x5B, 0x53)
    tbl2 = data.find(magic)
    if tbl2 < 0:
        return None
    for i in '\x01' + data[tbl2+4:tbl2+10]:
        n = tbl2 + 10
        while True:
            len = struct.unpack('>H', data[n:n+2])[0]
            if len == 0xFFFF:
                n += 2
                break
            len >>= 14
            n += (2 + (len + 1) * 2)
    return data[tbl2:n]


def parseBinIDInfo(binid_fn):
    bin_map = {}
    global PQ_MAIN_ID,PQ_MAIN_TEXT_ID,PQ_MAIN_EX_ID,PQ_MAIN_SIZE,PQ_MAIN_TEXT_SIZE,PQ_MAIN_EX_SIZE

    PQ_MAIN_ID = 0x0
    PQ_MAIN_TEXT_ID = 0x0
    PQ_MAIN_EX_ID  = 0x0

    define = re.compile('^\s*#define\s+(\S+)\s+(\S+)\s+//~([0-9]+)KB(\+[0-9]*)?\s+//@(\S+)\s+(..*)?')
    f_binid = open(binid_fn)
    for l in f_binid:
        m = define.match(l)
        if (m):
            id = int(m.group(2).strip(), 16)
            len = int(m.group(3), 10) * 1024
            if m.group(4) is not None:
                len = len + int(m.group(4), 10)

            if m.group(1) == "BIN_ID_PQ_MAIN":
                PQ_MAIN_ID = id
                PQ_MAIN_SIZE = len
            elif m.group(1) == "BIN_ID_PQ_MAIN_TEXT":
                PQ_MAIN_TEXT_ID = id
                PQ_MAIN_TEXT_SIZE = len
            elif m.group(1) == "BIN_ID_PQ_MAIN_EX":
                PQ_MAIN_EX_ID = id
                PQ_MAIN_EX_SIZE = len

            fn = m.group(5).strip().replace('\\', '/')
            flags = 0
            if m.group(6) is not None:
                if m.group(6).find('-c') >= 0:
                    flags |= FLAG_COMPRESS
                if m.group(6).find('-g') >= 0:
                    flags |= FLAG_MSCOMPRESS
                if m.group(6).find('-7') >= 0:
                    flags |= FLAG_MSCOMPRESS7
                if m.group(6).find('-2') >= 0:
                    flags |= FLAG_FLASH2
            bin_map[id] = (fn, len, flags)

    return bin_map

def doPack(bin_align, file_align, magic, dst_fn, binid_fn, ImgInfo_Offset, ap_c_fn, compress_format):
    dir = os.path.dirname(binid_fn)
    bin_id = parseBinIDInfo(binid_fn)
    f = open(dst_fn, 'r+b', 0)
    data = f.read()
    tail = f.tell()
    tail = ((tail + file_align - 1) / file_align) * file_align
    tbl2 = getFlashTable2(data)
    magic = int(magic, 16)
    magic = struct.pack("BBBBB",
                        (magic >> 32) & 0xFF,
                        (magic >> 24) & 0xFF,
                        (magic >> 16) & 0xFF,
                        (magic >> 8)  & 0xFF,
                        (magic >> 0)  & 0xFF)
    idx_magic = data.find(magic)
    if idx_magic < 0:
        sys.stderr.write('Could not find magic signature\n')
    else:
        idx_count = idx_magic + len(magic)
        flash_leftsize = struct.unpack('>L', data[idx_count:idx_count+4])[0] # Get left flash size
        idx_count = idx_count + 4
        idx_item  = idx_count + 2
        count = 0
        while True:
            (id, ) = struct.unpack('>H', data[idx_item:idx_item+2])
            if id == 0xF000:
                break
            count = count + 1
            tail = (tail + (bin_align - 1)) & ~(bin_align - 1)

            (fn, rs, flags) = bin_id[id]

            try:
                if bMultiFlash and (flags & FLAG_FLASH2):
                    flash2_bin.append(id)
                    f.seek(idx_item + 2)
                    f.write(struct.pack('>L', 0))
                    f.write(struct.pack('>L', 0))
                    f.write(struct.pack('>B', 0x80 | ((flags & FLAG_COMPRESS) != 0)))
                else:
                    if flags & FLAG_COMPRESS:
    				    os.system(LZSS + dir + "/../" + fn + " " + dir + "/../" + fn + "c");
    				    fn = fn + "c"
                    if flags & FLAG_MSCOMPRESS:
    				    os.system(MSCOMP + dir + "/../" + fn + " > " + dir + "/../" + fn + "c");
    				    fn = fn + "c"
                    if flags & FLAG_MSCOMPRESS7:
    				    os.system(MSCOMP7 + dir + "/../" + fn + " " + dir + "/../" + fn + "c");
    				    fn = fn + "c"
                    b = open(dir + "/../" + fn, "rb")
                    d = b.read()

                    d += '\x00' * (8 - ((len(d) + 2) % 8))  # padding + CRC16
                    d += struct.pack('>H', CRC16(d))

                    if id == PQ_MAIN_ID: #BIN_ID_PQ_MAIN 400K
                        Length = PQ_MAIN_SIZE
                        if len(d)>PQ_MAIN_SIZE:
                            print "PQ_MAIN.BIN is too large"
                    elif id == PQ_MAIN_TEXT_ID:  #BIN_ID_PQ_MAIN_TEXT 22K
                        Length = PQ_MAIN_TEXT_SIZE
                        if len(d)>PQ_MAIN_TEXT_SIZE:
                            print "PQ_MAIN_TEXT.BIN is too large"
                    elif id == PQ_MAIN_EX_ID:  #BIN_ID_PQ_MAIN_EX 20K
                        Length = PQ_MAIN_EX_SIZE
                        if len(d)>PQ_MAIN_EX_SIZE:
                            print "PQ_MAIN_EX.BIN is too large"
                    else:
                        Length = len(d)
                    print "%04X @ %06X %6X %X %s" % (id, tail, Length, flags, fn)

                    f.seek(idx_item + 2)
                    f.write(struct.pack('>L', tail))
                    f.write(struct.pack('>L', Length))
                    f.write(struct.pack('>B', (flags & FLAG_COMPRESS)|(flags & FLAG_MSCOMPRESS)|(flags & FLAG_MSCOMPRESS7) ))

                    f.seek(tail, 0)
                    f.write(d)

                    tail = tail + Length

                    b.close()
            except IOError, e:
                sys.stderr.write(str(e) + '\n')
                quit(2)

            idx_item = idx_item + 11

        f.seek(idx_count)
        f.write(struct.pack('>H', count))

    print '%s:\n\t0x%X octets (%f KB / %f MB)' % (dst_fn, tail, tail / 1024.0, tail / 1024.0 / 1024.0)

	#len_of_MERGE_bytes is the size of MERGE.bin, exclude the last 4B which is the whole CRC32 result as in line#247
    len_of_MERGE_bytes = struct.pack("BBBB",
                        (tail >> 0) & 0xFF,
                        (tail >> 8) & 0xFF,
                        (tail >> 16)  & 0xFF,
                        (tail >> 24)  & 0xFF)
    f.seek((CHUNK_HEADER_BASE + 0x20))
    f.write(len_of_MERGE_bytes)
	
	#hide sboot size to position 0x24 of chunk header
    len_of_sboot_bytes = struct.pack("BBBB",
                        (CHUNK_HEADER_BASE >> 0) & 0xFF,
                        (CHUNK_HEADER_BASE >> 8) & 0xFF,
                        (CHUNK_HEADER_BASE >> 16)  & 0xFF,
                        (CHUNK_HEADER_BASE >> 24)  & 0xFF)
    f.seek((CHUNK_HEADER_BASE + 0x24))
    f.write(len_of_sboot_bytes)
	
    fcompress = open(ap_c_fn, 'r+b', 0)
    datac = fcompress.read()
    len_of_AP = fcompress.tell()
    print "After compress: 0x%X" % (len_of_AP)
    fcompress.close()
    if compress_format == '0':
        CompressMagicNum = 0x00DEADBE
    else:
        CompressMagicNum = 0x00DEADEF

    CompressMagicNum = struct.pack("BBB",
                        (CompressMagicNum >> 0) & 0xFF,
                        (CompressMagicNum >> 8) & 0xFF,
                        (CompressMagicNum >> 16)  & 0xFF)
    f.seek((AP_BASE + ImgInfo_Offset + 0x47))
    f.write(CompressMagicNum)

    #len_of_AP is the size of AP_C.bin
    len_of_AP_bytes = struct.pack("BBBB",
                        (len_of_AP >> 0) & 0xFF,
                        (len_of_AP >> 8) & 0xFF,
                        (len_of_AP >> 16)  & 0xFF,
                        (len_of_AP >> 24)  & 0xFF)
    f.seek((AP_BASE + ImgInfo_Offset + 0x4A))
    f.write(len_of_AP_bytes)
    UNCOMP_LEN_bytes = struct.pack("BBBB",
                        (UNCOMP_LEN >> 0) & 0xFF,
                        (UNCOMP_LEN >> 8) & 0xFF,
                        (UNCOMP_LEN >> 16)  & 0xFF,
                        (UNCOMP_LEN >> 24)  & 0xFF)
    f.write(UNCOMP_LEN_bytes)

    f.seek(BOOTLOADER_SIZE)
    data = f.read(len(data) - BOOTLOADER_SIZE - 2)
    crc = struct.pack('>H', CRC16(data))
    f.write(crc)

    # calculate CRC32 of AP_C.bin and then write CRC32 into chunk_header (offset: 0x14)
    f.seek(AP_BASE)
    data = f.read(len_of_AP)
    crc32 = CRC32(data)
    crc32_bytes = struct.pack("BBBB",
                        (crc32 >> 0) & 0xFF,
                        (crc32 >> 8) & 0xFF,
                        (crc32 >> 16)  & 0xFF,
                        (crc32 >> 24)  & 0xFF)
    #print "crc32 of AP %X" % (crc32)
    f.seek((CHUNK_HEADER_BASE + 0x14))
    f.write(crc32_bytes)

    # write out AP.bin with bin_info for Obama
    ap = open(os.path.dirname(dst_fn) + '/AP_INFO.bin', 'wb')
    ap.write(data + crc)
    ap.close()

    f.seek(AP_BASE)
    crc32 = CRC32(f.read())
    crc = struct.pack('>L', crc32)
    print "crc32 of AP %X" % (crc32)
    f.write(crc)

    f.seek(0)
    crc32 = CRC32(f.read())
    crc = struct.pack('>L', crc32)
    print "crc32 of AP+SBOOT %X" % (crc32)
    f.write(crc)

    f.close()

    #
    # flash2
    #
    if len(flash2_bin) > 0:
        i = dst_fn.find('.')
        if i >= 0:
            dst_fn = dst_fn[0:i] + '2' + dst_fn[i:]
        else:
            dst_fn = dst_fn + '2'

        f = open(dst_fn, 'w+b', 0)

        f.write(magic)

        f.write(struct.pack('>H', len(flash2_bin)))

        for id in flash2_bin:
            f.write(struct.pack('>H', id))
            f.write(struct.pack('>L', 0))
            f.write(struct.pack('>L', 0))
            f.write(struct.pack('>B', 0x80))

        f.write(struct.pack('>H', 0xF000))
        f.write(struct.pack('>L', 0))
        f.write(struct.pack('>L', 0))
        f.write(struct.pack('>B', 0x80))

        if tbl2 != None:
            f.write(tbl2)

        idx_item = 7
        tail = f.tell()
        tail = (tail + (bin_align - 1)) & ~(bin_align - 1)

        for id in flash2_bin:
            tail = (tail + (bin_align - 1)) & ~(bin_align - 1)

            (fn, rs, flags) = bin_id[id]

            try:
                if flags & FLAG_COMPRESS:
				    os.system(LZSS + dir + "/../" + fn + " " + dir + "/../" + fn + "c");
				    fn = fn + "c"
                b = open(dir + "/../" + fn, "rb")
                d = b.read()

                d += '\x00' * (8 - ((len(d) + 2) % 8))  # padding + CRC16
                d += struct.pack('>H', CRC16(d))

                print "%04X xx@ %06X %6X %X %s" % (id, tail, len(d), flags, fn)

                f.seek(idx_item + 2)
                f.write(struct.pack('>L', tail))
                f.write(struct.pack('>L', len(d)))
                f.write(struct.pack('>B', 0x80 | ((flags & FLAG_COMPRESS) != 0)))

                f.seek(tail, 0)
                f.write(d)

                tail = tail + len(d)

                b.close()
            except IOError, e:
                sys.stderr.write(str(e) + '\n')
                quit(2)

            idx_item = idx_item + 11

        print '%s:\n\t0x%X octets (%f KB / %f MB)' % (dst_fn, tail, tail / 1024.0, tail / 1024.0 / 1024.0)

    f.close()

    if tail > flash_leftsize:
        sys.stderr.write("\n\n  *************************   Warning   ******************************\n")
        sys.stderr.write("  *     File size larger than 0x%X! Flash will be overwrite!!!    *" % (flash_leftsize))
        sys.stderr.write("\n  ********************************************************************\n\n")

if __name__ == '__main__':
    args = []

    for arg in sys.argv[1:]:
        l_arg = arg.lower()
        if l_arg == '-bigendian':
            bLittleEndian = False
        elif l_arg == '-littleendian':
            bLittleEndian = True
        elif l_arg == '-crc16enable':
            bCRC16Enable = True
        elif l_arg == '-crc16disable':
            bCRC16Enable = False
        elif l_arg == '-multiflash':
            bMultiFlash = True
        else:
            args.append(arg)

#    print "%s %s %s %s %s %s" % (args[0], args[1], args[2], args[3], args[4], args[5])
#    print "%s %s %s %s %s %s" % (args[6], args[7], args[8], args[9], args[10], args[11])
    
    bin_align       = int(args[0])
    file_align      = int(args[1])
    magic           = args[2]
    dst_fn          = args[3]
    binid_fn        = args[4]
    ImgInfo_Offset  = int(args[5])
    ap_c_fn         = args[6]
    compress_format = args[7]
    PM_CODE_SIZE    = int(args[9])
    BOOTLOADER_SIZE = int(args[10])
    UNCOMP_LEN      = int(args[11])
    flash2_bin      = []

    PM_CODE_SIZE = 0
    UNCOMP_LEN = 0
    CHUNK_HEADER_BASE = BOOTLOADER_SIZE
#    AP_BASE         = BOOTLOADER_SIZE + CHUNK_HEADER_SIZE + PM_CODE_SIZE
    AP_BASE         = BOOTLOADER_SIZE

    (z,y,x,w,v) = os.uname()
    #print "%s %s %s %s %s \n" % (z,y,x,w,v)
    if z[:6] == "CYGWIN":
		LZSS = "./scripts/lzss/lzss.exe c "
    else:
		LZSS = "./scripts/lzss/lzss.out c "
    if z[:6] == "CYGWIN":
		MSCOMP = "./scripts/util/mscompress.exe -c -u 0 -9 "
    else:
		MSCOMP = "./scripts/util/mscompress -c -u 0 -9 "
    if z[:6] == "CYGWIN":
		MSCOMP7 = "./scripts/util/mscompress7.exe e 0 "
    else:
		MSCOMP7 = "./scripts/util/mscompress7 e 0 "
    doPack(bin_align, file_align, magic, dst_fn, binid_fn, ImgInfo_Offset, ap_c_fn, compress_format)
