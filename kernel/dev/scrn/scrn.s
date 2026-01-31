
.section .text
.globl screen_init
.type screen_init, @function
screen_init:
  # rdi = frame_buffer_request
  subq $8, %rsp

  testq %rdi, %rdi
  movl $1, %eax
  je .L1

  call save_screen_request
  testq %rax, %rax
  movl $1, %eax
  jne .L1

  call clear_screen
  xorl %eax, %eax
.L1:
  addq $8, %rsp
  retq

