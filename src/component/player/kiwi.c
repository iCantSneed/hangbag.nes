#include "player_internal.h"
#include <component/controller/controller.h>
#include <neslib/neslib.h>

#pragma bss-name (push,"RODATA")

const unsigned char kiwi_metaspr[] = {
  0,  0,  0x40, 0x00,
  8,  0,  0x41, 0x00,
  16, 0,  0x42, 0x00,
  0,  8,  0x50, 0x00,
  8,  8,  0x51, 0x00,
  16, 8,  0x52, 0x00,
  0,  16, 0x60, 0x00,
  8,  16, 0x61, 0x01,
  16, 16, 0x62, 0x00,
  0,  24, 0x70, 0x00,
  8,  24, 0x71, 0x01,
  16, 24, 0x72, 0x00,
  128
};

#define PAL_KIWI_X1 0x0f
#define PAL_KIWI_X2 0x17
#define PAL_KIWI_03 0x37
#define PAL_KIWI_13 0x39

#define KIWI_SPR_IDX 4*1

void fastcall kiwi_init()
{
  pal_col(16+1, PAL_KIWI_X1);
  pal_col(16+2, PAL_KIWI_X2);
  pal_col(16+3, PAL_KIWI_03);
  pal_col(20+1, PAL_KIWI_X1);
  pal_col(20+2, PAL_KIWI_X2);
  pal_col(20+3, PAL_KIWI_13);
}

void fastcall kiwi_tick()
{
  if (pad0 & PAD_LEFT)
  {
    --player_x_pos;
  }
  else if (pad0 & PAD_RIGHT)
  {
    ++player_x_pos;
  }
  oam_meta_spr(player_x_pos, 32, KIWI_SPR_IDX, kiwi_metaspr);
}
