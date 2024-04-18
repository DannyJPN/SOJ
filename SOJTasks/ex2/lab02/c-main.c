//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>
#include <string.h>

// Variables

void minmax_array();
void text_len();
void text_nahrad();

int g_int_array[ 10 ] = { 10000, -2, 5, 16, 20, -30, -100, 1000, -50, -5000 };
int g_int_array_len = 10;
int g_min, g_max;

char g_text[] = "zj1t1m3 d3lku r3t3zc3";
char g_text_len;
char g_znak = ' ';



int main()
{
    minmax_array();
    printf( "min = %d max = %d\n", g_min, g_max );

    text_len();
    printf( "len = %d, len = %d\n", g_text_len, strlen( g_text ) );

    text_nahrad();
    printf( "text = '%s'\n", g_text );
}
