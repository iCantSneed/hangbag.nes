#include "textbox.h"
#include <neslib/neslib.h>
#include <neslib/vram_update.h>

#pragma bss-name (push,"ZEROPAGE")

TextboxTick textbox_tick;
unsigned char const* textbox_ptr;
unsigned int text_vram_addr;
unsigned char line_count;
unsigned char curr_char;

#pragma bss-name (push,"RODATA")

#define TEXT_VRAM_X_INIT 3
#define TEXT_VRAM_ADDR_INIT (NTADR_A(TEXT_VRAM_X_INIT, 7) | (NT_UPD_HORZ << 8))

const unsigned char blank_line[] = "                          ";

char fastcall textbox_tick_write();
char fastcall textbox_tick_clear();

void fastcall textbox_init()
{
  textbox_tick = textbox_tick_write;
  text_vram_addr = TEXT_VRAM_ADDR_INIT;
  line_count = 0;
}

char fastcall textbox_tick_write()
{
  curr_char = *textbox_ptr;
  if (curr_char == 0x00)
  {
    return TRUE;
  }
  if (curr_char == '\f')
  {
    if (pad_state(0) & PAD_A)
    {
      textbox_tick = textbox_tick_clear;
      text_vram_addr = TEXT_VRAM_ADDR_INIT;
      ++line_count;
    }
  }
  else if (curr_char == '\n')
  {
    text_vram_addr = (text_vram_addr & 0xffe0) + 0x20 + TEXT_VRAM_X_INIT;
    ++textbox_ptr;
    ++line_count;
  }
  else
  {
    vram_update_append(text_vram_addr, 1, textbox_ptr);
    ++textbox_ptr;
    ++text_vram_addr;
  }
  return FALSE;
}

char fastcall textbox_tick_clear()
{
  vram_update_append(text_vram_addr, sizeof(blank_line) - 1, blank_line);
  --line_count;
  if (!line_count)
  {
    textbox_init();
    ++textbox_ptr;
  }
  else
  {
    text_vram_addr += 0x20;
  }
  return FALSE;
}
