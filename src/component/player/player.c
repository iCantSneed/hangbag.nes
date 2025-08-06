#include "player_internal.h"
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char player_x_pos;
unsigned char player_noose_activated;

#pragma bss-name (push,"RODATA")

void fastcall player_init()
{
  player_x_pos = KIWI_RIGHT_X;
  player_noose_activated = FALSE;
  kiwi_init();
}

void fastcall player_tick()
{
  kiwi_tick();
  noose_tick();
}
