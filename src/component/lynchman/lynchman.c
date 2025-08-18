#include "lynchman.h"
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

const Lynchable *lynchables[16];
unsigned char insertion_idx;
unsigned char render_idx;
const Lynchable **ptr;
unsigned char lynchable_attached_idx;
unsigned char noose_x, noose_y;

void fastcall lynchman_init()
{
  insertion_idx = 0;
  render_idx = 0;
  lynchable_attached_idx = NO_LYNCHABLE_ATTACHED;
  memfill(lynchables, 0, sizeof(lynchables));
}

void fastcall lynchman_append(const Lynchable* lynchable)
{
  lynchables[insertion_idx] = lynchable;
  lynchable->init(insertion_idx);
  ++insertion_idx;
}

void fastcall lynchman_tick()
{
  unsigned char idx = 0;
  ptr = &lynchables[0];
  for (; idx < sizeof(lynchables) / sizeof(lynchables[0]); ++idx, ++ptr)
  {
    if (*ptr)
    {
      (*(*ptr)->tick)(idx);
    }
  }

  if (lynchable_attached_idx == NO_LYNCHABLE_ATTACHED)
  {
    idx = 0;
    ptr = &lynchables[0];
    for (; idx < sizeof(lynchables) / sizeof(lynchables[0]); ++idx, ++ptr)
    {
      if (*ptr && (*ptr)->check_collide(idx))
      {
        lynchable_attached_idx = idx;
        break;
      }
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
      (*ptr)->render(render_idx);
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
