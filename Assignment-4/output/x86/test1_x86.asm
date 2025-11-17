section .data
    str_1 db `%d\n`, 0
    str_2 db `%d\n`, 0
    str_3 db `%d\n`, 0
    str_4 db `%d\n`, 0
    str_5 db `%d\n`, 0
    str_6 db `%d\n`, 0
    str_7 db `%d\n`, 0
    str_8 db `%d\n`, 0
    str_9 db `%d\n`, 0

section .text
    global main
    extern printf
    extern scanf

    ; Unparsed: Parsing completed successfully.
main:
    push ebp
    mov ebp, esp
    sub esp, 584
    lea eax, [ebp-400]
    mov [ebp-404], eax
    mov eax, [ebp-404]
    mov dword [eax], 1
    add dword [ebp-404], 4
    mov eax, [ebp-404]
    mov dword [eax], 2
    add dword [ebp-404], 4
    mov eax, [ebp-404]
    mov dword [eax], 3
    add dword [ebp-404], 4
    mov eax, 0
    imul eax, eax, 10
    mov [ebp-408], eax
    mov eax, [ebp-408]
    imul eax, eax, 4
    mov [ebp-408], eax
    lea eax, [ebp-400]
    mov ebx, [ebp-408]
    add eax, ebx
    mov [ebp-412], eax
    mov eax, 0
    imul eax, eax, 1
    mov [ebp-416], eax
    mov eax, [ebp-416]
    imul eax, eax, 4
    mov [ebp-416], eax
    mov eax, [ebp-412]
    mov ebx, [ebp-416]
    add eax, ebx
    mov [ebp-420], eax
    mov eax, [ebp-420]
    mov eax, [eax]
    push eax
    mov eax, str_1
    push eax
    call printf
    mov [ebp-424], eax
    add esp, 8
    mov eax, 0
    imul eax, eax, 10
    mov [ebp-428], eax
    mov eax, [ebp-428]
    imul eax, eax, 4
    mov [ebp-428], eax
    lea eax, [ebp-400]
    mov ebx, [ebp-428]
    add eax, ebx
    mov [ebp-432], eax
    mov eax, 1
    imul eax, eax, 1
    mov [ebp-436], eax
    mov eax, [ebp-436]
    imul eax, eax, 4
    mov [ebp-436], eax
    mov eax, [ebp-432]
    mov ebx, [ebp-436]
    add eax, ebx
    mov [ebp-440], eax
    mov eax, [ebp-440]
    mov eax, [eax]
    push eax
    mov eax, str_2
    push eax
    call printf
    mov [ebp-444], eax
    add esp, 8
    mov eax, 3
    imul eax, eax, 10
    mov [ebp-448], eax
    mov eax, [ebp-448]
    imul eax, eax, 4
    mov [ebp-448], eax
    lea eax, [ebp-400]
    mov ebx, [ebp-448]
    add eax, ebx
    mov [ebp-452], eax
    mov eax, 0
    imul eax, eax, 1
    mov [ebp-456], eax
    mov eax, [ebp-456]
    imul eax, eax, 4
    mov [ebp-456], eax
    mov eax, [ebp-452]
    mov ebx, [ebp-456]
    add eax, ebx
    mov [ebp-460], eax
    mov eax, [ebp-460]
    mov eax, [eax]
    push eax
    mov eax, str_3
    push eax
    call printf
    mov [ebp-464], eax
    add esp, 8
    mov eax, 3
    imul eax, eax, 10
    mov [ebp-468], eax
    mov eax, [ebp-468]
    imul eax, eax, 4
    mov [ebp-468], eax
    lea eax, [ebp-400]
    mov ebx, [ebp-468]
    add eax, ebx
    mov [ebp-472], eax
    mov eax, 5
    imul eax, eax, 1
    mov [ebp-476], eax
    mov eax, [ebp-476]
    imul eax, eax, 4
    mov [ebp-476], eax
    mov eax, [ebp-472]
    mov ebx, [ebp-476]
    add eax, ebx
    mov [ebp-480], eax
    mov eax, [ebp-480]
    mov dword [eax], 8
    mov eax, 2
    imul eax, eax, 10
    mov [ebp-484], eax
    mov eax, [ebp-484]
    imul eax, eax, 4
    mov [ebp-484], eax
    lea eax, [ebp-400]
    mov ebx, [ebp-484]
    add eax, ebx
    mov [ebp-488], eax
    mov eax, 2
    imul eax, eax, 1
    mov [ebp-492], eax
    mov eax, [ebp-492]
    imul eax, eax, 4
    mov [ebp-492], eax
    mov eax, [ebp-488]
    mov ebx, [ebp-492]
    add eax, ebx
    mov [ebp-496], eax
    mov eax, [ebp-496]
    mov eax, [eax]
    push eax
    mov eax, str_4
    push eax
    call printf
    mov [ebp-500], eax
    add esp, 8
    mov eax, 0
    imul eax, eax, 10
    mov [ebp-504], eax
    mov eax, [ebp-504]
    imul eax, eax, 4
    mov [ebp-504], eax
    lea eax, [ebp-400]
    mov ebx, [ebp-504]
    add eax, ebx
    mov [ebp-508], eax
    mov eax, 2
    imul eax, eax, 1
    mov [ebp-512], eax
    mov eax, [ebp-512]
    imul eax, eax, 4
    mov [ebp-512], eax
    mov eax, [ebp-508]
    mov ebx, [ebp-512]
    add eax, ebx
    mov [ebp-516], eax
    mov eax, [ebp-516]
    mov eax, [eax]
    push eax
    mov eax, str_5
    push eax
    call printf
    mov [ebp-520], eax
    add esp, 8
    mov eax, 3
    imul eax, eax, 10
    mov [ebp-524], eax
    mov eax, [ebp-524]
    imul eax, eax, 4
    mov [ebp-524], eax
    lea eax, [ebp-400]
    mov ebx, [ebp-524]
    add eax, ebx
    mov [ebp-528], eax
    mov eax, 5
    imul eax, eax, 1
    mov [ebp-532], eax
    mov eax, [ebp-532]
    imul eax, eax, 4
    mov [ebp-532], eax
    mov eax, [ebp-528]
    mov ebx, [ebp-532]
    add eax, ebx
    mov [ebp-536], eax
    mov eax, [ebp-536]
    mov eax, [eax]
    push eax
    mov eax, str_6
    push eax
    call printf
    mov [ebp-540], eax
    add esp, 8
    mov dword [ebp-544], 5
    lea eax, [ebp-544]
    mov [ebp-548], eax
    mov eax, [ebp-548]
    mov [ebp-552], eax
    lea eax, [ebp-552]
    mov [ebp-556], eax
    mov eax, [ebp-556]
    mov [ebp-560], eax
    mov eax, [ebp-552]
    mov eax, [eax]
    mov [ebp-564], eax
    mov dword [ebp-564], 8
    mov eax, [ebp-544]
    push eax
    mov eax, str_7
    push eax
    call printf
    mov [ebp-568], eax
    add esp, 8
    mov dword [ebp-544], 12
    mov eax, [ebp-544]
    push eax
    mov eax, str_8
    push eax
    call printf
    mov [ebp-572], eax
    add esp, 8
    mov eax, [ebp-560]
    mov eax, [eax]
    mov [ebp-576], eax
    mov eax, [ebp-576]
    mov eax, [eax]
    mov [ebp-580], eax
    mov dword [ebp-580], 11
    mov eax, [ebp-544]
    push eax
    mov eax, str_9
    push eax
    call printf
    mov [ebp-584], eax
    add esp, 8
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
