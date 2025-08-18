#if !defined(PLAYER_H_)
#define PLAYER_H_

extern void (*player_tick)(void);
#pragma zpsym ("player_tick")

void player_init(void);
void player_render(void);

#endif // PLAYER_H_
