#if !defined(PLAYER_INTERNAL_H_)
#define PLAYER_INTERNAL_H_

extern unsigned char player_x_pos;
#pragma zpsym ("player_x_pos");

void fastcall kiwi_init();
void fastcall kiwi_tick();

#define KIWI_RIGHT_X (8*30-13+2)

#endif // PLAYER_INTERNAL_H_
