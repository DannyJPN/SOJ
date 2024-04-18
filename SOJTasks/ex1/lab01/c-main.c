//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>

// Variables

int g_x, g_y;

int fun_xy();


int main()
{
    g_y = 1;
    g_x = 3456;
    printf( "x %d y %d\n", g_x, g_y );
    fun_xy();
    printf( "x %d y %d\n", g_x, g_y );
}
