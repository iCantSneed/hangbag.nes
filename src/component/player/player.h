#if !defined(PLAYER_H_)
#define PLAYER_H_

#include "../component.h"

#define NOOSE_HIDDEN_Y 0xff

extern const Component player_component;

extern unsigned char player_x_pos;
#pragma zpsym ("player_x_pos")

extern unsigned char noose_y;
#pragma zpsym ("noose_y")

#endif // PLAYER_H_
