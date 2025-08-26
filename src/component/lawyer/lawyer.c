#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

static struct {
  unsigned int lawyer_obj_vram_addr;
  const unsigned char *lawyer_obj_ptr;
} ephemeral;

#pragma bss-name (push,"RODATA")

const unsigned char lawyer_obj_rows[][3] = {
  {0x0e, 0x0f, 0x00},
  {0x1e, 0x1f, 0x00},
  {0x0c, 0x0d, 0x1d},
};

#define LAWYER_OBJ_ROW 14

void fastcall lawyer_init_0(void)
{
  ephemeral.lawyer_obj_vram_addr = NTADR_A(2, LAWYER_OBJ_ROW);
  ephemeral.lawyer_obj_ptr = lawyer_obj_rows;
  for (
    ;
    ephemeral.lawyer_obj_ptr < (lawyer_obj_rows + sizeof(lawyer_obj_rows) / sizeof(lawyer_obj_rows[0]));  // TODO why???
    ephemeral.lawyer_obj_vram_addr += 32, ephemeral.lawyer_obj_ptr += sizeof(lawyer_obj_rows) / sizeof(lawyer_obj_rows[0]))
  {
    vram_adr(ephemeral.lawyer_obj_vram_addr);
    vram_write(ephemeral.lawyer_obj_ptr, sizeof(lawyer_obj_rows[0]));
  }
}
