#if !defined(TEXTBOX_H_)
#define TEXTBOX_H_

void fastcall textbox_init();
void fastcall textbox_tick();
void fastcall textbox_append(unsigned int addr, unsigned char length, const unsigned char* bytes);

#endif // TEXTBOX_H_
