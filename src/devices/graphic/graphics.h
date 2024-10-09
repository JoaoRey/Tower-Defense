#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "macros/VBE.h"
#include <lcom/lcf.h>
#include <lcom/video_gr.h>
#include <stdint.h>
#include <stdio.h>

vbe_mode_info_t graphic_mode_info;
uint8_t *adress_base_v;

int(set_vbe_mode)(uint16_t submode);

int(set_text_mode)();

int(set_video_mem)(uint16_t mode);

int(draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int(normalize_color)(uint32_t color, uint32_t *normalized_color);

void allocate_image_loader();

void copy_buffer_to_screen();

#endif
