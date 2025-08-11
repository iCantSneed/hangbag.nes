#if !defined(MONEYBAG_H_)
#define MONEYBAG_H_

#define MONEYBAG_GROUND_Y_POS 0xc900
#define MONEYBAG_IDLE_Y_POS ((MONEYBAG_GROUND_Y_POS >> 8) + 0x02)

extern unsigned int moneybag_x_pos;
#pragma zpsym ("moneybag_x_pos");

extern unsigned char moneybag_idle_frame;
#pragma zpsym ("moneybag_idle_frame");

void fastcall moneybag_init();
void fastcall moneybag_tick();
void fastcall moneybag_render();

inline unsigned char moneybag_is_grounded()
{
  return moneybag_idle_frame != 0;
}

#endif // MONEYBAG_H_
