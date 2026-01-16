
.section .text
.type pixel, @function
.globl pixel
pixel:
  # rdi = x, rsi = y, rdx = r, rcx = g, r8 = b
  # on system-v xmm0-xmm15 are caller-saved
  # all 8 bit values are promoted to 32 bit

  # TODO: implement this function

  xorl %eax, %eax
  retq
