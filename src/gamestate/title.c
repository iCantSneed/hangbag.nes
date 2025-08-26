#include "bigmoneybag_nametable.h"
#include "gamestate.h"
#include "title_nametable.h"
#include <neslib/mmc3.h>
#include <neslib/neslib.h>

#define BACKGROUND_COLOR 0x0f
static const unsigned char palette[32] = {
  BACKGROUND_COLOR, TEXT_PALETTE, // text
  0, 0x02, 0x36, 0x26,            // logo
  0, 0x37, 0x17, 0x07,            // moneybag
  0, BACKGROUND_COLOR, 0, 0,      // sprite 0 hit

  0, BACKGROUND_COLOR, 0, 0,      // sprite 0 hit
};

#define RLE_TAG 0xff
const unsigned char attribute_rle[] = {
  RLE_TAG,
  0b01010101, RLE_TAG, 15,
  0b00000101, RLE_TAG, 7,
  0b10101111, RLE_TAG, 7,
  0b10101010, RLE_TAG, 30,
  0b10101010, RLE_TAG, 0,
};

void fastcall gamestate_title_wait(void);

void fastcall gamestate_title_init(void)
{
  // Declare variables we'll need in the future
  const unsigned char *bigmoneybag_nametable_ptr = bigmoneybag_nametable[0];
  int bigmoneybag_vram_addr = NTADR_A(0, 30 - (sizeof(bigmoneybag_nametable) / sizeof(bigmoneybag_nametable[0])));
  unsigned char i = 0;

  ppu_off();
  pal_all(palette);

  // Set CHR banks
  mmc3_bank_select(2, 0x08);
  mmc3_bank_select(3, 0x09);
  mmc3_bank_select(4, 0x0a);
  mmc3_bank_select(5, 0x0b);

  // Draw title
  vram_adr(NTADR_A(0, 0));
  vram_unrle(title_nametable);

  // Draw big moneybag
  for (;
    i < sizeof(bigmoneybag_nametable) / sizeof(bigmoneybag_nametable[0]);
    ++i, bigmoneybag_nametable_ptr += sizeof(bigmoneybag_nametable[0]), bigmoneybag_vram_addr += 32
  )
  {
    vram_adr(bigmoneybag_vram_addr);
    vram_write(bigmoneybag_nametable_ptr, sizeof(bigmoneybag_nametable[0]));
  }

  // Populate attribute table
  vram_adr(NTADR_A(0, 30));
  vram_unrle(attribute_rle);

  // Place the sprite 0 on the horizontal line
  // Remember that sprite Y-position is off by 1
  oam_spr(0, 8 * (30 - sizeof(bigmoneybag_nametable) / sizeof(bigmoneybag_nametable[0])) + 7 - 1, 0x00, 0, 0);

  // Set nametable mirroring
  mcc3_nametable_arrangement(1);

  ppu_on_all();
  music_play(0);
  next_gamestate = gamestate_title_wait;
}

void fastcall gamestate_title_wait(void)
{
  if (pad_poll(0) & PAD_START)
  {
    next_gamestate = gamestate_play_init;
  }
  split(nesclock(), 0);
}
