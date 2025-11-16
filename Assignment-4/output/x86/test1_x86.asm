section .data
    str_1 db "%d", 0

section .text
    global main
    extern printf
    extern scanf

    ; Unparsed: Parsing completed successfully.
main:
    push ebp
    mov ebp, esp
    sub esp, 9
    mov dword [ebp-4], 0
main.L1:
    mov eax, [ebp-4]
    cmp eax, 10
    setl al
    movzx eax, al
    mov [ebp-5], eax
    mov eax, [ebp-5]
    test eax, eax
    jz main.L2
    mov eax, [ebp-4]
    push eax
    mov eax, str_1
    push eax
    call printf
    mov [ebp-13], eax
    add esp, 8
    mov eax, [ebp-4]
    mov [ebp-9], eax
    mov eax, [ebp-9]
    add eax, 1
    mov [ebp-4], eax
    jmp main.L1
main.L2:
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
