#if !defined(LYNCHABLE_H_)
#define LYNCHABLE_H_

typedef void (*Init)(unsigned char);
typedef void (*Tick)(unsigned char);
typedef unsigned char (*CheckCollide)(unsigned char);
typedef void (*fastcall Render)(unsigned char);
typedef void (*Deinit)(unsigned char);

#endif // LYNCHABLE_H_
