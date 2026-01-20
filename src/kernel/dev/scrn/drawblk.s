.set BLOCK_WIDTH_DIVISOR, 512
.set BLOCK_HEIGTH_DIVISOR, 256

.section .bss
block_width: .space 8
block_height: .space 8

.section .text
.globl init_drawblk
.type init_drawblk, @function
init_drawblk:
  # rdi = screen_height, rsi = screen_width
  cmpq $BLOCK_HEIGTH_DIVISOR, %rdi
  jl .err
  cmpq $BLOCK_WIDTH_DIVISOR, %rsi
  jl .err

  # format height and width
  # TODO:

  xorl %eax, %eax
  retq
.err:
  movl $1, %eax
  retq

.section .text
.globl drawblk
.type drawblk, @function
drawblk:
  # zero blocks written
  xorl %eax, %eax
  retq
