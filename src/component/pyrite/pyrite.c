#include "pyrite.h"
#include <chr/gfx.h>

#pragma bss-name (push,"ZEROPAGE")

#define PYRITE_MAX_COUNT 14
unsigned char y_pos[PYRITE_MAX_COUNT];
unsigned char x_pos;

#pragma bss-name (push,"RODATA")

const unsigned char pyrite_metaspr[] = {
  -7, 0, 0x0c, 2 | OAM_BEHIND,
  1,  0, 0x0c, 2 | OAM_BEHIND | OAM_FLIP_H | OAM_FLIP_V,
  128
};

const unsigned char starting_y_pos[] = {
  0x40, 0x50, 0x60, 0x70, 0x70, 0x60, 0x50,
  0x50, 0x60, 0x70, 0x70, 0x60, 0x50, 0x40,
};

unsigned char fastcall get_x_pos(unsigned char adjusted_idx)
{
  return 23 + adjusted_idx * 16;
}

void fastcall pyrite_init(unsigned char idx)
{
  --idx;
  y_pos[idx] = starting_y_pos[idx];

  // TODO this will init the palette for every sprite, which is wasteful, but whatever
  pal_col(24+1, 0x07);
  pal_col(24+2, 0x27);
  pal_col(24+3, 0x29);
}

void fastcall pyrite_tick(unsigned char idx)
{
  // TODO
}

unsigned char fastcall pyrite_check_collide(unsigned char idx)
{
  // TODO
  return FALSE;
}

void fastcall pyrite_render(unsigned char idx)
{
  --idx;
  x_pos = get_x_pos(idx);
  gfx_oam_metaspr(x_pos, y_pos[idx], pyrite_metaspr);
}

Tick pyrite_tick_ptr = pyrite_tick;

const Lynchable pyrite_lynchable = {
  pyrite_init,
  &pyrite_tick_ptr,
  pyrite_check_collide,
  pyrite_render,
};
