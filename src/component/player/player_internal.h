#if !defined(PLAYER_INTERNAL_H_)
#define PLAYER_INTERNAL_H_

#define KIWI_RIGHT_X (8*30-13+2)
#define KIWI_Y 50

extern unsigned char player_noose_activated;
#pragma zpsym ("player_noose_activated");

extern unsigned char player_power;
#pragma zpsym ("player_power");

void fastcall powerbar_init();
void fastcall powerbar_tick();
void fastcall powerbar_render();

void fastcall kiwi_init();
void fastcall kiwi_tick();
void fastcall kiwi_render();

void fastcall noose_tick();
void fastcall noose_render();

#endif // PLAYER_INTERNAL_H_
