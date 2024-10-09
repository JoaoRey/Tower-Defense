#include "kbd.h"
#include "macros/i8042.h"
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

uint8_t keyboard_scancode;
int keyboard_hook_id = 1;

int(subscription_of_keyboard_interrupts)(uint8_t *bit_number) {
  if (bit_number == NULL) {
    return 1;
  }
  *bit_number = BIT(keyboard_hook_id);
  return sys_irqsetpolicy(KBD_IRQ_LINE, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id);
}

int(unsubscription_of_keyboard_interrupts)() {
  return sys_irqrmpolicy(&keyboard_hook_id);
}

void(keyboard_interrupt_handler)() {
  if (read_pressed_key(KBD_OUT_BUF, &keyboard_scancode, 0) != 0) {
    printf("Error has been detected!");
  }
}

int(read_status_code)(uint8_t *status) {
  if (util_sys_inb(KBD_IN_BUF, status) != 0) {
    return 1;
  }
  return 0;
}

int(write_command_byte)(int chosen_port, uint8_t command_code) {
  uint8_t status_code;
  int tentativas = 5;
  if (util_sys_inb(0x64, &status_code) != 0) {
    return 1;
  }
  while (tentativas) {
    if (read_status_code(&status_code) != 0) {
      return 1;
    }
    if ((command_code & (1 << (1))) == 0) {
      if (util_sys_inb(chosen_port, &command_code) != 0) {
        return 1;
      }
      return 0;
    }
    else {
      tickdelay(micros_to_ticks(20000));
      tentativas--;
    }
  }
  return 1;
}

int(read_pressed_key)(int chosen_port, uint8_t *output_code, uint8_t mouse_code) {
  uint8_t status_code;
  int tentativas = TENTATIVAS;
  if (read_status_code(&status_code) != 0) {
    return 1;
  }
  while (tentativas) {
    if ((status_code & (1 << (0))) != 0) {
      if ((status_code & (1 << (7))) != 0 && (status_code & (1 << (6))) != 0) {
        return 1;
      }

      if (util_sys_inb(chosen_port, output_code) != 0) {
        return 1;
      }
      if ((mouse_code && (status_code & BIT(5)) == 0) || (!mouse_code && (status_code & BIT(5)) != 0)) {
        return 1;
      }
      return 0;
    }
    else {
      tickdelay(micros_to_ticks(20000));
      tentativas--;
    }
  }
  return 1;
}
