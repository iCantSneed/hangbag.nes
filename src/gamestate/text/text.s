  .export _level_text

text_level1:
  .incbin "level1.txt"
text_level2:
  .incbin "level2.txt"
text_level3:
  .incbin "level3.txt"

_level_text:
  .addr text_level1, text_level2, text_level3
