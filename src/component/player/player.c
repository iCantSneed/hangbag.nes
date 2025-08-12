#include "player.h"
#include "player_internal.h"
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

Callback player_tick;
unsigned char player_x_pos;
unsigned char player_power;

#pragma bss-name (push,"RODATA")

void fastcall player_tick_nooseless();
void fastcall player_tick_noosed();

void fastcall player_init()
{
  player_tick = player_tick_nooseless;
  player_x_pos = KIWI_RIGHT_X;
  powerbar_init();
  kiwi_init();
  noose_init_nooseless();
  rope_init();
}

void fastcall player_tick_nooseless()
{
  powerbar_tick_nooseless();
  kiwi_tick_nooseless();

  if (pad_poll(0) & PAD_A)
  {
    player_tick = player_tick_noosed;
    noose_init_noosed();
  }
}

void fastcall player_tick_noosed()
{
  if (noose_tick_noosed())
  {
    player_tick = player_tick_nooseless;
  }
  rope_tick_noosed();
}

void fastcall player_render()
{
  powerbar_render();
  kiwi_render();
  noose_render();
  rope_render();
}

const Component player_component = {
  player_init,
  &player_tick,
  player_render,
};
