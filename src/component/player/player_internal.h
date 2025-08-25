#if !defined(PLAYER_INTERNAL_H_)
#define PLAYER_INTERNAL_H_

#define KIWI_RIGHT_X (8*30-13+2)
#define KIWI_Y 50
#define SPRITE_HIDDEN_Y 0xff

extern unsigned char player_power;
#pragma zpsym ("player_power")

void fastcall player_make_nooseless(void);

void fastcall powerbar_init(void);
void fastcall powerbar_tick_nooseless(void);
void fastcall powerbar_render(void);

void fastcall kiwi_init(void);
void fastcall kiwi_tick_nooseless(void);
void fastcall kiwi_render(void);

void fastcall lasso_reset(void);
void fastcall lasso_tick_nooseless(void);
void fastcall lasso_render(void);

void fastcall noose_init_nooseless(void);
void fastcall noose_init_noosed(void);
void fastcall noose_tick_noosed(void);
void fastcall noose_render(void);

void fastcall rope_init(void);
void fastcall rope_tick_noosed(void);
void fastcall rope_render(void);

#endif // PLAYER_INTERNAL_H_
