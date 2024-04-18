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
; variables
; global
; extern

        section .text

    global div_fix
div_fix:
    enter 0,0

    mov eax, [ ebp + 8 ]        ; t_a
    ;mov edx, [ ebp + 12 ]       ; t_b
    mov cl, [ ebp + 16 ]       ; t_fixed

    cdq
    shld edx, eax, cl           ; |edx|eax| << cl
    shl eax, cl                 ; eax << cl

    idiv dword [ ebp + 12 ]
   
    leave
    ret

    global mult_fix
mult_fix:
    enter 0,0

    mov eax, [ ebp + 8 ]        ; t_a
    mov edx, [ ebp + 12 ]       ; t_b
    mov cl, [ ebp + 16 ]       ; t_fixed
   
    imul edx

    shrd eax, edx, cl

    leave
    ret

    global shrd_test
shrd_test:
    enter 0,0

    mov eax, [ ebp + 8 ]        ; t_a
    mov edx, [ ebp + 12 ]       ; t_b
    mov cl, [ ebp + 16 ]        ; t_okolik

    shrd eax, edx, cl           ; |edx|eax| >> cl
    ;shld eax, edx, cl           ; |eax|edx| << cl

    leave
    ret


; functions
; global
; extern

; labels:
