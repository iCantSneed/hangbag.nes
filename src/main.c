#include "neslib/neslib.h"

#pragma bss-name (push,"ZEROPAGE")
unsigned char oam_off;

void main()
{
  while (1)
  {
    nesclock();
  }
}