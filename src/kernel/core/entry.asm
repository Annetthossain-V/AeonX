extern _start_c

section .bss
align 16
kstack_bottom:
  resb 16384
kstack_top:

section .text
global _start
_start:
  lea rsp, [rel kstack_top]
  mov rbp, rsp
  call _start_c
  jmp _start
