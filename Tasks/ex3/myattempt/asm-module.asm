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

    section .text

	global charsum
charsum:
	enter 0,0
		push ebx
		push esi;
		mov ecx,[ebp +12]  	;int i = N;
		mov eax,0           ;int sum  = 0;
		mov edx,[ebp + 8]      ;*chars
	.loopstart:	;{
		mov bl,byte [edx+(ecx-1)];
		movzx esi,bl;
		add eax,esi;
		
		loop .loopstart		;}
		
		pop esi;
		pop ebx;
	leave
	ret

	global dwordbitset,qwordbitset
dwordbitset:
qwordbitset:

	enter 0,0
	push ebx;
	push edi;
	push esi;
	mov ebx,[ebp +8];         *bits
	mov ecx,[ebp +12];           *size
	xor eax,eax
	xor edx,edx
	
	
	.loopend:
	mov esi,1
	push ecx;

	movzx edi,byte[ebx+(ecx-1)]
	mov ecx,edi;
	cmp ecx,32;
	jb .int
	
	sub ecx,32
	shl esi,cl
	or edx,esi
	jmp .end
	
.int: 	
	shl esi,cl  
	or eax,esi
	.end:
	
	pop ecx;
	
	loop .loopend
	
	pop esi;
	pop edi;
	pop ebx;
	leave
	ret
	
	
	global changenibbles
changenibbles:
	enter 0,0

	
		mov edx,[ebp+8]        ;int evenpart = g_arr[i] & g_evenmask
		mov ecx,[ebp+8]         ;int oddpart = g_arr[i] & g_oddmask
		and edx,0xF0F0F0F0
		and ecx,0x0F0F0F0F
		shr edx,4
		shl ecx,4	
		
		mov eax,0
		or eax,edx	;num |= evenpart
		or eax,ecx		;num |=oddpart
		
    


	leave
	ret
	
	
	
	global pos_neg
pos_neg:
	enter 0,0
		push ebx;
		push edi;
		mov ebx,[ebp+8]           ;*nums
		mov ecx,[ebp +12]  	;int i = N;
		mov eax,dword 0           ;int countp = 0;
		mov edx,dword 0          ;int countn = 0;
	.loopstart:                     ;{
		cmp [ebx+(ecx-1)*4] ,dword 0
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
		mov edi,[ebp+16]
		mov[edi],eax
		mov[edi+4],edx
		
		pop edi;
		pop ebx;
		
	leave
	ret
	
	
	global changecase:
changecase:
	enter 0,0
	
	mov ecx,[ebp+12]        ; upper
	mov edx, [ebp+8]         ; * chars
	
	.back:                      ; {
	cmp [ edx ], byte 0     ; if ( *edx == '\0' )
	je .endloop
	
	cmp ecx,dword 0
	je .tolower
	jne .toupper
	
.toupper:
	cmp [edx],byte 'a' ;if(*edx < 'a')
	jl .outofrange
	cmp [edx],byte 'z'  ;if(*edx > 'z')
	jg .outofrange
	mov eax,dword 'a'-'A';
	sub [edx],eax                      ;touppercase
	jmp .changedone
.tolower:
	cmp [edx],byte 'A' ;if(*edx < 'A')
	jl .outofrange
	cmp [edx],byte 'Z'  ;if(*edx > 'Z')
	jg .outofrange
	mov eax,dword 'a'-'A';
	add [edx],eax                      ;tolowercase
	jmp .changedone
	
	
	
	
	
	.changedone:
	.outofrange:
	inc edx                 ; edx++
	jmp .back               ; }
	.endloop:

 	leave
	ret