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

    global m_shr_intN
m_shr_intN:
    enter 0,0

    mov ecx, [ ebp + 12 ]       ; t_N
    mov eax, [ ebp + 8 ]        ; t_intN
    clc
.back:
    rcr dword [ eax + ecx * 4 - 4 ], 1
    loop .back

    ; rotace?
    ; 

    mov eax, 0
    setc al

    leave
    ret

    global m_shl_intN
m_shl_intN:
    enter 0,0

    mov ecx, [ ebp + 12 ]       ; t_N
    mov eax, [ ebp + 8 ]        ; t_intN
    mov edx, 0
    clc
.back:
    rcl dword [ eax + edx * 4 ], 1
    inc edx
    loop .back

    ; rotace?
    ; adc [ eax ], 0

    mov eax, 0
    setc al

    leave
    ret

    global m_add_intNintN 
m_add_intNintN:
    enter 0,0
    push ebx
    push edi

    mov ebx, [ ebp + 8 ]        ; t_intaN
    mov edx, [ ebp + 12 ]       ; t_intbN
    mov ecx, [ ebp + 16 ]       ; t_N
    mov edi, 0
    clc
.back:
    mov eax, [ edx + edi * 4 ]
    adc [ ebx + edi * 4 ], eax  ; t_intaN[ edi ] += t_intbN[ edi ]
    inc edi
    loop .back

    mov eax, 0
    adc eax, 0

    pop edi
    pop ebx
    leave
    ret
    
 
    global m_sub_intNintN 
m_sub_intNintN:
    enter 0,0
    push ebx
    push edi

    mov ebx, [ ebp + 8 ]        ; t_intaN
    mov edx, [ ebp + 12 ]       ; t_intbN
    mov ecx, [ ebp + 16 ]       ; t_N
    mov edi, 0
    clc
.back:
    mov eax, [ edx + edi * 4 ]
    sbb [ ebx + edi * 4 ], eax  ; t_intaN[ edi ] += t_intbN[ edi ]
    inc edi
    loop .back

    mov eax, 0
    sbb eax, 0

    pop edi
    pop ebx
    leave
    ret
    
    
       
    
    
    
    
    
    
    

    global m_div_intNint32
m_div_intNint32:
    enter 0,0
    push ebx

    mov ecx, [ ebp + 16 ]       ; t_N
    mov ebx, [ ebp + 8 ]        ; t_intN
    mov edx, 0
.back:
    mov eax, [ ebx + ecx * 4 - 4 ]
    div dword [ ebp + 12 ]      ; / t_b
    mov [ ebx + ecx * 4 - 4 ], eax
    loop .back

    mov eax, edx                ; zbytek
    
    pop ebx
    leave
    ret


    global m_mul_intNint32
m_mul_intNint32:
    enter 0,0
    push ebx
    push esi

    mov ebx, [ ebp + 8 ]        ; t_intN
    mov ecx, [ ebp + 16 ]       ; t_N
    mov esi, 0                  ; prenos 
.back:
    mov eax, [ ebx ]
    mul dword [ ebp + 12 ]      ; t_intN[ ebx ] * t_b
    add eax, esi                
    adc edx, 0                  ; +cf
    mov [ ebx ], eax            ; ulozeni casti mezivysledku
    mov esi, edx
    add ebx, 4
    loop .back

    pop esi
    pop ebx
    leave
    ret

    global m_add_intNint32 
m_add_intNint32:
    enter 0,0
    push ebx
    push edi

    mov ebx, [ ebp + 8 ]        ; t_intN
    mov ecx, [ ebp + 16 ]       ; t_N
    dec ecx
    mov edi, 1 
    mov eax, [ ebp + 12 ]       ; t_b
    cdq
    add [ ebx ], eax
.back:
    adc [ ebx + edi * 4 ], edx
    inc edi
    loop .back

    pop edi
    pop ebx
    leave
    ret
    

    
    
    

    global m_div_int64int32
m_div_int64int32:
    enter 0,0
    push ebx

    mov edx, 0
    mov eax, [ ebp + 12 ]       ; t_a_h
    div dword [ ebp + 16 ]      ; /= t_b

    mov ebx, eax

    mov eax, [ ebp + 8 ]        ; t_a_l
    div dword [ ebp + 16 ]      ; /= t_b

    ; ?? edx ?? zbytek se momentalne nevraci
    mov ecx, [ ebp + 20 ]
    jcxz .no_r
    mov [ ecx ], edx            ; zbytek
.no_r:
    mov edx, ebx

    pop ebx
    leave
    ret


    global m_mul_int64int32
m_mul_int64int32:
    enter 0,0
    push edi

    mov eax, [ ebp + 8 ]        ; t_a_l
    mul dword [ ebp + 16 ]      ; t_a_l * t_b

    mov ecx, eax
    mov edi, edx

    mov eax, [ ebp + 12 ]       ; t_a_h
    mul dword [ ebp + 16 ]      ; t_a_h * t_b

    ; ? edx ?
    add edi, eax
    mov eax, ecx
    mov edx, edi

    pop edi
    leave
    ret

    global m_add_int64int32
m_add_int64int32:
    enter 0,0

    mov eax, [ ebp + 16 ]       ; t_b
    cdq                         ; edx - signum extension
    add eax, [ ebp + 8 ]        ; t_b + t_a_l
    adc edx, [ ebp + 12 ]       ; edx += t_a_h

    leave
    ret


; functions
; global
; extern

; labels:
