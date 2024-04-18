;***************************************************************************
;
; Program for education in subject "Assembly Languages"
; daniel.krupa.st@vsb.cz, Department of Computer Science, VSB-TUO
;
; Empty project
;
;***************************************************************************
	bits 32

	section .data



    section .text
    global palindrom
palindrom:
    enter 0,0

	push edi;
	push esi;
	
	mov ecx, dword 0       ; citac
	mov eax,dword 0;       druhe cislo 

	
	mov esi,[ebp+8]          ; prvni cislo

.zpet:
    cmp ecx, 16
    jae .end
	mov edx,dword 1
	and edx,esi
		
	shr esi,1
	shl eax,1
	or eax,edx



    inc ecx;
    jmp .zpet
    
    ;0110 1101
    ;0000 0110
    ;0000 1011
.end:
	
    xor eax,esi
    ; vraci nulu,pokud jsou stejne,jinak vrati nenulove cislo,ne nutne 1
    
    
    


    pop esi;
    pop edi;

    leave
    ret

	global changecase
changecase:
	enter 0,0
	
	push edi;
	push esi;
	push ebx;
	
	mov edi,dword 'a'        ;pozdeji realna konstanta
	mov esi,dword 0          
	mov edx,dword 'z';
	
	mov eax,dword 'A'        ;hranice A
	mov ebx,dword 'Z'        ;hranice B


	mov ecx,[ebp+12]        ; upper 
	cmp ecx,dword 0
	cmovne eax,edi
	cmovne ebx,edx
	
	
	mov edx, [ebp+8]         ; * chars
	
	
.back:                      ; {
	cmp [ edx ], byte 0     ; if ( *edx == '\0' )
	je .endloop
	mov edi,dword 32;        XOR konstanta
	
	cmp [edx], al ;if(*edx < 'A')
	cmovl edi,esi
	cmp [edx],bl  ;if(*edx > 'Z')
	cmovg edi,esi

	
	xor [edx],edi

	

	inc edx                 ; edx++
	jmp .back               ; }
	.endloop:

	pop ebx;
	pop esi;
	pop edi;
 	leave
	ret
	
	
	
	
	global isprime
isprime:
	enter 0,0
	
	push edi;
	
	mov ecx,[ebp+8]
	mov edi,dword 0
	
.loopback:
	
	mov eax,[ebp+8]
	mov edx,dword 0;
	cmp eax,dword 1
	jle .notprime
	
	cdq;
	idiv ecx;
	
	cmp edx,dword 0
	jne .nondividable
	inc edi;
	
	
	
.nondividable:
	loop .loopback
	
	cmp edi,dword 2;
	je .prime
	
	
	
.notprime:
	mov eax,dword 0;
	jmp .end
.prime:
	mov eax,dword 1;
	jmp .end
	
.end:
	pop edi;
	leave
	ret;
	
	
	
	global onlyprimes
onlyprimes:
	enter 0,0
	push edi;
	push esi;
	push ebx;
	
	mov edi,[ebp +8]        ; pole
	mov esi,dword 0      ;
	mov ebx,dword 0
	
.cycle:
	cmp esi,[ebp+12];            if(esi < count)
	je .endprimes
	
	
	push dword [edi+esi*4]
	call isprime;
	add esp, 4;
	mov edx,[edi+esi*4]
	cmp eax,dword 0
	cmove edx,ebx
	
	
	mov [edi+esi*4],edx;

	inc esi;
	jmp .cycle
	
	
	
.endprimes:
	pop ebx;
	pop esi;
	pop edi;
	leave
	ret
	
	
	
	
	global no_digit
no_digit:
	enter 0,0
	
	push ebx;
	push edi;
	push esi;
	
	mov edx,[ebp +8]
	xor eax,eax              ;src
	xor ecx,ecx              ;dest
	mov esi,dword 1;	
.back:                      ; {
	cmp [ edx +eax], byte 0     ; if ( edx[src] == '\0' )
	je .endloop
	xor edi,edi;
	
	movzx ebx,byte [edx + eax]          ; ebx = edx[src]
	cmp [edx + eax],byte '0'
	cmovb edi,esi
	cmp [edx + eax],byte '9'
	cmova edi,esi
	

	mov [edx+ecx],bl           ;edx[ecx] = edx[eax]
	inc eax
	add ecx,edi;
	
	jmp .back                  ;}
.endloop:
	mov [edx+ecx],dword 0
	mov eax,edx
	
	pop esi;
	pop edi;
	pop ebx;
	leave
	ret