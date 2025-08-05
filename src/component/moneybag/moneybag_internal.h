#if !defined(MONEYBAG_INTERNAL_H_)
#define MONEYBAG_INTERNAL_H_

typedef void (*jumpaction)();

void jump_action_prepare_jump();
void jump_action_jumping();
void jump_action_falling();
void jump_action_landed();

#endif // MONEYBAG_INTERNAL_H_
