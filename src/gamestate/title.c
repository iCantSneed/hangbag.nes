#include "gamestate.h"
#include "title_nametable.h"
#include <neslib/mmc3.h>
#include <neslib/neslib.h>

void fastcall gamestate_title_wait();

void fastcall gamestate_title_init()
{
  ppu_off();
  pal_col(0, 0x0f);

  // Set CHR banks
  mmc3_bank_select(4, 0x08);
  mmc3_bank_select(5, 0x09);

  // Set logo palette
  pal_col(5, 0x02);
  pal_col(6, 0x36);
  pal_col(7, 0x26);

  // Draw title screen
  vram_adr(NTADR_A(0, 0));
  vram_unrle(title_nametable);

  ppu_on_bg();
  next_gamestate = gamestate_title_wait;
}

void fastcall gamestate_title_wait()
{
  if (pad_state(0) & PAD_START)
  {
    next_gamestate = gamestate_play_init;
  }
}
