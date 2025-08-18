#if !defined(PLAYER_H_)
#define PLAYER_H_

extern void (*player_tick)();
#pragma zpsym ("player_tick")

void player_init();
void player_render();

#endif // PLAYER_H_
