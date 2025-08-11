#if !defined(PLAYER_H_)
#define PLAYER_H_

#define NOOSE_HIDDEN_Y 0xff

typedef void (*PlayerTick)();
extern PlayerTick player_tick;
#pragma zpsym ("player_tick");

extern unsigned char player_x_pos;
#pragma zpsym ("player_x_pos");

extern unsigned char noose_y;
#pragma zpsym ("noose_y");

void fastcall player_init();
void fastcall player_render();

#endif // PLAYER_H_
