#include <component/controller/controller.h>
#include <component/moneybag/moneybag.h>
#include <component/player/player.h>
#include <component/score/score.h>
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

unsigned char i;

#pragma bss-name (push,"RODATA")

void fastcall screen_playfield()
{
  pal_col(0, 0x00);
  score_init();
  player_init();
  moneybag_init();

  // Prepare palette
  pal_col(4+1, 0x0f);
  pal_col(4+2, 0x15);
  pal_col(4+3, 0x05);

  // Draw bricks on the side
  i = 4;
  vram_adr(NTADR_A(0, 4));
  for (; i < 28; ++i)
  {
    vram_put(0x80);
    vram_put(0x80);
    vram_fill(' ', 28);
    vram_put(0x80);
    vram_put(0x80);
  }
  i = 0;
  vram_adr(0x23d0);
  for (; i < 5; ++i)
  {
    vram_put(0b00010001);
    vram_fill(0, 6);
    vram_put(0b01000100);
  }

  // Draw the grated floor
  vram_adr(NTADR_A(2, 6));
  vram_fill(0x81, 28);
  vram_adr(0x23c8);
  vram_fill(0b01010101, 8);

  // Draw bricks at the bottom
  vram_adr(NTADR_A(0, 28));
  vram_fill(0x80, 64);
  vram_adr(0x23f8);
  vram_fill(0b01010101, 8);

  ppu_on_all();

  while (1)
  {
    controller_tick();
    player_tick();
    moneybag_tick();
    ppu_wait_nmi();
  }
}