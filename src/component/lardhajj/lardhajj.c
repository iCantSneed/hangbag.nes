#include <chr/gfx.h>
#include <component/lynchman/lynchman.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned int lardhajj_x;
unsigned int lardhajj_delta;
static unsigned char metaspr_idx;

#pragma bss-name (push,"RODATA")

#define LARDHAJJ_THICCNESS 29
#define X_OFF -16
#define Y_OFF -10
#define LARDHAJJ_RIGHT_METASPR(walk_idx) { \
  X_OFF + 8*0, Y_OFF + 16*0, 0x50, 0, \
  X_OFF + 8*1, Y_OFF + 16*0, 0x52, 0, \
  X_OFF + 8*2, Y_OFF + 16*0, 0x54, 0, \
  X_OFF + 8*3, Y_OFF + 16*0, 0x56, 0, \
  X_OFF + 8*0, Y_OFF + 16*1, 0x58, 0, \
  X_OFF + 8*1, Y_OFF + 16*1, 0x5a, 0, \
  X_OFF + 8*2, Y_OFF + 16*1, walk_idx, 0, \
  X_OFF + 8*3, Y_OFF + 16*1, 0x5e, 0, \
  128 \
}
#define LARDHAJJ_LEFT_METASPR(walk_idx) { \
  -LARDHAJJ_THICCNESS - X_OFF + 8*0, Y_OFF + 16*0, 0x56, OAM_FLIP_H, \
  -LARDHAJJ_THICCNESS - X_OFF + 8*1, Y_OFF + 16*0, 0x54, OAM_FLIP_H, \
  -LARDHAJJ_THICCNESS - X_OFF + 8*2, Y_OFF + 16*0, 0x52, OAM_FLIP_H, \
  -LARDHAJJ_THICCNESS - X_OFF + 8*3, Y_OFF + 16*0, 0x50, OAM_FLIP_H, \
  -LARDHAJJ_THICCNESS - X_OFF + 8*0, Y_OFF + 16*1, 0x5e, OAM_FLIP_H, \
  -LARDHAJJ_THICCNESS - X_OFF + 8*1, Y_OFF + 16*1, walk_idx, OAM_FLIP_H, \
  -LARDHAJJ_THICCNESS - X_OFF + 8*2, Y_OFF + 16*1, 0x5a, OAM_FLIP_H, \
  -LARDHAJJ_THICCNESS - X_OFF + 8*3, Y_OFF + 16*1, 0x58, OAM_FLIP_H, \
  128 \
}
const unsigned char lardhajj_metaspr_right_1[] = LARDHAJJ_RIGHT_METASPR(0x5c);
const unsigned char lardhajj_metaspr_right_2[] = LARDHAJJ_RIGHT_METASPR(0x4e);
const unsigned char lardhajj_metaspr_left_1[] = LARDHAJJ_LEFT_METASPR(0x5c);
const unsigned char lardhajj_metaspr_left_2[] = LARDHAJJ_LEFT_METASPR(0x4e);
const unsigned char *lardhajj_metaspr[] = {
  lardhajj_metaspr_right_1, lardhajj_metaspr_left_1, lardhajj_metaspr_right_2, lardhajj_metaspr_left_2
};

#define LARDHAJJ_HEIGHT 32

#define LARDHAJJ_LEFT_X (8*2 - X_OFF)
#define LARDHAJJ_RIGHT_X (8*30 - X_OFF - LARDHAJJ_THICCNESS)
#define LARDHAJJ_GROUND_POS (8*28 - Y_OFF - LARDHAJJ_HEIGHT)

void fastcall lardhajj_reset(void)
{
  lardhajj_x = 0x8000;
  lardhajj_delta = -0x80;
}

void fastcall lardhajj_tick(void)
{
  lardhajj_x += lardhajj_delta;
  if (MSB(lardhajj_x) < LARDHAJJ_LEFT_X)
  {
    lardhajj_x = LARDHAJJ_LEFT_X << 8;
    lardhajj_delta = -lardhajj_delta;
  }
  else if (MSB(lardhajj_x) >= LARDHAJJ_RIGHT_X)
  {
    lardhajj_x = LARDHAJJ_RIGHT_X << 8;
    lardhajj_delta = -lardhajj_delta;
  }
}

NooseState fastcall lardhajj_check_collide(void)
{
  if (
    noose_y >= LARDHAJJ_GROUND_POS - 8 &&
    noose_y <= LARDHAJJ_GROUND_POS + 8 &&
    noose_x >= MSB(lardhajj_x) - 8 &&
    noose_x <= MSB(lardhajj_x) + 8
  )
  {
    return NOOSE_STATE_HURT;
  }
  return NOOSE_STATE_UNCHANGED;
}

void fastcall lardhajj_render(void)
{
  metaspr_idx = ((MSB(lardhajj_x) >> 1) & 2);
  metaspr_idx |= (MSB(lardhajj_delta) >= 0x80);
  gfx_oam_metaspr(
    MSB(lardhajj_x),
    LARDHAJJ_GROUND_POS,
    lardhajj_metaspr[metaspr_idx]
  );
}
