#ifndef _VBE_H_
#define _VBE_H_

#include <stdint.h>
#include <lcom/lcf.h>
#include <lcom/video_gr.h>

//Bios calls
#define BIOS_SET_VIDEOMODE 0x00
#define VBE_CALL 0x10
#define BIOS_SET_VIDEO_MODE_AH 0x4F
#define BIOS_RETURN_STATUS_AL 0x00
#define BIOS_RETURN_MODE_INFO_AL 0x01
#define BIOS_SET_VIDEO_MODE_AL 0x02
#define BIOS_RETURN_CONTROLLER_INFO_AL 0x03

//Diferent modes
#define MODE_1280_1024 0x11C    // DIRECTED 16 BITS
#define MODE_1024_768 0x105     // INDEXED 8 BITS   
#define MODE_640_480 0x101      // DIRECTED 15 BITS
#define MODE_800_600 0x103      // DIRECTED 24 BITS
#define MODE_1150_864 0X14C     // DIRECTED 32 BITS

//VBE functions
#define SET_VBE_MODE 0x02
#define SET_VBE_MODE_LINEAR 0x4000

//Directed or Indexed Mode
#define DIRECTED 0x06
#define INDEXED 0x110
#define TRANSPARENCY_COLOR 0xFFFF01

#endif
