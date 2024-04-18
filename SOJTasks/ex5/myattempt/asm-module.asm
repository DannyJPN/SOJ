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

    global move_mem
move_mem:
    enter 0,0

    push edi
    push esi



    mov ax, ds
    mov es, ax
    
    mov esi, [ ebp + 12 ]   ; t_src
    mov edi, [ ebp + 8 ]    ; t_dest
    mov ecx, [ ebp + 16 ]   ; t_len
    cmp esi,edi
    jb .fromleftshift
    ja .fromrightshift
    je .end
    
.fromleftshift:
	std
	
	add esi,ecx
	dec esi;
	add edi,ecx
	dec edi;
    jmp .end
	
	
.fromrightshift:	
	
	cld
	
	jmp .end
	
.end:

    

    rep movsb

cld
	pop esi
    pop edi

    leave
    ret
    
    
  global removenum
removenum:
    enter 0,0

    push edi
	push esi;



    mov edi, [ ebp + 8 ]    ; arr
    
    mov esi,edi   ; arr
        ;mov ax, ds
    ;mov es, ax
;
	cld
.back:
	
    lodsb
    test al, al 
    jz .end

    cmp al, '0'            ;if(al < 0 || al >9 )      =>    
    jb .next
    cmp al, '9'
    ja .next
    jmp .back
.next:  
    stosb



    jmp .back
.end:
	stosb
	mov eax,[ebp+8]
	pop esi;
    pop edi

    leave
    ret
    
    
	global str_comp
str_comp:
	enter 0,0
    push edi
    push esi



    mov ax, ds
    mov es, ax
    
    mov esi, [ ebp + 12 ]   ; s2
    mov edi, [ ebp + 8 ]    ; s1
     mov ecx , 1
     mov eax,0
    mov edx,-1
    
    
.loopback:
	cmp [esi],byte 0
	je .end
	cmp [edi],byte 0
	je .end


	cmpsb
	cmovb eax,ecx
	cmova eax,edx
	
	cmp eax,0
	jnz .end
	
	
	jmp .loopback



.end:
	pop esi
	pop edi
	
	
	leave
	ret
    
    global occurrence_count
occurrence_count:
	enter 0,0
	push edi
	push esi
	push ebx
	
	mov edi,[ebp+8]       ;array
	mov eax,[ebp+12]    ;searched num
	mov ecx,[ebp + 16]   ;len
	mov esi,dword 1;
	xor edx,edx          ;counter
.back:	 
	 
	 xor ebx,ebx
	 scasd
	cmove ebx,esi 
	add edx,ebx
	
	loop .back
	
	mov eax,edx
	pop ebx
	pop esi
	pop edi
	
	leave
	ret
    
    
    