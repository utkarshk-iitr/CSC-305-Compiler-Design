section .data
    str_1 db `Allocated array elements:\n`, 0
    str_2 db "%d ", 0
    str_3 db "%d ", 0
    str_4 db `\n`, 0
    str_5 db `Memory successfully deallocated.\n`, 0

section .text
    global main
    extern printf
    extern scanf
    extern malloc
    extern free
    extern nullptr

main:
    push ebp
    mov ebp, esp
    sub esp, 48
    mov dword [ebp-8], 5
    mov dword [ebp-12], 4
    mov eax, 5
    imul eax, [ebp-12]
    mov [ebp-16], eax
    mov eax, [ebp-16]
    push eax
    call malloc
    mov [ebp-20], eax
    add esp, 4
    mov eax, [ebp-20]
    mov [ebp-24], eax
    mov eax, [ebp-24]
    mov [ebp-4], eax
    mov eax, str_1
    push eax
    call printf
    mov [ebp-28], eax
    add esp, 4
    mov dword [ebp-32], 0
main.L1:
    mov eax, [ebp-32]
    cmp eax, 5
    setl al
    movzx eax, al
    mov [ebp-36], eax
    mov eax, [ebp-36]
    test eax, eax
    jz main.L2
    mov eax, [ebp-32]
    imul eax, eax, 4
    mov [ebp-44], eax
    mov eax, [ebp-4]
    mov ebx, [ebp-44]
    add eax, ebx
    mov [ebp-48], eax
    mov eax, [ebp-48]
    mov [ebp-52], eax
    mov eax, [ebp-52]
    push eax
    mov eax, str_2
    push eax
    call scanf
    mov [ebp-56], eax
    add esp, 8
    mov eax, [ebp-32]
    imul eax, eax, 4
    mov [ebp-60], eax
    mov eax, [ebp-4]
    mov ebx, [ebp-60]
    add eax, ebx
    mov [ebp-64], eax
    mov eax, [ebp-64]
    mov eax, [eax]
    push eax
    mov eax, str_3
    push eax
    call printf
    mov [ebp-68], eax
    add esp, 8
    mov eax, [ebp-32]
    mov [ebp-40], eax
    mov eax, [ebp-40]
    add eax, 1
    mov [ebp-32], eax
    jmp main.L1
main.L2:
    mov eax, str_4
    push eax
    call printf
    mov [ebp-44], eax
    add esp, 4
    mov eax, [ebp-4]
    push eax
    call free
    add esp, 4
    mov dword [ebp-4], 0
    mov eax, str_5
    push eax
    call printf
    mov [ebp-48], eax
    add esp, 4
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
