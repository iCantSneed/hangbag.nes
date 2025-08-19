#include "gamestate.h"
#include "play_nametable.h"
#include <chr/gfx.h>
#include <component/lynchman/lynchman.h>
#include <component/player/player.h>
#include <component/score/score.h>
#include <component/time/time.h>
#include <component/textbox/textbox.h>
#include <neslib/mmc3.h>
#include <neslib/vram_update.h>

unsigned char level_number;

extern const unsigned char* level_text[];

static const unsigned char palette[32] = {
  0x00, TEXT_PALETTE,  // text
  0, 0x0f, 0x15, 0x05, // scenery
  0, 0x07, 0x16, 0x27, // powerbar, health
  0, 0x16, 0x28, 0x19, // powerbar

  0, 0x0f, 0x17, 0x37, // kiwi, moneybag
  0, 0x0f, 0x17, 0x39, // kiwi
  0, 0x07, 0x27, 0x29, // pyrite
};

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
  const LynchableObject lynchable;
} LevelLynchable;
const LevelLynchable level_lynchable_objects[] = {
  {1, LYNCHABLE_MONEYBAG}, {0, 0},
  {14, LYNCHABLE_PYRITE}, {1, LYNCHABLE_MONEYBAG}, {0, 0},
};
unsigned char lynchable_object_idx;

void fastcall render(void);

void fastcall gamestate_play_prepare_level(void);
void fastcall gamestate_play_text(void);
void fastcall gamestate_play_normal(void);
void fastcall gamestate_play_pozzed(void);
void fastcall gamestate_play_level_completed(void);

void fastcall gamestate_play_init(void)
{
  level_number = 0;
  lynchable_object_idx = 0;

  ppu_off();
  pal_all(palette);
  mmc3_bank_select(2, 0x04);
  mmc3_bank_select(3, 0x05);

  gamestate_play_prepare_level();
}

void fastcall gamestate_play_prepare_level(void)
{
  unsigned char i;

  vram_adr(NTADR_A(0, 0));
  vram_unrle(play_nametable);
  textbox_init();
  time_init();
  score_init();
  lynchman_init();
  player_init();

  for (; level_lynchable_objects[lynchable_object_idx].count; ++lynchable_object_idx)
  {
    i = 0;
    for (; i < level_lynchable_objects[lynchable_object_idx].count; ++i)
    {
      lynchman_append(level_lynchable_objects[lynchable_object_idx].lynchable);
    }
  }
  ++lynchable_object_idx;

  ppu_on_bg();
  textbox_ptr = level_text[level_number];
  next_gamestate = gamestate_play_text;
}

void fastcall gamestate_play_text(void)
{
  if (textbox_tick())
  {
    ppu_on_all();
    next_gamestate = gamestate_play_normal;
  }
  render();
}

void fastcall gamestate_play_normal(void)
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

void fastcall gamestate_play_pozzed(void)
{
  if (pad_state(0) & PAD_START)
  {
    vram_update_append(POZZED_VRAM_UPDATE_ADDR, sizeof(unpozzed_text) - 1, unpozzed_text);
    next_gamestate = gamestate_play_normal;
  }

  render();
}

void fastcall gamestate_play_moneybag_hanged(void)
{
  // TODO
  score_add(time_remaining);
  vram_update_append(LEVEL_COMPLETED_VRAM_UPDATE_ADDR, sizeof(level_completed_text) - 1, level_completed_text);
  vram_update_append(TIME_BONUS_VRAM_UPDATE_ADDR, sizeof(time_bonus_text) - 1, time_bonus_text);
  bcd_vram_update(time_remaining, TIME_BONUS_VRAM_UPDATE_ADDR + sizeof(time_bonus_text) - 5);
  next_gamestate = gamestate_play_level_completed;

  render();
}

void fastcall gamestate_play_level_completed(void)
{
  if (pad_state(0) & PAD_A)
  {
    ppu_off();
    ++level_number;
    next_gamestate = gamestate_play_prepare_level;
  }

  render();
}

void fastcall gamestate_play_timesup(void)
{
  // TODO
  next_gamestate = gamestate_gameover_init;
}

void fastcall gamestate_play_dead(void)
{
  // TODO
  next_gamestate = gamestate_gameover_init;
}

void fastcall render(void)
{
  gfx_oam_start();

  player_render();
  lynchman_render();

  gfx_oam_end();
}
