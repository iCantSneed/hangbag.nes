#include <neslib/neslib.h>

const unsigned char score_template[] = "$0000000";

#define SCORE_ROW 2
#define SCORE_COL (32-sizeof(score_template))

void fastcall score_init()
{
  vram_adr(NTADR_A(SCORE_COL, SCORE_ROW));
  vram_write(score_template, sizeof(score_template)-1);
}
