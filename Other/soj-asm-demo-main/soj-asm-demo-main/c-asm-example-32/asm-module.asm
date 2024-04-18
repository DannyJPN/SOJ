;***************************************************************************
;
; Program for education in subject "Assembly Languages"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
; Example of linking of module in C and module in Assembly
;
;***************************************************************************
	bits 32

	section .data

; external variable
extern  g_main_pub_x
extern  g_main_loc_x

; public variable
global  g_module_pub_x

; local variables
g_module_pub_x      dd      0
g_module_loc_x      dd      0

        section .text

; public label (function)
global  tool_fun_pub

tool_fun_pub:
	enter 0,0

        mov     [ g_main_pub_x ], dword 40
        ;mov     [ g_main_loc_x ], dword 30     ; impossible
        mov     [ g_module_pub_x ], dword 20
        mov     [ g_module_loc_x ], dword 10

        leave
        ret

tool_fun_loc:
	enter 0,0

        mov     [ g_main_pub_x ], dword 100
        ;mov     [ g_main_loc_x ], dword 200     ; impossible
        mov     [ g_module_pub_x ], dword 300
        mov     [ g_module_loc_x ], dword 400

        leave
        ret
