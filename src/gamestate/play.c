#include "gamestate.h"
#include <component/moneybag/moneybag.h>
#include <component/player/player.h>
#include <component/score/score.h>
#include <component/textbox/textbox.h>
#include <neslib/neslib.h>

const unsigned char pozzed_text[] = "POZZED";
const unsigned char unpozzed_text[] = "      ";

#define POZZED_POS (NTADR_A((16 - (sizeof(pozzed_text) - 1) / 2), 10) | (NT_UPD_HORZ << 8))

void fastcall render();

void fastcall gamestate_play_normal();
void fastcall gamestate_play_pozzed();

void fastcall gamestate_play_init()
{
  unsigned char i;

  pal_col(0, 0x00);
  textbox_init();
  score_init();
  player_init();
  moneybag_init();

  // Prepare palette
  pal_col(4+1, 0x0f);
  pal_col(4+2, 0x15);
  pal_col(4+3, 0x05);

  // Draw bricks on the side
  i = 4;
  vram_adr(NTADR_A(0, 4));
  for (; i < 28; ++i)
  {
    vram_put(0x80);
    vram_put(0x80);
    vram_fill(' ', 28);
    vram_put(0x80);
    vram_put(0x80);
  }
  i = 0;
  vram_adr(0x23d0);
  for (; i < 5; ++i)
  {
    vram_put(0b00010001);
    vram_fill(0, 6);
    vram_put(0b01000100);
  }

  // Draw the grated floor
  vram_adr(NTADR_A(2, 6));
  vram_fill(0x81, 28);
  vram_adr(0x23c8);
  vram_fill(0b01010101, 8);

  // Draw bricks at the bottom
  vram_adr(NTADR_A(0, 28));
  vram_fill(0x80, 64);
  vram_adr(0x23f8);
  vram_fill(0b01010101, 8);

  ppu_on_all();
  next_gamestate = gamestate_play_normal;
}

void fastcall gamestate_play_normal()
{
  if (pad_state(0) & PAD_START)
  {
    textbox_tick();
    textbox_append(POZZED_POS, sizeof(pozzed_text) - 1, pozzed_text);
    next_gamestate = gamestate_play_pozzed;
  }

  player_tick();
  moneybag_tick();
  render();
}

void fastcall gamestate_play_pozzed()
{
  if (pad_state(0) & PAD_START)
  {
    textbox_tick();
    textbox_append(POZZED_POS, sizeof(unpozzed_text) - 1, unpozzed_text);
    next_gamestate = gamestate_play_normal;
  }

  render();
}

void fastcall gamestate_play_moneybag_hanged()
{
  render();
}

void fastcall render()
{
  oam_clear_fast();
  player_render();
  moneybag_render();
}
