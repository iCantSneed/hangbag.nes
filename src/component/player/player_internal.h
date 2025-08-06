#if !defined(PLAYER_INTERNAL_H_)
#define PLAYER_INTERNAL_H_

#define KIWI_RIGHT_X (8*30-13+2)
#define KIWI_Y 50

extern unsigned char player_x_pos;
#pragma zpsym ("player_x_pos");

extern unsigned char player_noose_activated;
#pragma zpsym ("player_noose_activated");

void fastcall kiwi_init();
void fastcall kiwi_tick();
void fastcall noose_tick();

#endif // PLAYER_INTERNAL_H_
