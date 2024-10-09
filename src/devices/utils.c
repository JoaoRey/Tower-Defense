#include <lcom/lcf.h>
#include <stdint.h>

int(util_get_LSB)(uint16_t value, uint8_t *LSB) {
  if (LSB == NULL) {
    return 1;
  }
  *LSB = value & 0xFF;
  return 0;
}

int(util_get_MSB)(uint16_t value, uint8_t *MSB) {
  if (MSB == NULL) {
    return 1;
  }
  *MSB = value >> 8;
  return 0;
}

int(util_sys_inb)(int port, uint8_t *value) {
  uint32_t val;
  if (value == NULL) {
    return 1;
  }
  if (sys_inb(port, &val) != 0) {
    return 1;
  }
  *value = val & 0xFF;
  return 0;
}
