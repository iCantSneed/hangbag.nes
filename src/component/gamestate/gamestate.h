#if !defined(GAMESTATE_H_)
#define GAMESTATE_H_

typedef enum {GAME_STATE_PLAYING, GAME_STATE_COMPLETED} GameState;

extern GameState game_state;
#pragma zpsym ("game_state");

#endif // GAMESTATE_H_
