#include <chr/gfx.h>
#include <component/lynchman/lynchman.h>
#include <component/score/score.h>

const unsigned char pyrite_metaspr[] = {
  -7, 0, 0x0c, 2 | OAM_BEHIND,
  1,  0, 0x0c, 2 | OAM_BEHIND | OAM_FLIP_H | OAM_FLIP_V,
  128
};

// FIXME dumb hack
unsigned char fastcall pyrite_check_collide(void)
{
  return TRUE;
}

void fastcall pyrite_render(void)
{
  gfx_oam_metaspr(noose_x, noose_y, pyrite_metaspr);
}

void fastcall pyrite_deinit(void)
{
  score_add(0x01);
}
