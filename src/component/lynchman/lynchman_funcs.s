  .export _lynchable_inits_lo, _lynchable_inits_hi
  .import _moneybag_init, _pyrite_init

_lynchable_inits_lo:
  .byte <_pyrite_init, <_moneybag_init
_lynchable_inits_hi:
  .byte >_pyrite_init, >_moneybag_init

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_ticks_lo, _lynchable_ticks_hi
  .import _moneybag_tick

no_tick_do:
  rts
no_tick:
  .addr no_tick_do
_lynchable_ticks_lo:
  .byte <no_tick, <_moneybag_tick
_lynchable_ticks_hi:
  .byte >no_tick, >_moneybag_tick

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_check_collides_lo, _lynchable_check_collides_hi
  .import _moneybag_check_collide, _pyrite_check_collide

_lynchable_check_collides_lo:
  .byte <_pyrite_check_collide, <_moneybag_check_collide
_lynchable_check_collides_hi:
  .byte >_pyrite_check_collide, >_moneybag_check_collide

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_renders_lo, _lynchable_renders_hi
  .import _moneybag_render, _pyrite_render

_lynchable_renders_lo:
  .byte <_pyrite_render, <_moneybag_render
_lynchable_renders_hi:
  .byte >_pyrite_render, >_moneybag_render

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_deinits_lo, _lynchable_deinits_hi
  .import _pyrite_deinit

_lynchable_deinits_lo:
  .byte <_pyrite_deinit, 0
_lynchable_deinits_hi:
  .byte >_pyrite_deinit, 0
