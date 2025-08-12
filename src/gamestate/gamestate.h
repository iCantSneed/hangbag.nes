#if !defined(GAMESTATE_H_)
#define GAMESTATE_H_

typedef void (*GameState)();
extern GameState next_gamestate;
#pragma zpsym ("next_gamestate")

void gamestate_play_init();
void gamestate_play_moneybag_hanged();
void gamestate_play_timesup();

#endif // GAMESTATE_H_
