#include "gamestate.h"
#include <chr/gfx.h>
#include <component/moneybag/moneybag.h>
#include <component/player/player.h>
#include <component/score/score.h>
#include <component/time/time.h>
#include <component/textbox/textbox.h>
#include <neslib/mmc3.h>
#include <neslib/vram_update.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char level_number;
const Component *components[16];
const Component **component_ptr, **component_render_start_ptr;

#pragma bss-name (push,"RODATA")

// Pozzed text
const unsigned char pozzed_text[] = "POZZED";
const unsigned char unpozzed_text[] = "      ";

// Level text
extern const unsigned char text_level1[];
const unsigned char* level_text[] = {
  text_level1,
};

// Level completion messages
const unsigned char level_completed_text[] = "LEVEL COMPLETED!";
const unsigned char time_bonus_text[] = "TIME BONUS   $0000";

#define POZZED_VRAM_UPDATE_ADDR (NTADR_A((16 - (sizeof(pozzed_text) - 1) / 2), 10) | (NT_UPD_HORZ << 8))
#define LEVEL_COMPLETED_VRAM_UPDATE_ADDR (NTADR_A((16 - (sizeof(level_completed_text) - 1) / 2), 14) | (NT_UPD_HORZ << 8))
#define TIME_BONUS_VRAM_UPDATE_ADDR (NTADR_A((16 - (sizeof(time_bonus_text) - 1) / 2), 16) | (NT_UPD_HORZ << 8))

void fastcall render();

void fastcall gamestate_play_prepare_level();
void fastcall gamestate_play_text();
void fastcall gamestate_play_normal();
void fastcall gamestate_play_pozzed();
void fastcall gamestate_play_level_completed();

void fastcall gamestate_play_init()
{
  unsigned char i;

  level_number = 0;

  ppu_off();
  mmc3_bank_select(2, 0x04);
  mmc3_bank_select(3, 0x05);

  // TODO
  vram_adr(NTADR_A(0, 0));
  vram_fill(0x00, 1024);
  pal_col(0, 0x00);
  textbox_init();
  time_init();
  score_init();
  components[0] = &player_component; components[0]->init();
  components[1] = &moneybag_component; components[1]->init();
  components[2] = NULL;
  component_render_start_ptr = &components[0];

  // Prepare palette
  pal_col(4+1, 0x0f);
  pal_col(4+2, 0x15);
  pal_col(4+3, 0x05);

  // Draw bricks on the side
  i = 4;
  vram_adr(NTADR_A(0, 4));
  for (; i < 28; ++i)
  {
    vram_put(0x01);
    vram_put(0x01);
    vram_fill(' ', 28);
    vram_put(0x01);
    vram_put(0x01);
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
  vram_fill(0x02, 28);
  vram_adr(0x23c8);
  vram_fill(0b01010101, 8);

  // Draw bricks at the bottom
  vram_adr(NTADR_A(0, 28));
  vram_fill(0x01, 64);
  vram_adr(0x23f8);
  vram_fill(0b01010101, 8);

  ppu_on_all();
  next_gamestate = gamestate_play_prepare_level;
}

void fastcall gamestate_play_prepare_level()
{
  textbox_ptr = level_text[level_number];
  next_gamestate = gamestate_play_text;
}

void fastcall gamestate_play_text()
{
  if (textbox_tick())
  {
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

  component_ptr = &components[0];
  for (; *component_ptr; ++component_ptr)
  {
    (*(*component_ptr)->tick)();
  }

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
  // TODO
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

  component_ptr = component_render_start_ptr;
  do
  {
    (*component_ptr)->render();
    ++component_ptr;
    if (!*component_ptr)
    {
      component_ptr = &components[0];
    }
  } while (component_ptr != component_render_start_ptr);
  
  ++component_render_start_ptr;
  if (!*component_render_start_ptr)
  {
    component_render_start_ptr = &components[0];
  }

  gfx_oam_end();
}
