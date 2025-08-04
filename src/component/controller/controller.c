#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char pad0;

#pragma bss-name (push,"RODATA")

void fastcall controller_tick()
{
  pad0 = pad_poll(0);
}
