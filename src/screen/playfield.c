#include <component/controller/controller.h>
#include <component/moneybag/moneybag.h>
#include <component/player/player.h>
#include <component/score/score.h>
#include <neslib/neslib.h>

void fastcall screen_playfield()
{
  pal_col(0, 0x00);
  score_init();
  player_init();
  moneybag_init();

  ppu_on_all();

  while (1)
  {
    controller_tick();
    player_tick();
    moneybag_tick();
    ppu_wait_nmi();
  }
}