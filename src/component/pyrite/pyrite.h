#if !defined(PYRITE_H_)
#define PYRITE_H_

void fastcall pyrite_init(void);
unsigned char fastcall pyrite_check_collide(void);
void fastcall pyrite_render(void);
void fastcall pyrite_deinit(void);

#endif // PYRITE_H_
