#include "gamestate.h"
#include "gameover_nametable.h"
#include <chr/gfx.h>

void fastcall gamestate_gameover_wait();

const unsigned char gameover_palette[16] = {
  0x0f, 0x06, 0x16, 0x07,
  0,    0x1c, 0x0c, 0,
  0,    0x27, 0,    0,
};

void fastcall gamestate_gameover_init()
{
  ppu_off();
  oam_clear();
  pal_bg(gameover_palette);

  vram_adr(NTADR_A(0, 0));
  vram_unrle(gameover_nametable);

  ppu_on_bg();
  next_gamestate = gamestate_gameover_wait;
}

void fastcall gamestate_gameover_wait()
{
  // TODO
}
