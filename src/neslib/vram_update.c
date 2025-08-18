#include <neslib/neslib.h>
#include <string.h>

unsigned char vram_update[64];
unsigned char vram_update_idx;

void fastcall vram_update_init(void)
{
  set_vram_update(vram_update);
}

void fastcall vram_update_reset(void)
{
  vram_update[0] = NT_UPD_EOF;
  vram_update_idx = 0;
}

void fastcall vram_update_append(unsigned int addr, unsigned char length, const unsigned char* bytes)
{
  vram_update[vram_update_idx] = MSB(addr);
  vram_update[++vram_update_idx] = LSB(addr);
  vram_update[++vram_update_idx] = length;
  ++vram_update_idx;
  memcpy(&vram_update[vram_update_idx], bytes, length);
  vram_update_idx += length;
  vram_update[vram_update_idx] = NT_UPD_EOF;
}
