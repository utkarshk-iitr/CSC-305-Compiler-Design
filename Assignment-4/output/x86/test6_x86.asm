section .data
    str_1 db "Enter the number of elements: ", 0
    str_2 db "%d", 0
    str_3 db `Memory allocation failed!\n`, 0
    str_4 db `Enter %d numbers:\n`, 0
    str_5 db "%lf", 0
    str_6 db `\nYou entered: `, 0
    str_7 db "%lf ", 0
    str_8 db `\nSum = %lf\nAverage = %lf\n`, 0

section .text
    global main
    extern printf
    extern scanf

main:
    push ebp
    mov ebp, esp
    sub esp, 127
    mov eax, 0.00
    mov [ebp-12], eax
    mov eax, str_1
    push eax
    call printf
    mov [ebp-16], eax
    add esp, 4
    lea eax, [ebp-4]
    mov [ebp-24], eax
    mov eax, [ebp-24]
    push eax
    mov eax, str_2
    push eax
    call scanf
    mov [ebp-28], eax
    add esp, 8
    mov dword [ebp-36], 8
    mov eax, [ebp-4]
    imul eax, [ebp-36]
    mov [ebp-40], eax
    mov eax, [ebp-40]
    push eax
    call malloc
    mov [ebp-48], eax
    add esp, 4
    mov eax, [ebp-48]
    mov [ebp-56], eax
    mov eax, [ebp-56]
    mov [ebp-64], eax
    mov eax, nullptr
    mov [ebp-72], eax
    mov eax, [ebp-64]
    mov ebx, [ebp-72]
    cmp eax, ebx
    sete al
    movzx eax, al
    mov [ebp-73], eax
    mov eax, [ebp-73]
    test eax, eax
    jz main.L1
    sub esp, 4
    mov eax, str_3
    push eax
    call printf
    mov [ebp-77], eax
    add esp, 4
    add esp, 4
    mov eax, 1
    mov esp, ebp
    pop ebp
    ret
main.L1:
    mov eax, [ebp-4]
    push eax
    mov eax, str_4
    push eax
    call printf
    mov [ebp-77], eax
    add esp, 8
    mov dword [ebp-81], 0
main.L2:
    mov eax, [ebp-81]
    mov ebx, [ebp-4]
    cmp eax, ebx
    setl al
    movzx eax, al
    mov [ebp-82], eax
    mov eax, [ebp-82]
    test eax, eax
    jz main.L3
    sub esp, 44
    mov eax, [ebp-81]
    imul eax, eax, 8
    mov [ebp-94], eax
    mov eax, [ebp-64]
    mov [ebp-102], eax
    mov ebx, [ebp-94]
    add dword [ebp-102], ebx
    lea eax, [ebp-102]
    mov [ebp-110], eax
    mov eax, [ebp-110]
    push eax
    mov eax, str_5
    push eax
    call scanf
    mov [ebp-114], eax
    add esp, 8
    mov eax, [ebp-81]
    imul eax, eax, 8
    mov [ebp-122], eax
    mov eax, [ebp-64]
    mov [ebp-130], eax
    mov ebx, [ebp-122]
    add dword [ebp-130], ebx
    mov ebx, [ebp-130]
    add dword [ebp-12], ebx
    add esp, 44
    mov eax, [ebp-81]
    mov [ebp-86], eax
    mov eax, [ebp-86]
    mov [ebp-81], eax
    add dword [ebp-81], 1
    jmp main.L2
main.L3:
    mov eax, [ebp-4]
    mov [ebp-94], eax
    mov eax, [ebp-12]
    cdq
    idiv [ebp-94]
    mov [ebp-102], eax
    mov eax, [ebp-102]
    mov [ebp-110], eax
    mov eax, str_6
    push eax
    call printf
    mov [ebp-114], eax
    add esp, 4
    mov dword [ebp-118], 0
main.L4:
    mov eax, [ebp-118]
    mov ebx, [ebp-4]
    cmp eax, ebx
    setl al
    movzx eax, al
    mov [ebp-119], eax
    mov eax, [ebp-119]
    test eax, eax
    jz main.L5
    sub esp, 20
    mov eax, [ebp-118]
    imul eax, eax, 8
    mov [ebp-131], eax
    mov eax, [ebp-64]
    mov [ebp-139], eax
    mov ebx, [ebp-131]
    add dword [ebp-139], ebx
    mov eax, [ebp-139]
    push eax
    mov eax, str_7
    push eax
    call printf
    mov [ebp-143], eax
    add esp, 8
    add esp, 20
    mov eax, [ebp-118]
    mov [ebp-123], eax
    mov eax, [ebp-123]
    mov [ebp-118], eax
    add dword [ebp-118], 1
    jmp main.L4
main.L5:
    mov eax, [ebp-110]
    push eax
    mov eax, [ebp-12]
    push eax
    mov eax, str_8
    push eax
    call printf
    mov [ebp-127], eax
    add esp, 12
    mov eax, [ebp-64]
    push eax
    call free
    add esp, 4
    add esp, 127
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
