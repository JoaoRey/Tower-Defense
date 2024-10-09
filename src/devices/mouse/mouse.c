#include "mouse.h"
#include "devices/keyboard/kbd.h"
#include "macros/i8042.h"
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int mouse_hook_id = 3;
struct packet mouse_packet_structure;
uint8_t mouse_bytes_array[3];
uint8_t mouse_bytes_index = 0;
uint8_t byte_used;
int x = 5;
int y = 5;

int(subscription_of_mouse_interrupts)(uint8_t *bit_number) {
  if (bit_number == NULL) {
    return 1;
  }
  *bit_number = BIT(mouse_hook_id);
  return sys_irqsetpolicy(MOUSE_IRQ_LINE, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int(unsubscription_of_mouse_interrupts)() {
  return sys_irqrmpolicy(&mouse_hook_id);
}

void(interrupt_handler_of_mouse)() {
  if (read_pressed_key(0x60, &byte_used, 1) != 0) {
    return;
  }
}

void(transform_mouse_bytes_to_packets)() {
  for (int i = 0; i < 3; i++) {
    mouse_packet_structure.bytes[i] = mouse_bytes_array[i];
  }

  mouse_packet_structure.lb = mouse_bytes_array[0] & BIT(0);
  mouse_packet_structure.mb = mouse_bytes_array[0] & BIT(2);
  mouse_packet_structure.rb = mouse_bytes_array[0] & BIT(1);
  mouse_packet_structure.x_ov = mouse_bytes_array[0] & BIT(6);
  mouse_packet_structure.y_ov = mouse_bytes_array[0] & BIT(7);
  if (mouse_bytes_array[0] & BIT(4)) {
    mouse_packet_structure.delta_x = 0xFF00 | mouse_bytes_array[1];
  }
  else {
    mouse_packet_structure.delta_x = mouse_bytes_array[1];
  }

  if (mouse_bytes_array[0] & BIT(5)) {
    mouse_packet_structure.delta_y = 0xFF00 | mouse_bytes_array[2];
  }
  else {
    mouse_packet_structure.delta_y = mouse_bytes_array[2];
  }
}

int(mouse_write_command)(uint8_t comando) {
  uint8_t attemps = 10;
  uint8_t mouse_response_code;
  while (attemps > 0) {
    if (write_command_byte(0x60, 0xD4) != 0) {
      return 1;
    }
    if (write_command_byte(0x64, comando) != 0) {
      return 1;
    }
    if (read_pressed_key(0x60, &mouse_response_code, 1) != 0) {
      return 1;
    }
    if (mouse_response_code == 0xFA) {
      return 0;
    }
    attemps--;
  }
  return 1;
}

void(synchronization_of_mouse_bytes)() {
  if (mouse_bytes_index == 0 && (byte_used & (1 << (3)))) {
    mouse_bytes_array[mouse_bytes_index] = byte_used;
    mouse_bytes_index++;
  }
  else if (mouse_bytes_index > 0) {
    mouse_bytes_array[mouse_bytes_index] = byte_used;
    mouse_bytes_index++;
  }
}
void(update_mouse_location)() {
  if (x + mouse_packet_structure.delta_x < 0 && !mouse_packet_structure.x_ov) {
    x = 0;
  }
  else if (x + mouse_packet_structure.delta_x > 800 && !mouse_packet_structure.x_ov) {
    x = 800;
  }
  else if (!mouse_packet_structure.x_ov) {
    x += mouse_packet_structure.delta_x;
  }

  if (y - mouse_packet_structure.delta_y < 0 && !mouse_packet_structure.y_ov) {
    y = 0;
  }
  else if (y - mouse_packet_structure.delta_y > 600 && !mouse_packet_structure.y_ov) {
    y = 600;
  }
  else if (!mouse_packet_structure.y_ov) {
    y -= mouse_packet_structure.delta_y;
  }
}
