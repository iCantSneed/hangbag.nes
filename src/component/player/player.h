#if !defined(PLAYER_H_)
#define PLAYER_H_

#define PLAYER_PALETTES \
  0, 0x0f, 0x17, 0x37, \
  0, 0x0f, 0x17, 0x39

void fastcall player_init();
void fastcall player_tick();

#endif // PLAYER_H_
