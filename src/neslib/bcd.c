#include "bcd.h"
#include "neslib.h"
#include "vram_update.h"

#pragma bss-name (push,"ZEROPAGE")

Bcd bcd_num;

#pragma bss-name (push,"RODATA")

Bcd fastcall bcd_add(Bcd* num, Bcd delta)
{
  // TODO
  *num += delta;
  return 0x00;
}

unsigned char fastcall bcd_decrement(Bcd* num_ptr)
{
  bcd_num = *num_ptr;
  if (!bcd_num)
  {
    return TRUE;
  }
  if ((bcd_num & 0x0f) == 0x00)
  {
    bcd_num -= 0x10 - 0x09;
  }
  else
  {
    --bcd_num;
  }
  *num_ptr = bcd_num;
  return FALSE;
}

void fastcall bcd_vram_update(Bcd num, unsigned int vram_update_addr)
{
  unsigned char bytes[2];
  bytes[0] = (num >> 4) + '0';
  bytes[1] = (num & 0xf) + '0';
  vram_update_append(vram_update_addr, sizeof(bytes), bytes);
}
