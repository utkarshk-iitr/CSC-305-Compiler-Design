section .bss
    b resd 1
    e resd 1

section .data
    a dd 10
    c dd 10
    d dd 11
    str_1 db `%d\n`, 0
    str_2 db `%d\n`, 0
    str_3 db `%d\n`, 0

section .text
    global main
    extern printf
    extern scanf

main:
    push ebp
    mov ebp, esp
    sub esp, 52
    mov dword [ebp-4], 5
    lea eax, [ebp-4]
    mov [ebp-8], eax
    mov eax, [ebp-8]
    mov [ebp-12], eax
    lea eax, [ebp-12]
    mov [ebp-16], eax
    mov p1, [ebp-16]
    lea eax, [p1]
    mov [ebp-20], eax
    mov eax, [ebp-20]
    mov [ebp-24], eax
    mov eax, [ebp-4]
    push eax
    mov eax, str_1
    push eax
    call printf
    mov [ebp-28], eax
    add esp, 8
    mov eax, [ebp-24]
    mov eax, [eax]
    mov [ebp-32], eax
    mov eax, [ebp-32]
    mov eax, [eax]
    mov [ebp-36], eax
    mov eax, [ebp-36]
    mov dword [eax], 13
    mov eax, [ebp-4]
    push eax
    mov eax, str_2
    push eax
    call printf
    mov [ebp-40], eax
    add esp, 8
    mov dword [ebp-4], 7
    mov eax, p1
    mov eax, [eax]
    mov [ebp-44], eax
    mov eax, [ebp-44]
    mov eax, [eax]
    mov [ebp-48], eax
    mov eax, [ebp-48]
    push eax
    mov eax, str_3
    push eax
    call printf
    mov [ebp-52], eax
    add esp, 8
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
