#include <chr/gfx.h>
#include <component/lawyer/lawyer.h>
#include <component/lynchman/lynchman.h>
#include <component/player/player.h>

#define HAMMER_COUNT 1

#pragma bss-name (push,"ZEROPAGE")

unsigned int hammer_x[HAMMER_COUNT], hammer_y[HAMMER_COUNT];
int hammer_delta_x[HAMMER_COUNT];

#pragma bss-name (push,"RODATA")

const unsigned char hammer_metaspr_0[] = {
  -8, -8, 0x60, 0 | OAM_BEHIND,
  0,  -8, 0x62, 0 | OAM_BEHIND,
  128
};

#define HAMMER_Y_HIDDEN 0xff
#define HAMMER_FRAMES_TO_HIT_TARGET 128
#define HAMMER_DELTA_Y (256 * (LAWYER_Y - KIWI_Y) / HAMMER_FRAMES_TO_HIT_TARGET)

void fastcall hammer_spawn_at_lawyer(unsigned char lawyer_idx)
{
  if (MSB(hammer_y[lawyer_idx]) == HAMMER_Y_HIDDEN) // TODO generated assembly is inefficient
  {
    lynchman_append(LYNCHABLE_HAMMER0 + lawyer_idx);
  }
}

void fastcall hammer_reset(void)
{
  memfill(hammer_y, HAMMER_Y_HIDDEN, sizeof(hammer_y));
}

void fastcall hammer_init_0(void)
{
  hammer_x[0] = LAWYER0_X << 8;
  hammer_y[0] = LAWYER_Y << 8;
  hammer_delta_x[0] = 256 / HAMMER_FRAMES_TO_HIT_TARGET * (noose_x - LAWYER0_X);
}

#define hammer_destroy() { \
  lynchman_destroy_active(); \
  hammer_y[0] = HAMMER_Y_HIDDEN << 8; \
}

void fastcall hammer_tick_0(void)
{
  hammer_y[0] -= HAMMER_DELTA_Y;
  if (MSB(hammer_y[0]) == 0xff)
  {
    hammer_destroy();
  }
  else
  {
    hammer_x[0] += hammer_delta_x[0];
    if (MSB(hammer_x[0]) >= 0xf0)
    {
      hammer_destroy();
    }
  }
}

void fastcall hammer_render_0(void)
{
  gfx_oam_metaspr(MSB(hammer_x[0]), MSB(hammer_y[0]), hammer_metaspr_0);
}
