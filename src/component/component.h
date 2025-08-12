#if !defined(COMPONENT_H_)
#define COMPONENT_H_

typedef void (*Callback)();
typedef struct {
  Callback init;
  Callback *tick;
  Callback render;
} Component;

#endif // COMPONENT_H_
