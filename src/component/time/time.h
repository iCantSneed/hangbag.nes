#if !defined(TIME_H_)
#define TIME_H_

#include <neslib/bcd.h>

extern Bcd time_remaining;
#pragma zpsym ("time_remaining")

void fastcall time_init(void);
void fastcall time_tick(void);

#endif // TIME_H_
