#if !defined(PLAYER_H_)
#define PLAYER_H_

#define PLAYER_PLATFORM_BOTTOM 55
#define PLAYER_POWER_CRAP 3
#define KIWI_Y 50

extern void (*player_tick)(void);
#pragma zpsym ("player_tick")

extern unsigned char player_power;
#pragma zpsym ("player_power")

void player_init(void);
void player_render(void);

#endif // PLAYER_H_
