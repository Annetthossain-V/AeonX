.intel_syntax noprefix

.section .bss
.align 16
kstack_bottom:
  .skip 8388608 # 8 MiB
.globl kstack_top
kstack_top:

.section .text
.globl _start
.type _start, @function
_start:
  lea rsp, kstack_top[rip]
  mov rbp, rsp

  call __enable_sse
  xor rax, rax

  # setup basic kernel gdt & tss
  call set_gdt
  call set_tss
  xor rax, rax

  call start_c
  hlt
  jmp hcf

__enable_sse:
  push rbp
  mov rbp, rsp

  mov eax, 0x1
  cpuid
  test edx, 1<<25
  jz hcf # sse support not found

  mov rax, cr0
  and ax, 0xFFFB # clear coprocessor emulation CR0.EM
  or ax, 0x2 # set coprocessor monitoring CR0.MP

  mov cr0, rax
  mov rax, cr4

  or ax, 3 << 9 # set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
  mov cr4, rax

  pxor xmm0, xmm0
  pxor xmm1, xmm1
  nop
  pop rbp
  ret
