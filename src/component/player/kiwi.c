#include "player.h"
#include "player_internal.h"
#include <chr/gfx.h>

#pragma bss-name (push,"RODATA")

const unsigned char kiwi_metaspr[] = {
  -11, -29, 0x40, 0x00,
  -3,  -29, 0x41, 0x00,
  5,   -29, 0x42, 0x00,
  -11, -21, 0x50, 0x00,
  -3,  -21, 0x51, 0x00,
  5,   -21, 0x52, 0x00,
  -11, -13, 0x60, 0x00,
  -3,  -13, 0x61, 0x01,
  5,   -13, 0x62, 0x00,
  -11, -5,  0x70, 0x00,
  -3,  -5,  0x71, 0x01,
  5,   -5,  0x72, 0x00,
  128
};

#define PAL_KIWI_X1 0x0f
#define PAL_KIWI_X2 0x17
#define PAL_KIWI_03 0x37
#define PAL_KIWI_13 0x39

#define KIWI_LEFT_X (8*2+11-2)

void fastcall kiwi_init()
{
  pal_col(16+1, PAL_KIWI_X1);
  pal_col(16+2, PAL_KIWI_X2);
  pal_col(16+3, PAL_KIWI_03);
  pal_col(20+1, PAL_KIWI_X1);
  pal_col(20+2, PAL_KIWI_X2);
  pal_col(20+3, PAL_KIWI_13);
}

void fastcall kiwi_tick_nooseless()
{
  if (pad_state(0) & PAD_LEFT)
  {
    if (player_x_pos > KIWI_LEFT_X)
    {
      --player_x_pos;
    }
  }
  else if (pad_state(0) & PAD_RIGHT)
  {
    if (player_x_pos < KIWI_RIGHT_X)
    {
      ++player_x_pos;
    }
  }
}

void fastcall kiwi_render()
{
  gfx_oam_metaspr(player_x_pos, KIWI_Y, kiwi_metaspr);
}
