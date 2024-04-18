;***************************************************************************
;
; Program for education in subject "Assembly Languages"
; daniel.krupa.st@vsb.cz, Department of Computer Science, VSB-TUO
;
; Empty project
;
;***************************************************************************
	bits 64

	section .data
; variables
; global
; extern
	extern strlen;
        section .text
;rdi,rsi,rdx,rcx,r8,r9
    global m_shr_intN
m_shr_intN:
    enter 0,0

    mov rcx, rsi       ; t_N
    mov rax, rdi      ; t_intN
    clc
.back:
    rcr dword [ rax + rcx * 4 - 4 ], 1
    loop .back

    ; rotace?
    ; 

    mov rax, 0
    setc al

    leave
    ret
;rdi,rsi,rdx,rcx,r8,r9
    global m_shl_intN
m_shl_intN:
    enter 0,0

    mov rcx, rsi       ; t_N
    mov rax, rdi        ; t_intN
    mov rdx, 0
    clc
.back:
    rcl dword [ rax + rdx * 4 ], 1
    inc rdx
    loop .back

    ; rotace?
    ; adc [ eax ], 0

    mov rax, 0
    setc al

    leave
    ret
;rdi,rsi,rdx,rcx,r8,r9
    global m_add_intNintN 
m_add_intNintN:
    enter 0,0
    
    ;RDI =mov ebx, [ ebp + 8 ]        ; t_intaN
    ;RSI = mov edx, [ ebp + 12 ]       ; t_intbN
    mov rcx, rdx      ; t_N
    mov r8, 0
    clc
.back:
    mov eax, [ rsi + r8 * 4 ]
    adc [ rdi + r8 * 4 ], eax  ; t_intaN[ r8 ] += t_intbN[ r8 ]
    inc r8
    loop .back

    mov eax, 0
    adc eax, 0

    leave
    ret
;rdi,rsi,rdx,rcx,r8,r9
    global m_sub_intNintN 
m_sub_intNintN:
    enter 0,0
    
    ;RDI =mov ebx, [ ebp + 8 ]        ; t_intaN
    ;RSI = mov edx, [ ebp + 12 ]       ; t_intbN
    mov rcx, rdx      ; t_N
    mov r8, 0
    clc
.back:
    mov eax, [ rsi + r8 * 4 ]
    sbb [ rdi + r8 * 4 ], eax  ; t_intaN[ r8] -= t_intbN[ r8 ]
    inc r8
    loop .back

    mov eax, 0
    adc eax, 0

    leave
    ret


    global m_mul_intNint32
m_mul_intNint32:
    enter 0,0
    

    ;RDI = mov ebx, [ ebp + 8 ]        ; t_intN
    mov ecx, edx;[ ebp + 16 ]       ; t_N
    mov r8d, 0                  ; prenos 
.back:
    mov eax, [ rdi ]
    mul  esi;[ ebp + 12 ]      ; t_intN[ ebx ] * t_b
    add eax, r8d                
    adc edx, 0                  ; +cf
    mov [ rdi ], eax            ; ulozeni casti mezivysledku
    mov r8d, edx
    add rdi, 4
    loop .back

    
    
    leave
    ret
    
    
    
    global mirror
mirror:
    enter 0,0
	push rbx
    mov rbx,rdi;
    push rdi     ; push t_str
    call strlen
    pop rcx

    mov rcx,rbx        ; t_str, levy
    mov rdx, rcx
    add rdx, rax                ; s = "A"  s[ 0 ] = 'A', s[ 1 ] = '\0'
    dec rdx                     ; t_str + length - 1, pravy
.zpet:
    cmp rcx, rdx
    jae .hotovo

    mov al, [ rcx ]
    mov ah, [ rdx ]
    mov [ rcx ], ah
    mov [ rdx ], al

    inc rcx
    dec rdx
    jmp .zpet
.hotovo:

    mov rax, rdi

	pop rbx
    leave
    ret



    global m_div_intNint32
m_div_intNint32:
    enter 0,0
    
    mov ecx,edx ;[ ebp + 16 ]       ; t_N
    ;RDI = mov ebx, [ ebp + 8 ]        ; t_intN
    mov edx, 0
.back:
    mov eax, [ rdi+ rcx * 4 - 4 ]
    div  esi      ; / t_b
    mov [ rdi + rcx * 4 - 4 ], eax
    loop .back

    mov eax, edx                ; zbytek
    
    
    leave
    ret


;rdi,rsi,rdx,rcx,r8,r9
    global m_add_intNint32 
m_add_intNint32:
    enter 0,0
   
    ;RDI = mov ebx, [ ebp + 8 ]        ; t_intN
    mov ecx, edx     ; t_N
    dec ecx
    mov r8, 1 
    mov eax, esi       ; t_b
    cdq
    add [ rdi ], eax
.back:
    adc [ rdi + r8 * 4 ], edx
    inc rdi
    loop .back


   leave
    ret
   