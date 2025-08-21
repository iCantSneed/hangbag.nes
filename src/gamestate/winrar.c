#include "gamestate.h"
#include "winrar_nametable.h"
#include <neslib/mmc3.h>
#include <neslib/neslib.h>
#include <neslib/vram_update.h>

#define THANKS_Y 26
#define THANKS_VRAM_UPDATE_ADDR_MSB_A (MSB(NTADR_A(0, THANKS_Y)) | NT_UPD_HORZ)
#define THANKS_VRAM_UPDATE_ADDR_MSB_B (MSB(NTADR_B(0, THANKS_Y)) | NT_UPD_HORZ)
#define THANKS_VRAM_UPDATE_ADDR_LSB LSB(NTADR_B(0, THANKS_Y))

extern const unsigned char thanks_text[];
const unsigned char spaces[] = "                               ";

#define BACKGROUND_COLOR 0x0f
static const unsigned char palette[32] = {
  BACKGROUND_COLOR, TEXT_PALETTE,
  0, 0x18, 0x38, 0x28,
  0, 0x07, 0x07, 0x17,
  0, 0x38, 0x27, 0x07,

  0, BACKGROUND_COLOR, 0, 0, // sprite 0
};

unsigned int x_scroll;
unsigned char thanks_text_idx;
unsigned char skip_next_nametable;

void fastcall gamestate_winrar_wait(void);

void fastcall gamestate_winrar_init(void)
{
  ppu_off();
  oam_clear();
  pal_all(palette);

  // Set static CHR banks
  mmc3_bank_select(4, 0x0e);
  mmc3_bank_select(5, 0x0f);

  // Set nametable mirroring (needs to be done before drawing)
  mcc3_nametable_arrangement(0);

  // Draw nametable
  vram_adr(NTADR_A(0, 0));
  vram_unrle(winrar_nametable);

  // Set nametable B attributes (just in case)
  vram_adr(NTADR_B(0, 30));
  vram_fill(0b00000000, 64);

  // Draw thanks text
  vram_adr(NTADR_B(0, THANKS_Y));
  vram_write(&thanks_text[0], 32);

  // Place sprite 0 on the last visible pixel, which as the bottom-right of the "!"
  // Remember that sprite Y-position is off by 1
  oam_spr(192 + 7, 184 + 7 - 1, 0x00, 0, 0);

  // Init variables
  x_scroll = 0;
  thanks_text_idx = 32;
  skip_next_nametable = FALSE;

  ppu_on_all();
  next_gamestate = gamestate_winrar_wait;
}

void fastcall gamestate_winrar_wait(void)
{
  // Set top half of CHR banks
  mmc3_bank_select(2, 0x0c);
  mmc3_bank_select(3, 0x0d);

  ++x_scroll;
  if (LSB(x_scroll) == 0)
  {
    vram_update_append(
      ((((MSB(x_scroll) & 1) == 1) ? THANKS_VRAM_UPDATE_ADDR_MSB_A : THANKS_VRAM_UPDATE_ADDR_MSB_B) << 8) | THANKS_VRAM_UPDATE_ADDR_LSB,
      32,
      skip_next_nametable ? spaces : &thanks_text[thanks_text_idx]
    );

    skip_next_nametable = FALSE;
    thanks_text_idx += 32;
    if (thanks_text[thanks_text_idx] == '\0')
    {
      skip_next_nametable = TRUE;
      thanks_text_idx = -32;
    }
  }

  // Split and change banks at sprite 0 hit
  split(x_scroll, 0);
  mmc3_bank_select(2, 0x04);
  mmc3_bank_select(3, 0x05);
}
