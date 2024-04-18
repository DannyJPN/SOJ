;***************************************************************************
;
; Program for education in subject "Assembly Languages"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
; FPU unit usage examples
;
;***************************************************************************

	bits 32

	section .data

        section .text

;***************************************************************************

        ;float add_float( float a, float b );
        ;double add_double( double a, double b );
        global add_float, add_double
add_float:
        enter 0,0
        fld dword [ ebp + 8 ]       ; a
        fadd dword [ ebp + 12 ]     ; a += b
        leave
        ret

add_double:
        enter 0,0
        fld qword [ ebp + 8 ]       ; a
        fadd qword [ ebp + 16 ]     ; a += b
        leave
        ret

;***************************************************************************

        ;double area_sphere( double r );
        global area_sphere
area_sphere:
        enter 0,0
        ; A = 4 pi r^2
        fld qword [ ebp + 8 ]       ; st0 = r
        fmul st0, st0               ; st0 = r*r
        fld1                        ; st0 = 1
        fadd st0, st0               ; st0 = 2
        fadd st0, st0               ; st0 = 4
        fmulp st1                   ; st1 = r*r*st0 and pop
        fldpi                       ; st0 = pi
        fmulp st1                   ; st1 = r*r*4*st0 and pop
        leave
        ret

;***************************************************************************

        ;float find_max( float *array, int N );
        global find_max
find_max:
        enter 0,0
        mov edx, [ ebp + 8 ]        ; array
        mov ecx, [ ebp + 12 ]       ; N
        fld dword [ edx ]           ; first elem. as MAX
        dec ecx                     ; skip first element
.back:
        fld dword [ edx + ecx * 4 ] ; st0 = array[ ecx ]
        fcomi st1                   ; cmp st0, st1
        jb .skip
        fst st1                     ; exchange st1 = st0
.skip:
        fstp st0                    ; pop st0
        loop .back
                                    ; MAX is in st0
        leave
        ret

;***************************************************************************

        ;double array_average( double *array, int N );
        global array_average
array_average:
        enter 0,0
        
        mov edx, [ ebp + 8 ]        ; array
        mov ecx, [ ebp + 12 ]       ; N
        fldz                        ; st0 = 0
.back:
        fadd qword [ edx + ecx * 8 - 8 ] ; st0 += pole[ ecx ]
        loop .back

        fild dword [ ebp + 12 ]     ; N
        fdivp st1                   ; st0 /= N
        leave
        ret

;***************************************************************************
    
        ;double power_xy( double x, double exp );
        global power_xy
power_xy:
        enter 4,0
        ; x^exp = 2 ^ ( exp * log2( x ) ) 

        fld qword [ ebp + 16 ]      ; st0 = exp
        fld qword [ ebp + 8 ]       ; st0 = x, st1 = exp
        fyl2x                       ; st1 *= log2(st0), pop
                                    ; st0 is el2x
        fld st0
        fld st0                     ; 2 copies of el2x

        fstcw [ ebp - 4 ]           ; save CW
        fstcw [ ebp - 2 ]           ; save CW
        or word [ ebp - 4 ], 0xc00  ; rounding to 0
        fldcw [ ebp - 4 ]           ; restore CW
        frndint                     ; st0 = int( st0 )
        fldcw [ ebp - 2 ]           ; restore CW

        fsubp st1,st0               ; st1 -= st0, pop
                                    ; st0 = frac. of el2x
        f2xm1                       ; st0 = 2^st0 - 1
        fld1
        faddp st1, st0              ; st1 += 1 and pop
                                    ; st1 = el2x
        fscale                      ; st0 = 2^int(st1)*st0
        fstp st1                    ; st1 = st0 and pop

        leave
        ret

        
