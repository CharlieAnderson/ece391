#ifndef _RTC_H
#define _RTC_H

#include "types.h"
#include "i8259.h"
#include "lib.h"

/* Ports that each PIC sits on */
#define INDEX_RTC_PORT 0x70
#define DATA_RTC_PORT  0x71

/* Initialize the rtc */
void rtc_init(void);
extern void rtc_handler(void);
int rtc_write(int rate);
int rtc_read(void);
int rtc_open(void);
int rtc_close(void);
void rtc_test(int new_rate);
#endif /* _RTC_H */
