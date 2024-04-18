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

        section .text
 ;RDI,       RSI,        RDX,         RCX,  R8 a R9
    global div_fix2
div_fix2:
    enter 0,0

    mov Rax, RDI       ; t_a
    ;mov edx, [ ebp + 12 ]       ; t_b
    mov cl, DL       ; t_fixed

    cqo
    shld Rdx, Rax, cl           ; |edx|eax| << cl
    shl Rax, cl                 ; eax << cl

    idiv RSI
   
    leave
    ret

    global mult_fix2
mult_fix2:
    enter 0,0

    mov Rax, RDI        ; t_a
    mov cl, DL       ; t_fixed
    mov Rdx,RSI       ; t_b
   
    imul Rdx

    shrd Rax, Rdx, cl

    leave
    ret

 ;RDI,       RSI,        RDX,         RCX,  R8 a R9
    global div_fix10
div_fix10:
    enter 0,0

    mov Rax, RDI       ; t_a
    ;mov edx, [ ebp + 12 ]       ; t_b
    mov RCX, RDX       ; t_fixed
	mov R8,qword 10
    cqo
 .loopend:   
    imul R8;
    loop .loopend
    ;shld Rdx, Rax, cl           ; |edx|eax| << cl
    shl Rax, cl                 ; eax << cl

    idiv RSI
   
    leave
    ret

    global mult_fix10
mult_fix10:
    enter 0,0

    mov Rax, RDI        ; t_a
    mov RCX, RDX       ; t_fixed
    mov Rdx,RSI       ; t_b
	mov R8,qword 10;
   
    imul Rdx
    
.loopend:
    idiv R8;
    
    loop .loopend
    
    ;shrd Rax, Rdx, cl

    leave
    ret


; functions
; global
; extern

; labels:
