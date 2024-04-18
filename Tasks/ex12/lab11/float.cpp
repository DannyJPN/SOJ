#include <stdio.h>
#include <stdlib.h>

int main( int t_na, char **t_arg )
{
    union float_sep
    {
        float f_num ;
        struct
        {
            unsigned int m :23;
            unsigned int e :8;
            unsigned int s :1;
        };
    };

    float_sep f;

    f.f_num = atof( t_arg[ 1 ] );   
    printf( "s:%d e:%d m:(1.)%x\n", f.s, f.e, f.m );
}

int mmain()
{
    union abcd {
        int a;
        struct {
            unsigned int b: 4;
            unsigned int c: 24;
            unsigned int d: 4;
        };
    };

    abcd aa;
    aa.a = 0x12345678;
    printf( "%x %x %x\n", aa.b, aa.c, aa.d );

    return 0;
}
