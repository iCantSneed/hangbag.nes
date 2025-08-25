#include <component/lynchman/lynchman.h>
#include <component/moneybag/moneybag.h>
#include <component/player/player.h>
#include <component/health/health.h>
#include <chr/gfx.h>

#define MAX_SCISSOR_COUNT 3

#pragma bss-name (push,"ZEROPAGE")

unsigned char scissors_lynchable_id[MAX_SCISSOR_COUNT];
unsigned char scissors_x[MAX_SCISSOR_COUNT];
unsigned char scissors_y[MAX_SCISSOR_COUNT];
static unsigned char idx;
static struct {
  union {
    struct {
      unsigned char active_scissors_x;
      unsigned char active_scissors_y;
    };
  };
} ephemeral;

#pragma bss-name (push,"RODATA")

const unsigned char scissors_opened_metaspr[] = {
  -7, 0, 0x0e, 1 | OAM_BEHIND,
  1,  0, 0x0e, 1 | OAM_BEHIND | OAM_FLIP_H,
  128
};

const unsigned char scissors_closed_metaspr[] = {
  -7, 0, 0x3e, 1 | OAM_BEHIND,
  1,  0, 0x3e, 1 | OAM_BEHIND | OAM_FLIP_H,
  128
};

#define SCISSORS_Y_DELTA 2
#define NO_LYNCHABLE_ATTACHED 0xff

void fastcall scissors_spawn_at_moneybag(void)
{
  idx = 0;
  for (; idx < MAX_SCISSOR_COUNT; ++idx)
  {
    if (scissors_lynchable_id[idx] == NO_LYNCHABLE_ATTACHED)
    {
      lynchman_append(LYNCHABLE_SCISSORS);
      break;
    }
  }
}

void fastcall scissors_reset(void)
{
  memfill(scissors_lynchable_id, NO_LYNCHABLE_ATTACHED, MAX_SCISSOR_COUNT);
}

void fastcall scissors_init(void)
{
  // idx is set by scissors_spawn_at_moneybag
  scissors_lynchable_id[idx] = lynchable_active_idx;
  scissors_x[idx] = MSB(moneybag_x_pos);
  scissors_y[idx] = MSB(moneybag_y_pos);
}

#define set_idx_to_active_lynchable() \
{ \
  idx = 0; \
  for (; scissors_lynchable_id[idx] != lynchable_active_idx; ++idx) {} \
}

void fastcall scissors_tick(void)
{
  set_idx_to_active_lynchable();
  ephemeral.active_scissors_y = scissors_y[idx] - SCISSORS_Y_DELTA;
  if (ephemeral.active_scissors_y <= PLAYER_PLATFORM_BOTTOM)
  {
    lynchman_destroy_active();
    scissors_lynchable_id[idx] = NO_LYNCHABLE_ATTACHED;
  }
  else
  {
    scissors_y[idx] = ephemeral.active_scissors_y;
  }
}

NooseState fastcall scissors_check_collide(void)
{
  set_idx_to_active_lynchable();
  ephemeral.active_scissors_x = scissors_x[idx];
  ephemeral.active_scissors_y = scissors_y[idx];
  if (
    noose_y >= (unsigned char)(ephemeral.active_scissors_y - 8) &&
    noose_y <= (unsigned char)(ephemeral.active_scissors_y + 8) &&
    noose_x >= (unsigned char)(ephemeral.active_scissors_x - 4) &&
    noose_x <= (unsigned char)(ephemeral.active_scissors_x + 4)
  )
  {
    lynchman_destroy_active();
    scissors_lynchable_id[idx] = NO_LYNCHABLE_ATTACHED;
    return NOOSE_STATE_HURT;
  }
  return NOOSE_STATE_UNCHANGED;
}

void fastcall scissors_render(void)
{
  set_idx_to_active_lynchable();
  gfx_oam_metaspr(scissors_x[idx], scissors_y[idx], nesclock() & 0b1000 ? scissors_closed_metaspr : scissors_opened_metaspr);
}
