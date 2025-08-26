  .export _level_text, _level_text_size, _thanks_text

text_level1:
  .incbin "level1.txt"
  .byte 0
text_level2:
  .incbin "level2.txt"
  .byte 0
text_level3:
  .incbin "level3.txt"
  .byte 0
text_level4:
  .incbin "level4.txt"
  .byte 0
text_level5:
  .incbin "level5.txt"
  .byte 0
text_level6:
  .incbin "level6.txt"
  .byte 0

.proc _level_text
  .addr text_level1, text_level2, text_level3, text_level4, text_level5, text_level6
.endproc
_level_text_size:
  .byte .sizeof(_level_text) / 2

_thanks_text:
  ; Size must be a multiple of 32
  .incbin "thanks.txt"
  .byte 0
