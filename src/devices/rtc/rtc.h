#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>

int verify_rtc_mode();
int rtc_read_write(uint8_t command, uint8_t *output);
void initialize_rtc();
int update_rtc_seconds();
int update_rtc_minutes();
int update_rtc_hours();
int update_rtc_year();
int update_rtc_month();
int update_rtc_day();
int update_rtc_date();
int update_rtc_time();
uint8_t bcd_to_bin(uint8_t bcd_number);

#endif
