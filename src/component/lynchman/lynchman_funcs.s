do_nothing:
  rts

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_resets_lo, _lynchable_resets_hi
  .import _moneybag_reset, _scissors_reset

_lynchable_resets_lo:
  .byte <do_nothing, <_moneybag_reset, <_moneybag_reset, <_scissors_reset
_lynchable_resets_hi:
  .byte >do_nothing, >_moneybag_reset, >_moneybag_reset, >_scissors_reset
  rts

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_inits_lo, _lynchable_inits_hi
  .import _moneybag_init_regular, _moneybag_init_aggro, _scissors_init

_lynchable_inits_lo:
  .byte <do_nothing, <_moneybag_init_regular, <_moneybag_init_aggro, <_scissors_init
_lynchable_inits_hi:
  .byte >do_nothing, >_moneybag_init_regular, >_moneybag_init_aggro, >_scissors_init

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_ticks_lo, _lynchable_ticks_hi
  .import _moneybag_tick, _scissors_tick

_lynchable_ticks_lo:
  .byte <do_nothing, <_moneybag_tick, <_moneybag_tick, <_scissors_tick
_lynchable_ticks_hi:
  .byte >do_nothing, >_moneybag_tick, >_moneybag_tick, >_scissors_tick

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_check_collides_lo, _lynchable_check_collides_hi
  .import _moneybag_check_collide, _pyrite_check_collide, _scissors_check_collide

_lynchable_check_collides_lo:
  .byte <_pyrite_check_collide, <_moneybag_check_collide, <_moneybag_check_collide, <_scissors_check_collide
_lynchable_check_collides_hi:
  .byte >_pyrite_check_collide, >_moneybag_check_collide, >_moneybag_check_collide, >_scissors_check_collide

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_renders_lo, _lynchable_renders_hi
  .import _moneybag_render, _pyrite_render, _scissors_render

_lynchable_renders_lo:
  .byte <_pyrite_render, <_moneybag_render, <_moneybag_render, <_scissors_render
_lynchable_renders_hi:
  .byte >_pyrite_render, >_moneybag_render, >_moneybag_render, >_scissors_render

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_deinits_lo, _lynchable_deinits_hi
  .import _pyrite_deinit

_lynchable_deinits_lo:
  .byte <_pyrite_deinit, 0, 0
_lynchable_deinits_hi:
  .byte >_pyrite_deinit, 0, 0
