#include "player.h"
#include "player_internal.h"
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char rope_start_y;
unsigned char rope_curr_y;

#pragma bss-name (push,"RODATA")

unsigned char rope_metaspr[] = {
  -1, -15, 0x0d, 0,
  128
};

void fastcall rope_init()
{
  rope_start_y = NOOSE_HIDDEN_Y;
}

void fastcall rope_tick_noosed()
{
  rope_start_y = noose_y;
}

void fastcall rope_render()
{
  if (rope_start_y == NOOSE_HIDDEN_Y)
  {
    return;
  }

  rope_curr_y = rope_start_y;
  for (; rope_curr_y > KIWI_Y; rope_curr_y -= 8)
  {
    oam_meta_spr_clip(player_x_pos, rope_curr_y, rope_metaspr);
  }
}
