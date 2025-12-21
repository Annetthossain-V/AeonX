.intel_syntax noprefix

.section .rodata
.globl kernel_version_info
.type kernel_version_info, @object
kernel_version_info: .string "aecore kernel v0.4; code-name: Blue Phoenix"

.section .text
.globl hcf
.type hcf, @function
hcf:
  nop
  cli
  hlt
  jmp hcf
  ret


