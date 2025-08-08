#include "player_internal.h"
#include <component/controller/controller.h>
#include <component/moneybag/moneybag.h>
#include <neslib/neslib.h>

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
#define NOOSE_X_TOLERANCE 8
#define NOOSE_Y_TOLERANCE 4

void fastcall noose_tick()
{
  if (player_noose_activated)
  {
    noose_y += noose_delta;
    if (
      moneybag_is_grounded() &&
      player_x_pos >= MSB(moneybag_x_pos) - NOOSE_X_TOLERANCE &&
      player_x_pos <= MSB(moneybag_x_pos) + NOOSE_X_TOLERANCE &&
      noose_y >= MONEYBAG_IDLE_Y_POS - NOOSE_Y_TOLERANCE &&
      noose_y <= MONEYBAG_IDLE_Y_POS + NOOSE_Y_TOLERANCE
    )
    {
      asm ("brk");
    }
    else if (noose_y <= NOOSE_INITIAL_Y)
    {
      player_noose_activated = FALSE;
      return;
    }
    if (noose_y >= NOOSE_MAX_Y)
    {
      noose_delta = -noose_delta;
    }
    oam_meta_spr_clip(player_x_pos, noose_y, noose_metaspr);
  }
  else if (pad0 & PAD_A)
  {
    player_noose_activated = TRUE;
    noose_y = NOOSE_INITIAL_Y;
    noose_delta = player_power;
  }
}
