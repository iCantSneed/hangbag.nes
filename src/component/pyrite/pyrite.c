#include "pyrite.h"
#include <chr/gfx.h>
#include <component/lynchman/lynchman.h>
#include <component/score/score.h>

#pragma bss-name (push,"RODATA")

const unsigned char pyrite_metaspr[] = {
  -7, 0, 0x0c, 2 | OAM_BEHIND,
  1,  0, 0x0c, 2 | OAM_BEHIND | OAM_FLIP_H | OAM_FLIP_V,
  128
};

const unsigned char starting_y_pos[] = {
  0x50, 0x60, 0x70, 0x80, 0x80, 0x70, 0x60,
  0x60, 0x70, 0x80, 0x80, 0x70, 0x60, 0x50,
};

unsigned char fastcall get_x_pos(unsigned char adjusted_idx)
{
  return 23 + adjusted_idx * 16;
}

void fastcall pyrite_init(unsigned char)
{
  // TODO this will init the palette for every sprite, which is wasteful, but whatever
  pal_col(24+1, 0x07);
  pal_col(24+2, 0x27);
  pal_col(24+3, 0x29);
}

void fastcall pyrite_tick_nothing(unsigned char)
{
  // Do nothing.
}

unsigned char fastcall pyrite_check_collide(unsigned char idx)
{
  unsigned char x_pos, y_pos;

  --idx;
  x_pos = get_x_pos(idx);
  y_pos = starting_y_pos[idx];
  return (
    noose_y >= y_pos &&
    noose_y <= y_pos + 16 &&
    noose_x >= x_pos - 8 &&
    noose_x <= x_pos + 8
  );
}

void fastcall pyrite_render(unsigned char idx)
{
  if (idx == lynchable_attached_idx)
  {
    gfx_oam_metaspr(noose_x, noose_y, pyrite_metaspr);
    return;
  }

  --idx;
  gfx_oam_metaspr(get_x_pos(idx), starting_y_pos[idx], pyrite_metaspr);
}

void fastcall pyrite_deinit(unsigned char)
{
  score_add(0x01);
}

void (*fastcall pyrite_tick)(unsigned char) = pyrite_tick_nothing;
