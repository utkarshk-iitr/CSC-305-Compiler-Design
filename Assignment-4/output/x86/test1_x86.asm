section .bss
    p resd 1

section .data
    str_1 db `%d\n`, 0
    str_2 db `%d\n`, 0

section .text
    global main
    extern printf
    extern scanf

main:
    push ebp
    mov ebp, esp
    sub esp, 24
    mov dword [ebp-4], 5
    lea eax, [ebp-4]
    mov [ebp-8], eax
    mov eax, [ebp-8]
    mov [p], eax
    lea eax, [p]
    mov [ebp-12], eax
    mov eax, [ebp-12]
    mov [ebp-16], eax
    mov eax, [p]
    mov dword [eax], 8
    mov eax, [ebp-4]
    push eax
    mov eax, str_1
    push eax
    call printf
    mov [ebp-20], eax
    add esp, 8
    mov dword [ebp-4], 11
    mov eax, [p]
    mov eax, [eax]
    push eax
    mov eax, str_2
    push eax
    call printf
    mov [ebp-24], eax
    add esp, 8
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
