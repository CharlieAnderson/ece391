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
extern int rtc_read(void);
extern int rtc_write(uint32_t freq);
extern int rtc_write_rate(int rate);
extern int rtc_open(void);
extern int rtc_close(void);
extern void rtc_test(uint32_t freq);
extern void rtc_full_test(void);

#endif /* _RTC_H */
