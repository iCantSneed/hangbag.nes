#if !defined(LYNCHMAN_H_)
#define LYNCHMAN_H_

#define NOOSE_Y_INACTIVE 0xff

typedef enum {
  LYNCHABLE_PYRITEMAN,
  LYNCHABLE_MONEYBAG_REGULAR,
  LYNCHABLE_MONEYBAG_AGGRO,
  LYNCHABLE_SCISSORS,
  LYNCHABLE_LARDHAJJ,
  LYNCHABLE_PYRITE,
  LYNCHABLE_MONEYBAG_HANGRY,
  LYNCHABLE_NONE
} LynchableObject;

typedef enum {
  NOOSE_STATE_UNCHANGED,
  NOOSE_STATE_ATTACHED,
  NOOSE_STATE_HURT,
} NooseState;

extern unsigned char noose_x;
#pragma zpsym ("noose_x")

extern unsigned char noose_y;
#pragma zpsym ("noose_y")

extern NooseState next_noose_state;
#pragma zpsym ("next_noose_state")

extern unsigned char lynchable_active_idx;
#pragma zpsym ("lynchable_active_idx")

void fastcall lynchman_init(void);
void fastcall lynchman_append(LynchableObject);
void fastcall lynchman_tick(void);
void fastcall lynchman_render(void);
void fastcall lynchman_remove_attached(void);
void fastcall lynchman_destroy_active(void);

#endif // LYNCHMAN_H_
