#include <screen/screens.h>
#include <neslib/neslib.h>

void main()
{
  // Init CHR banks
  bank_spr(0);
  bank_bg(1);

  // Init text palettes
  pal_col(1, 0x30);
  pal_col(2, 0x3d);
  pal_col(3, 0x10);

  screen_playfield();
}