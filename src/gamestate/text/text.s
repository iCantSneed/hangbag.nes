  .export _level_text, _level_text_size

text_level1:
  .incbin "level1.txt"
  .byte 0
text_level2:
  .incbin "level2.txt"
  .byte 0
text_level3:
  .incbin "level3.txt"
  .byte 0

.proc _level_text
  .addr text_level1, text_level2, text_level3
.endproc
_level_text_size:
  .byte .sizeof(_level_text) / 2
