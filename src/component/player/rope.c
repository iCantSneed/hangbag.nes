#include "player_internal.h"
#include <chr/gfx.h>
#include <component/lynchman/lynchman.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char rope_start_y;
unsigned char rope_curr_y;
unsigned char rope_x;

#pragma bss-name (push,"RODATA")

void fastcall rope_init(void)
{
  rope_start_y = SPRITE_HIDDEN_Y;
}

void fastcall rope_tick_noosed(void)
{
  rope_start_y = noose_y;
}

void fastcall rope_render(void)
{
  if (rope_start_y == SPRITE_HIDDEN_Y)
  {
    return;
  }

  rope_x = noose_x - 1;
  rope_curr_y = rope_start_y - 23;
  for (; rope_curr_y > KIWI_Y - 23; rope_curr_y -= 16)
  {
    gfx_oam_spr(rope_x, rope_curr_y, 0x06, OAM_BEHIND);
  }
}
