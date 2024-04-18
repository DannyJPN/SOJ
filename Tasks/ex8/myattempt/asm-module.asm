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
  extern printf, strlen
        section .text
;rdi,rsi,rdx,rcx,r8,r9
    global div_intNint32
div_intNint32:
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
    global mul_intNint32
mul_intNint32:
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
;rdi,rsi,rdx,rcx,r8,r9
    global add_intNint32 
add_intNint32:
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
   

;rdi,rsi,rdx,rcx,r8,r9
global mirror
mirror:
    enter 0,0

    push rdi     ; push t_str
    call strlen
    pop rcx

    mov rcx,rdi        ; t_str, levy
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

    leave
    ret



; functions
; global
; extern

; labels:
