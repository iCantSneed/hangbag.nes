#if !defined(LYNCHMAN_H_)
#define LYNCHMAN_H_

#define NOOSE_Y_INACTIVE 0xff

typedef enum {
  LYNCHABLE_NONE,
  LYNCHABLE_LARDHAJJ,

  LYNCHABLE_MONEYBAG_REGULAR,
  LYNCHABLE_MONEYBAG_AGGRO,
  LYNCHABLE_MONEYBAG_HANGRY,

  LYNCHABLE_PYRITE,
  LYNCHABLE_PYRITEMAN_LONG,
  LYNCHABLE_PYRITEMAN_SHORT,

  LYNCHABLE_SCISSORS_0,
  LYNCHABLE_SCISSORS_1,
  LYNCHABLE_SCISSORS_2,

  LYNCHABLE_LAWYER0,

  LYNCHABLE_HAMMER0,

  LYNCHABLE_END
} LynchableObject;

typedef enum {
  NOOSE_STATE_UNCHANGED,
  NOOSE_STATE_ATTACHED,
  NOOSE_STATE_HURT,
  NOOSE_STATE_RETRACT,
} NooseState;

extern unsigned char noose_x;
#pragma zpsym ("noose_x")

extern unsigned char noose_y;
#pragma zpsym ("noose_y")

extern NooseState next_noose_state;
#pragma zpsym ("next_noose_state")

void fastcall lynchman_init(void);
void fastcall lynchman_append(LynchableObject);
void fastcall lynchman_tick(void);
void fastcall lynchman_render(void);
void fastcall lynchman_remove_attached(void);
void fastcall lynchman_destroy_active(void);

#endif // LYNCHMAN_H_
