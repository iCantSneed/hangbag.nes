  .export _lynchable_inits_lo, _lynchable_inits_hi
  .import _moneybag_init, _pyrite_init

_lynchable_inits_lo:
  .byte <_moneybag_init, <_pyrite_init
_lynchable_inits_hi:
  .byte >_moneybag_init, >_pyrite_init

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_ticks_lo, _lynchable_ticks_hi
  .import _moneybag_tick

no_tick_do:
  rts
no_tick:
  .addr no_tick_do
_lynchable_ticks_lo:
  .byte <_moneybag_tick, <no_tick
_lynchable_ticks_hi:
  .byte >_moneybag_tick, >no_tick

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_check_collides_lo, _lynchable_check_collides_hi
  .import _moneybag_check_collide, _pyrite_check_collide

_lynchable_check_collides_lo:
  .byte <_moneybag_check_collide, <_pyrite_check_collide
_lynchable_check_collides_hi:
  .byte >_moneybag_check_collide, >_pyrite_check_collide
  .byte >_moneybag_tick, >no_tick

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_renders_lo, _lynchable_renders_hi
  .import _moneybag_render, _pyrite_render

_lynchable_renders_lo:
  .byte <_moneybag_render, <_pyrite_render
_lynchable_renders_hi:
  .byte >_moneybag_render, >_pyrite_render

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_deinits_lo, _lynchable_deinits_hi
  .import _pyrite_deinit

_lynchable_deinits_lo:
  .byte 0, <_pyrite_deinit
_lynchable_deinits_hi:
  .byte 0, >_pyrite_deinit
