section .data
    str_1 db `Integer Array:\n`, 0
    str_2 db "%d ", 0
    str_3 db `\n`, 0
    str_4 db `Multidimensional Array:\n`, 0
    str_5 db "%d ", 0
    str_6 db `\n`, 0
    str_7 db `Pointer:\n`, 0
    str_8 db `%d\n`, 0
    str_9 db `%d\n`, 0
    str_10 db `Multilevel Pointer:\n`, 0
    str_11 db `%d\n`, 0

section .text
    global main
    extern printf
    extern scanf

main:
    push ebp
    mov ebp, esp
    sub esp, 114
    lea eax, [ebp-12]
    mov [ebp-20], eax
    mov dword [ebp-20], 1
    add dword [ebp-20], 4
    mov dword [ebp-20], 2
    add dword [ebp-20], 4
    mov dword [ebp-20], 3
    add dword [ebp-20], 4
    lea eax, [ebp-24]
    mov [ebp-32], eax
    mov dword [ebp-32], 'w'
    add dword [ebp-32], 1
    mov dword [ebp-32], 'x'
    add dword [ebp-32], 1
    mov dword [ebp-32], 'y'
    add dword [ebp-32], 1
    mov dword [ebp-32], 'z'
    add dword [ebp-32], 1
    mov eax, [ebp-12]
    mov [ebp-40], eax
    lea eax, [ebp-40]
    mov [ebp-48], eax
    mov eax, [ebp-48]
    mov [ebp-56], eax
    mov eax, str_1
    push eax
    call printf
    mov [ebp-60], eax
    add esp, 4
    mov dword [ebp-64], 0
main.L1:
    mov eax, [ebp-64]
    cmp eax, 3
    setl al
    movzx eax, al
    mov [ebp-65], eax
    mov eax, [ebp-65]
    test eax, eax
    jz main.L2
    sub esp, 12
    mov eax, [ebp-64]
    imul eax, eax, 1
    mov [ebp-73], eax
    mov eax, [ebp-73]
    imul eax, eax, 4
    mov [ebp-73], eax
    mov eax, [ebp-12]
    mov [ebp-77], eax
    mov ebx, [ebp-73]
    add dword [ebp-77], ebx
    mov eax, [ebp-77]
    push eax
    mov eax, str_2
    push eax
    call printf
    mov [ebp-81], eax
    add esp, 8
    add esp, 12
    mov eax, [ebp-64]
    mov [ebp-69], eax
    mov eax, [ebp-69]
    mov [ebp-64], eax
    add dword [ebp-64], 1
    jmp main.L1
main.L2:
    mov eax, str_3
    push eax
    call printf
    mov [ebp-73], eax
    add esp, 4
    mov eax, str_4
    push eax
    call printf
    mov [ebp-77], eax
    add esp, 4
    mov dword [ebp-81], 0
main.L5:
    mov eax, [ebp-81]
    cmp eax, 2
    setl al
    movzx eax, al
    mov [ebp-82], eax
    mov eax, [ebp-82]
    test eax, eax
    jz main.L6
    sub esp, 13
    mov dword [ebp-90], 0
main.L3:
    mov eax, [ebp-90]
    cmp eax, 2
    setl al
    movzx eax, al
    mov [ebp-91], eax
    mov eax, [ebp-91]
    test eax, eax
    jz main.L4
    sub esp, 15
    mov eax, [ebp-81]
    imul eax, eax, 2
    mov [ebp-96], eax
    mov eax, [ebp-96]
    imul eax, eax, 1
    mov [ebp-96], eax
    mov eax, [ebp-24]
    mov [ebp-104], eax
    mov ebx, [ebp-96]
    add dword [ebp-104], ebx
    mov eax, [ebp-90]
    imul eax, eax, 1
    mov [ebp-105], eax
    mov eax, [ebp-105]
    imul eax, eax, 1
    mov [ebp-105], eax
    mov eax, [ebp-104]
    mov [ebp-106], eax
    mov ebx, [ebp-105]
    add dword [ebp-106], ebx
    mov eax, [ebp-106]
    push eax
    mov eax, str_5
    push eax
    call printf
    mov [ebp-110], eax
    add esp, 8
    add esp, 15
    mov eax, [ebp-90]
    mov [ebp-95], eax
    mov eax, [ebp-95]
    mov [ebp-90], eax
    add dword [ebp-90], 1
    jmp main.L3
main.L4:
    mov eax, str_6
    push eax
    call printf
    mov [ebp-99], eax
    add esp, 4
    add esp, 13
    mov eax, [ebp-81]
    mov [ebp-86], eax
    mov eax, [ebp-86]
    mov [ebp-81], eax
    add dword [ebp-81], 1
    jmp main.L5
main.L6:
    mov eax, str_7
    push eax
    call printf
    mov [ebp-90], eax
    add esp, 4
    mov eax, [ebp-40]
    push eax
    mov eax, str_8
    push eax
    call printf
    mov [ebp-94], eax
    add esp, 8
    mov eax, [ebp-40]
    mov [ebp-102], eax
    add dword [ebp-102], 1
    mov eax, [ebp-102]
    push eax
    mov eax, str_9
    push eax
    call printf
    mov [ebp-106], eax
    add esp, 8
    mov eax, str_10
    push eax
    call printf
    mov [ebp-110], eax
    add esp, 4
    mov eax, [ebp-56]
    push eax
    mov eax, str_11
    push eax
    call printf
    mov [ebp-114], eax
    add esp, 8
    add esp, 114
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
