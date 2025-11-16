section .data
    str_1 db "%d", 0
    str_2 db "%d", 0

section .text
    global main
    extern printf
    extern scanf

    ; Unparsed: Parsing completed successfully.
main:
    push ebp
    mov ebp, esp
    sub esp, 25
    mov dword [ebp-4], 5
    lea eax, [ebp-4]
    mov [ebp-8], eax
    mov eax, [ebp-8]
    mov [ebp-12], eax
    mov dword [ebp-16], 0
main.L1:
    mov eax, [ebp-16]
    cmp eax, 10
    setl al
    movzx eax, al
    mov [ebp-17], eax
    mov eax, [ebp-17]
    test eax, eax
    jz main.L2
    sub esp, 4
    mov eax, [ebp-16]
    push eax
    mov eax, str_1
    push eax
    call printf
    mov [ebp-25], eax
    add esp, 8
    mov eax, [ebp-16]
    mov [ebp-21], eax
    mov eax, [ebp-21]
    add eax, 1
    mov [ebp-16], eax
    jmp main.L1
main.L2:
    mov eax, [ebp-12]
    mov dword [eax], 6
    mov eax, [ebp-4]
    push eax
    mov eax, str_2
    push eax
    call printf
    mov [ebp-25], eax
    add esp, 8
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
