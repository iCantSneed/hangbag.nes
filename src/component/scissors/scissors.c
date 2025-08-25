#include <component/lynchman/lynchman.h>
#include <component/moneybag/moneybag.h>
#include <component/player/player.h>
#include <component/health/health.h>
#include <chr/gfx.h>

#define MAX_SCISSOR_COUNT 3

#pragma bss-name (push,"ZEROPAGE")

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
#define SCISSORS_Y_HIDDEN 0xff

#define SCISSORS_FORWARD(where, id) fastcall scissors_ ## where ## _ ## id () { idx = id; scissors_ ## where ();  }
#define SCISSORS_RETURN(where, id) fastcall scissors_ ## where ## _ ## id () { idx = id; return scissors_ ## where ();  }

void fastcall scissors_spawn_at_moneybag(void)
{
  idx = 0;
  for (; idx < MAX_SCISSOR_COUNT; ++idx)
  {
    if (scissors_y[idx] == SCISSORS_Y_HIDDEN)
    {
      lynchman_append(LYNCHABLE_SCISSORS_0 + idx);
      break;
    }
  }
}

void fastcall scissors_reset(void)
{
  memfill(scissors_y, SCISSORS_Y_HIDDEN, MAX_SCISSOR_COUNT);
}

void fastcall scissors_init(void)
{
  // idx is set by scissors_spawn_at_moneybag
  // TODO generated assembly here sucks
  scissors_x[idx] = MSB(moneybag_x_pos);
  scissors_y[idx] = MSB(moneybag_y_pos);
}

static void fastcall scissors_tick(void)
{
  ephemeral.active_scissors_y = scissors_y[idx] - SCISSORS_Y_DELTA;
  if (ephemeral.active_scissors_y <= PLAYER_PLATFORM_BOTTOM)
  {
    lynchman_destroy_active();
    scissors_y[idx] = SCISSORS_Y_HIDDEN;
  }
  else
  {
    scissors_y[idx] = ephemeral.active_scissors_y;
  }
}
void SCISSORS_FORWARD(tick, 0)
void SCISSORS_FORWARD(tick, 1)
void SCISSORS_FORWARD(tick, 2)

static NooseState fastcall scissors_check_collide(void)
{
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
    scissors_y[idx] = SCISSORS_Y_HIDDEN;
    return NOOSE_STATE_HURT;
  }
  return NOOSE_STATE_UNCHANGED;
}
NooseState SCISSORS_RETURN(check_collide, 0)
NooseState SCISSORS_RETURN(check_collide, 1)
NooseState SCISSORS_RETURN(check_collide, 2)

static void fastcall scissors_render(void)
{
  gfx_oam_metaspr(scissors_x[idx], scissors_y[idx], nesclock() & 0b1000 ? scissors_closed_metaspr : scissors_opened_metaspr);
}
void SCISSORS_FORWARD(render, 0);
void SCISSORS_FORWARD(render, 1);
void SCISSORS_FORWARD(render, 2);
