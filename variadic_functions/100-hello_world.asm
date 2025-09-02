; 100-hello_world.asm  (GCC-friendly)
; Prints "Hello, World\n" using Linux x86-64 sys_write, then returns 0 from main.

global main

section .data
msg:     db "Hello, World", 10
msg_len: equ $ - msg

section .text
main:
        ; write(1, msg, msg_len)
        mov     rax, 1              ; sys_write
        mov     rdi, 1              ; fd = stdout
        lea     rsi, [rel msg]      ; buf
        mov     rdx, msg_len        ; count
        syscall

        xor     eax, eax            ; return 0 from main
        ret

