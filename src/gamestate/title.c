#include "bigmoneybag_nametable.h"
#include "gamestate.h"
#include "title_nametable.h"
#include <neslib/mmc3.h>
#include <neslib/neslib.h>

#define RLE_TAG 0xff
const unsigned char attribute_rle[] = {
  RLE_TAG,
  0b01010101, RLE_TAG, 15,
  0b00000101, RLE_TAG, 7,
  0b10101010, RLE_TAG, 38,
  0b10101010, RLE_TAG, 0,
};

void fastcall gamestate_title_wait();

void fastcall gamestate_title_init()
{
  // Declare variables we'll need in the future
  const unsigned char *bigmoneybag_nametable_ptr = bigmoneybag_nametable[0];
  int bigmoneybag_vram_addr = NTADR_A(0, 14);
  unsigned char i = 0;

  ppu_off();
  pal_col(0, 0x0f);

  // Set CHR banks
  mmc3_bank_select(2, 0x08);
  mmc3_bank_select(3, 0x09);
  mmc3_bank_select(4, 0x0a);
  mmc3_bank_select(5, 0x0b);

  // Set logo palette
  pal_col(5, 0x02);
  pal_col(6, 0x36);
  pal_col(7, 0x26);

  // Set moneybag palette
  pal_col(9, 0x37);
  pal_col(10, 0x17);
  pal_col(11, 0x07);

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

  ppu_on_bg();
  next_gamestate = gamestate_title_wait;
}

void fastcall gamestate_title_wait()
{
  if (pad_state(0) & PAD_START)
  {
    next_gamestate = gamestate_play_init;
  }
}
