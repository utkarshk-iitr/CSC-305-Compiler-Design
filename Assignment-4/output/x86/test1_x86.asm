section .data
    str_1 db "%f", 0

section .text
    global main
    extern printf
    extern scanf

main:
    push ebp
    mov ebp, esp
    sub esp, 8
    mov eax, 1.2
    mov [ebp-4], eax
    mov eax, [ebp-4]
    push eax
    mov eax, str_1
    push eax
    call printf
    mov [ebp-8], eax
    add esp, 8
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
