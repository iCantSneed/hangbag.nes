#if !defined(LYNCHABLE_H_)
#define LYNCHABLE_H_

#include "lynchman.h"

typedef void (*Reset)(void);
typedef void (*Init)(void);
typedef void (*Tick)(void);
typedef NooseState (*CheckCollide)(void);
typedef void (*Render)(void);
typedef void (*Deinit)(void);

#endif // LYNCHABLE_H_
