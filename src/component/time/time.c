#include <gamestate/gamestate.h>
#include <neslib/bcd.h>
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char frame_number;
Bcd time_remaining;

#pragma bss-name (push,"RODATA")

// TODO should compensate for lag and PAL/NTSC?
#define FRAMES_PER_SECOND 60

const unsigned char time_text[] = "TIME";

#define TIME_TEXT_VRAM_ADDR NTADR_A(10, 2)
#define TIME_REMAIN_VRAM_UPDATE_ADDR ((TIME_TEXT_VRAM_ADDR + sizeof(time_text)) | (NT_UPD_HORZ << 8))

#define draw_time() { bcd_vram_update(time_remaining, TIME_REMAIN_VRAM_UPDATE_ADDR); }

void fastcall time_init()
{
  frame_number = 0;
  time_remaining = 0x99;
  vram_adr(TIME_TEXT_VRAM_ADDR);
  vram_write(time_text, sizeof(time_text) - 1);
  draw_time();
}

void fastcall time_tick()
{
  ++frame_number;
  if (frame_number == FRAMES_PER_SECOND)
  {
    frame_number = 0;
    if (bcd_decrement(&time_remaining))
    {
      next_gamestate = gamestate_play_timesup;
    }
    draw_time();
  }
}
