#include "player_internal.h"
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char player_x_pos;
unsigned char player_noose_activated;
unsigned char player_power;

#pragma bss-name (push,"RODATA")

void fastcall player_init()
{
  player_x_pos = KIWI_RIGHT_X;
  player_noose_activated = FALSE;
  powerbar_init();
  kiwi_init();
}

void fastcall player_tick()
{
  powerbar_tick();
  kiwi_tick();
  noose_tick();
}
