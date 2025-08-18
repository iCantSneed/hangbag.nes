#include "pyrite.h"
#include <chr/gfx.h>
#include <component/lynchman/lynchman.h>
#include <component/score/score.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char idx;

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

void fastcall pyrite_init(void)
{
  // TODO this will init the palette for every sprite, which is wasteful, but whatever
  pal_col(24+1, 0x07);
  pal_col(24+2, 0x27);
  pal_col(24+3, 0x29);
}

unsigned char fastcall pyrite_check_collide(void)
{
  unsigned char x_pos, y_pos;

  idx = lynchable_active_idx - 1;
  x_pos = get_x_pos(idx);
  y_pos = starting_y_pos[idx];
  return (
    noose_y >= y_pos &&
    noose_y <= y_pos + 16 &&
    noose_x >= x_pos - 8 &&
    noose_x <= x_pos + 8
  );
}

void fastcall pyrite_render(void)
{
  if (lynchable_active_idx == lynchable_attached_idx)
  {
    gfx_oam_metaspr(noose_x, noose_y, pyrite_metaspr);
    return;
  }

  idx = lynchable_active_idx - 1;
  gfx_oam_metaspr(get_x_pos(idx), starting_y_pos[idx], pyrite_metaspr);
}

void fastcall pyrite_deinit(void)
{
  score_add(0x01);
}
