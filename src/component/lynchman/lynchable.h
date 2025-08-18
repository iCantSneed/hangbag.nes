#if !defined(LYNCHABLE_H_)
#define LYNCHABLE_H_

typedef void (*Init)(unsigned char);
typedef void (*Tick)(unsigned char);
typedef unsigned char (*CheckCollide)(unsigned char);
typedef void (*Render)(unsigned char);
typedef void (*Deinit)(unsigned char);

typedef struct {
  Init init;
  Tick* tick;
  CheckCollide check_collide;
  Render render;
  Deinit deinit;
} Lynchable;

#endif // LYNCHABLE_H_
