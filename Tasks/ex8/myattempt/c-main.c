//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// daniel.krupa.st@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Variables
//
//long long add_int64int32( long long t_a, int t_b );
//long long mul_int64int32( long long t_a, int t_b );
//long long div_int64int32( long long t_a, int t_b, int *t_r );

void add_intNint32( int *t_intN, int t_b, int t_N ); // t_intN += t_b
void mul_intNint32( int *t_intN, int t_b, int t_N ); // t_intN *= t_b
int div_intNint32( int *t_intN, int t_b, int t_N ); // t_intN *= t_b
char *mirror( char *t_str );

int is_zero( int *n, int N )
{
  int i = 0;
  while ( i < N ) if ( n[ i++ ] ) return 0;
  return 1;
}


// function template for intN to string conversion

void intN_to_str( int *n, int N, char *s )
{
  int * num = (int*)malloc(N*sizeof(int));
	for(int i =0;i<N;i++)
	{
			num[i] = n[i];
	}
	
int i = 0;
  while ( !is_zero( num, N ) )
    s[ i++ ] = div_intNint32( num,10,N ) + '0';
    
  
  s[i] = 0;
mirror(s);
free(num);
  
}

// function template for string to intN conversion

void str_to_intN( char *s, int *n, int N )
{
  	for(int i =0;i<N;i++)
	{
			 n[i]=0;
	}
	//printf("Trasnfer\n");
  while ( *s )
  {
	//  printf("Analyzing %c\n",*s);
      mul_intNint32( n,10,N );
      add_intNint32( n,*s++ - '0',N );

	  }
  
}







#define N 8

int main()
{
   // printf( "add_32_64 %llX\n", add_int64int32( 0xFFFFFFFFFFFFFFll, 1 ) ); 
   // printf( "mul_32_64 %lld\n", mul_int64int32( 1111111111111111ll, 3 ) ); 
   // printf( "mul_32_64 %llX\n", mul_int64int32( 0xCAFECAFECAFEll, 16 ) ); 
   // int l_zbytek;
//printf( "div_32_64 %d %lld\n", l_zbytek, div_int64int32( 1234567891234ll, 100, &l_zbytek ) ); 
//printf( "div_32_64 %llX\n", div_int64int32( 0xCAFECAFECAFEll, 16, NULL ) ); 
//
    //int l_aN[ N ] = { 0xFFFFFFFF, 0xFFFFEFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0, 0, 0, 0 };
	int l_aN[ N ] = { 0xFFFFFFFF,0 , 0, 0, 0, 0, 0, 0 };
	int l_aN2[ N ] = { 0xFFFFFFFF,0xF, 0xF	, 0, 0, 0, 0, 0 };
	int l_aN3[ N ] = { 0,0 , 0, 0, 0, 0, 0, 0 };
	char num []  = "77777777777777777777777777153";
    printf( "add\n" );
    add_intNint32( l_aN, 10, N );
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_aN[ i ] );
    printf( "\n" );
    printf( "mul\n" );
    mul_intNint32( l_aN, 64, N );
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_aN[ i ] );
    printf( "\n" );
    printf( "div\n" );
    add_intNint32( l_aN, 33, N );
    int l_r = div_intNint32( l_aN, 64, N );
    for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_aN[ i ] );
    printf( "\n zbytek %d\n", l_r );

	
	char str[1024] = "ahoj";
	for ( int i = N - 1; i >= 0; i-- )
        printf( "%u ", l_aN2[ i ] );
printf("\n");
intN_to_str(l_aN2,N,str);

printf("IntToStr = -%s-\n",str);
str_to_intN(num,l_aN3,N);

printf("%s\nStrToInt: ",num);
	for ( int i = N - 1; i >= 0; i-- )
        printf( "%08X ", l_aN3[ i ] );
printf("\n")	;
	
	
	
	
	
	
	
	
}
