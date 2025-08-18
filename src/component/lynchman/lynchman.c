#include "lynchman.h"
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

const Lynchable *lynchables[16];
unsigned char insertion_idx;
unsigned char render_idx;
const Lynchable **ptr;

void fastcall lynchman_init()
{
  insertion_idx = 0;
  render_idx = 0;
  memfill(lynchables, 0, sizeof(lynchables));
}

void fastcall lynchman_append(const Lynchable* lynchable)
{
  lynchables[insertion_idx] = lynchable;
  ++insertion_idx;
  lynchable->init();
}

void fastcall lynchman_tick()
{
  unsigned char idx = 0;
  ptr = &lynchables[0];
  for (; idx < sizeof(lynchables) / sizeof(lynchables[0]); ++idx, ++ptr)
  {
    if (*ptr)
    {
      (*(*ptr)->tick)();
    }
  }
}

void fastcall lynchman_render()
{
  unsigned char render_start_idx = render_idx;
  do
  {
    ptr = &lynchables[render_idx];
    if (*ptr)
    {
      (*ptr)->render();
    }
    ++render_idx;
    if (render_idx >= sizeof(lynchables) / sizeof(lynchables[0]))
    {
      render_idx = 0;
    }
  } while (render_idx != render_start_idx);

  ++render_idx;
    if (render_idx >= sizeof(lynchables) / sizeof(lynchables[0]))
    {
      render_idx = 0;
    }
}
