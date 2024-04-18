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

    section .text
	extern strchr
 ;RDI,       RSI,        RDX,         RCX,  R8 a R9
    global palindrom
palindrom:
    enter 0,0

	
	mov Rcx, dword 0       ; citac
	mov Rax,dword 0;       druhe cislo 

	
	;RDI =  prvni cislo

.zpet:
    cmp Rcx, 32
    jae .end
	mov Rdx,dword 1
	and Rdx,rdi
		
	shr rdi,1
	shl rax,1
	or rax,rdx



    inc rcx;
    jmp .zpet
    
    ;0110 1101
    ;0000 0110
    ;0000 1011
.end:
	
    xor rax,rdi
    ; vraci nulu,pokud jsou stejne,jinak vrati nenulove cislo,ne nutne 1
    
    
    



    leave
    ret
	
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
  global maxdeviation
maxdeviation:
  enter 0,0
  ;RDI = pole
  ;RSI = delka
  call longsum
  ;RAX = suma
  cqo;
  idiv RSI;
  ;RAX = result
  ;RDX = remainder
  mov rcx,rsi
  xor r9,r9
.loopback:
	mov r10,rax
	sub r10,qword [rdi+(rcx-1)*4]
	;R10 = rozdil
	mov r8,r10
	;r8 = rozdil
	sar r8,31
	xor r10,r8
	sub r10,r8
	;R10 = abs
	cmp r10,r9
	cmova r9,r10

	
	

	loop .loopback 
  
  mov r9,rax
  
  
  
  leave 
  ret






  
    
   ;RDI,       RSI,        RDX,         RCX,  R8 a R9  
    	global isprime
isprime:
	enter 0,0
	
	
	mov rcx,rdi
	mov r8,qword 0
	
.loopback:
	
	mov rax,rdi
	mov rdx,qword 0;
	cmp rax,qword 1
	jle .notprime
	
	cqo;
	idiv rcx;
	
	cmp rdx,qword 0
	jne .nondividable
	inc r8;
	
	
	
.nondividable:
	loop .loopback
	
	cmp r8,qword 2;
	je .prime
	
	
	
.notprime:
	mov rax,qword 0;
	jmp .end
.prime:
	mov rax,qword 1;
	jmp .end
	
.end:
	
	leave
	ret;
	
	
  ;RDI,       RSI,        RDX,         RCX,  R8 a R9  	
	global onlyprimes
onlyprimes:
	enter 0,0
	
	push rbx;
	
	;RDI= pole
	mov r8,qword 0      ;
	mov rbx,qword 0
	
.cycle:
	cmp r8,rsi;            if(esi < count)
	je .endprimes
	
	
	mov r9,rdi
	mov r10,r8
	mov rdi,[rdi+r8*8]
	
	call isprime;
	mov rdi,r9
	mov r8,r10
	
	mov rdx,[rdi+r8*8]
	cmp rax,qword 0
	cmove rdx,rbx
	
	
	mov [rdi+r8*8],rdx;

	inc r8;
	jmp .cycle
	
	
	
.endprimes:
	pop rbx;
	leave
	ret
	
	
    
    
    
    
 ;RDI,       RSI,        RDX,         RCX,  R8 a R9   	
	global no_chars
no_chars:
	enter 0,0
	
	push rbx;
	
	;mov rdx,rdi
	xor rax,rax              ;src
	xor rcx,rcx              ;dest
	mov r8,qword 1;	
.back:                      ; {
	cmp [ rdi +rax], byte 0     ; if ( edx[src] == '\0' )
	je .endloop
	xor r9,r9;
	xor rbx,rbx
	
	;mov bl,byte [rdi + rax]          ; 
	;cmp [rdi + rax], SIL
	push rax
	push r8
	push r9
	push rbx
	push rdi
	push rcx
	push rsi
	
	
	;RDI = t_str
	;RSI = t_rem
	xchg rdi,rsi                     
	;RDI = t_rem
	;RSI = t_str
	
	movzx RSI,byte [ rsi +rax] ; rsi = rsi[rax]
	
	call strchr
	
	pop rsi
	pop rcx
	pop rdi
	pop rbx
	pop r9
	pop r8
	
	
	cmp rax,qword 0
	cmove r9,r8
	pop rax
	mov bl,byte [rdi+rax]
	mov [rdi+rcx],bl           ;edx[ecx] = edx[eax]
	inc rax
	add rcx,r9;
	
	jmp .back                  ;}
.endloop:
	mov [rdi+rcx],dword 0
	mov rax,rdi
	;mov rax,rcx;
	pop rbx;
	leave
	ret
