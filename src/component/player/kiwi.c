#include "player.h"
#include "player_internal.h"
#include <chr/gfx.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char kiwi_walk_frame;

#pragma bss-name (push,"RODATA")

#define KIWI_METASPR(walk_chr, nose_chr) { \
  -11, -29, 0x40, 0, \
  -3,  -29, 0x42, 0, \
  5,   -29, 0x44, 0, \
  -11, -13, walk_chr, 0, \
  -3,  -13, nose_chr, 1, \
  5,   -13, walk_chr, OAM_FLIP_H, \
  128 \
}
const unsigned char kiwi_normal_metaspr[] = KIWI_METASPR(0x46, 0x48);
const unsigned char kiwi_walk_metaspr[] = KIWI_METASPR(0x4a, 0x4c);

#define PAL_KIWI_X1 0x0f
#define PAL_KIWI_X2 0x17
#define PAL_KIWI_03 0x37
#define PAL_KIWI_13 0x39

#define KIWI_LEFT_X (8*2+11-2)

#define KIWI_WALK_MASK 0b1111

void fastcall kiwi_init()
{
  kiwi_walk_frame = 0;
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
    kiwi_walk_frame = (kiwi_walk_frame + 1) & KIWI_WALK_MASK;
  }
  else if (pad_state(0) & PAD_RIGHT)
  {
    if (player_x_pos < KIWI_RIGHT_X)
    {
      ++player_x_pos;
    }
    kiwi_walk_frame = (kiwi_walk_frame + 1) & KIWI_WALK_MASK;
  }
  else
  {
    kiwi_walk_frame = 0;
  }
}

void fastcall kiwi_render()
{
  gfx_oam_metaspr(player_x_pos, KIWI_Y, (kiwi_walk_frame > (KIWI_WALK_MASK >> 1)) ? kiwi_walk_metaspr : kiwi_normal_metaspr);
}
