no_check_collide:
  lda #$00
do_nothing:
  rts

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_resets_lo, _lynchable_resets_hi
  .import _moneybag_reset, _scissors_reset, _lardhajj_reset

_lynchable_resets_lo:
  .byte <do_nothing, <_lardhajj_reset
  .byte <_moneybag_reset, <do_nothing, <do_nothing
  .byte <do_nothing, <do_nothing, <do_nothing
  .byte <_scissors_reset, <do_nothing, <do_nothing
  .byte <do_nothing
_lynchable_resets_hi:
  .byte >do_nothing, >_lardhajj_reset
  .byte >_moneybag_reset, >do_nothing, >do_nothing
  .byte >do_nothing, >do_nothing, >do_nothing
  .byte >_scissors_reset, >do_nothing, >do_nothing
  .byte >do_nothing

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_inits_lo, _lynchable_inits_hi
  .import _pyriteman_init_long, _pyriteman_init_short, _moneybag_init_regular, _moneybag_init_aggro, _scissors_init, _moneybag_init_hangry, _lawyer_init_0

_lynchable_inits_lo:
  .byte <do_nothing, <do_nothing
  .byte <_moneybag_init_regular, <_moneybag_init_aggro, <_moneybag_init_hangry
  .byte <do_nothing, <_pyriteman_init_long, <_pyriteman_init_short
  .byte <_scissors_init, <_scissors_init, <_scissors_init
  .byte <_lawyer_init_0
_lynchable_inits_hi:
  .byte >do_nothing, >do_nothing
  .byte >_moneybag_init_regular, >_moneybag_init_aggro, >_moneybag_init_hangry
  .byte >do_nothing, >_pyriteman_init_long, >_pyriteman_init_short
  .byte >_scissors_init, >_scissors_init, >_scissors_init
  .byte >_lawyer_init_0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_ticks_lo, _lynchable_ticks_hi
  .import _moneybag_tick, _lardhajj_tick, _pyrite_tick, _scissors_tick_0, _scissors_tick_1, _scissors_tick_2

_lynchable_ticks_lo:
  .byte <do_nothing, <_lardhajj_tick
  .byte <_moneybag_tick, <_moneybag_tick, <_moneybag_tick
  .byte <_pyrite_tick, <do_nothing, <do_nothing
  .byte <_scissors_tick_0, <_scissors_tick_1, <_scissors_tick_2
  .byte <do_nothing
_lynchable_ticks_hi:
  .byte >do_nothing, >_lardhajj_tick
  .byte >_moneybag_tick, >_moneybag_tick, >_moneybag_tick
  .byte >_pyrite_tick, >do_nothing, >do_nothing
  .byte >_scissors_tick_0, >_scissors_tick_1, >_scissors_tick_2
  .byte >do_nothing

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_check_collides_lo, _lynchable_check_collides_hi
  .import _pyriteman_check_collide, _moneybag_check_collide, _lardhajj_check_collide, _scissors_check_collide_0, _scissors_check_collide_1, _scissors_check_collide_2

_lynchable_check_collides_lo:
  .byte <no_check_collide, <_lardhajj_check_collide
  .byte <_moneybag_check_collide, <_moneybag_check_collide, <_moneybag_check_collide
  .byte <no_check_collide, <_pyriteman_check_collide, <_pyriteman_check_collide
  .byte <_scissors_check_collide_0, <_scissors_check_collide_1, <_scissors_check_collide_2
  .byte <no_check_collide

_lynchable_check_collides_hi:
  .byte >no_check_collide, >_lardhajj_check_collide
  .byte >_moneybag_check_collide, >_moneybag_check_collide, >_moneybag_check_collide
  .byte >no_check_collide, >_pyriteman_check_collide, >_pyriteman_check_collide
  .byte >_scissors_check_collide_0, >_scissors_check_collide_1, >_scissors_check_collide_2
  .byte >no_check_collide

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  .export _lynchable_renders_lo, _lynchable_renders_hi
  .import _moneybag_render, _lardhajj_render, _pyrite_render, _scissors_render_0, _scissors_render_1, _scissors_render_2

_lynchable_renders_lo:
  .byte <do_nothing, <_lardhajj_render
  .byte <_moneybag_render, <_moneybag_render, <_moneybag_render
  .byte <_pyrite_render, <do_nothing, <do_nothing
  .byte <_scissors_render_0, <_scissors_render_1, <_scissors_render_2
  .byte <do_nothing
_lynchable_renders_hi:
  .byte >do_nothing, >_lardhajj_render
  .byte >_moneybag_render, >_moneybag_render, >_moneybag_render
  .byte >_pyrite_render, >do_nothing, >do_nothing
  .byte >_scissors_render_0, >_scissors_render_1, >_scissors_render_2
  .byte >do_nothing
