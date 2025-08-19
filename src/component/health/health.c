#include <gamestate/gamestate.h>
#include <neslib/neslib.h>
#include <neslib/vram_update.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char health;

#pragma bss-name (push,"RODATA")

#define HEALTH_X 18
#define HEALTH_Y 2
#define HEALTH_UPDATE_VRAM_ADDR (NTADR_A(HEALTH_X, HEALTH_Y) | NT_UPD_HORZ)
#define STARTING_HEALTH 2
#define HEALTH_TILE 0x07

const unsigned char health_damage_update_vram[] = { 0x00 };

void fastcall health_init()
{
  health = STARTING_HEALTH;
}

void fastcall health_damage()
{
  vram_update_append(HEALTH_UPDATE_VRAM_ADDR + health, sizeof(health_damage_update_vram), health_damage_update_vram);
  if (health)
  {
    --health;
    // TODO play sfx
  }
  else
  {
    next_gamestate = gamestate_play_dead;
  }
}
