#include <gamestate/gamestate.h>
#include <neslib/mmc3.h>
#include <neslib/neslib.h>
#include <neslib/vram_update.h>

#pragma bss-name (push,"ZEROPAGE")

GameState next_gamestate;

#pragma bss-name (push,"RODATA")

void main(void)
{
  // Populate common CHR banks
  mmc3_bank_select(0, 0x00);

  // Init CHR banks and sprite size
  bank_bg(1);
  oam_size(1);

  // Init vram update
  vram_update_init();

  next_gamestate = gamestate_title_init;
  while (1)
  {
    pad_poll(0);
    vram_update_reset();
    rand8();
    next_gamestate();
    ppu_wait_nmi();
  }
}