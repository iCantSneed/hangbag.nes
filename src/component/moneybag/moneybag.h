#if !defined(MONEYBAG_H_)
#define MONEYBAG_H_

void fastcall moneybag_init(void);
extern void (*fastcall moneybag_tick)(void);
#pragma zpsym ("moneybag_tick")
unsigned char fastcall moneybag_check_collide(void);
void fastcall moneybag_render(void);

#endif // MONEYBAG_H_
