#include <chr/gfx.h>
#include <component/lynchman/lynchman.h>
#include <component/score/score.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char x_pos, y_pos;

#pragma bss-name (push,"RODATA")

const unsigned char pyrite_metaspr[] = {
  -7, 0, 0x0c, 2 | OAM_BEHIND,
  1,  0, 0x0c, 2 | OAM_BEHIND | OAM_FLIP_H | OAM_FLIP_V,
  128
};

const unsigned char starting_x_pos[] = {
  0x17, 0x27, 0x37, 0x47, 0x57, 0x67, 0x77,
  0x87, 0x97, 0xa7, 0xb7, 0xc7, 0xd7, 0xe7,
};

const unsigned char starting_y_pos[] = {
  0x50, 0x60, 0x70, 0x80, 0x80, 0x70, 0x60,
  0x60, 0x70, 0x80, 0x80, 0x70, 0x60, 0x50,
};

void fastcall pyrite_init(void)
{
  // TODO this will init the palette for every sprite, which is wasteful, but whatever
  pal_col(24+1, 0x07);
  pal_col(24+2, 0x27);
  pal_col(24+3, 0x29);
}

unsigned char fastcall pyrite_check_collide(void)
{
  x_pos = starting_x_pos[lynchable_active_idx];
  y_pos = starting_y_pos[lynchable_active_idx];
  return (
    noose_y >= y_pos &&
    noose_y <= (unsigned char)(y_pos + 16) &&
    noose_x >= (unsigned char)(x_pos - 8) &&
    noose_x <= (unsigned char)(x_pos + 8)
  );
}

void fastcall pyrite_render(void)
{
  if (lynchable_active_idx == lynchable_attached_idx)
  {
    gfx_oam_metaspr(noose_x, noose_y, pyrite_metaspr);
    return;
  }

  gfx_oam_metaspr(starting_x_pos[lynchable_active_idx], starting_y_pos[lynchable_active_idx], pyrite_metaspr);
}

void fastcall pyrite_deinit(void)
{
  score_add(0x01);
}
