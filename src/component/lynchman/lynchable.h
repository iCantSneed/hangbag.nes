#if !defined(LYNCHABLE_H_)
#define LYNCHABLE_H_

typedef struct {
  void (*init)();
  void (*(*tick))();
  void (*render)();
} Lynchable;

#endif // LYNCHABLE_H_
