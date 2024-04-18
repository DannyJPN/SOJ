//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// daniel.krupa@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>
#include<stdlib.h>
// Variables
//
extern "C"{  

long mult_fix2( long t_a, long t_b, int t_fixed );
long div_fix2( long t_a, long t_b, int t_fixed );
long mult_fix10( long t_a, long t_b, int t_fixed );
long div_fix10( long t_a, long t_b, int t_fixed );
}

long float2fix2( float t_a, int t_fixed )
{
    return t_a * ( 1L << t_fixed ); // 2**t_fixed
}

float fix2float2( long t_a, int t_fixed )
{
	//printf("FFLO %f   %f\n",(float)t_a,(float)( 1L << t_fixed ));
	
    return ( ( float ) t_a ) / (float)( 1L << t_fixed );
}


long float2fix10( float t_a, int t_fixed )
{
	for(int i =0;i<t_fixed;i++)
	{
		t_a*=10;
	}
	
	
    return t_a; // 10**t_fixed
}

float fix2float10( long t_a, int t_fixed )
{
	float a = (float)t_a;
		for(int i =0;i<t_fixed;i++)
	{
		a /=10;
	}
	
	
    return a; // 10**t_fixed
    
}




#define FIXED2 32
#define FIXED10 6


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
if(t_na < 3)
{
	printf("enter numbers\n");
return 0;
}
    f.f_num = atof( t_arg[ 1 ] );   
    printf( "s:%llu e:%llu m:(1.)%llx\n", f.s, f.e, f.m );
	double num1 = atof( t_arg[ 1 ] );  ;
	double num2 = atof( t_arg[ 2 ] );  ;



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
	//l_mz . i_num = ( ( long long ) l_mx.i_num ) * l_my.i_num >> 52;
	l_mz.i_num = mult_fix2( l_mx.i_num , l_my.i_num , 52 );
	
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

printf("---------------------------------------------------------\n");
//-----------------------------------------------------------------
	// double l_x , l_y , l_z
	
	// l_x and l_y initialization
	l_x.f_num = num1 ;
	l_y.f_num = num2 ;
	long long Q =0;
	l_mx.m = l_x.m, l_mx.m1 = 1  ;

	l_my.m = l_y.m, l_my.m1 = 1  ;
	//printf("LMX: %016llX (%llu . %016llx)\n",l_mx.i_num,l_mx.m1,l_mx.m);
	//printf("LMY: %016llX (%llu . %016llx)\n",l_my.i_num,l_my.m1,l_my.m);

	if(l_x.e < l_y.e)
	{
		//printf("X lower: %llu < %llu\n",l_x.e,l_y.e);
		Q = l_y.e - l_x.e;
		l_z.e  = l_x.e+Q;
		l_mx.i_num>>=Q;
	}
	else if (l_x.e > l_y.e)
	{
		//printf("Y lower: %llu > %llu\n",l_x.e,l_y.e);
		Q = l_x.e - l_y.e;
		l_z.e  = l_y.e+Q;
		l_my.i_num>>=Q;
	}
	//printf("Q: %llu\n",Q);
	//
	//printf("LMX new: %016llX (%llu . %016llx)\n",l_mx.i_num,l_mx.m1,l_mx.m);
	//printf("LMY: new %016llX (%llu . %016llx)\n",l_my.i_num,l_my.m1,l_my.m);

	
	
	
	l_mz.i_num =  l_mx.i_num + l_my.i_num;
	//printf("LMZ INUM:%016llx + %016llx =  %016llX (%llu . %016llx)\n",l_mx.i_num,l_my.i_num,l_mz.i_num,l_mz.m1,l_mz.m);
	if( l_mz.m1 >= 2 )
	{
	l_mz.i_num >>= 1; // normalize mantissa
	l_z .e ++;
	// adjust exponent
	}
	//printf("LMZ norm: %016llX (%llu . %016llx)\n",l_mz.i_num,l_mz.m1,l_mz.m);
	// l_z mantissa
	l_z .m = l_mz .m;
	// result
	
	
	l_z.s = 0;
		
	
	
	
	printf ( "%lf+%lf_=_%lf (%llu %llu %llx)\n", l_x.f_num , l_y . f_num , l_z . f_num ,l_z.s,l_z.e,l_z.m);


printf("---------------------------------------------------------\n");
//-----------------------------------------------------------------
	// double l_x , l_y , l_z
	
	// l_x and l_y initialization
	l_x.f_num = num1 ;
	l_y.f_num = num2 ;
	 Q =0;
	l_mx.m = l_x.m, l_mx.m1 = 1  ;

	l_my.m = l_y.m, l_my.m1 = 1  ;
	//printf("LMX: %016llX (%llu . %016llx)\n",l_mx.i_num,l_mx.m1,l_mx.m);
	//printf("LMY: %016llX (%llu . %016llx)\n",l_my.i_num,l_my.m1,l_my.m);

	if(l_x.e < l_y.e)
	{
		//printf("X lower: %llu < %llu\n",l_x.e,l_y.e);
		Q = l_y.e - l_x.e;
		l_z.e  = l_x.e+Q;
		l_mx.i_num>>=Q;
	}
	else if (l_x.e > l_y.e)
	{
		//printf("Y lower: %llu > %llu\n",l_x.e,l_y.e);
		Q = l_x.e - l_y.e;
		l_z.e  = l_y.e+Q;
		l_my.i_num>>=Q;
	}
	//printf("Q: %llu\n",Q);
	//
	//printf("LMX new: %016llX (%llu . %016llx)\n",l_mx.i_num,l_mx.m1,l_mx.m);
	//printf("LMY: new %016llX (%llu . %016llx)\n",l_my.i_num,l_my.m1,l_my.m);

	
	
	
	l_mz.i_num =  l_mx.i_num - l_my.i_num;
	//printf("LMZ INUM:%016llx - %016llx =  %016llX (%llu . %016llx)\n",l_mx.i_num,l_my.i_num,l_mz.i_num,l_mz.m1,l_mz.m);
	if( l_mz.m1 >= 2 )
	{
	l_mz.i_num >>= 1; // normalize mantissa
	l_z .e ++;
	// adjust exponent
	}
	//printf("LMZ norm: %016llX (%llu . %016llx)\n",l_mz.i_num,l_mz.m1,l_mz.m);
	// l_z mantissa
	l_z .m = l_mz .m;
	// result
	l_z.s = 0;
		
	
	
	
	printf ( "%lf-%lf_=_%lf (%llu %llu %llx)\n", l_x.f_num , l_y . f_num , l_z . f_num ,l_z.s,l_z.e,l_z.m);


	
	
	//l_z.s = ( l_x .s == l_y .s ) ?l_x.s:1;
	
	







}