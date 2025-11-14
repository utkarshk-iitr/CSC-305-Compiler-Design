section .data
    str_1 db `%d\n`, 0
    str_2 db `%d\n`, 0

section .text
    global main
    extern printf
    extern scanf

    ; Unparsed: Parsing completed successfully.
A.fn_int_char:
    push ebp
    mov ebp, esp
    sub esp, 12
    add dword [ebp+9], 11
    mov dword [ecx+0], 8
    mov eax, [ebp+9]
    mov [ebp-4], eax
    mov ebx, [ecx+0]
    add dword [ebp-4], ebx
    mov eax, [ebp-4]
    mov [ebp-8], eax
    mov ebx, [ecx+0]
    add dword [ebp-8], ebx
    mov eax, [ebp-8]
    mov [ebp-12], eax
    add dword [ebp-12], 5
    add esp, 12
    mov eax, [ebp-12]
    mov esp, ebp
    pop ebp
    ret
main:
    push ebp
    mov ebp, esp
    sub esp, 24
    mov dword [ebp-4], 8
    mov eax, [ebp-4]
    mov [ebp-8], eax
    mov eax, [ebp-8]
    push eax
    mov eax, str_1
    push eax
    call printf
    mov [ebp-12], eax
    add esp, 8
    lea ecx, [ebp-16]
    push 'a'
    push 8
    call A.fn_int_char
    mov [ebp-20], eax
    add esp, 8
    mov eax, [ebp-20]
    mov [ebp-8], eax
    mov eax, [ebp-8]
    push eax
    mov eax, str_2
    push eax
    call printf
    mov [ebp-24], eax
    add esp, 8
    add esp, 24
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
