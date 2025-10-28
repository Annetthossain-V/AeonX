

section .text
global halt ; void halt(void);
halt:
  hlt 
  jmp halt

