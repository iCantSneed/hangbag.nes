#if !defined(GAMESTATE_H_)
#define GAMESTATE_H_

typedef enum {GAME_STATE_PLAYING, GAME_STATE_COMPLETED, GAME_STATE_POZZED} GameState;

extern GameState game_state;
#pragma zpsym ("game_state");

void fastcall gamestate_init();
void fastcall gamestate_tick();

#endif // GAMESTATE_H_
