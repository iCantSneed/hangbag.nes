#include <neslib/bcd.h>
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

Bcd score[3];

#pragma bss-name (push,"RODATA")

#define SCORE_ROW 2
#define SCORE_COL 22
#define SCORE_VRAM_UPDATE_ADDR (NTADR_A(SCORE_COL + 1, SCORE_ROW) | (NT_UPD_HORZ << 8))

void fastcall score_draw(void)
{
  bcd_vram_update(score[0], SCORE_VRAM_UPDATE_ADDR);
  bcd_vram_update(score[1], SCORE_VRAM_UPDATE_ADDR + 2);
  bcd_vram_update(score[2], SCORE_VRAM_UPDATE_ADDR + 4);
}

void fastcall score_init(void)
{
  score_draw();
}

void fastcall score_add(Bcd delta)
{
  if (bcd_add(&score[2], delta))
  {
    if (bcd_add_with_carry(&score[1], 0x00))
    {
      bcd_add_with_carry(&score[0], 0x00);
    }
  }
  score_draw();
}
