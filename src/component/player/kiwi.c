#include "player.h"
#include "player_internal.h"
#include <chr/gfx.h>
#include <component/lynchman/lynchman.h>

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

#define KIWI_LEFT_X (8*2+11-2)

#define KIWI_WALK_MASK 0b1111

void fastcall kiwi_init(void)
{
  kiwi_walk_frame = 0;
}

void fastcall kiwi_tick_nooseless(void)
{
  if (pad_state(0) & PAD_LEFT)
  {
    if (noose_x > KIWI_LEFT_X)
    {
      --noose_x;
    }
    kiwi_walk_frame = (kiwi_walk_frame + 1) & KIWI_WALK_MASK;
  }
  else if (pad_state(0) & PAD_RIGHT)
  {
    if (noose_x < KIWI_RIGHT_X)
    {
      ++noose_x;
    }
    kiwi_walk_frame = (kiwi_walk_frame + 1) & KIWI_WALK_MASK;
  }
  else
  {
    kiwi_walk_frame = 0;
  }
}

void fastcall kiwi_render(void)
{
  gfx_oam_metaspr(noose_x, KIWI_Y, (kiwi_walk_frame > (KIWI_WALK_MASK >> 1)) ? kiwi_walk_metaspr : kiwi_normal_metaspr);
}
