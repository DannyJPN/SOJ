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
		
        section .text
		
 ;RDI,       RSI,        RDX,         RCX,  R8 a R9
global ComparePass
	ComparePass:
	enter 0,0
	xor rax,rax
	xor rcx,rcx
	mov rcx,rdx
.cycle:
	mov r8b, byte [rdi+rcx-1]
	mov r9b, byte [rsi+rcx-1]
	cmp r8b, r9b
	jb .below
	ja .above
	jmp .endcycle
	
.below:
	sub rax,1
	jmp .end
.above:
	add rax,1
	jmp .end
	
.endcycle:
	loop .cycle


.end:
    leave
    ret
	
	
	
global PadTo16
	PadTo16:
	enter 0,0
	mov rax , rdi ; moving content length to RAX
	xor rdx,rdx
	mov r8,rdi      ;backup RDI,as div will delete it
	;xor rcx,rcx   ; rcx = 0
	
	mov rcx,qword 16     ;  rcx = 16
	div rcx        ; rax/rcx, divising content length by 16
	mov rax,r8     ; result = RDI (length)
	sub rcx,rdx    ; rcx - rdx = 16 - remainder = size needed to pad
	add rax,rcx    ; actually padding
	;mov [rsi],cl


    leave
    ret
	
	
global Zeroize
	Zeroize:
	enter 0,0
	mov rcx,rsi
	;sub rcx,1
.cycle:
	mov [rdi+rcx-1],byte 0
	loop .cycle

    leave
    ret
	
	
global FillInfo
	FillInfo:
	enter 0,0
	mov [rdi+8],rdx
	mov [rdi+7],sil
    leave
    ret
 ;RDI,       RSI,        RDX,         RCX,  R8 a R9	
global GetInfectionInfo
	GetInfectionInfo:
	enter 0,0
	xor r8,r8
	mov r8,[rdi + rsi -8 ] ; extract original infector size
	mov [rdx],r8           ;save the size into output variable
	xor r9,r9
	mov r9b , byte [rdi+rsi-9]; extract the padded size
	mov [rcx],r9b;        save the padded size into output variable
	leave
	ret
	
	
global ExtractFormerContent
	ExtractFormerContent:
	enter 0,0
	
	
	xor r8,r8
	
.cycle:
	
	
	mov r10b, byte [rdi + rdx]
	mov [rsi+r8],r10b
	inc r8
	inc rdx
	cmp r8,rcx

	
	jb .cycle
	
	mov rax,rsi
	leave
	ret
	
		
	
	
global CalculateDerivateArray
	CalculateDerivateArray:
	enter 0,0
	mov rax,rdx      ;saving source len to RAX
	mov r11,rdx      ;backing up source len
	xor rdx,rdx
	div rcx           ;RAX = count of cycles,RCX = length of one cycle
	mov r9,rcx        ; backup cycle len
	sub r11,rdx
;zeroing up the initial array
.filler:
	mov [rdi+rcx-1],byte 0
	loop .filler
	
	;mov r10,r11
	
	
.round:
	mov rcx,r9
.xorer:
	;mov r8b,[rsi+r10+rcx-1]  
	mov r8b,[rsi+r11-1] 
	xor [rdi+rcx-1],r8b ; xor first round with r11'th round
	dec r11
	loop .xorer
	
	
	;dec r11
	cmp r11,0
	jnz .round
	
	
	
	leave
	ret
	
	

global Mirror
	Mirror:
    enter 0,0

	mov rax,rsi
   ; push rdi     ; push t_str
   ; call strlen
   ; pop rcx

	
    mov rcx,rdi        ; t_str, levy
    mov rdx, rcx
    add rdx, rax                ; s = "A"  s[ 0 ] = 'A', s[ 1 ] = '\0'
    dec rdx                     ; t_str + length - 1, pravy
	
.zpet:
    cmp rcx, rdx
    jae .hotovo

    mov al, [ rcx ]
    mov ah, [ rdx ]
    mov [ rcx ], ah
    mov [ rdx ], al

    inc rcx
    dec rdx
    jmp .zpet
.hotovo:

    mov rax, rdi

    leave
    ret
	
	
	
