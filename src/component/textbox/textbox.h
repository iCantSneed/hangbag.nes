#if !defined(TEXTBOX_H_)
#define TEXTBOX_H_

typedef char (*TextboxTick)(void);
extern TextboxTick textbox_tick;
#pragma zpsym ("textbox_tick")

extern unsigned char const* textbox_ptr;
#pragma zpsym ("textbox_ptr")

void fastcall textbox_init(void);

#endif // TEXTBOX_H_
