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

int strlen_s( char *t_str );

void upstr( char *t_str );

void set_int_array( int *t_array, int t_len, int t_set );

void move_mem( void *t_dest, void *t_str, int t_len );


// Variables
//
int main()
{

    char nazdar[ 128 ] = "Ahoj programatori!";
    printf( "strlen %d\n", strlen_s( nazdar ) );
    printf( "strlen %d\n", strlen( nazdar ) );
    upstr( nazdar );
    printf( "upstr '%s'\n", nazdar );

    int l_array[ 10 ] = { 1, 2, 1, 2, 1, 2, 1, 2, 1, 2 };
    set_int_array( l_array, 8, -10 );
    for ( int i = 0; i < 10; i++ )
        printf( "%d ", l_array[ i ] );
    printf( "\n" );

    move_mem( nazdar, nazdar + 2, strlen( nazdar ) + 1 );
    printf( "move '%s'\n", nazdar );

    char utf[] = "+ěš-říéěšč\n";
    printf( "strlen %d '%s'\n", strlen( utf ), utf );
}

