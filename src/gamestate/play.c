#include "gamestate.h"
#include "play_nametable.h"
#include <chr/gfx.h>
#include <component/lynchman/lynchman.h>
#include <component/moneybag/moneybag.h>
#include <component/player/player.h>
#include <component/pyrite/pyrite.h>
#include <component/score/score.h>
#include <component/time/time.h>
#include <component/textbox/textbox.h>
#include <neslib/mmc3.h>
#include <neslib/vram_update.h>

unsigned char level_number;

extern const unsigned char* level_text[];

// Pozzed text
const unsigned char pozzed_text[] = "POZZED";
const unsigned char unpozzed_text[] = "      ";

// Level completion messages
const unsigned char level_completed_text[] = "LEVEL COMPLETED!";
const unsigned char time_bonus_text[] = "TIME BONUS   $0000";

#define POZZED_VRAM_UPDATE_ADDR (NTADR_A((16 - (sizeof(pozzed_text) - 1) / 2), 10) | (NT_UPD_HORZ << 8))
#define LEVEL_COMPLETED_VRAM_UPDATE_ADDR (NTADR_A((16 - (sizeof(level_completed_text) - 1) / 2), 14) | (NT_UPD_HORZ << 8))
#define TIME_BONUS_VRAM_UPDATE_ADDR (NTADR_A((16 - (sizeof(time_bonus_text) - 1) / 2), 16) | (NT_UPD_HORZ << 8))

typedef struct {
  unsigned char count;
  const Lynchable* lynchable;
} LynchableObject;
const LynchableObject level_lynchable_objects[] = {
  {1, &moneybag_lynchable}, {0, 0},
  {1, &moneybag_lynchable}, {14, &pyrite_lynchable}, {0, 0},
};
const LynchableObject *lynchable_object_ptr;

void fastcall render();

void fastcall gamestate_play_prepare_level();
void fastcall gamestate_play_text();
void fastcall gamestate_play_normal();
void fastcall gamestate_play_pozzed();
void fastcall gamestate_play_level_completed();

void fastcall gamestate_play_init()
{
  level_number = 0;
  lynchable_object_ptr = &level_lynchable_objects[0];

  ppu_off();
  mmc3_bank_select(2, 0x04);
  mmc3_bank_select(3, 0x05);

  // Prepare palette
  pal_col(0, 0x00);
  pal_col(4+1, 0x0f);
  pal_col(4+2, 0x15);
  pal_col(4+3, 0x05);

  gamestate_play_prepare_level();
}

void fastcall gamestate_play_prepare_level()
{
  unsigned char i;

  vram_adr(NTADR_A(0, 0));
  vram_unrle(play_nametable);
  textbox_init();
  time_init();
  score_init();
  player_init();

  lynchman_init();
  for (; lynchable_object_ptr->count; ++lynchable_object_ptr)
  {
    i = 0;
    for (; i < lynchable_object_ptr->count; ++i)
    {
      lynchman_append(lynchable_object_ptr->lynchable);
    }
  }
  ++lynchable_object_ptr;

  ppu_on_bg();
  textbox_ptr = level_text[level_number];
  next_gamestate = gamestate_play_text;
}

void fastcall gamestate_play_text()
{
  if (textbox_tick())
  {
    ppu_on_all();
    next_gamestate = gamestate_play_normal;
  }
  render();
}

void fastcall gamestate_play_normal()
{
  if (pad_state(0) & PAD_START)
  {
    vram_update_append(POZZED_VRAM_UPDATE_ADDR, sizeof(pozzed_text) - 1, pozzed_text);
    next_gamestate = gamestate_play_pozzed;
  }

  time_tick();
  player_tick();
  lynchman_tick();

  render();
}

void fastcall gamestate_play_pozzed()
{
  if (pad_state(0) & PAD_START)
  {
    vram_update_append(POZZED_VRAM_UPDATE_ADDR, sizeof(unpozzed_text) - 1, unpozzed_text);
    next_gamestate = gamestate_play_normal;
  }

  render();
}

void fastcall gamestate_play_moneybag_hanged()
{
  // TODO
  score_add(time_remaining);
  vram_update_append(LEVEL_COMPLETED_VRAM_UPDATE_ADDR, sizeof(level_completed_text) - 1, level_completed_text);
  vram_update_append(TIME_BONUS_VRAM_UPDATE_ADDR, sizeof(time_bonus_text) - 1, time_bonus_text);
  bcd_vram_update(time_remaining, TIME_BONUS_VRAM_UPDATE_ADDR + sizeof(time_bonus_text) - 5);
  next_gamestate = gamestate_play_level_completed;

  render();
}

void fastcall gamestate_play_level_completed()
{
  if (pad_state(0) & PAD_A)
  {
    ppu_off();
    ++level_number;
    next_gamestate = gamestate_play_prepare_level;
  }

  render();
}

void fastcall gamestate_play_timesup()
{
  // TODO
  next_gamestate = gamestate_gameover_init;
}

void fastcall render()
{
  gfx_oam_start();

  player_render();
  lynchman_render();

  gfx_oam_end();
}
