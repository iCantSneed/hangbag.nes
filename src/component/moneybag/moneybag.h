#if !defined(MONEYBAG_H_)
#define MONEYBAG_H_

void fastcall moneybag_init(unsigned char);
extern void (*fastcall moneybag_tick)(unsigned char);
#pragma zpsym ("moneybag_tick")
unsigned char fastcall moneybag_check_collide(unsigned char);
void fastcall moneybag_render(unsigned char);

#endif // MONEYBAG_H_
