
.section .text
.type pixel, @function
.globl pixel
# 30 instruction for this function is crazy
# need to optimize this later (TODO)
pixel:
  # rdi = x, rsi = y, rdx = r, rcx = g, r8 = b
  # on system-v xmm0-xmm15 are caller-saved
  # all 8 bit values are promoted to 32 bit
  subq $8, %rsp # align stack

  # clear used registers
  pxor %xmm0, %xmm0
  pxor %xmm1, %xmm1
  pxor %xmm2, %xmm2

  # xmm1 contains rdi and rsi
  movq %rdi, %xmm1 # xmm1-low64 = x
  movq %rsi, %xmm0 # xmm0-low64 = y
  pslldq $8, %xmm0 # shift y to xmm0-high64
  por %xmm0, %xmm1 # xmm1-low64 = x, xmm1-high64 = y

  # xmm2 contains edx, ecx, r8d
  movd %edx, %xmm2 # xmm2-low64-low32 = r
  movd %ecx, %xmm0 # xmm0-low64-low32 = g
  pslldq $4, %xmm0 # shift g to xmm0-low64-high32
  movd %r8d, %xmm0 # xmm0-low64-low32 = b
  pslldq $8, %xmm0 # shift b to xmm0-high64-low32
  por %xmm0, %xmm2 # xmm2-low64-low32 = r, xmm2-low64-high32 = g, xmm2-high64-low32 = b

  # get screen and check if its null
  callq get_screen
  test %rax, %rax
  je .err
  movq %rax, %rdi # rdi = screen

  # restore registers
  movq %xmm1, %rsi # xmm1[0:63] -> rsi
  psrldq $8, %xmm1 # shift y to lower 64 bits of xmm1
  movq %xmm1, %rdx # xmm1[0:63] -> rdx

  movd %xmm2, %ecx # xmm2[0:31] -> ecx
  psrldq $4, %xmm2 # shift g to lower 32 bits of lower 64 bits of xmm2 
  movd %xmm2, %r8d # xmm2[0:31] -> r8d
  psrldq $8, %xmm2 # shift b to lower 32 bits of lower 64 bits of xmm2
  movd %xmm2, %r9d # xmm2[0:31] -> r9d

  callq Pixel
  addq $8, %rsp # align stack
  xorl %eax, %eax
  retq
.err:
  addq $8, %rsp # restore stack
  movl $1, %eax
  retq

