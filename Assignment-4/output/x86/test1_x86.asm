section .data
    incrementCallCount.callCount dd 0
    str_1 db `Inside incrementCallCount, callCount = %d\n`, 0
    str_2 db `Static variable test:\n`, 0
    main.localStatic dd 100
    str_3 db `Local static variable: %d\n`, 0
    str_4 db `Modified local static: %d\n`, 0

section .text
    global main
    extern printf
    extern scanf
    extern malloc
    extern free
    extern nullptr

incrementCallCount:
    push ebp
    mov ebp, esp
    sub esp, 12
    mov eax, [incrementCallCount.callCount]
    mov [ebp-8], eax
    mov eax, [ebp-8]
    add eax, 1
    mov [incrementCallCount.callCount], eax
    mov eax, [incrementCallCount.callCount]
    push eax
    mov eax, str_1
    push eax
    call printf
    mov [ebp-12], eax
    add esp, 8
    mov esp, ebp
    pop ebp
    ret
main:
    push ebp
    mov ebp, esp
    mov eax, str_2
    push eax
    call printf
    mov [ebp-4], eax
    add esp, 4
    call incrementCallCount
    mov [ebp-4], eax
    call incrementCallCount
    mov [ebp-4], eax
    call incrementCallCount
    mov [ebp-4], eax
    mov eax, [main.localStatic]
    push eax
    mov eax, str_3
    push eax
    call printf
    mov [ebp-12], eax
    add esp, 8
    mov eax, [main.localStatic]
    add eax, 10
    mov [ebp-16], eax
    mov eax, [ebp-16]
    mov [main.localStatic], eax
    mov eax, [main.localStatic]
    push eax
    mov eax, str_4
    push eax
    call printf
    mov [ebp-20], eax
    add esp, 8
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
