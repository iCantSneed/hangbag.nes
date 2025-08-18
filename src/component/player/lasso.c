#include "player_internal.h"
#include <chr/gfx.h>
#include <component/lynchman/lynchman.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char lasso_x, lasso_y;
unsigned char clock;

#pragma bss-name (push,"RODATA")

unsigned char lasso_metaspr[] = {
  -7, -41, 0x0a, 0,
  1,  -41, 0x0a, OAM_FLIP_H,
  128,
};

void fastcall lasso_reset()
{
  lasso_y = SPRITE_HIDDEN_Y;
}

void fastcall lasso_tick_nooseless()
{
  clock = nesclock() & 0b1100;
  lasso_x = noose_x;
  lasso_y = KIWI_Y;
  if (!(clock & 0b0100))
  {
    lasso_x += ((clock & 0b1000) << 1) - 8;
  }
  else
  {
    lasso_y += ((clock & 0b1000) << 0) - 4;
  }
}

void fastcall lasso_render()
{
  if (lasso_y == SPRITE_HIDDEN_Y)
  {
    return;
  }

  gfx_oam_spr(noose_x - 1, KIWI_Y - 37, 0x08, 0);
  gfx_oam_metaspr(lasso_x, lasso_y, lasso_metaspr);
}
