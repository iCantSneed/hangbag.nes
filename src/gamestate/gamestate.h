#if !defined(GAMESTATE_H_)
#define GAMESTATE_H_

#define TEXT_PALETTE 0x30, 0x3d, 0x10

typedef void (*GameState)(void);
extern GameState next_gamestate;
#pragma zpsym ("next_gamestate")

void fastcall gamestate_title_init(void);

void fastcall gamestate_play_init(void);
void fastcall gamestate_play_moneybag_hanged(void);
void fastcall gamestate_play_timesup(void);
void fastcall gamestate_play_dead(void);

void fastcall gamestate_gameover_init(void);

void fastcall gamestate_winrar_init(void);

#endif // GAMESTATE_H_
