#include "player.h"
#include "player_internal.h"
#include <component/controller/controller.h>
#include <component/gamestate/gamestate.h>
#include <component/moneybag/moneybag.h>
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char noose_y;
unsigned char noose_delta;
unsigned char rope_y;

#pragma bss-name (push,"RODATA")

unsigned char noose_metaspr[] = {
  -7, -7, 0x0c, 0,
  1,  -7, 0x0c, OAM_FLIP_H,
  -7, 1,  0x0c, OAM_FLIP_V,
  1,  1,  0x0c, OAM_FLIP_H | OAM_FLIP_V,
  128
};
unsigned char rope_metaspr[] = {
  -1, -15, 0x0d, 0,
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
    if (game_state == GAME_STATE_PLAYING)
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
        game_state = GAME_STATE_COMPLETED;
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
    }
  }
  else if (game_state == GAME_STATE_PLAYING && (pad0 & PAD_A))
  {
    player_noose_activated = TRUE;
    noose_y = NOOSE_INITIAL_Y;
    noose_delta = player_power;
  }
}

void fastcall noose_render()
{
  if (player_noose_activated)
  {
    if (game_state == GAME_STATE_PLAYING)
    {
      oam_meta_spr_clip(player_x_pos, noose_y, noose_metaspr);
    }
    rope_y = noose_y;
    for (; rope_y > KIWI_Y; rope_y -= 8)
    {
      oam_meta_spr_clip(player_x_pos, rope_y, rope_metaspr);
    }
  }
}
