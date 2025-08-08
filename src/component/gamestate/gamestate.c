#include "gamestate.h"
#include <component/controller/controller.h>
#include <component/textbox/textbox.h>
#include <neslib/neslib.h>

#pragma bss-name (push,"ZEROPAGE")

GameState game_state;

#pragma bss-name (push,"RODATA")

const unsigned char pozzed_text[] = "POZZED";
const unsigned char unpozzed_text[] = "      ";

#define POZZED_POS (NTADR_A((16 - (sizeof(pozzed_text) - 1) / 2), 10) | (NT_UPD_HORZ << 8))

void fastcall gamestate_init()
{
  game_state = GAME_STATE_PLAYING;
}

void fastcall gamestate_tick()
{
  if (pad0 & PAD_START)
  {
    if (game_state == GAME_STATE_PLAYING)
    {
      game_state = GAME_STATE_POZZED;
      textbox_append(POZZED_POS, sizeof(pozzed_text) - 1, pozzed_text);
    }
    else if (game_state == GAME_STATE_POZZED)
    {
      game_state = GAME_STATE_PLAYING;
      textbox_append(POZZED_POS, sizeof(unpozzed_text) - 1, unpozzed_text);
    }
  }
}
