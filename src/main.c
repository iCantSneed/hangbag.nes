#include <gamestate/gamestate.h>
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

GameState next_gamestate;

#pragma bss-name (push,"RODATA")

void main()
{
  // Init CHR banks
  bank_spr(0);
  bank_bg(1);

  // Init text palettes
  pal_col(1, 0x30);
  pal_col(2, 0x3d);
  pal_col(3, 0x10);

  next_gamestate = gamestate_play_init;
  while (1)
  {
    pad_poll(0);
    next_gamestate();
    ppu_wait_nmi();
  }
}