;***************************************************************************
;
; Program for education in subject "Assembly Languages"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
; Empty project
;
;***************************************************************************
	bits 64

	section .data
; variables
; global
; extern

        section .text
        extern strlen

; char *strmirror( char *t_str );
        ;               RDI,       RSI,        RDX,         RCX,  R8 a R9
    global strmirror
strmirror:
    enter 8,0
    mov [ rbp - 8 ], rdi        ; zachrana pro nas
    ; strlen( char * )
    call strlen
    mov rdi, [ rbp - 8 ]        ; obnova t_str, rdi

    mov rsi, rdi
    add rsi, rax
    dec rsi
.back:
    cmp rdi, rsi
    jae .done

    mov al, [ rdi ]
    mov ah, [ rsi ]
    mov [ rdi ], ah
    mov [ rsi ], al 
    mov al, sil
    mov ah, sil

    inc rdi
    dec rsi
    jmp .back
.done:

    mov rax, [ rbp - 8 ]

    leave
    ret

; long mystrlen( char *t_str );
        ;               RDI,       RSI,        RDX,         RCX,  R8 a R9
    global mystrlen
mystrlen:
    enter 8,0
    mov [ rbp - 8 ], rdi        ; save t_str

    mov rax, rdi

.back:
    cmp [ rax ], byte 0
    je .done
    inc rax
    jmp .back
.done:
    sub rax, rdi

    leave
    ret

;void average( long *t_array, int t_N );
        ;             RDI,       RSI,        RDX,         RCX,  R8 a R9
    global average
average:
    enter 0,0

    movsx rcx, esi
    mov rax, 0
.back:
    add rax, [ rdi + rcx * 8 - 8 ]
    loop .back

    movsx rsi, esi
    cqo
    idiv rsi

    leave
    ret


;void minmax( long *t_array, int t_N, long *t_min, long *t_max );
        ;             RDI,       RSI,        RDX,         RCX,  R8 a R9
    global minmax
minmax:
    enter 0,0

    mov r8, rcx             ; save rcx, t_max
    movsx rcx, esi          ; t_N
    mov r10, [ rdi ]        ; min = t_array[ 0 ]
    mov r11, [ rdi ]        ; max = t_array[ 0 ]
.back:
    cmp r10, [ rdi + rcx * 8 - 8 ]
    cmovg r10, [ rdi + rcx * 8 - 8 ]
    cmp r11, [ rdi + rcx * 8 - 8 ]
    cmovl r11, [ rdi + rcx * 8 - 8 ]
    loop .back

    mov [ rdx ], r10        ; *t_min = min
    mov [ r8 ], r11        ; *t_max = max

    leave
    ret


    ; int add32( int, int )
        ;        RDI, RSI, RDX, RCX, R8 a R9
    global add32
add32:
    ;enter 0, 0

    mov eax, edi
    add eax, esi

    ;leave
    ret

    ; int add64( int, int )
        ;        RDI, RSI, RDX, RCX, R8 a R9
    global add64
add64:
    ;enter 0, 0

    mov rax, rdi
    add rax, rsi

    ;leave
    ret
