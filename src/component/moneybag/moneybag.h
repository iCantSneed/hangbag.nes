#if !defined(MONEYBAG_H_)
#define MONEYBAG_H_

typedef void (*MoneybagTick)();
extern MoneybagTick moneybag_tick;
#pragma zpsym ("moneybag_tick");

extern unsigned char moneybag_idle_frame;
#pragma zpsym ("moneybag_idle_frame");

void fastcall moneybag_init();
void fastcall moneybag_render();

#endif // MONEYBAG_H_
