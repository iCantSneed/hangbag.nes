#include "gamestate.h"
#include "winrar_nametable.h"
#include <neslib/mmc3.h>
#include <neslib/neslib.h>

static const unsigned char palette[32] = {
  0x0f, TEXT_PALETTE,
  0, 0x18, 0x38, 0x28,
  0, 0x07, 0x07, 0x17,
  0, 0x38, 0x27, 0x07,
};

void fastcall gamestate_winrar_wait(void);

void fastcall gamestate_winrar_init(void)
{
  ppu_off();
  oam_clear();
  pal_all(palette);

  // Set static CHR banks
  mmc3_bank_select(4, 0x0e);
  mmc3_bank_select(5, 0x0f);

  // Draw nametable
  vram_adr(NTADR_A(0, 0));
  vram_unrle(winrar_nametable);

  // Set nametable mirroring
  mcc3_nametable_arrangement(0);

  ppu_on_all();
  next_gamestate = gamestate_winrar_wait;
}

void fastcall gamestate_winrar_wait(void)
{
  // Set top half of CHR banks
  mmc3_bank_select(2, 0x0c);
  mmc3_bank_select(3, 0x0d);
}
