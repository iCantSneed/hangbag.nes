#include <chr/gfx.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char lardhajj_x;
char lardhajj_delta;

#pragma bss-name (push,"RODATA")

const unsigned char lardhajj_metaspr[] = {
  0, 0, 0x50, 0,
  8, 0, 0x52, 0,
  16, 0, 0x54, 0,
  24, 0, 0x56, 0,
  0, 16, 0x58, 0,
  8, 16, 0x5a, 0,
  16, 16, 0x5c, 0,
  24, 16, 0x5e, 0,
  128
};

#define LARDHAJJ_LEFT_X (8*2+14-5)
#define LARDHAJJ_RIGHT_X (8*30-10)
#define LARDHAJJ_GROUND_POS (8*24)

void fastcall lardhajj_reset(void)
{
  lardhajj_x = 0x80;
  lardhajj_delta = -1;
}

void fastcall lardhajj_tick(void)
{
  lardhajj_x += lardhajj_delta;
  if (lardhajj_x <= LARDHAJJ_LEFT_X)
  {
    lardhajj_x = LARDHAJJ_LEFT_X;
    lardhajj_delta = -lardhajj_delta;
  }
  else if (lardhajj_x >= LARDHAJJ_RIGHT_X)
  {
    lardhajj_x = LARDHAJJ_RIGHT_X;
    lardhajj_delta = -lardhajj_delta;
  }
}

unsigned char fastcall lardhajj_check_collide(void)
{
  // TODO
  return FALSE;
}

void fastcall lardhajj_render(void)
{
  gfx_oam_metaspr(lardhajj_x, LARDHAJJ_GROUND_POS, lardhajj_metaspr);
}
