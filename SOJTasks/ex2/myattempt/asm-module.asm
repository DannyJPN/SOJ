;***************************************************************************
;
; Program for education in subject "Assembly Languages"
; daniel.krupa@vsb.cz, Department of Computer Science, VSB-TUO
;
; Empty project
;
;***************************************************************************
	bits 32

	section .data

	extern g_text, g_diff, g_evenmask, g_oddmask,g_arr, g_arrlen, g_intsize,g_nibblesize,g_sum,g_average,g_countn,g_countp
    section .text

    global strtoupper
strtoupper:
    enter 0,0
 mov edx, g_text         ; char * edx = g_text
.back:                      ; {
    cmp [ edx ], byte 0     ; if ( *edx == '\0' )
    je .endloop
   cmp [edx],byte 'a' ;if(*edx < 'a')
   jl .outofrange
   cmp [edx],byte 'z'  ;if(*edx > 'z')
   jg .outofrange
   mov eax,dword[g_diff]
    sub [edx],eax                      ;*edx -= 'g_diff
    
.outofrange:
    inc edx                 ; edx++
    jmp .back               ; }
.endloop:

    


    
    leave
    ret

    global sumarr
sumarr:
    enter 0,0
	mov ecx,[g_arrlen]  	;int i = g_arrlen;
	mov eax,dword 0           ;int sum  = 0;
.loopstart:                     ;{
	add eax, [g_arr+(ecx-1)*4]

	loop .loopstart		;}
	
	mov [g_sum],eax            ;g_sum = *ecx
	mov ecx,[g_arrlen]	         ;*ecx = g_arrlen
	mov edx,[g_arrlen]           ;*edx = g_arrlen-1
	sub edx, dword 1
	and edx,ecx                    ;*edx &= ecx
	cmp edx, dword 0             ;if(*edx == 0)
	jz .notpower
	
	mov edx,0
	div ecx
	mov[g_average],eax
.notpower:
	
    leave
    ret

    global switchnibble
switchnibble:
    enter 0,0
	mov ecx,[g_arrlen]  	;int i = g_arrlen;
	
.loopstart:		;{
	mov edx,[g_arr+(ecx-1)*4]        ;int evenpart = g_arr[i] & g_evenmask
	mov eax,[g_arr+(ecx-1)*4]         ;int oddpart = g_arr[i] & g_oddmask
	and edx,[g_evenmask]
	and eax,[g_oddmask]
	shr edx,4
	shl eax,4
	
	mov [g_arr+(ecx-1)*4],edx	;g_arr[i] = evenpart
	or [g_arr+(ecx-1)*4],eax		;g_arr[i] |=oddpart
	
	;dec edx;
	loop .loopstart		;}
    


    
    leave
    ret



    global posneg
posneg:
    enter 0,0
	mov ecx,[g_arrlen]  	;int i = g_arrlen;
	mov eax,dword 0           ;int countp = 0;
	mov edx,dword 0          ;int countn = 0;
.loopstart:                     ;{
	cmp [g_arr+(ecx-1)*4] ,dword 0
	jl .negative
	jg .positive
.negative:
	inc edx
	jmp .nextline
.positive:
	inc eax
	jmp .nextline
	
.nextline:
	
	loop .loopstart		;}
	
	mov[g_countp],eax
	mov[g_countn],edx
	
	
    leave
    ret
