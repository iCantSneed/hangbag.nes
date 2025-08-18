#if !defined(SCORE_H_)
#define SCORE_H_

#include <neslib/bcd.h>

void fastcall score_init(void);
void fastcall score_add(Bcd delta);

#endif // SCORE_H_
