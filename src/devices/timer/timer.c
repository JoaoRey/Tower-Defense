#include "timer.h"
#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <stdint.h>

int timer_hook_id = 0;
int counter = 0;

int(configure_timer_freq)(uint8_t timer_code, uint32_t frequency) {
  if (frequency > 1193182 | frequency <= 19) {
    return 1;
  }
  uint32_t portion = 1193182 / frequency;
  if (portion > 65535) {
    return 1;
  }
  uint8_t word;
  uint8_t MoSB, LeSB;
  util_get_MSB(portion, &MoSB);
  util_get_LSB(portion, &LeSB);
  uint8_t timer_to_be_used;
  if (timer_get_conf(timer_code, &word) != 0) {
    return 1;
  }
  if (timer_code == 0) {
    word = 0x00;
    timer_to_be_used = 0x40;
  }
  else if (timer_code == 1) {
    word = (1 << 6);
    timer_to_be_used = 0x41;
  }
  else if (timer_code == 2) {
    word = (1 << 7);
    timer_to_be_used = 0x42;
  }
  if (sys_outb(TIMER_CTRL, word) != 0) {
    return 1;
  }
  if (sys_outb(timer_to_be_used, LeSB) != 0) {
    return 1;
  }
  if (sys_outb(timer_to_be_used, MoSB) != 0) {
    return 1;
  }
  return 0;
}

int(subscription_of_timer_interrupts)(uint8_t *bit_number) {
  if (bit_number == NULL) {
    return 1;
  }
  *bit_number = BIT(timer_hook_id);
  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id) != 0) {
    return 1;
  }
  return 0;
}

int(unsubscription_of_timer_interrupts)() {
  if (sys_irqrmpolicy(&timer_hook_id) != 0) {
    return 1;
  }
  return 0;
}

void(handler_of_timer_interrupts)() {
  counter++;
}

int(timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (st == NULL || timer > 2 || timer < 0) {
    return 1;
  }
  uint8_t read_back_command = (TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer));

  if (sys_outb(TIMER_CTRL, read_back_command) != 0) {
    return 1;
  }
  if (util_sys_inb(TIMER_0 + timer, st)) {
    return 1;
  }
  return 0;
}
