section .data
    str_1 db `fib called %d times\n`, 0
    str_2 db `Fibonacci of %d is %d\n`, 0
    str_3 db `Product of array elements is %d\n`, 0

section .text
    global main
    extern printf
    extern scanf

    mov dword [ebp-4], 0
fib_int:
    push ebp
    mov ebp, esp
    sub esp, 33
    mov eax, [ebp-4]
    mov [ebp-8], eax
    mov eax, [ebp-8]
    mov [ebp-4], eax
    add dword [ebp-4], 1
    mov eax, [ebp-4]
    push eax
    mov eax, str_1
    push eax
    call printf
    mov [ebp-12], eax
    add esp, 8
    mov eax, [ebp+8]
    cmp eax, 1
    setle al
    movzx eax, al
    mov [ebp-13], eax
    mov eax, [ebp-13]
    test eax, eax
    jz fib_int.L1
    mov eax, 1
    mov esp, ebp
    pop ebp
    ret
fib_int.L1:
    mov eax, [ebp+8]
    mov [ebp-17], eax
    sub dword [ebp-17], 1
    mov eax, [ebp-17]
    push eax
    call fib_int
    mov [ebp-21], eax
    add esp, 4
    mov eax, [ebp+8]
    mov [ebp-25], eax
    sub dword [ebp-25], 2
    mov eax, [ebp-25]
    push eax
    call fib_int
    mov [ebp-29], eax
    add esp, 4
    mov eax, [ebp-21]
    mov [ebp-33], eax
    mov ebx, [ebp-29]
    add dword [ebp-33], ebx
    add esp, 33
    mov eax, [ebp-33]
    mov esp, ebp
    pop ebp
    ret
arr_prod_int*_int:
    push ebp
    mov ebp, esp
    sub esp, 13
    mov dword [ebp-4], 1
    mov dword [ebp-8], 0
arr_prod_int*_int.L1:
    mov eax, [ebp-8]
    mov ebx, [ebp+8]
    cmp eax, ebx
    setl al
    movzx eax, al
    mov [ebp-9], eax
    mov eax, [ebp-9]
    test eax, eax
    jz arr_prod_int*_int.L2
    sub esp, 12
    mov eax, [ebp-8]
    imul eax, eax, 4
    mov [ebp-21], eax
    mov eax, [ebp+12]
    mov [ebp-25], eax
    mov ebx, [ebp-21]
    add dword [ebp-25], ebx
    mov eax, [ebp-4]
    imul eax, [ebp-25]
    mov [ebp-4], eax
    add esp, 12
    mov eax, [ebp-8]
    mov [ebp-13], eax
    mov eax, [ebp-13]
    mov [ebp-8], eax
    add dword [ebp-8], 1
    jmp arr_prod_int*_int.L1
arr_prod_int*_int.L2:
    add esp, 13
    mov eax, [ebp-4]
    mov esp, ebp
    pop ebp
    ret
main:
    push ebp
    mov ebp, esp
    sub esp, 64
    mov dword [ebp-4], 5
    mov eax, [ebp-4]
    push eax
    call fib_int
    mov [ebp-8], eax
    add esp, 4
    mov eax, [ebp-8]
    mov [ebp-12], eax
    push 1
    call fib_int
    mov [ebp-16], eax
    add esp, 4
    push 0
    call fib_int
    mov [ebp-20], eax
    add esp, 4
    mov eax, [ebp-12]
    push eax
    mov eax, [ebp-4]
    push eax
    mov eax, str_2
    push eax
    call printf
    mov [ebp-24], eax
    add esp, 12
    lea eax, [ebp-40]
    mov [ebp-48], eax
    mov dword [ebp-48], 1
    add dword [ebp-48], 4
    mov dword [ebp-48], 2
    add dword [ebp-48], 4
    mov dword [ebp-48], 3
    add dword [ebp-48], 4
    mov dword [ebp-48], 4
    add dword [ebp-48], 4
    mov dword [ebp-52], 4
    mov eax, [ebp-52]
    push eax
    mov eax, [ebp-40]
    push eax
    call arr_prod_int*_int
    mov [ebp-56], eax
    add esp, 8
    mov eax, [ebp-56]
    mov [ebp-60], eax
    mov eax, [ebp-60]
    push eax
    mov eax, str_3
    push eax
    call printf
    mov [ebp-64], eax
    add esp, 8
    add esp, 64
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
