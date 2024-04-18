;***************************************************************************
;
; Program for education in subject "Assembly Languages"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
; SSE unit usage examples
;
;***************************************************************************

	bits 64

	section .data

pi      dq 3.141592653589793238462 ; pi

        section .text

;***************************************************************************

        global add_float, add_double
add_float:
        addss xmm0, xmm1            ; a += b
        ret

add_double:
        addsd xmm0, xmm1            ; a += b
        ret

;***************************************************************************

        global volume_sphere
volume_sphere:
        ; volume 4/3 * pi * r^3
        movsd xmm1, xmm0            ; r
        mulsd xmm0, xmm0            ; r*r
        mulsd xmm0, xmm1            ; r*r*r
        mulsd xmm0, [ pi ]          ; *pi
        mov eax, 4
        cvtsi2sd xmm1, eax          
        mulsd xmm0, xmm1            ; *4
        dec eax
        cvtsi2sd xmm1, eax          
        divsd xmm0, xmm1            ; /3
        ret

;***************************************************************************

        global find_max
find_max:

        movss xmm0, [ rdi ]         ; sel. first element as MAX 
        movsx rcx, esi              ; N
        dec rcx                     ; skip first element
.back:
        comiss xmm0, [ rdi + rcx * 4 ] ; compare
        jae .skip
        movss xmm0, [ rdi + rcx * 4 ]  ; exchange MAX
.skip:
        loop .back  
                                    ; resutl is in XMM0
        ret

;***************************************************************************

        global array_average
array_average:

        xorpd xmm0, xmm0            ; sum = 0
        xor rdx, rdx                ; inx = 0
        movsx rcx, esi              ; N
        shr rcx, 1                  ; N /= 2
        jnc .nocf                   ; is N odd? 
        movsd xmm0, [ rdi ]         ; store odd element
        inc rdx                     ; skip odd element
.nocf:
        xorpd xmm1, xmm1            ; sum2 = 0,0
.back:
        movupd xmm2, [ rdi + rdx * 8 ] 
        addpd xmm1, xmm2            ; sum2 += pair of numbers
        add rdx, 2                  ; skip two numbers
        loop .back                  ; while ( --RCX )

        addsd xmm0, xmm1            ; sum += sum2
        shufpd xmm1, xmm1, 1        ; exchange numbers in sum2 
        addsd xmm0, xmm1            ; sum += sum2
        cvtsi2sd xmm1, esi
        divsd xmm0, xmm1            ; sum /= N

        ret

        
