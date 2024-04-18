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

    global pocet_az
pocet_az:
    enter 0,0

    mov eax, 0                      ; pocet = 0
    mov ecx, [ ebp + 8 ]            ; *str
.zpet:
    cmp [ ecx ], byte 0             ; *str == '\0'
    je .takhotovo

    cmp [ ecx ], byte 'a'
    jb .taknic
    cmp [ ecx ], byte 'z'
    ja .taknic
    inc eax
.taknic:
    inc ecx                         ; str++
    jmp .zpet

.takhotovo:
    leave
    ret

    global prumer
prumer:
    enter 0,0

    mov eax, 0                      ; sum = 0
    mov ecx, [ ebp + 12 ]           ; N
    mov edx, [ ebp + 8 ]            ; *pole

.back:
    ;add eax, [ g_pole_int + ecx * 4 - 4 ] 
    add eax,  [ edx        + ecx * 4 - 4 ]  ; sum += pole[ ecx ]
    loop .back

    cdq                             ; sum -> sign-ext eax-edx
    idiv dword [ ebp + 12 ]         ; sum /= N

    leave
    ret

    global sum_int64
sum_int64:
    enter 0,0

    mov eax, [ ebp + 8 ]            ; a
    cdq                             ; sign_ext eax -> eax-edx
    add eax, [ ebp + 12 ]           ; a += b
    adc edx, 0                      ; edx + 0 + CF
                                    ; ret eax-edx
    leave
    ret

    global imul_int, imul_int64
imul_int:
imul_int64:
    enter 0,0

    mov eax, [ ebp + 8 ]            ; a
    imul dword [ ebp + 12 ]         ; a *= b

    leave
    ret

    global sum_int
sum_int:
    enter 0,0

    mov eax, [ ebp + 8 ]            ; a
    add eax, [ ebp + 12 ]           ; a += b
                                    ; return a
    leave
    ret



