; A::fn(int) in NASM
; -------------------
; Registers:
;   ecx = this pointer (address of object)
; Stack:
;   [ebp+8] = int c
; Local:
;   [ebp-4] = int d

section .data
    fmt db "Sum = %d", 10, 0      ; format string for printf

section .text
    extern printf
    global main

; void fn(A* this, int c)
fn:
    push ebp
    mov ebp, esp
    sub esp, 4                    ; local int d

    mov eax, [ecx]                ; a
    add eax, [ecx+4]              ; a + b
    add eax, [ebp+8]              ; a + b + c
    mov [ebp-4], eax              ; d = sum

    push eax                      ; push d
    push fmt                      ; push "Sum = %d\n"
    call printf
    add esp, 8                    ; clean stack

    mov esp, ebp
    pop ebp
    ret 4                         ; pop int c

; main()
main:
    push ebp
    mov ebp, esp
    sub esp, 8                    ; reserve space for obj (a,b)

    mov DWORD [ebp-8], 11         ; obj.a = 11
    mov DWORD [ebp-4], 12         ; obj.b = 12

    push 10                       ; push argument c = 10
    lea ecx, [ebp-8]              ; ecx = &obj
    call fn                       ; call fn(&obj, 10)

    mov eax, 0                    ; return 0
    leave
    ret
