section .data
    str_1 db "%d", 0
    str_2 db "%s", 0
    str_3 db "passed", 0
    str_4 db "%s", 0
    str_5 db "promoted", 0
    str_6 db "%s", 0
    str_7 db "failed", 0
    str_8 db "%s", 0
    str_9 db "passed", 0
    str_10 db "%s", 0
    str_11 db "promoted", 0
    str_12 db "%s", 0
    str_13 db "failed", 0

section .text
    global main
    extern printf
    extern scanf

main:
    push ebp
    mov ebp, esp
    sub esp, 32
    lea eax, [ebp-4]
    mov [ebp-12], eax
    mov eax, [ebp-12]
    push eax
    mov eax, str_1
    push eax
    call scanf
    mov [ebp-16], eax
    add esp, 8
    mov eax, [ebp-4]
    cmp eax, 6
    setge al
    movzx eax, al
    mov [ebp-17], eax
    mov eax, [ebp-17]
    test eax, eax
    jz main.L3
    sub esp, 4
    mov eax, str_3
    push eax
    mov eax, str_2
    push eax
    call printf
    mov [ebp-21], eax
    add esp, 8
    add esp, 4
    jmp main.L4
main.L3:
    mov eax, [ebp-4]
    cmp eax, 4
    setge al
    movzx eax, al
    mov [ebp-18], eax
    mov eax, [ebp-18]
    test eax, eax
    jz main.L1
    sub esp, 4
    mov eax, str_5
    push eax
    mov eax, str_4
    push eax
    call printf
    mov [ebp-22], eax
    add esp, 8
    add esp, 4
    jmp main.L2
main.L1:
    sub esp, 4
    mov eax, str_7
    push eax
    mov eax, str_6
    push eax
    call printf
    mov [ebp-22], eax
    add esp, 8
    add esp, 4
main.L2:
main.L4:
    mov eax, [ebp-4]
    cmp eax, 6
    setge al
    movzx eax, al
    mov [ebp-19], eax
    mov eax, [ebp-19]
    test eax, eax
    jz main.L7
    mov dword [ebp-28], 2
    jmp main.L8
main.L7:
    mov eax, [ebp-4]
    cmp eax, 4
    setge al
    movzx eax, al
    mov [ebp-20], eax
    mov eax, [ebp-20]
    test eax, eax
    jz main.L5
    mov dword [ebp-24], 1
    jmp main.L6
main.L5:
    mov dword [ebp-24], 0
main.L6:
    mov eax, [ebp-24]
    mov [ebp-28], eax
main.L8:
    mov eax, [ebp-28]
    mov [ebp-32], eax
    mov eax, [ebp-32]
    cmp eax, 2
    je main.L9
    mov eax, [ebp-32]
    cmp eax, 1
    je main.L10
    jmp main.L11
    jmp main.L12
main.L9:
    sub esp, 4
    mov eax, str_9
    push eax
    mov eax, str_8
    push eax
    call printf
    mov [ebp-36], eax
    add esp, 8
    jmp main.L12
    add esp, 4
main.L10:
    sub esp, 4
    mov eax, str_11
    push eax
    mov eax, str_10
    push eax
    call printf
    mov [ebp-36], eax
    add esp, 8
    jmp main.L12
    add esp, 4
main.L11:
    sub esp, 4
    mov eax, str_13
    push eax
    mov eax, str_12
    push eax
    call printf
    mov [ebp-36], eax
    add esp, 8
    jmp main.L12
    add esp, 4
main.L12:
    add esp, 32
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
