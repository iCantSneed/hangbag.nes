#if !defined(GFX_H_)
#define GFX_H_

#include <neslib/neslib.h>

extern unsigned char sprid;
#pragma zpsym ("sprid")

#define gfx_oam_start() { sprid = 0; }

#define gfx_oam_spr(x, y, chrnum, attr) { sprid = oam_spr(x, y, chrnum, attr, sprid); }

#define gfx_oam_metaspr(x, y, data) { sprid = oam_meta_spr(x, y, sprid, data); }

#define gfx_oam_end() { oam_hide_rest(sprid); }

#endif // GFX_H_
