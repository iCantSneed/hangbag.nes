#include "bcd.h"
#include "neslib.h"
#include "vram_update.h"

#pragma bss-name (push,"ZEROPAGE")

Bcd bcd_num;
unsigned char carry;

#pragma bss-name (push,"RODATA")

unsigned char fastcall bcd_add(Bcd* num_ptr, Bcd delta)
{
  bcd_num = *num_ptr;
  carry = FALSE;

  if ((bcd_num & 0x0f) + (delta & 0x0f) > 9)
  {
    bcd_num += 0x10 - 0x0a;
  }
  bcd_num += delta & 0x0f;

  if ((bcd_num & 0xf0) + (delta & 0xf0) > 0x90)
  {
    carry = TRUE;
    bcd_num += 0x100 - 0xa0;
  }
  bcd_num += delta & 0xf0;

  *num_ptr = bcd_num;
  return carry;
}

unsigned char fastcall bcd_add_with_carry(Bcd* num_ptr, Bcd delta)
{
  if (bcd_add(&delta, 0x01))
  {
    *num_ptr = 0x00;
    return TRUE;
  }
  return bcd_add(num_ptr, delta);
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
