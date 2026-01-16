.section .rodata
.globl kernel_version_info
.type kernel_version_info, @object
kernel_version_info: .string "aecore kernel v0.4; code-name: Blue Phoenix"

.section .text
.globl hcf
.type hcf, @function
hcf:
  cli
  hlt
  jmp hcf

.section .text
.globl _soft_kernel_reboot
_soft_kernel_reboot:
  movq $67108864, %rcx
  leaq kstack_top - 67108864, %rdi

  cld
  xorl %eax, %eax
  rep stosb

  jmp _start