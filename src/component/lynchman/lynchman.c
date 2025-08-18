#include "lynchable.h"
#include "lynchman.h"
#include <component/moneybag/moneybag.h>
#include <component/pyrite/pyrite.h>
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

LynchableObject lynchables[16];
unsigned char insertion_idx;
unsigned char render_idx;
unsigned char lynchable_attached_idx;
unsigned char noose_x, noose_y;
unsigned char lynchable_object;

#pragma bss-name (push,"RODATA")

const Init lynchable_inits[] = { moneybag_init, pyrite_init };
const Tick *lynchable_ticks[] = { &moneybag_tick, &pyrite_tick };
const CheckCollide lynchable_check_collides[] = { moneybag_check_collide, pyrite_check_collide };
const Render lynchable_renders[] = { moneybag_render, pyrite_render };
const Deinit lynchable_deinits[] = { NULL, pyrite_deinit };

void fastcall lynchman_init(void)
{
  insertion_idx = 0;
  render_idx = 0;
  lynchable_attached_idx = NO_LYNCHABLE_ATTACHED;
  memfill(lynchables, LYNCHABLE_NONE, sizeof(lynchables));
}

void fastcall lynchman_append(LynchableObject lynchable)
{
  lynchables[insertion_idx] = lynchable;
  lynchable_inits[lynchable](insertion_idx);
  ++insertion_idx;
}

void fastcall lynchman_tick(void)
{
  unsigned char idx = 0;
  for (; idx < sizeof(lynchables) / sizeof(lynchables[0]); ++idx)
  {
    lynchable_object = lynchables[idx];
    if (lynchable_object != LYNCHABLE_NONE)
    {
      (*lynchable_ticks[lynchable_object])(idx);
    }
  }

  if (lynchable_attached_idx == NO_LYNCHABLE_ATTACHED)
  {
    idx = 0;
    for (; idx < sizeof(lynchables) / sizeof(lynchables[0]); ++idx)
    {
      lynchable_object = lynchables[idx];
      if (lynchable_object != LYNCHABLE_NONE && lynchable_check_collides[lynchable_object](idx))
      {
        lynchable_attached_idx = idx;
        break;
      }
    }
  }
}

void fastcall lynchman_render(void)
{
  unsigned char render_start_idx = render_idx;
  do
  {
    lynchable_object = lynchables[render_idx];
    if (lynchable_object != LYNCHABLE_NONE)
    {
      lynchable_renders[lynchable_object](render_idx);
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

void fastcall lynchman_remove_attached(void)
{
  if (lynchable_attached_idx != NO_LYNCHABLE_ATTACHED)
  {
    lynchable_deinits[lynchable_object](lynchable_attached_idx);
    lynchables[lynchable_attached_idx] = LYNCHABLE_NONE;
    lynchable_attached_idx = NO_LYNCHABLE_ATTACHED;
  }
}
