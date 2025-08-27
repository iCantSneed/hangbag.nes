#include "lawyer.h"
#include <component/hammer/hammer.h>
#include <neslib/neslib.h>

typedef const unsigned char LawyerObjRow[LAWYER_OBJ_WIDTH];

#pragma bss-name (push,"ZEROPAGE")

static struct {
  unsigned int lawyer_obj_vram_addr;
  LawyerObjRow *lawyer_obj_ptr;
} ephemeral;

#pragma bss-name (push,"RODATA")

LawyerObjRow lawyer_obj_rows[LAWYER_OBJ_HEIGHT] = {
  {0x0e, 0x0f, 0x00},
  {0x1e, 0x1f, 0x00},
  {0x0c, 0x0d, 0x1d},
};

void fastcall lawyer_init_0(void)
{
  ephemeral.lawyer_obj_vram_addr = NTADR_A(LAWYER0_OBJ_COL, LAWYER_OBJ_ROW);
  ephemeral.lawyer_obj_ptr = lawyer_obj_rows;
  for (
    ;
    ephemeral.lawyer_obj_ptr < (lawyer_obj_rows + LAWYER_OBJ_HEIGHT); // just a fun C thing
    ephemeral.lawyer_obj_vram_addr += 32, ++ephemeral.lawyer_obj_ptr  // this too
  )
  {
    vram_adr(ephemeral.lawyer_obj_vram_addr);
    vram_write((const unsigned char*)ephemeral.lawyer_obj_ptr, LAWYER_OBJ_WIDTH);
  }
}

void fastcall lawyer_tick_0(void)
{
  rand8(); // dummy call because otherwise the moneybag becomes too predictable
  if (rand8() > 0xfc)
  {
    hammer_spawn_at_lawyer(0);
  }
}
