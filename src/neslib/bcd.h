#if !defined(BCD_H_)
#define BCD_H_

typedef unsigned char Bcd;

unsigned char fastcall bcd_add(Bcd* num_ptr, Bcd delta);
unsigned char fastcall bcd_add_with_carry(Bcd* num_ptr, Bcd delta);
unsigned char fastcall bcd_decrement(Bcd* num_ptr);
void fastcall bcd_vram_update(Bcd num, unsigned int vram_update_addr);

#endif // BCD_H_
