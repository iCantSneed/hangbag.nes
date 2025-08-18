#if !defined(LYNCHMAN_H_)
#define LYNCHMAN_H_

#include "lynchable.h"

#define NO_LYNCHABLE_ATTACHED 0xff

extern unsigned char noose_x;
#pragma zpsym ("noose_x")

extern unsigned char noose_y;
#pragma zpsym ("noose_y")

extern unsigned char lynchable_attached_idx;
#pragma zpsym ("lynchable_attached_idx")

void fastcall lynchman_init();
void fastcall lynchman_append(const Lynchable*);
void fastcall lynchman_tick();
void fastcall lynchman_render();

#endif // LYNCHMAN_H_
