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

int max_int_array( int *t_pole , int t_N );
void minmax_int_array( int *t_pole , int t_N, int *t_minmax );
char *replace_digit( char *t_str, char t_replace );
char *otoc_str( char *t_str );

// Variables
//
int main()
{
    int int_array[ 10 ] = { -1000, 20, -30, -40, 5000, 60, -70, -80, 90, 100 };
    printf( "max %d\n", max_int_array( int_array, 10 ) );
    int int_minmax[ 2 ];
    minmax_int_array( int_array, 10, int_minmax );
    printf( "min %d max %d\n", int_minmax[ 0 ], int_minmax[ 1 ] );

    char l_str[] = "ahoj NAZDAR 4.3.2021";
    printf( "replace '%s'\n", replace_digit( l_str, '.' ) );
    printf( "mirror '%s'\n", otoc_str( l_str ) );
}
