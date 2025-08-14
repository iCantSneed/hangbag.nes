#if !defined(GAMESTATE_H_)
#define GAMESTATE_H_

typedef void (*GameState)();
extern GameState next_gamestate;
#pragma zpsym ("next_gamestate")

void fastcall gamestate_play_init();
void fastcall gamestate_play_moneybag_hanged();
void fastcall gamestate_play_timesup();

void fastcall gamestate_gameover_init();

#endif // GAMESTATE_H_
