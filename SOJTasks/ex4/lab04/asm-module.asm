;***************************************************************************
;
; Program for education in subject "Assembly Languages"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
; Empty project
;
;***************************************************************************
	bits 32

	section .data

g_str   db "asm replace '%s'", 10, 0

    section .text
    extern printf, strlen

    global otoc_str
otoc_str:
    enter 0,0

    push dword [ ebp + 8 ]      ; push t_str
    call strlen
    pop ecx

    mov ecx, [ ebp + 8 ]        ; t_str, levy
    mov edx, ecx
    add edx, eax                ; s = "A"  s[ 0 ] = 'A', s[ 1 ] = '\0'
    dec edx                     ; t_str + length - 1, pravy
.zpet:
    cmp ecx, edx
    jae .hotovo

    mov al, [ ecx ]
    mov ah, [ edx ]
    mov [ ecx ], ah
    mov [ edx ], al

    inc ecx
    dec edx
    jmp .zpet
.hotovo:

    mov eax, [ ebp + 8 ]

    leave
    ret


    global replace_digit
replace_digit:
    enter 0,0

    push ebx
    push esi

    mov eax, [ ebp + 8 ]            ; t_str
    mov cl, [ ebp + 12 ]            ; t_replace
    mov esi, 0
.zpet:
    cmp [ eax + esi ], byte 0       ; t_str[ esi ] == '\0'
    je .hotovo

;    cmp [ eax + esi ], byte '0'
;    jb .taknic
;    cmp [ eax + esi ], byte '9'
;    ja .taknic
;    mov [ eax + esi ], cl
;.taknic:

;    ; simulace OR
;    mov cl, [ ebp + 12 ]            ; t_replace
;    mov dl, [ eax + esi ]
;    ; if ( znak < '0' || znak > '9' ) { tak_s_nim_nic }
;    cmp [ eax + esi ], byte '0'
;    cmovb cx, dx    
;    cmp [ eax + esi ], byte '9'
;    cmova cx, dx
;
;    mov [ eax + esi ], cl

    ; if ( znak >= '0' && znak <= '9' ) { tak_prepis }
    ; t_replace -> dl -> cl 
    mov cl, [ eax + esi ]
    mov dl, cl
    cmp [ eax + esi ], byte '0'
    cmovae dx, [ ebp + 12 ]
    cmp [ eax + esi ], byte '9'
    cmovbe cx, dx 
    mov [ eax + esi ], cl

    inc esi                         ; esi++
    jmp .zpet
.hotovo:

    pop esi
    pop ebx

    ; printf( g_str, t_str );
    push eax            ; t_str
    push dword g_str    ; "asm replace `%s`\n"
    call printf         ; nici eax, ecx, edx
    ;pop ecx
    ;pop ecx
    add esp, 8

    mov eax, [ ebp + 8 ]

    leave
    ret

    global minmax_int_array
minmax_int_array:
    enter 0,0

    push ebx

    mov edx, [ ebp + 8 ]        ; t_pole
    mov ecx, [ ebp + 12 ]       ; t_N
    mov eax, [ edx ]            ; l_max = t_pole[ 0 ]
    mov ebx, [ edx ]            ; l_min = t_pole[ 0 ]
.zpet:

    cmp eax, [ edx + ecx * 4 - 4 ]
    ;       <
    cmovl eax, [ edx + ecx * 4 - 4 ]

    cmp ebx, [ edx + ecx * 4 - 4 ]
    ;       >
    cmovg ebx, [ edx + ecx * 4 - 4 ]

    loop .zpet

    mov ecx, [ ebp + 16 ]       ; t_minmax
    mov [ ecx ], ebx
    mov [ ecx + 4 ], eax

    pop ebx

    leave
    ret

    global max_int_array
max_int_array:
    enter 0,0

    mov edx, [ ebp + 8 ]        ; t_pole
    mov ecx, [ ebp + 12 ]       ; t_N
    mov eax, [ edx ]            ; l_max = t_pole[ 0 ]
.zpet:

    cmp eax, [ edx + ecx * 4 - 4 ]
    ;       <
    cmovl eax, [ edx + ecx * 4 - 4 ]

    loop .zpet

    leave
    ret

