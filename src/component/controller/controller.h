#if !defined(CONTROLLER_H_)
#define CONTROLLER_H_

extern unsigned char pad0;
#pragma zpsym ("pad0");

void fastcall controller_tick();

#endif // CONTROLLER_H_
