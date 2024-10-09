#include "graphics.h"
#include <lcom/lcf.h>
#include <math.h>

uint16_t x_res, y_res;
uint8_t *drawer_buffer;
uint8_t *image_loader;
unsigned int bytes_being_user_per_pixel;

int(set_vbe_mode)(uint16_t submode) {
  reg86_t reg86;
  memset(&reg86, 0, sizeof(reg86));
  reg86.intno = VBE_CALL;
  reg86.ax = 0x4F02;
  reg86.bx = submode | BIT(14);
  if (sys_int86(&reg86) != 0) {
    printf("set_vbe_mode: sys_int86() failed\n");
    return 1;
  }
  return 0;
}

int(set_text_mode)() {
  reg86_t reg86;
  memset(&reg86, 0, sizeof(reg86));
  reg86.intno = VBE_CALL;
  reg86.ah = BIOS_SET_VIDEOMODE;
  reg86.al = BIOS_RETURN_CONTROLLER_INFO_AL;
  reg86.bx = 0x0000;
  if (sys_int86(&reg86) != 0) {
    printf("set_text_mode: sys_int86() failed\n");
    return 1;
  }
  return 0;
}

int(set_video_mem)(uint16_t mode) {
  memset(&graphic_mode_info, 0, sizeof(graphic_mode_info));
  if (vbe_get_mode_info(mode, &graphic_mode_info))
    return 1;
  bytes_being_user_per_pixel = (graphic_mode_info.BitsPerPixel + 7) / 8;
  x_res = graphic_mode_info.XResolution;
  y_res = graphic_mode_info.YResolution;

  int r;
  uint8_t *video_mem;
  struct minix_mem_range mr;
  unsigned int vram_base_adress = graphic_mode_info.PhysBasePtr;
  unsigned int vram_all_size = (graphic_mode_info.XResolution * graphic_mode_info.YResolution * graphic_mode_info.BitsPerPixel) / 8;
  mr.mr_base = (phys_bytes) vram_base_adress;
  mr.mr_limit = mr.mr_base + vram_all_size;
  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) {
    return 1;
  }
  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_all_size);
  if (video_mem == MAP_FAILED) {
    return 1;
  }
  adress_base_v = video_mem;
  return 0;
}

int(draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  if (x >= x_res || y >= y_res) {
    return 0;
  }
  memcpy(&image_loader[(x_res * y + x) * bytes_being_user_per_pixel], &color, bytes_being_user_per_pixel);
  return 0;
}

int(normalize_color)(uint32_t color, uint32_t *normalized_color) {
  if (graphic_mode_info.BitsPerPixel == 32) {
    *normalized_color = color;
  }
  else {
    *normalized_color = color & (BIT(graphic_mode_info.BitsPerPixel) - 1);
  }
  return 0;
}

void allocate_image_loader() {
  image_loader = (uint8_t *) malloc(x_res * y_res * bytes_being_user_per_pixel);
}

void copy_buffer_to_screen() {
  memcpy(adress_base_v, image_loader, x_res * y_res * bytes_being_user_per_pixel);
}
