#include <gamestate/gamestate.h>
#include <neslib/neslib.h>
#include <neslib/vram_update.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char frame_number;
unsigned char time_remaining;

#pragma bss-name (push,"RODATA")

// TODO should compensate for lag and PAL/NTSC?
#define FRAMES_PER_SECOND 60

const unsigned char time_text[] = "TIME";

#define TIME_TEXT_VRAM_ADDR NTADR_A(10, 2)
#define TIME_REMAIN_VRAM_UPDATE_ADDR ((TIME_TEXT_VRAM_ADDR + sizeof(time_text)) | (NT_UPD_HORZ << 8))

void fastcall draw_time()
{
  unsigned char bytes[2];
  bytes[0] = (time_remaining >> 4) + '0';
  bytes[1] = (time_remaining & 0xf) + '0';
  vram_update_append(TIME_REMAIN_VRAM_UPDATE_ADDR, sizeof(bytes), bytes);
}

void fastcall time_init()
{
  frame_number = 0;
  time_remaining = 0x60;
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
    --time_remaining; // let it overflow
    if ((time_remaining & 0x0f) == 0x0f)
    {
      if (time_remaining == 0xff)
      {
        next_gamestate = gamestate_play_timesup;
        time_remaining = 0x00;
      }
      else
      {
        time_remaining -= 0xf-0x9;
      }
    }
    draw_time();
  }
}
