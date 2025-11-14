section .data
    ; No global data

section .text
    global main
    extern printf
    extern scanf

ABCD.setter_int:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, [ebp+8]
    mov [ecx+0], eax
    add esp, 0
    mov esp, ebp
    pop ebp
    ret
ABCD.setter_int_int:
    push ebp
    mov ebp, esp
    sub esp, 0
    mov eax, [ebp+12]
    mov [ecx+0], eax
    mov eax, [ebp+8]
    mov [ecx+4], eax
    add esp, 0
    mov esp, ebp
    pop ebp
    ret
ABCD.getx:
    push ebp
    mov ebp, esp
    sub esp, 0
    add esp, 0
    mov eax, [ecx+0]
    mov esp, ebp
    pop ebp
    ret
ABCD.gety:
    push ebp
    mov ebp, esp
    sub esp, 0
    add esp, 0
    mov eax, [ecx+4]
    mov esp, ebp
    pop ebp
    ret
main:
    push ebp
    mov ebp, esp
    sub esp, 24
    lea ecx, [ebp-8]
    push 7
    call ABCD.setter_int
    add esp, 4
    lea ecx, [ebp-8]
    push 8
    push 7
    call ABCD.setter_int_int
    add esp, 8
    call ABCD.getx
    mov [ebp-12], eax
    mov eax, [ebp-12]
    mov [ebp-16], eax
    call ABCD.gety
    mov [ebp-20], eax
    mov eax, [ebp-20]
    mov [ebp-24], eax
    add esp, 24
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
