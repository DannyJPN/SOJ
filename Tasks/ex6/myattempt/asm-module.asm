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

    section .text
 ;RDI,       RSI,        RDX,         RCX,  R8 a R9
	global longsum
longsum:
	enter 0,0
		;RDI = *ints;
		;RSI = N
		push rbx;
	
		mov rcx,rsi  	;int i = N;
		mov rax,0           ;int sum  = 0
	.loopstart:	;{
		mov ebx,dword [rdi+(rcx-1)*4];
		movsx r8,ebx;
		add rax,r8;
		
		loop .loopstart		;}
		
		pop rbx;
	leave
	ret
 ;RDI,       RSI,        RDX,         RCX,  R8 a R9
	global qwordbitset

qwordbitset:

	enter 0,0

		;RDI=         *bits
		mov rcx,rsi;           *size
		xor rax,rax
		xor rdx,rdx
		
		
		.loopend:
		mov rsi,1
		push rcx;
	
		movzx r8,byte[rdi+(rcx-1)]
		mov rcx,r8;
	
		
		shl rsi,cl  
		or rax,rsi
		.end:
		
		pop rcx;
		
		loop .loopend
	
	leave
	ret
	
 ;RDI,       RSI,        RDX,         RCX,  R8 a R9	
	global changenibbles
changenibbles:
	enter 0,0

		mov R8,qword 0xF0F0F0F0F0F0F0F0
		mov R9,R8
		shr R9,4
		mov rdx,rdi        ;int evenpart = g_arr[i] & g_evenmask
		mov rcx,rdi       ;int oddpart = g_arr[i] & g_oddmask
		and rdx,R8
		and rcx,R9
		
		shr rdx,4
		shl rcx,4	
		
		mov rax,0
		or rax,rdx	;num |= evenpart
		or rax,rcx		;num |=oddpart
		
    


	leave
	ret
	
	
	
 ;RDI,       RSI,        RDX,         RCX,  R8 a R9		
	global pos_neg
pos_neg:
	enter 0,0
		
		push rbx;
		;RDI=*nums
		mov rcx,rsi;RSI  = N;
		mov rax,qword 0           ;int countp = 0;
		mov rbx,qword 0          ;int countn = 0;
		mov r8,qword 0
	.loopstart:                     ;{
		cmp [rdi+(rcx-1)*8] ,r8
		jl .negative
		jg .positive
	.negative:
		inc rbx
		jmp .nextline
	.positive:
		inc rax
		jmp .nextline
		
	.nextline:
		
		loop .loopstart		;}
		;RDX = *counts
		mov[rdx],rax
		mov[rdx+4],rbx
		
	pop rbx;
	leave
	ret
	
	 ;RDI,       RSI,        RDX,         RCX,  R8 a R9	
	global changecase
changecase:
	enter 0,0
	
	push rbx
	
	mov r8,qword 'a'        ;pozdeji realna konstanta
	mov r9,qword 0          
	mov rdx,qword 'z';
	
	mov rax,qword 'A'        ;hranice A
	mov rbx,qword 'Z'        ;hranice B
	; RSI= upper 

	cmp RSI,Qword 0
	cmovne rax,r8
	cmovne rbx,rdx

	;RDI= * chars
	
	
.back:                      ; {
	cmp [ rdi ], byte 0     ; if ( *edx == '\0' )
	je .endloop
	mov r8,qword 'a'-'A';        XOR konstanta

	cmp [rdi], al ;if(*edx < 'A')
	cmovl r8,r9
	cmp [rdi],bl  ;if(*edx > 'Z')
	cmovg r8,r9

	xor [rdi],r8

	inc rdi                 ; edx++
	jmp .back               ; }
.endloop:

	pop rbx;
 	leave

	ret

	