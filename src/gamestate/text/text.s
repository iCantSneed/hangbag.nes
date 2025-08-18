  .export _level_text

text_level1:
  .incbin "level1.txt"

text_level2:
  .incbin "level2.txt"

_level_text:
  .byte <text_level1, >text_level1
  .byte <text_level2, >text_level2
