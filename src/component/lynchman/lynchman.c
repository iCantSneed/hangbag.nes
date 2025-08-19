#include "lynchable.h"
#include "lynchman.h"
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

LynchableObject lynchables[16];
struct {
  union {
    unsigned char render_idx;
  };
} data;
unsigned char lynchable_attached_idx;
unsigned char noose_x, noose_y;
LynchableObject lynchable_object;
unsigned char lynchable_active_idx;

#pragma bss-name (push,"RODATA")

#define DEF_PTRS(WHAT) extern unsigned char lynchable_ ## WHAT ##_lo[], lynchable_ ## WHAT ##_hi[]
DEF_PTRS(inits);
DEF_PTRS(ticks);
DEF_PTRS(check_collides);
DEF_PTRS(renders);
DEF_PTRS(deinits);

#define MAKE_PTR(WHAT) (lynchable_ ## WHAT ##_lo[lynchable_object] | (lynchable_ ## WHAT ##_hi[lynchable_object] << 8))

void fastcall lynchman_init(void)
{
  lynchable_active_idx = 0;
  lynchable_attached_idx = NO_LYNCHABLE_ATTACHED;
  memfill(lynchables, LYNCHABLE_NONE, sizeof(lynchables));
}

void fastcall lynchman_append(LynchableObject lynchable)
{
  lynchable_object = lynchable;
  lynchables[lynchable_active_idx] = lynchable_object;
  ((Init)MAKE_PTR(inits))();
  ++lynchable_active_idx;
}

void fastcall lynchman_tick(void)
{
  lynchable_active_idx = 0;
  for (; lynchable_active_idx < sizeof(lynchables) / sizeof(lynchables[0]); ++lynchable_active_idx)
  {
    lynchable_object = lynchables[lynchable_active_idx];
    if (lynchable_object != LYNCHABLE_NONE)
    {
      ((Tick)MAKE_PTR(ticks))();
    }
  }

  if (lynchable_attached_idx == NO_LYNCHABLE_ATTACHED)
  {
    lynchable_active_idx = 0;
    for (; lynchable_active_idx < sizeof(lynchables) / sizeof(lynchables[0]); ++lynchable_active_idx)
    {
      lynchable_object = lynchables[lynchable_active_idx];
      if (lynchable_object != LYNCHABLE_NONE && ((CheckCollide)MAKE_PTR(check_collides))())
      {
        lynchable_attached_idx = lynchable_active_idx;
        break;
      }
    }
  }
}

void fastcall lynchman_render(void)
{
  lynchable_active_idx = data.render_idx;
  do
  {
    lynchable_object = lynchables[lynchable_active_idx];
    if (lynchable_object != LYNCHABLE_NONE)
    {
      ((Render)MAKE_PTR(renders))();
    }
    ++lynchable_active_idx;
    if (lynchable_active_idx >= sizeof(lynchables) / sizeof(lynchables[0]))
    {
      lynchable_active_idx = 0;
    }
  } while (lynchable_active_idx != data.render_idx);

  ++data.render_idx;
    if (data.render_idx >= sizeof(lynchables) / sizeof(lynchables[0]))
    {
      data.render_idx = 0;
    }
}

void fastcall lynchman_remove_attached(void)
{
  if (lynchable_attached_idx != NO_LYNCHABLE_ATTACHED)
  {
    lynchable_active_idx = lynchable_attached_idx;
    lynchable_object = lynchables[lynchable_attached_idx];
    ((Deinit)MAKE_PTR(deinits))();
    lynchables[lynchable_attached_idx] = LYNCHABLE_NONE;
    lynchable_attached_idx = NO_LYNCHABLE_ATTACHED;
  }
}
