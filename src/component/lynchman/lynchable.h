#if !defined(LYNCHABLE_H_)
#define LYNCHABLE_H_

typedef void (*Init)(void);
typedef void (*Tick)(void);
typedef unsigned char (*CheckCollide)(void);
typedef void (*Render)(void);
typedef void (*Deinit)(void);

#endif // LYNCHABLE_H_
