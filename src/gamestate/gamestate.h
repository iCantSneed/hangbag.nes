#if !defined(GAMESTATE_H_)
#define GAMESTATE_H_

typedef void (*GameState)(void);
extern GameState next_gamestate;
#pragma zpsym ("next_gamestate")

void fastcall gamestate_title_init(void);

void fastcall gamestate_play_init(void);
void fastcall gamestate_play_moneybag_hanged(void);
void fastcall gamestate_play_timesup(void);

void fastcall gamestate_gameover_init(void);

#endif // GAMESTATE_H_
