#include "moneybag.h"
#include "moneybag_internal.h"
#include <component/gamestate/gamestate.h>
#include <component/player/player.h>
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned int moneybag_x_pos, moneybag_y_pos;
int moneybag_x_velocity, moneybag_y_velocity;
jumpaction next_jump_action;
unsigned char moneybag_idle_frame;
unsigned char moneybag_x_velocity_negative;
unsigned char const* moneybag_metaspr_render;

#pragma bss-name (push,"RODATA")

#define MONEYBAG_TOP_METASPR \
  -6, -9, 0x01, 0x00, \
  2,  -9, 0x02, 0x00

const unsigned char moneybag_normal_metaspr[] = {
  MONEYBAG_TOP_METASPR,
  -14, -1, 0x10, 0x00,
  -6,  -1, 0x11, 0x00,
  2,   -1, 0x12, 0x00,
  10,  -1, 0x13, 0x00,
  -14, 7,  0x20, 0x00,
  -6,  7,  0x21, 0x00,
  2,   7,  0x22, 0x00,
  10,  7,  0x23, 0x00,
  -14, 15, 0x30, 0x00,
  -6,  15, 0x31, 0x00,
  2,   15, 0x32, 0x00,
  10,  15, 0x33, 0x00,
  128
};

const unsigned char moneybag_fat_metaspr[] = {
  MONEYBAG_TOP_METASPR,
  -14, -1, 0x14, 0x00,
  -6,  -1, 0x15, 0x00,
  2,   -1, 0x16, 0x00,
  10,  -1, 0x17, 0x00,
  -14, 7,  0x24, 0x00,
  -6,  7,  0x25, 0x00,
  2,   7,  0x26, 0x00,
  10,  7,  0x27, 0x00,
  -14, 15, 0x34, 0x00,
  -6,  15, 0x35, 0x00,
  2,   15, 0x36, 0x00,
  10,  15, 0x37, 0x00,
  128
};

const unsigned char moneybag_skinny_metaspr[] = {
  MONEYBAG_TOP_METASPR,
  -6,  -1, 0x19, 0x00,
  2,   -1, 0x1a, 0x00,
  -14, 7,  0x28, 0x00,
  -6,  7,  0x29, 0x00,
  2,   7,  0x2a, 0x00,
  -14, 15, 0x38, 0x00,
  -6,  15, 0x39, 0x00,
  2,   15, 0x3a, 0x00,
  -6,  23, 0x49, 0x00,
  2,   23, 0x4a, 0x00,
  128
};

#define MONEYBAG_GRAVITY 0x29
#define MONEYBAG_LEFT_X (8*2+14-5)
#define MONEYBAG_RIGHT_X (8*30-10)

void fastcall moneybag_init()
{
  moneybag_x_pos = MONEYBAG_LEFT_X << 8;
  moneybag_y_pos = MONEYBAG_GROUND_Y_POS;
  next_jump_action = &jump_action_prepare_jump;
  moneybag_idle_frame = 0;
  moneybag_x_velocity_negative = FALSE;
  moneybag_metaspr_render = moneybag_normal_metaspr;
}

void fastcall moneybag_tick()
{
  if (game_state == GAME_STATE_COMPLETED)
  {
    moneybag_x_pos = player_x_pos << 8;
    moneybag_metaspr_render = moneybag_skinny_metaspr;
  }
  else if (game_state == GAME_STATE_PLAYING)
  {
    next_jump_action();
  }
}

void fastcall moneybag_render()
{
  oam_meta_spr_clip(MSB(moneybag_x_pos), MSB(moneybag_y_pos), moneybag_metaspr_render);
}

void fastcall airborne_adjust_position()
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

void jump_action_prepare_jump()
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
  next_jump_action = &jump_action_jumping;
  moneybag_metaspr_render = moneybag_skinny_metaspr;
}

void jump_action_jumping()
{
  airborne_adjust_position();
  if (MSB(moneybag_y_velocity) > 0)
  {
    next_jump_action = &jump_action_falling;
    moneybag_metaspr_render = moneybag_normal_metaspr;
  }
}

void jump_action_falling()
{
  airborne_adjust_position();
  if (MSB(moneybag_y_pos) >= MSB(MONEYBAG_GROUND_Y_POS))
  {
    moneybag_y_pos = MONEYBAG_IDLE_Y_POS << 8;
    moneybag_idle_frame = (rand8() & 15) + 15;
    next_jump_action = &jump_action_landed;
    moneybag_metaspr_render = moneybag_fat_metaspr;
  }
}

void jump_action_landed()
{
  --moneybag_idle_frame;
  if (!moneybag_idle_frame)
  {
    moneybag_y_pos = MONEYBAG_GROUND_Y_POS;
    next_jump_action = &jump_action_prepare_jump;
    moneybag_metaspr_render = moneybag_normal_metaspr;
  }
}
