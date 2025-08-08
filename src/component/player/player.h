#if !defined(PLAYER_H_)
#define PLAYER_H_

extern unsigned char player_x_pos;
#pragma zpsym ("player_x_pos");

void fastcall player_init();
void fastcall player_tick();

#endif // PLAYER_H_
