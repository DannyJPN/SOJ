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

    extern g_int_array, g_int_array_len, g_min, g_max
    extern g_text, g_text_len, g_znak

    section .text

    ; int c;        [ c ]
    ;     &c          c
    ; int *ptr      edx
    ;      *ptr = 1         mov [ edx ], dword 1
    ;       ptr = 0         mov edx, 0 

    global text_nahrad
text_nahrad:
    enter 0,0

    push edi

    mov ecx, 0              ; inx = 0
    mov al, [ g_znak ]      ; g_znak
.zpet:                              ; {
    cmp [ g_text + ecx ], byte 0    ; if ( g_text[ inx ] == '\0' )
    je .hotovo
    
    cmp [ g_text + ecx ], byte '0'  ; if ( g_text[ inx ] >= '0' &&
    jl .taktedynic
    cmp [ g_text + ecx ], byte '9'  ; g_text[ ecx ] <= '9' ) ....
    jg .taktedynic

    mov [ g_text + ecx ], al

.taktedynic:

    inc ecx                         ; inx++

    jmp .zpet                       ; }

.hotovo:

    pop edi

    leave
    ret

    global text_len
text_len:
    enter 0,0

    mov edx, g_text         ; char * edx = g_text
.back:                      ; {
    cmp [ edx ], byte 0     ; if ( *edx == '\0' )
    je .hotovo
    inc edx                 ; edx++
    jmp .back               ; }
.hotovo:

    sub edx, g_text         ; edx - g_text
    mov [ g_text_len ], edx

    leave
    ret

    global minmax_array
minmax_array:
    enter 0,0

    mov ecx, [ g_int_array_len ]
    mov eax, [ g_int_array + 0 ] ; max
    mov edx, [ g_int_array + 0 ] ; min
.back:
    ; < l, > g, == e, <= le, >= ge
    ;cmp x, y 
    ;    x < y
    ;      jl navesti
    ;cmp a, b
    ;    a == b
    ;      je navesti    
    ; goto ( vyraz ) navz, nav0, navk

    cmp eax, [ g_int_array + ( ecx - 1 ) * 4 ] ; if ( max < g_int_array[ ecx ] )
    jge .takmaxne
    mov eax, [ g_int_array + ecx * 4 - 4 ]
.takmaxne:    

    cmp edx, [ g_int_array + ( ecx - 1 ) * 4 ] ; if ( min > g_int_array[ ecx ] )
    jle .takminne
    mov edx, [ g_int_array + ecx * 4 - 4 ]
.takminne:    

    loop .back                  ; for ( ecx = g_int_array_len; ecx > 0; ecx-- )

    mov [ g_max ], eax
    mov [ g_min ], edx

    leave
    ret
