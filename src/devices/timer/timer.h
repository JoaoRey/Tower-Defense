#ifndef _TIMER_H_
#define _TIMER_H_

#include "macros/i8254.h"
#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <stdint.h>

int(configure_timer_freq)(uint8_t timer, uint32_t frequency);

int(subscription_of_timer_interrupts)(uint8_t *bit_number);

int(unsubscription_of_timer_interrupts)();

void(handler_of_timer_interrupts)();

#endif
