#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include "macros/i8042.h"
#include <lcom/lcf.h>
#include <minix/sysutil.h>

int(subscription_of_mouse_interrupts)(uint8_t *bit_no);

void(interrupt_handler_of_mouse)();

int(unsubscription_of_mouse_interrupts)();

int(mouse_enable_data_report)();

int(mouse_disable_data_report)();

void(transform_mouse_bytes_to_packets)();

int(mouse_write_command(uint8_t comando));

void(synchronization_of_mouse_bytes)();

void(update_mouse_location)();

#endif
