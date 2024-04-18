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

    section .text

    global move_mem
move_mem:
    enter 0,0

    push edi
    push esi

    mov esi, [ ebp + 12 ]   ; t_src
    mov edi, [ ebp + 8 ]    ; t_dest
    mov ax, ds
    mov es, ax
    mov ecx, [ ebp + 16 ]   ; t_len

    rep movsb

    pop esi
    pop edi

    leave
    ret

    global set_int_array
set_int_array:
    enter 0,0

    push edi

    mov edi, [ ebp + 8 ]        ; t_array
    mov ecx, [ ebp + 12 ]       ; t_len
    mov eax, [ ebp + 16 ]

    mov dx, ds
    mov es, dx

    rep stosd

    pop edi

    leave
    ret

    global upstr
upstr:
    enter 0,0

    push edi
    push esi

    mov esi, [ ebp + 8 ]
    mov edi, esi
    mov ax, ds
    mov es, ax

.back:

    lodsb
    or al, al 
    jz .hotovo

    cmp al, 'a'
    jb .taknic
    cmp al, 'z'
    ja .taknic
    xor al, 'a' - 'A'
.taknic:
    stosb

    jmp .back
.hotovo:


    pop esi
    pop edi

    leave
    ret

    global strlen_s
strlen_s:
    enter 0,0

    push edi

    mov edi, [ ebp + 8 ]        ; t_str
    ;mov es, ds
    mov ax, ds                  ; es = ds
    mov es, ax

    mov al, 0
    mov ecx, -1

    repnz scasb

    mov eax, edi                ; t_str[ strlen + 1 ], za '\0'
    sub eax, [ ebp + 8 ]        ; esi -= t_str
    dec eax

    pop edi

    leave
    ret

