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
#include <strings.h>
#include <math.h>

// Variables
//
void intN_to_str( int *n, int N, char *s );
void str_to_intN( char *s, int *n, int N );

long long m_add_int64int32( long long t_a, int t_b );
long long m_mul_int64int32( long long t_a, int t_b );
long long m_div_int64int32( long long t_a, int t_b, int *t_r );

void div_intNintN( int *t_a, int *t_b, int t_N ); // t_a = t_a / t_b; t_b=zbytek
void mul_intNintN( int *t_a, int *t_b, int t_N ); // t_a *= t_b;

void m_add_intNint32( int *t_intN, int t_b, int t_N ); // t_intN += t_b



void m_sub_intNintN( int *t_intN, int *t_b, int t_N ); // t_intN += t_b
int m_add_intNintN( int *t_intaN, int* t_intbN, int t_N ); // t_intaN += t_intbN
void m_mul_intNint32( int *t_intN, int t_b, int t_N ); // t_intN *= t_b
int m_div_intNint32( int *t_intN, int t_b, int t_N ); // t_intN /= t_b
int m_shl_intN( int *t_intN, int t_N );             ; // t_intN <<= 1
int m_shr_intN( int *t_intN, int t_N );             ; // t_intN >>= 1

int is_zero( int *n, int N )
{
  int i = 0;
  while ( i < N ) if ( n[ i++ ] ) return 0;
  return 1;
}

int m_comp_intNintN(int *a, int *b, int N )
{
  int i;
  for ( i = N - 1; i >= 0; i-- )
  {
      if ( a[ i ] == b[ i ] ) continue;
      if ( ( unsigned int ) a[ i ] > ( unsigned int ) b[ i ] ) return 1;
      return -1;
  }
  return 0;
}

int* m_mult_intNintN( int *t_a, int *t_b ,int*l_res,int N)
{
    for ( int i = 0; i < N; i++ )
	{
	l_res[i]=0;
	}
	int l_a[N];
	int l_b[N];
	
memcpy(l_a,t_a,N*sizeof(int));
memcpy(l_b,t_b,N*sizeof(int));
	
	
    for ( int i = 0; i < N*32; i++ )
    {
        if ( l_b[0] & 1 )
		m_add_intNintN(l_res,l_a,N);
	
        m_shl_intN(l_a,N);
        m_shr_intN(l_b ,N); 
    }
    return l_res;
}

// N-bitu = |t_a|+|t_b|
// mul_intNint32 -> t_a*t_b -> t_a*t_b[0]*2^0 + t_a*t_b[1]*2^32 + t_a*t_b[2]*2^64 ...

int* m_div_intNintN( int *t_a, int *t_b, int* l_res,int *t_zbytek ,int N)
{
	for ( int i = 0; i < N; i++ )
	{
	l_res[i]=0;
		
	}
	
    int l_divadlo [2*N]; // cislo dvojnasobne velikost
    
    int *l_p_divadlo = l_divadlo;
	
	
//memcpy
    memcpy(l_p_divadlo, t_a,N*sizeof(int)); // delenec
    memset(&l_p_divadlo[ N ] ,0,N*sizeof(int));   // scena zacina uprostred divadla

    for ( int i = 0; i < N*32; i++ )
    {
        m_shl_intN(l_divadlo,2*N);    // vystrcime 1 bit na scenu
        m_shl_intN(l_res,N);
        if (m_comp_intNintN( &l_p_divadlo[ N] ,t_b,N)>=0 )
        {
            l_res[0] |= 1;     // l_res[ 0 ] |= 1
            m_sub_intNintN(&l_p_divadlo[ N ] ,t_b,N);
        }
    }
    if ( t_zbytek ) memcpy(t_zbytek , &l_p_divadlo[ N ],N*sizeof(int));

    return l_res;
}



#define N 10
#define sN 1024

#define pinNstr 10002
#define piN    2048

int main()
{
	char numA[sN] = "20000000000000";
	char numB[sN] = "65536";
	 char numC[sN] = "30000000000";
	 
	int a[N] = {0x0,0,0,0,0,0,0,0,0,0};
	int b[N] = {0x0,0,0,0,0,0,0,0,0,0};
	int c[N] = {0x0,0,0,0,0,0,0,0,0,0};
	
	int res[N] = {0,0,0,0,0,0,0,0,0,0};
	int rem[N] = {0,0,0,0,0,0,0,0,0,0};
	str_to_intN( numA, a, N );
	str_to_intN( numB, b, N );
	str_to_intN( numC, c, N );
	
	char strN[ sN ] = "";
    
printf("Numb A: \n");
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", a[ i ] );
    printf( "\n" );
	intN_to_str( a, N, strN );
    printf( "%s\n", strN );
	
printf("Numb B: \n");
   for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", b[ i ] );
    printf( "\n" );
	intN_to_str( b, N, strN );
    printf( "%s\n", strN );
	
	m_mult_intNintN(a,b,res,N);
	
	printf("RESULT: \n");
	for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", res[ i ] );
    printf( "\n" );
	intN_to_str( res, N, strN );
    printf( "%s\n", strN );
	
	printf("DIVISO: \n");
	for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", c[ i ] );
    printf( "\n" );
	intN_to_str( c, N, strN );
    printf( "%s\n", strN );
	
	m_div_intNintN(a,c,res,rem,N);
	
	printf("RESULT: \n");
	for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", res[ i ] );
    printf( "\n" );
	intN_to_str( res, N, strN );
    printf( "%s\n", strN );
		
	
	printf("REMAIN: \n");
	for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", rem[ i ] );
    printf( "\n" );
	intN_to_str( rem, N, strN );
    printf( "%s\n", strN );
		
	
	
	//rozpracovano
	
	int iter = 100;
	int onepercent = iter/100;
    int l_piN[ piN ], l_ZN[ piN ], l_Z[ piN ];
    char l_piNstr[ pinNstr ], l_ZNstr[ pinNstr ];
	
    memset( l_ZNstr, '0', sizeof( l_ZNstr ) );
	
    l_ZNstr[ pinNstr - 1 ] = 0; // konec retezce
    l_ZNstr[ 0 ] = '1';
    str_to_intN( l_ZNstr, l_ZN, piN );
	
   
   
    for ( int k = 0; k < iter; k++ )
    {
		memcpy( l_Z, l_ZN, sizeof( l_ZN ) );
		
		int nomin = 120*k*k + 151*k + 47;
		int denomin=512*k*k*k*k + 1024*k*k*k + 712*k*k + 194*k + 15;
		m_mul_intNint32( l_Z, nomin, piN );// l_z *= nomin
		m_div_intNint32( l_Z, denomin, piN );//l_z /= denomin
		for(int i = 0 ; i< 4*k;i++)
		{
			m_shr_intN(l_Z,piN);  //l_z /= 16^k 
			
		}
		
		//mel jsem tu improvizovany progressbar
		//if(k % onepercent == 0)
		//{
		//
		//printf("Iter %02d\n",k/onepercent);
		//	
		//}
		
		
		
		m_add_intNintN( l_piN, l_Z, piN );
    }
	
    intN_to_str( l_piN, piN,l_piNstr);
    printf( "pi=%s\n", l_piNstr );

	
	
	
	
		
	

}


