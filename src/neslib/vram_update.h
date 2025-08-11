#if !defined(VRAM_UPDATE_H_)
#define VRAM_UPDATE_H_

void fastcall vram_update_init();
void fastcall vram_update_reset();
void fastcall vram_update_append(unsigned int addr, unsigned char length, const unsigned char* bytes);

#endif // VRAM_UPDATE_H_
