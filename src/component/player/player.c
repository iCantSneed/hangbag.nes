#include "player_internal.h"

#pragma bss-name (push,"ZEROPAGE")

unsigned char player_x_pos;

#pragma bss-name (push,"RODATA")

void fastcall player_init()
{
  player_x_pos = 80;
  kiwi_init();
}

void fastcall player_tick()
{
  kiwi_tick();
}
