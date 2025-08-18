#include "gamestate.h"
#include "gameover_nametable.h"
#include <chr/gfx.h>
#include <neslib/mmc3.h>

void fastcall gamestate_gameover_wait(void);

const unsigned char gameover_palette[16] = {
  0x0f, 0x06, 0x16, 0x07,
  0,    0x1c, 0x0c, 0x11,
  0,    0x27, 0x17, 0,
  0,    0x07, 0x17, 0x37,
};

void fastcall gamestate_gameover_init(void)
{
  ppu_off();
  oam_clear();
  pal_bg(gameover_palette);

  // Set CHR banks
  mmc3_bank_select(4, 0x06);
  mmc3_bank_select(5, 0x07);

  vram_adr(NTADR_A(0, 0));
  vram_unrle(gameover_nametable);

  ppu_on_bg();
  next_gamestate = gamestate_gameover_wait;
}

void fastcall gamestate_gameover_wait(void)
{
  // TODO
}
