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

    global max
max:
    movsx rcx, esi
    movss xmm0, [ rdi ]     ; max = pole[ 0 ]
.back:
    comiss xmm0, [ rdi + rcx * 4 - 4 ]
    ja .taknic
    movss xmm0, [ rdi + rcx * 4 - 4 ]
.taknic:
    loop .back
    ret

    global soucet
soucet:
    movsx rcx, esi
    xorpd xmm0, xmm0
.back:  
    addss xmm0, [ rdi + rcx * 4 - 4 ]
    loop .back
    ret

    global diskriminant
diskriminant:
    mulsd xmm1, xmm1    ; b*b
    mulsd xmm0, xmm2    ; a*c
    mov eax, 4
    cvtsi2sd xmm2, eax  ; xmm2 = 4
    mulsd xmm0, xmm2    ; 4*a*c
    subsd xmm1, xmm0
    movsd xmm0, xmm1
    ret

    global prepona
prepona:
    mulss xmm0, xmm0    ; a*=a
    mulss xmm1, xmm1    ; b*=b
    addss xmm0, xmm1    ; c*c
    sqrtss xmm0, xmm0
    ret

    global add_d
add_d:
    addsd xmm0, xmm1

    global f2f
f2f:
    ret

    global d2d
d2d:
    ret

    global d2f
d2f:
    cvtsd2ss xmm0, xmm0
    ret

    global f2d
f2d:
    cvtss2sd xmm0, xmm0
    ret





; functions
; global
; extern

; labels:
