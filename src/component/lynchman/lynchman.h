#if !defined(LYNCHMAN_H_)
#define LYNCHMAN_H_

#include "lynchable.h"

void fastcall lynchman_init();
void fastcall lynchman_append(const Lynchable*);
void fastcall lynchman_tick();
void fastcall lynchman_render();

#endif // LYNCHMAN_H_
