#include <neslib/neslib.h>
#include <string.h>

unsigned char textbox[32];
unsigned char textbox_idx;

void fastcall textbox_init()
{
  textbox[0] = NT_UPD_EOF;
  set_vram_update(textbox);
}

void fastcall textbox_tick()
{
  textbox[0] = NT_UPD_EOF;
  textbox_idx = -1;
}

void fastcall textbox_append(unsigned int addr, unsigned char length, const unsigned char* bytes)
{
  textbox[++textbox_idx] = MSB(addr);
  textbox[++textbox_idx] = LSB(addr);
  textbox[++textbox_idx] = length;
  ++textbox_idx;
  memcpy(&textbox[textbox_idx], bytes, length);
  textbox_idx += length;
  textbox[textbox_idx] = NT_UPD_EOF;
}
