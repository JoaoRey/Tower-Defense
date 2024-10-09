#include "rtc.h"

uint8_t rtc_binary_mode;
uint8_t rtc_time_data[6];

int verify_rtc_mode() {
  uint8_t status;
  if (rtc_read_write(11, &status) != 0) {
    return -1;
  }
  if (status & BIT(2)) {
    return 0;
  }
  return 1;
}

void initialize_rtc() {
  rtc_binary_mode = (verify_rtc_mode() == 1) ? 0 : 1;
  update_rtc_time();
}
int update_rtc_time() {
  uint8_t busy_flag;
  if (rtc_read_write(10, &busy_flag))
    return 1;

  if (!(busy_flag & BIT(7))) {
    if (update_rtc_seconds() != 0) {
      return 1;
    }
    if (update_rtc_minutes() != 0) {
      return 1;
    }
    if (update_rtc_hours() != 0) {
      return 1;
    }
    if (update_rtc_year() != 0) {
      return 1;
    }
    if (update_rtc_month() != 0) {
      return 1;
    }
    if (update_rtc_day() != 0) {
      return 1;
    }
  }
  return 0;
}
int rtc_read_write(uint8_t command, uint8_t *output) {
  if (sys_outb(0x70, command) != 0) {
    return 1;
  }
  if (util_sys_inb(0x71, output) != 0) {
    return 1;
  }
  return 0;
}

int update_rtc_minutes() {
  uint8_t minutes;
  if (rtc_read_write(2, &minutes) != 0) {
    return 1;
  }
  rtc_time_data[4] = rtc_binary_mode ? minutes : bcd_to_bin(minutes);
  return 0;
}

int update_rtc_year() {
  uint8_t year;
  if (rtc_read_write(9, &year) != 0) {
    return 1;
  }
  rtc_time_data[0] = rtc_binary_mode ? year : bcd_to_bin(year);
  return 0;
}
int update_rtc_seconds() {
  uint8_t seconds;
  if (rtc_read_write(0, &seconds) != 0) {
    return 1;
  }
  rtc_time_data[5] = rtc_binary_mode ? seconds : bcd_to_bin(seconds);
  return 0;
}
int update_rtc_month() {
  uint8_t month;
  if (rtc_read_write(8, &month) != 0) {
    return 1;
  }
  rtc_time_data[1] = rtc_binary_mode ? month : bcd_to_bin(month);
  return 0;
}

int update_rtc_day() {
  uint8_t day;
  if (rtc_read_write(7, &day) != 0) {
    return 1;
  }
  rtc_time_data[2] = rtc_binary_mode ? day : bcd_to_bin(day);
  return 0;
}
uint8_t bcd_to_bin(uint8_t bcd_number) {
  return (bcd_number - 6 * (bcd_number >> 4));
}
int update_rtc_hours() {
  uint8_t hours;
  if (rtc_read_write(4, &hours) != 0) {
    return 1;
  }
  rtc_time_data[3] = rtc_binary_mode ? hours : bcd_to_bin(hours);
  return 0;
}


