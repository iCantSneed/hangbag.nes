#include "player.h"
#include "player_internal.h"
#include <chr/gfx.h>
#include <component/moneybag/moneybag.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char noose_y;
unsigned char noose_delta;

#pragma bss-name (push,"RODATA")

unsigned char noose_metaspr[] = {
  -7, -7, 0x0c, 0,
  1,  -7, 0x0c, OAM_FLIP_H,
  -7, 1,  0x0c, OAM_FLIP_V,
  1,  1,  0x0c, OAM_FLIP_H | OAM_FLIP_V,
  128
};

#define NOOSE_INITIAL_Y (KIWI_Y + 7)
#define NOOSE_MAX_Y (8*28 - 9)

void fastcall noose_init_nooseless()
{
  noose_y = NOOSE_HIDDEN_Y;
}

void fastcall noose_init_noosed()
{
  noose_y = NOOSE_INITIAL_Y;
  noose_delta = player_power;
}

unsigned char fastcall noose_tick_noosed()
{
  noose_y += noose_delta;
  if (noose_y <= NOOSE_INITIAL_Y)
  {
    noose_init_nooseless();
    return TRUE;
  }
  if (noose_y >= NOOSE_MAX_Y)
  {
    noose_delta = -noose_delta;
  }
  return FALSE;
}

void fastcall noose_render()
{
  if (noose_y == NOOSE_HIDDEN_Y)
  {
    return;
  }
  
  gfx_oam_metaspr(player_x_pos, noose_y, noose_metaspr);
}
