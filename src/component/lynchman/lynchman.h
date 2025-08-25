#if !defined(LYNCHMAN_H_)
#define LYNCHMAN_H_

#define NO_LYNCHABLE_ATTACHED 0xff

typedef enum {
  LYNCHABLE_PYRITE,
  LYNCHABLE_MONEYBAG_REGULAR,
  LYNCHABLE_MONEYBAG_AGGRO,
  LYNCHABLE_SCISSORS,
  LYNCHABLE_LARDHAJJ,
  LYNCHABLE_NONE,
} LynchableObject;

extern unsigned char noose_x;
#pragma zpsym ("noose_x")

extern unsigned char noose_y;
#pragma zpsym ("noose_y")

extern unsigned char lynchable_attached_idx;
#pragma zpsym ("lynchable_attached_idx")

extern unsigned char lynchable_active_idx;
#pragma zpsym ("lynchable_active_idx")

void fastcall lynchman_init(void);
void fastcall lynchman_append(LynchableObject);
void fastcall lynchman_tick(void);
void fastcall lynchman_render(void);
void fastcall lynchman_remove_attached(void);
void fastcall lynchman_destroy_active(void);

#endif // LYNCHMAN_H_
