#include "moneybag_internal.h"
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned int moneybag_x_pos, moneybag_y_pos;
int moneybag_x_velocity, moneybag_y_velocity;
jumpaction next_jump_action;
unsigned char idle_frame;

#pragma bss-name (push,"RODATA")

#define MONEYBAG_TOP_METASPR \
  8,  0, 0x01, 0x00, \
  16, 0, 0x02, 0x00

const unsigned char moneybag_normal_metaspr[] = {
  MONEYBAG_TOP_METASPR,
  0,  8,  0x10, 0x00,
  8,  8,  0x11, 0x00,
  16, 8,  0x12, 0x00,
  24, 8,  0x13, 0x00,
  0,  16, 0x20, 0x00,
  8,  16, 0x21, 0x00,
  16, 16, 0x22, 0x00,
  24, 16, 0x23, 0x00,
  0,  24, 0x30, 0x00,
  8,  24, 0x31, 0x00,
  16, 24, 0x32, 0x00,
  24, 24, 0x33, 0x00,
  128
};

const unsigned char moneybag_fat_metaspr[] = {
  MONEYBAG_TOP_METASPR,
  0,  8,  0x14, 0x00,
  8,  8,  0x15, 0x00,
  16, 8,  0x16, 0x00,
  24, 8,  0x17, 0x00,
  0,  16, 0x24, 0x00,
  8,  16, 0x25, 0x00,
  16, 16, 0x26, 0x00,
  24, 16, 0x27, 0x00,
  0,  24, 0x34, 0x00,
  8,  24, 0x35, 0x00,
  16, 24, 0x36, 0x00,
  24, 24, 0x37, 0x00,
  128
};

const unsigned char moneybag_skinny_metaspr[] = {
  MONEYBAG_TOP_METASPR,
  8,  8,  0x19, 0x00,
  16, 8,  0x1a, 0x00,
  0,  16, 0x28, 0x00,
  8,  16, 0x29, 0x00,
  16, 16, 0x2a, 0x00,
  0,  24, 0x38, 0x00,
  8,  24, 0x39, 0x00,
  16, 24, 0x3a, 0x00,
  8,  32, 0x49, 0x00,
  16, 32, 0x4a, 0x00,
  -1, -1, 0x00, 0x00, //pad
  -1, -1, 0x00, 0x00, //pad
  128
};

#define MONEYBAG_SPR_IDX 4*13

#define MONEYBAG_GROUND_Y_POS 0xc000
#define MONEYBAG_GRAVITY 0x29
#define MONEYBAG_IDLE_FRAMES 10

void fastcall moneybag_init()
{
  moneybag_x_pos = 0x8000;
  moneybag_y_pos = MONEYBAG_GROUND_Y_POS;
  next_jump_action = &jump_action_prepare_jump;
  idle_frame = 0;
}

void fastcall moneybag_tick()
{
  next_jump_action();
}

void jump_action_prepare_jump()
{
  oam_meta_spr(MSB(moneybag_x_pos), MSB(moneybag_y_pos), MONEYBAG_SPR_IDX, moneybag_normal_metaspr);
  moneybag_x_velocity = (unsigned int)rand8() + 0x100;
  moneybag_y_velocity = -(rand16() & 0x01ff) - 0x02ff;
  next_jump_action = &jump_action_jumping;
}

void jump_action_jumping()
{
  moneybag_x_pos += moneybag_x_velocity;
  moneybag_y_velocity += MONEYBAG_GRAVITY;
  moneybag_y_pos += moneybag_y_velocity;
  oam_meta_spr(MSB(moneybag_x_pos), MSB(moneybag_y_pos), MONEYBAG_SPR_IDX, moneybag_skinny_metaspr);
  if (MSB(moneybag_y_velocity) > 0)
  {
    next_jump_action = &jump_action_falling;
  }
}

void jump_action_falling()
{
  moneybag_x_pos += moneybag_x_velocity;
  moneybag_y_velocity += MONEYBAG_GRAVITY;
  moneybag_y_pos += moneybag_y_velocity;
  oam_meta_spr(MSB(moneybag_x_pos), MSB(moneybag_y_pos), MONEYBAG_SPR_IDX, moneybag_normal_metaspr);
  if (MSB(moneybag_y_pos) >= MSB(MONEYBAG_GROUND_Y_POS))
  {
    moneybag_y_pos = MONEYBAG_GROUND_Y_POS;
    next_jump_action = &jump_action_landed;
  }
}

void jump_action_landed()
{
  oam_meta_spr(MSB(moneybag_x_pos), MSB(moneybag_y_pos), MONEYBAG_SPR_IDX, moneybag_fat_metaspr);
  ++idle_frame;
  if (idle_frame == MONEYBAG_IDLE_FRAMES)
  {
    idle_frame = 0;
    next_jump_action = &jump_action_prepare_jump;
  }
}
