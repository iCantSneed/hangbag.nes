#if !defined(PLAYER_H_)
#define PLAYER_H_

#define PLAYER_PLATFORM_BOTTOM 55

extern void (*player_tick)(void);
#pragma zpsym ("player_tick")

void player_init(void);
void player_render(void);

void player_make_nooseless(void);

#endif // PLAYER_H_
