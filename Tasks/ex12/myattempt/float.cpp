#include <stdio.h>
#include <stdlib.h>


#define B 1023
int main( int t_na, char **t_arg )
{
    union double_sep
    {
        double f_num ;
        struct
        {
            unsigned long long m :52;
            unsigned long long e :11;
            unsigned long long s :1;
        };
    };
    
union mantissa
    {
        long long i_num ;
        struct
        {
            unsigned long long m :52;
            unsigned long long m1 :12;
	
        };
    };
    
    

    double_sep f;
if(t_na < 2)
{
	printf("enter a number\n");
return 0;
}
    f.f_num = atof( t_arg[ 1 ] );   
    printf( "s:%llu e:%llu m:(1.)%llx\n", f.s, f.e, f.m );
	double num1 = 3;
	double num2 = 2;



	// double l_x , l_y , l_z
	double_sep l_x , l_y , l_z ;
	// l_x and l_y initialization
	l_x.f_num = num1 ;
	l_y.f_num = num2 ;
	// z signum
	l_z .s = ( l_x .s + l_y .s ) % 2;
	// l_z exponent
	l_z .e = ( l_x.e + l_y.e - B );
	// mantissas extension with leading 1
	mantissa l_mx;   l_mx.m = l_x.m, l_mx.m1 = 1  ;
	mantissa l_my;   l_my.m = l_y.m, l_my.m1 = 1  ;
	mantissa l_mz ;
	// mantissa computing
	l_mz . i_num = ( ( long long ) l_mx.i_num ) * l_my.i_num >> 52;
	// adjust result in range <2,4)
	if ( l_mz.m1 >= 2 )
	{
	l_mz.i_num >>= 1; // normalize mantissa
	l_z .e ++;
	// adjust exponent
	}
	// l_z mantissa
	l_z .m = l_mz .m;
	// result
	printf ( "%lf*%lf_=_%lf\n", l_x.f_num , l_y . f_num , l_z . f_num );



	// double l_x , l_y , l_z

	// l_x and l_y initialization
	l_x.f_num = num1 ;
	l_y.f_num = num2 ;
	long long Q ;
	if(l_x.e < l_y.e){Q = l_y.e - l_x.e;}
	else if (l_x.e > l_y.e){Q = l_x.e - l_y.e;}
	l_z .s = ( l_x .s == l_y .s ) ?l_x.s:1;






















}

//int mmain()
//{
//    union abcd {
//        int a;
//        struct {
//            unsigned int b: 4;
//            unsigned int c: 24;
//            unsigned int d: 4;
//        };
//    };
//
//    abcd aa;
//    aa.a = 0x12345678;
//    printf( "%x %x %x\n", aa.b, aa.c, aa.d );
//
//    return 0;
//}
//