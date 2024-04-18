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
; variables
; global
; extern
    extern g_x, g_y
 

    section .text
    global fun_xy
fun_xy:
    enter 0,0
    
    ; mov [ g_y ], [ g_x ]
    mov eax, [ g_x ]
    mov [ g_y ], eax

    leave
    ret

