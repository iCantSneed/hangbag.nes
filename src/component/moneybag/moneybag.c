#include "moneybag.h"
#include <chr/gfx.h>
#include <component/lynchman/lynchman.h>
#include <gamestate/gamestate.h>

#pragma bss-name (push,"ZEROPAGE")

void (*fastcall moneybag_tick)(unsigned char);
unsigned int moneybag_x_pos, moneybag_y_pos;
int moneybag_x_velocity, moneybag_y_velocity;
unsigned char moneybag_idle_frame;
unsigned char moneybag_x_velocity_negative;
unsigned char const* moneybag_metaspr_render;

#pragma bss-name (push,"RODATA")

const unsigned char moneybag_normal_metaspr[] = {
  -14, -9, 0x10, 0,
  -6,  -9, 0x12, 0,
  2,   -9, 0x14, 0,
  10,  -9, 0x16, 0,
  -14, 7,  0x18, 0,
  -6,  7,  0x1a, 0,
  2,   7,  0x1c, 0,
  10,  7,  0x1e, 0,
  128
};

const unsigned char moneybag_fat_metaspr[] = {
  -14, -9, 0x20, 0,
  -6,  -9, 0x22, 0,
  2,   -9, 0x24, 0,
  10,  -9, 0x26, 0,
  -14, 7,  0x28, 0,
  -6,  7,  0x2a, 0,
  2,   7,  0x2c, 0,
  10,  7,  0x2e, 0,
  128
};

const unsigned char moneybag_skinny_metaspr[] = {
  -6,  -9, 0x30, 0,
  2,   -9, 0x32, 0,
  -14, 7,  0x34, 0,
  -6,  7,  0x36, 0,
  2,   7,  0x38, 0,
  -6,  23, 0x3a, 0,
  2,   23, 0x3c, 0,
  128
};

#define MONEYBAG_GROUND_Y_POS 0xc900
#define MONEYBAG_IDLE_Y_POS ((MONEYBAG_GROUND_Y_POS >> 8) + 0x02)
#define MONEYBAG_GRAVITY 0x29
#define MONEYBAG_LEFT_X (8*2+14-5)
#define MONEYBAG_RIGHT_X (8*30-10)

#define NOOSE_X_TOLERANCE 8
#define NOOSE_Y_TOLERANCE 4

void fastcall moneybag_tick_prepare_jump(unsigned char);
void fastcall moneybag_tick_jumping(unsigned char);
void fastcall moneybag_tick_falling(unsigned char);
void fastcall moneybag_tick_landed(unsigned char);

void fastcall moneybag_init(unsigned char)
{
  moneybag_tick = moneybag_tick_prepare_jump;
  moneybag_x_pos = MONEYBAG_LEFT_X << 8;
  moneybag_y_pos = MONEYBAG_GROUND_Y_POS;
  moneybag_idle_frame = 0;
  moneybag_x_velocity_negative = FALSE;
  moneybag_metaspr_render = moneybag_normal_metaspr;
}

void fastcall moneybag_render(unsigned char)
{
  gfx_oam_metaspr(MSB(moneybag_x_pos), MSB(moneybag_y_pos), moneybag_metaspr_render);
}

void fastcall airborne_adjust_position(void)
{
  moneybag_x_pos += moneybag_x_velocity;
  if (MSB(moneybag_x_pos) < MONEYBAG_LEFT_X)
  {
    moneybag_x_pos = MONEYBAG_LEFT_X << 8;
    moneybag_x_velocity = -moneybag_x_velocity;
    moneybag_x_velocity_negative = FALSE;
  }
  else if (MSB(moneybag_x_pos) >= MONEYBAG_RIGHT_X)
  {
    moneybag_x_pos = ((MONEYBAG_RIGHT_X - 1) << 8) | 0xff;
    moneybag_x_velocity = -moneybag_x_velocity;
    moneybag_x_velocity_negative = TRUE;
  }

  moneybag_y_velocity += MONEYBAG_GRAVITY;
  moneybag_y_pos += moneybag_y_velocity;
}

void fastcall moneybag_tick_prepare_jump(unsigned char)
{
  moneybag_x_velocity = (rand16() & 0x01ff) + 0x3f;
  if (LSB(moneybag_x_velocity) < 64) // 25% probability that the velocity will be reversed
  {
    moneybag_x_velocity_negative ^= TRUE;
  }
  if (moneybag_x_velocity_negative)
  {
    moneybag_x_velocity = -moneybag_x_velocity;
  }

  moneybag_y_velocity = -(rand16() & 0x02ff) - 0x01ff;
  moneybag_tick = moneybag_tick_jumping;
  moneybag_metaspr_render = moneybag_skinny_metaspr;
}

void fastcall moneybag_tick_jumping(unsigned char)
{
  airborne_adjust_position();
  if (MSB(moneybag_y_velocity) > 0)
  {
    moneybag_tick = moneybag_tick_falling;
    moneybag_metaspr_render = moneybag_normal_metaspr;
  }
}

void fastcall moneybag_tick_falling(unsigned char)
{
  airborne_adjust_position();
  if (MSB(moneybag_y_pos) >= MSB(MONEYBAG_GROUND_Y_POS))
  {
    moneybag_y_pos = MONEYBAG_IDLE_Y_POS << 8;
    moneybag_idle_frame = (rand8() & 15) + 15;
    moneybag_tick = moneybag_tick_landed;
    moneybag_metaspr_render = moneybag_fat_metaspr;
  }
}

void fastcall moneybag_tick_landed(unsigned char)
{
  --moneybag_idle_frame;
  if (!moneybag_idle_frame)
  {
    moneybag_y_pos = MONEYBAG_GROUND_Y_POS;
    moneybag_tick = moneybag_tick_prepare_jump;
    moneybag_metaspr_render = moneybag_normal_metaspr;
  }
}

unsigned char fastcall moneybag_check_collide(unsigned char)
{
  if (
    moneybag_idle_frame &&
    noose_x >= MSB(moneybag_x_pos) - NOOSE_X_TOLERANCE &&
    noose_x <= MSB(moneybag_x_pos) + NOOSE_X_TOLERANCE &&
    noose_y >= MONEYBAG_IDLE_Y_POS - NOOSE_Y_TOLERANCE &&
    noose_y <= MONEYBAG_IDLE_Y_POS + NOOSE_Y_TOLERANCE
  )
  {
    next_gamestate = gamestate_play_moneybag_hanged;
    moneybag_x_pos = noose_x << 8;
    moneybag_metaspr_render = moneybag_skinny_metaspr;
    return TRUE;
  }
  return FALSE;
}
