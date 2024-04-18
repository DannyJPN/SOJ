;***************************************************************************
;
; Program for education in subject "Assembly Languages"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
; Implementation of functions with parameters
;
;***************************************************************************

	bits 32

	section .data

        section .text

        ;int sum( int a, int b );
        global sum
sum:
        enter 0,0
        
        mov eax, [ ebp + 8 ]        ; parameter a
        add eax, [ ebp + 12 ]       ; a += b
                                    ; return value in eax
        leave
        ret

;***************************************************************************

        ;int average( int *array, int N );
        global average
average:
        enter 0,0

        mov ecx, [ ebp + 12 ]       ; length of array 
        mov edx, [ ebp + 8 ]        ; *array
        mov eax, 0                  ; sum
.back:
        add eax, [ edx + ecx * 4 - 4 ]; sum += array[ ecx - 1 ]
        loop .back

        cdq                         ; extension of eax to edx
        idiv dword [ ebp + 12 ]     ; sum /= N
                                    ; result in eax
        leave
        ret

;***************************************************************************

        ;int division( int a, int b, int *remainder );
        global division
division:
        enter 0,0
        
        mov eax, [ ebp + 8 ]        ; parameter a to eax
        cdq                         ; extension of eax to edx
        idiv dword [ ebp + 12 ]     ; eax /= b
                                    ; result is in eax
                                    ; remainder in edx
        mov ecx, [ ebp + 16 ]       ; remainder
        mov [ ecx ], edx            ; *remainder = edx

        leave
        ret
 
;***************************************************************************

        ;char *strmirror( char *str );
        global strmirror
        extern strlen
strmirror:
        enter 0,0
        
        push dword [ ebp + 8 ]      ; passing *str to strlen
        call strlen                 ; call strlen
        pop ecx                     ; clean stack
                                    ; length of string in eax
        mov ecx, [ ebp + 8 ]        ; first character of string
        mov edx, ecx
        add edx, eax
        dec edx                     ; last character of string
.back:
        cmp ecx, edx                ; while ( ecx < edx )
        jae .end
        mov al, [ ecx ]             ; sel. of first and last char
        mov ah, [ edx ]
        mov [ ecx ], ah             ; store sel. chars back
        mov [ edx ], al
        inc ecx                     ; move to the right
        dec edx                     ; move to the left
        jmp .back
.end:
        mov eax, [ ebp + 8 ]

        leave
        ret

;***************************************************************************

        ;char *int2str( int number, char *str );
        global int2str
int2str:
        enter 8,0

        mov eax, [ ebp + 8 ]        ; number
        mov ecx, [ ebp + 12 ]       ; *str
        mov [ ebp - 4 ], ecx        ; part of str. for mirror
        mov [ ebp - 8 ], dword 10   ; base of number system

        cmp eax, 0                  ; branches for < > = 0
        jg .positive
        jl .negative
        mov [ ecx ], word '0'       ; add to end of str "0\0"
        jmp .ret                    ; all is done
.negative:
        mov [ ecx ], byte '-'       ; sign at beginning of str
        inc dword [ ebp - 4 ]       ; skip sign
        neg eax                     ; turn sign
.back:
        inc ecx                     ; str++
.positive:
        test eax, eax               ; while ( eax )
        je .end
        mov edx, 0  
        div dword [ ebp - 8 ]       ; eax /= base
        add dl, '0'                 ; remainder += '0'
        mov [ ecx ], dl             ; *str = dl
        jmp .back
.end:
        mov [ ecx ], byte 0         ; *str = 0

        push dword [ ebp - 4 ]      ; begin of str. for mirror
        call strmirror
        pop ecx 
.ret:
        mov eax, [ ebp + 12 ]       ; return value is str

        leave
        ret
  
;***************************************************************************

        ;int strlength( char *str );
        global strlength
strlength:
        enter 0,0
        mov edi, [ ebp + 8 ]
        push ds
        pop es                      ; es = ds
        mov ecx, -1                 ; ecx = MAX
        mov al, 0                   ; searched character '\0'
        ; cld                       ; not necessary, DF is 0

        repne scasb                 ; searching

        inc ecx                     ; length without '\0'
        not ecx                     ; turn sign
        mov eax, ecx                ; string length

        leave
        ret

;***************************************************************************

        ;char *strnospaces( char *str );
        global strnospaces
strnospaces:
        enter 0,0

        push edi                    ; save registers
        push esi

        mov edi, [ ebp + 8 ]
        mov esi, edi                ; esi = edi
        push ds
        pop es                      ; es = ds
        ; cld                       ; not necessary, DF is 0
.back:
        lodsb                       ; al = [ rsi++ ]
        test al, al                 
        jz .end                     ; end of string
        cmp al, ' '
        je .back                    ; skip spave
        stosb                       ; [ edi++ ] = al
        jmp .back
.end:
        stosb                       ; [ edi ] = '\0'
        mov eax, [ ebp + 8 ]        ; return value

        pop esi                     ; restore registers
        pop edi

        leave
        ret

;***************************************************************************

