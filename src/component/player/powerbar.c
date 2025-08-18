#include "player_internal.h"
#include <chr/gfx.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char power_idx, power_idx_delta;
unsigned char power_gauge_x, power_gauge_x_delta;

#pragma bss-name (push,"RODATA")

#define POWER_CRAP 3
#define POWER_LOW 4
#define POWER_MED 5
#define POWER_HI 6
const unsigned char powers[] = {
  POWER_CRAP, POWER_CRAP, POWER_CRAP, POWER_CRAP, POWER_CRAP, POWER_CRAP,
  POWER_LOW, POWER_LOW, POWER_LOW, POWER_LOW, POWER_LOW,
  POWER_MED, POWER_MED, POWER_MED, POWER_MED,
  POWER_HI,
};

#define PAL_POWERBAR_21 0x07
#define PAL_POWERBAR_22 0x16
#define PAL_POWERBAR_31 0x16
#define PAL_POWERBAR_32 0x28
#define PAL_POWERBAR_33 0x19

void fastcall powerbar_init(void)
{
  player_power = powers[0];
  power_idx = 0;
  power_idx_delta = 1;
  power_gauge_x = 40;
  power_gauge_x_delta = 1;

  pal_col(8+1, PAL_POWERBAR_21);
  pal_col(8+2, PAL_POWERBAR_22);
  pal_col(12+1, PAL_POWERBAR_31);
  pal_col(12+2, PAL_POWERBAR_32);
  pal_col(12+3, PAL_POWERBAR_33);
}

void fastcall powerbar_tick_nooseless(void)
{
  power_idx += power_idx_delta;
  power_gauge_x += power_gauge_x_delta;
  player_power = powers[power_idx];
  if (power_idx == 0)
  {
    power_idx_delta = -power_idx_delta;
    power_gauge_x_delta = -power_gauge_x_delta;
  }
  else if (power_idx == sizeof(powers) - 1)
  {
    power_idx_delta = -power_idx_delta;
  }
}

void fastcall powerbar_render(void)
{
  gfx_oam_spr(power_gauge_x - 3, 10, 0x02, 0);
}
