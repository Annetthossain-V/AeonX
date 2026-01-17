
.section .text
.globl memcpy
.type memcpy, @function
memcpy:
  movq %rdi, %rax
  test %rdx, %rdx 
  je .complete

  cld
  movq %rdx, %rcx
  rep movsb

.complete:
  retq

.section .text
.globl memset
.type memset, @function
memset:
  movq %rdi, %rax
  movq %rdx, %rcx
  movb %sil, %al

  cld
  rep stosb
  retq
