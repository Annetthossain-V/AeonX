.intel_syntax noprefix

.globl hcf
.type hcf, @function
hcf:
  nop
  cli
  hlt
  jmp hcf
  ret
