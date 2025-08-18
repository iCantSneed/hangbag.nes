#if !defined(PLAYER_H_)
#define PLAYER_H_

#define SPRITE_HIDDEN_Y 0xff

extern unsigned char player_x_pos;
#pragma zpsym ("player_x_pos")

extern unsigned char noose_y;
#pragma zpsym ("noose_y")

extern void (*player_tick)();
#pragma zpsym ("player_tick")

void player_init();
void player_render();

#endif // PLAYER_H_
