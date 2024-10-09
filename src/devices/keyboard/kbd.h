#ifndef _KBD_H_
#define _KBD_H_

#include "macros/i8042.h"
#include <lcom/lcf.h>

int(subscription_of_keyboard_interrupts)(uint8_t *bit_no);

int(unsubscription_of_keyboard_interrupts)();

void(keyboard_interrupt_handler)();

int(read_status_code)(uint8_t *status);

int(read_pressed_key)(int chosen_port, uint8_t *output_code, uint8_t mouse_code);

int(write_command_byte)(int chosen_port, uint8_t command_code);

#endif
