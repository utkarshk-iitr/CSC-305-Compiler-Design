section .data
    str_1 db `For Loop:\n`, 0
    str_2 db "%d ", 0
    str_3 db `\n\nWhile Loop:\n`, 0
    str_4 db "%d ", 0
    str_5 db `\n\nDo-While Loop:\n`, 0
    str_6 db "%d ", 0
    str_7 db `\n\nUntil Loop:\n`, 0
    str_8 db "%d ", 0
    str_9 db `\n\nGoto Statement:\n`, 0
    str_10 db "%d ", 0
    str_11 db `\nEnd of program\n`, 0

section .text
    global main
    extern printf
    extern scanf

main:
    push ebp
    mov ebp, esp
    sub esp, 50
    mov eax, str_1
    push eax
    call printf
    mov [ebp-4], eax
    add esp, 4
    mov dword [ebp-8], 0
main.L3:
    mov eax, [ebp-8]
    cmp eax, 10
    setl al
    movzx eax, al
    mov [ebp-9], eax
    mov eax, [ebp-9]
    test eax, eax
    jz main.L4
    sub esp, 6
    mov eax, [ebp-8]
    cmp eax, 5
    sete al
    movzx eax, al
    mov [ebp-14], eax
    mov eax, [ebp-14]
    test eax, eax
    jz main.L1
    jmp main.L3
main.L1:
    mov eax, [ebp-8]
    cmp eax, 8
    sete al
    movzx eax, al
    mov [ebp-15], eax
    mov eax, [ebp-15]
    test eax, eax
    jz main.L2
    jmp main.L4
main.L2:
    mov eax, [ebp-8]
    push eax
    mov eax, str_2
    push eax
    call printf
    mov [ebp-19], eax
    add esp, 8
    add esp, 6
    mov eax, [ebp-8]
    mov [ebp-13], eax
    mov eax, [ebp-13]
    mov [ebp-8], eax
    add dword [ebp-8], 1
    jmp main.L3
main.L4:
    mov eax, str_3
    push eax
    call printf
    mov [ebp-17], eax
    add esp, 4
    mov dword [ebp-21], 0
main.L7:
    mov eax, [ebp-21]
    cmp eax, 10
    setl al
    movzx eax, al
    mov [ebp-22], eax
    mov eax, [ebp-22]
    test eax, eax
    jz main.L8
    sub esp, 10
    mov eax, [ebp-21]
    cmp eax, 3
    sete al
    movzx eax, al
    mov [ebp-23], eax
    mov eax, [ebp-23]
    test eax, eax
    jz main.L5
    sub esp, 4
    mov eax, [ebp-21]
    mov [ebp-27], eax
    mov eax, [ebp-27]
    mov [ebp-21], eax
    add dword [ebp-21], 1
    jmp main.L7
    add esp, 4
main.L5:
    mov eax, [ebp-21]
    cmp eax, 7
    sete al
    movzx eax, al
    mov [ebp-24], eax
    mov eax, [ebp-24]
    test eax, eax
    jz main.L6
    jmp main.L8
main.L6:
    mov eax, [ebp-21]
    push eax
    mov eax, str_4
    push eax
    call printf
    mov [ebp-28], eax
    add esp, 8
    mov eax, [ebp-21]
    mov [ebp-32], eax
    mov eax, [ebp-32]
    mov [ebp-21], eax
    add dword [ebp-21], 1
    add esp, 10
    jmp main.L7
main.L8:
    mov eax, str_5
    push eax
    call printf
    mov [ebp-26], eax
    add esp, 4
    mov dword [ebp-21], 0
main.L11:
    sub esp, 10
    mov eax, [ebp-21]
    cmp eax, 2
    sete al
    movzx eax, al
    mov [ebp-27], eax
    mov eax, [ebp-27]
    test eax, eax
    jz main.L9
    sub esp, 4
    mov eax, [ebp-21]
    mov [ebp-31], eax
    mov eax, [ebp-31]
    mov [ebp-21], eax
    add dword [ebp-21], 1
    jmp main.L11
    add esp, 4
main.L9:
    mov eax, [ebp-21]
    cmp eax, 6
    sete al
    movzx eax, al
    mov [ebp-28], eax
    mov eax, [ebp-28]
    test eax, eax
    jz main.L10
    jmp main.L12
main.L10:
    mov eax, [ebp-21]
    push eax
    mov eax, str_6
    push eax
    call printf
    mov [ebp-32], eax
    add esp, 8
    mov eax, [ebp-21]
    mov [ebp-36], eax
    mov eax, [ebp-36]
    mov [ebp-21], eax
    add dword [ebp-21], 1
    add esp, 10
    mov eax, [ebp-21]
    cmp eax, 10
    setl al
    movzx eax, al
    mov [ebp-27], eax
    mov eax, [ebp-27]
    test eax, eax
    jnz main.L11
main.L12:
    mov eax, str_7
    push eax
    call printf
    mov [ebp-31], eax
    add esp, 4
    mov dword [ebp-21], 0
main.L15:
    mov eax, [ebp-21]
    cmp eax, 10
    setge al
    movzx eax, al
    mov [ebp-32], eax
    mov eax, [ebp-32]
    test eax, eax
    jnz main.L16
    sub esp, 10
    mov eax, [ebp-21]
    cmp eax, 2
    sete al
    movzx eax, al
    mov [ebp-33], eax
    mov eax, [ebp-33]
    test eax, eax
    jz main.L13
    sub esp, 4
    mov eax, [ebp-21]
    mov [ebp-37], eax
    mov eax, [ebp-37]
    mov [ebp-21], eax
    add dword [ebp-21], 1
    jmp main.L15
    add esp, 4
main.L13:
    mov eax, [ebp-21]
    cmp eax, 6
    sete al
    movzx eax, al
    mov [ebp-34], eax
    mov eax, [ebp-34]
    test eax, eax
    jz main.L14
    jmp main.L16
main.L14:
    mov eax, [ebp-21]
    push eax
    mov eax, str_8
    push eax
    call printf
    mov [ebp-38], eax
    add esp, 8
    mov eax, [ebp-21]
    mov [ebp-42], eax
    mov eax, [ebp-42]
    mov [ebp-21], eax
    add dword [ebp-21], 1
    add esp, 10
    jmp main.L15
main.L16:
    mov eax, str_9
    push eax
    call printf
    mov [ebp-36], eax
    add esp, 4
    mov dword [ebp-21], 0
start:
    mov eax, [ebp-21]
    cmp eax, 4
    sete al
    movzx eax, al
    mov [ebp-37], eax
    mov eax, [ebp-37]
    test eax, eax
    jz main.L17
    jmp end
main.L17:
    mov eax, [ebp-21]
    push eax
    mov eax, str_10
    push eax
    call printf
    mov [ebp-41], eax
    add esp, 8
    mov eax, [ebp-21]
    mov [ebp-45], eax
    mov eax, [ebp-45]
    mov [ebp-21], eax
    add dword [ebp-21], 1
    mov eax, [ebp-21]
    cmp eax, 10
    setl al
    movzx eax, al
    mov [ebp-46], eax
    mov eax, [ebp-46]
    test eax, eax
    jz main.L18
    jmp start
main.L18:
end:
    mov eax, str_11
    push eax
    call printf
    mov [ebp-50], eax
    add esp, 4
    add esp, 50
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
