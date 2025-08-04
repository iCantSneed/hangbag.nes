#include <screen/screens.h>
#include <neslib/neslib.h>

void main()
{
  bank_spr(0);
  bank_bg(1);
  screen_playfield();
}