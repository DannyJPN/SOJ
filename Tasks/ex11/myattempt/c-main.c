//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// daniel.krupa@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>

// Variables
//


long mult_fix2( long t_a, long t_b, int t_fixed );
long div_fix2( long t_a, long t_b, int t_fixed );
long mult_fix10( long t_a, long t_b, int t_fixed );
long div_fix10( long t_a, long t_b, int t_fixed );

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


int main()
{
    
    float l_f_pi = 3.14;
   long l_i_pi = float2fix2( l_f_pi, FIXED2 );
    float l_f_10 = 10;
    long l_i_10 = float2fix2( l_f_10, FIXED2 );
    printf( "FLO pi %f\n", fix2float2( l_i_pi, FIXED2 ) );
printf( "FIX pi %li\n", float2fix2(fix2float2( l_i_pi, FIXED2 ),FIXED2) );

	
	
    long l_i_res = mult_fix2( l_i_10, l_i_pi, FIXED2 );
    printf( "%f * %li = %li (%f)\n",l_f_10,l_i_pi ,l_i_res, fix2float2( l_i_res, FIXED2 ) );

	float m1 = 0.25;
	float m2 = 6;
	float d1 = 7;
	float d2 = 49;
	
    printf( "%f * %f = %f\n",m1,m2 ,fix2float2( mult_fix2( float2fix2( m1, FIXED2 ), 
                                         float2fix2( m2, FIXED2 ), FIXED2 ), FIXED2 ) );
    printf( "%f/%f = %f\n",d1,d2, fix2float2( div_fix2( float2fix2( d1, FIXED2 ), 
                                         float2fix2( d2, FIXED2 ), FIXED2 ), FIXED2 ) );
					 
					 
	printf("--------------------------------------\n");				 

    float pi = 3.14;
   long lpi = float2fix10( pi, FIXED10 );
    float m0 = 10;
    long lm0 = float2fix10( m0, FIXED10 );
    printf( "FLO pi %f\n", fix2float10( lpi, FIXED10) );
printf( "FIX pi %li\n", float2fix10(fix2float10( lpi, FIXED10),FIXED10) );

	
	
     l_i_res = mult_fix10( lm0, lpi, FIXED10 );
    printf( "%f * %f = %li (%f)\n",m0,pi, l_i_res, fix2float10( l_i_res, FIXED10 ) );

	m1 = 0.25;
	m2 = 6;
	d1 = 7;
	d2 = 49;
	
    printf( "%f * %f = %f\n",m1,m2 , fix2float10( mult_fix10( float2fix10( m1, FIXED10 ), 
                                         float2fix10( m2, FIXED10 ), FIXED10 ), FIXED10 ) );
    printf( "%f/%f = %f\n",d1,d2,  fix2float10( div_fix10( float2fix10( d1, FIXED10 ), 
                                         float2fix10( d2, FIXED10 ), FIXED10 ), FIXED10 ) );
					 
					 
					 
	float R = 6;
	//viceciferna R se s velkou presnosti  nevleze
	
	
	
	float binsurf = fix2float2(          mult_fix2(float2fix2(R,FIXED2),   mult_fix2(float2fix2(R,FIXED2),           mult_fix2(float2fix2(4L,FIXED2),float2fix2( l_f_pi, FIXED2 ),FIXED2),FIXED2),                           FIXED2),FIXED2);
	printf("Kulicka povrch = 4 * %f * %f**2 = %f \n",l_f_pi, R  ,binsurf);
	
	float decsurf =fix2float10(   mult_fix10(float2fix10(R,FIXED10), mult_fix10(float2fix10(R,FIXED10),  mult_fix10(float2fix10(4L,FIXED10),float2fix10( pi, FIXED10 ),FIXED10),      FIXED10),FIXED10),FIXED10); 
	printf("Kulicka povrch = 4 * %f * %f**2 = %f \n",pi, R  ,decsurf);
	
	double realsurf = 4*pi*R*R;
	printf("Kulicka povrch = %f \n",realsurf);
	
	float binvol = fix2float2(  div_fix2(float2fix2(3L,FIXED2),     mult_fix2(float2fix2(R,FIXED2),      mult_fix2(float2fix2(R,FIXED2),   mult_fix2(float2fix2(R,FIXED2),           mult_fix2(float2fix2(4L,FIXED2),float2fix2( l_f_pi, FIXED2 ),FIXED2),FIXED2), FIXED2),   FIXED2),FIXED2),FIXED2);
	printf("Kulicka objem = 4 * %f * %f**3 / 3 = %f \n",l_f_pi, R  ,binvol);
	
	float decvol =fix2float10(  div_fix10(float2fix10(3L,FIXED10), mult_fix10(float2fix10(R,FIXED10),  mult_fix10(float2fix10(R,FIXED10), mult_fix10(float2fix10(R,FIXED10),  mult_fix10(float2fix10(4L,FIXED10),float2fix10( pi, FIXED10 ),FIXED10),      FIXED10),FIXED10),FIXED10),FIXED10),FIXED10); 
	printf("Kulicka objem = 4 * %f * %f**3 / 3 = %f \n",pi, R  ,decvol);
	
	double realvol = 4*pi*R*R*R/3;
	printf("Kulicka objem = %f \n",realvol);
	
	
	
					 
	float CZK = 1000;
	float course = 21.53;
	int prec = 1;

	float decUSD = fix2float10(div_fix10(float2fix10(CZK,prec),float2fix10(course,prec),prec),prec);
	printf("USD = %f \n",decUSD);

	
	
					 
					 
					 
					 
					 
					 
}
