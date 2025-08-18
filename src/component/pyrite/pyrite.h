#if !defined(PYRITE_H_)
#define PYRITE_H_

void fastcall pyrite_init(unsigned char);
extern void (*fastcall pyrite_tick)(unsigned char);
unsigned char fastcall pyrite_check_collide(unsigned char);
void fastcall pyrite_render(unsigned char);
void fastcall pyrite_deinit(unsigned char);

#endif // PYRITE_H_
