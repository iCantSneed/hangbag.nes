#include "player.h"
#include "player_internal.h"
#include <component/lynchman/lynchman.h>
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

void (*player_tick)(void);
unsigned char player_power;

#pragma bss-name (push,"RODATA")

void fastcall player_tick_nooseless(void);
void fastcall player_tick_noosed(void);

void fastcall player_init(void)
{
  player_tick = player_tick_nooseless;
  noose_x = KIWI_RIGHT_X;
  powerbar_init();
  kiwi_init();
  lasso_reset();
  noose_init_nooseless();
  rope_init();
}

void fastcall player_tick_nooseless(void)
{
  powerbar_tick_nooseless();
  kiwi_tick_nooseless();
  lasso_tick_nooseless();

  if (pad_poll(0) & PAD_A)
  {
    player_tick = player_tick_noosed;
    noose_init_noosed();
    lasso_reset();
  }
}

void fastcall player_tick_noosed(void)
{
  if (noose_tick_noosed())
  {
    player_tick = player_tick_nooseless;
  }
  rope_tick_noosed();
}

void fastcall player_render(void)
{
  powerbar_render();
  kiwi_render();
  lasso_render();
  noose_render();
  rope_render();
}
