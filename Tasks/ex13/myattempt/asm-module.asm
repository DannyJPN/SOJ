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
		extern pi
        section .text
		
		global array_average
array_average :
	xorps xmm0 , xmm0	; l_sum = 0
	xor r9 , r9	; inx = 0
	movsx rax , esi	; t_N
;	mov r8,4
;	idiv r8	; t_N /= 4
	mov rcx,rax
	shr rcx,2
;	cmp rdx,0
;	je .nocf	; is t_N %4 =0?
	;movups xmm0 , [ rdi ]	; store odd element
	
;	add r9,rdx	; skip odd element
;.nocf :
	;xorps xmm1 , xmm1	; l_sum2 = 0,0
.back :
	;psrlw xmm0,4
	movups xmm2 , [ rdi + r9 * 4 ]
	addps xmm1 , xmm2	; l_sum2 += quartet of numbers

	add r9 , 4	; skip 4 numbers
	loop .back	; while ( -- rcx )
	
	
	addss xmm0 , xmm1       ;l_sum + l_sum2
	shufps xmm1 , xmm1 , 0x39
	addss xmm0 , xmm1
	shufps xmm1 , xmm1 , 0x39
	addss xmm0 , xmm1
	shufps xmm1 , xmm1 , 0x39
	addss xmm0 , xmm1
	
	
	
	cvtsi2ss xmm1 , esi
	divss xmm0 , xmm1
ret
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		global array_average_d
array_average_d :
	xorpd xmm0 , xmm0
	; l_sum = 0
	xor rdx , rdx
	; inx = 0
	movsx rcx , esi
	; t_N
	shr rcx , 1
	; t_N /= 2
	jnc .nocf
	; is t_N odd?
	movsd xmm0 , [ rdi ]
	; store odd element
	inc rdx
	; skip odd element
	.nocf :
	xorpd xmm1 , xmm1
	; l_sum2 = 0,0
	.back :
	movupd xmm2 , [ rdi + rdx * 8 ]
	addpd xmm1 , xmm2
	; l_sum2 += pair of numbers
	add rdx , 2
	; skip two numbers
	loop .back
	; while ( -- rcx )
	addsd xmm0 , xmm1
	shufpd xmm1 , xmm1 , 1
	addsd xmm0 , xmm1
	cvtsi2sd xmm1 , esi
	divsd xmm0 , xmm1
ret
		
		
		
		
		
		
		
		
;rdi,rsi,rdx,rcx,r8,r9
	global surf_sphere
surf_sphere :
		 
		movsd xmm2,[pi]
		mulsd xmm0 , xmm0           ;r*r
		mulsd xmm0 ,  xmm2 		;r*r*pi
		mov eax , 4
		cvtsi2sd xmm1 , eax
		mulsd xmm0 , xmm1		;r*r*pi*4
		
	ret




;rdi,rsi,rdx,rcx,r8,r9
    global max_d
max_d:
    movsx rcx, esi
    movsd xmm0, [ rdi ]     ; max = pole[ 0 ]
.back:
    comisd xmm0, [ rdi + rcx * 8 - 8 ]
    ja .taknic
    movsd xmm0, [ rdi + rcx * 8- 8 ]
.taknic:
    loop .back
    ret


;rdi,rsi,rdx,rcx,r8,r9
    global min_d
min_d:
    movsx rcx, esi
    movsd xmm0, [ rdi ]     ; min = pole[ 0 ]
.back:
    comisd xmm0, [ rdi + rcx * 8 - 8 ]
    jb .taknic
    movsd xmm0, [ rdi + rcx * 8 - 8 ]
.taknic:
    loop .back
    ret




    global min
min:
    movsx rcx, esi
    movss xmm0, [ rdi ]     ; max = pole[ 0 ]
.back:
    comiss xmm0, [ rdi + rcx * 4 - 4 ]
    jb .taknic
    movss xmm0, [ rdi + rcx * 4 - 4 ]
.taknic:
    loop .back
    ret





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
