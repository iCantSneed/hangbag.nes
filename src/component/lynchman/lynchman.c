#include "lynchable.h"
#include "lynchman.h"
#include <neslib/neslib.h>

#define LYNCHABLE_COUNT 24

#pragma bss-name (push,"ZEROPAGE")

LynchableObject lynchables[LYNCHABLE_COUNT];
NooseState next_noose_state;
unsigned char noose_x, noose_y;
unsigned char lynchable_active_idx;
static LynchableObject lynchable_object;
static unsigned char render_idx;
static struct {
  union {
    struct {
      unsigned char insertion_idx;
      unsigned char prev_active_idx;
    };
  };
} ephemeral;

#pragma bss-name (push,"RODATA")

#define DEF_PTRS(WHAT) extern unsigned char lynchable_ ## WHAT ##_lo[], lynchable_ ## WHAT ##_hi[]
DEF_PTRS(resets);
DEF_PTRS(inits);
DEF_PTRS(ticks);
DEF_PTRS(check_collides);
DEF_PTRS(renders);

#define MAKE_PTR(WHAT) (lynchable_ ## WHAT ##_lo[lynchable_object] | (lynchable_ ## WHAT ##_hi[lynchable_object] << 8))

void fastcall lynchman_init(void)
{
  lynchable_active_idx = 0;
  next_noose_state = NOOSE_STATE_UNCHANGED;
  render_idx = 0;
  memfill(lynchables, LYNCHABLE_NONE, sizeof(lynchables));

  lynchable_object = 0;
  for (; lynchable_object < LYNCHABLE_NONE; ++lynchable_object)
  {
    ((Reset)MAKE_PTR(resets))();
  }
}

void fastcall lynchman_append(LynchableObject lynchable)
{
  ephemeral.insertion_idx = 0;
  for (; lynchables[ephemeral.insertion_idx] != LYNCHABLE_NONE; ++ephemeral.insertion_idx) {}
  ephemeral.prev_active_idx = lynchable_active_idx;
  lynchable_active_idx = ephemeral.insertion_idx;
  lynchable_object = lynchable;
  lynchables[lynchable_active_idx] = lynchable_object;
  ((Init)MAKE_PTR(inits))();
  lynchable_active_idx = ephemeral.prev_active_idx;
}

void fastcall lynchman_tick(void)
{
  lynchable_active_idx = 0;
  for (; lynchable_active_idx < LYNCHABLE_COUNT; ++lynchable_active_idx)
  {
    lynchable_object = lynchables[lynchable_active_idx];
    if (lynchable_object != LYNCHABLE_NONE)
    {
      ((Tick)MAKE_PTR(ticks))();
    }
  }

  lynchable_active_idx = 0;
  for (; lynchable_active_idx < LYNCHABLE_COUNT && next_noose_state == NOOSE_STATE_UNCHANGED; ++lynchable_active_idx)
  {
    lynchable_object = lynchables[lynchable_active_idx];
    if (lynchable_object != LYNCHABLE_NONE)
    {
      next_noose_state = ((CheckCollide)MAKE_PTR(check_collides))();
    }
  }
}

void fastcall lynchman_render(void)
{
  lynchable_active_idx = render_idx;
  do
  {
    lynchable_object = lynchables[lynchable_active_idx];
    if (lynchable_object != LYNCHABLE_NONE)
    {
      ((Render)MAKE_PTR(renders))();
    }
    ++lynchable_active_idx;
    if (lynchable_active_idx >= LYNCHABLE_COUNT)
    {
      lynchable_active_idx = 0;
    }
  } while (lynchable_active_idx != render_idx);

  do
  {
    ++render_idx;
    if (render_idx >= LYNCHABLE_COUNT)
    {
      render_idx = 0;
    }
    lynchable_object = lynchables[render_idx];
  } while (lynchable_object == LYNCHABLE_NONE);
}

void fastcall lynchman_destroy_active(void)
{
  lynchables[lynchable_active_idx] = LYNCHABLE_NONE;
}
