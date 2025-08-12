#if !defined(PLAYER_INTERNAL_H_)
#define PLAYER_INTERNAL_H_

#define KIWI_RIGHT_X (8*30-13+2)
#define KIWI_Y 50

extern unsigned char player_power;
#pragma zpsym ("player_power")

void fastcall powerbar_init();
void fastcall powerbar_tick_nooseless();
void fastcall powerbar_render();

void fastcall kiwi_init();
void fastcall kiwi_tick_nooseless();
void fastcall kiwi_render();

void fastcall lasso_reset();
void fastcall lasso_tick_nooseless();
void fastcall lasso_render();

void fastcall noose_init_nooseless();
void fastcall noose_init_noosed();
unsigned char fastcall noose_tick_noosed();
void fastcall noose_render();

void fastcall rope_init();
void fastcall rope_tick_noosed();
void fastcall rope_render();

#endif // PLAYER_INTERNAL_H_
