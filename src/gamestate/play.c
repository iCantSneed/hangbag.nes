#include "gamestate.h"
#include "play_nametable.h"
#include <chr/gfx.h>
#include <component/health/health.h>
#include <component/lynchman/lynchman.h>
#include <component/player/player.h>
#include <component/score/score.h>
#include <component/time/time.h>
#include <component/textbox/textbox.h>
#include <neslib/mmc3.h>
#include <neslib/vram_update.h>

unsigned char level_number;

extern const unsigned char* level_text[];
extern const unsigned char level_text_size;

static const unsigned char palette[32] = {
  0x00, TEXT_PALETTE,  // text
  0, 0x0f, 0x15, 0x05, // scenery
  0, 0x07, 0x16, 0x27, // powerbar, health, pyrite
  0, 0x16, 0x28, 0x19, // powerbar

  0, 0x0f, 0x17, 0x37, // kiwi, moneybag, lardhajj
  0, 0x0f, 0x17, 0x39, // kiwi, scissors
  0, 0x07, 0x16, 0x27, // pyrite
};

// Pozzed text
const unsigned char pozzed_text[] = "POZZED";
const unsigned char unpozzed_text[] = "      ";

// Level completion messages
const unsigned char level_completed_nametable_rle[67]={
0x02,0x01,0x01,0x00,0x02,0x05,0x4c,0x45,0x56,0x45,0x4c,0x00,0x43,0x4f,0x4d,0x50,
0x4c,0x45,0x54,0x45,0x44,0x21,0x00,0x02,0x05,0x01,0x02,0x03,0x00,0x02,0x1b,0x01,
0x02,0x03,0x00,0x02,0x04,0x54,0x49,0x4d,0x45,0x00,0x42,0x4f,0x4e,0x55,0x53,0x00,
0x02,0x02,0x24,0x30,0x02,0x03,0x00,0x02,0x04,0x01,0x02,0x03,0x00,0x02,0x1b,0x01,
0x01,0x02,0x00
};
#define RLE_TAG 0xff
const unsigned char level_completed_attributes_rle[] = {
  RLE_TAG,
  0b00010001,
  0b00000000, RLE_TAG, 5,
  0b01000100,
  0b00010001,
  0b00000000, RLE_TAG, 5,
  0b01000100, RLE_TAG, 0
};

#define POZZED_VRAM_UPDATE_ADDR (NTADR_A((16 - (sizeof(pozzed_text) - 1) / 2), 10) | (NT_UPD_HORZ << 8))
#define LEVEL_COMPLETED_NAMETABLE_VRAM_ADDR NTADR_A(0, 14)
#define LEVEL_COMPLETED_ATTRIBUTES_VRAM_ADDR 0x23d8
#define TIME_BONUS_VRAM_UPDATE_ADDR (NTADR_A(21, 16) | (NT_UPD_HORZ << 8))

const LynchableObject level_lynchable_objects[] = {
  LYNCHABLE_MONEYBAG_REGULAR, LYNCHABLE_NONE,
  LYNCHABLE_PYRITEMAN_LONG, LYNCHABLE_MONEYBAG_REGULAR, LYNCHABLE_NONE,
  LYNCHABLE_PYRITEMAN_LONG, LYNCHABLE_MONEYBAG_AGGRO, LYNCHABLE_NONE,
  LYNCHABLE_PYRITEMAN_LONG, LYNCHABLE_MONEYBAG_AGGRO, LYNCHABLE_LARDHAJJ, LYNCHABLE_NONE,
  LYNCHABLE_PYRITEMAN_LONG, LYNCHABLE_MONEYBAG_HANGRY, LYNCHABLE_LARDHAJJ, LYNCHABLE_NONE,
  LYNCHABLE_PYRITEMAN_SHORT, LYNCHABLE_MONEYBAG_HANGRY, LYNCHABLE_LARDHAJJ, LYNCHABLE_NONE,
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
  vram_adr(NTADR_A(0, 0));
  vram_unrle(play_nametable);
  textbox_init();
  time_init();
  score_init();
  health_init();
  lynchman_init();
  player_init();

  ppu_on_bg();
  textbox_ptr = level_text[level_number];
  next_gamestate = gamestate_play_text;
}

void fastcall gamestate_play_text(void)
{
  if (textbox_tick())
  {
    ppu_off();

    for (; level_lynchable_objects[lynchable_object_idx] != LYNCHABLE_NONE; ++lynchable_object_idx)
    {
      lynchman_append(level_lynchable_objects[lynchable_object_idx]);
    }
    ++lynchable_object_idx;

    render(); // TODO needed to get sprites in position for whatever reason
    ppu_on_all();
    next_gamestate = gamestate_play_normal;
  }
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
  ppu_off();
  score_add(time_remaining);
  vram_adr(LEVEL_COMPLETED_NAMETABLE_VRAM_ADDR);
  vram_unrle(level_completed_nametable_rle);
  vram_adr(LEVEL_COMPLETED_ATTRIBUTES_VRAM_ADDR);
  vram_unrle(level_completed_attributes_rle);
  bcd_vram_update(time_remaining, TIME_BONUS_VRAM_UPDATE_ADDR);

  ppu_on_all();
  next_gamestate = gamestate_play_level_completed;
  render();
}

void fastcall gamestate_play_level_completed(void)
{
  if (pad_state(0) & PAD_A)
  {
    ppu_off();
    if (level_number == level_text_size - 1)
    {
      next_gamestate = gamestate_winrar_init;
    }
    else
    {
      ++level_number;
      next_gamestate = gamestate_play_prepare_level;
    }
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
