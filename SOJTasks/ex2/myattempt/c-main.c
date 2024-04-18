//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// daniel.krupa@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>
#include <string.h>

// Variables

void strtoupper();
void switchnibble();
void sumarr();
void posneg();

int g_countp=0,g_countn = 0;
int g_sum =0;
int g_average = -1;
char g_text[] = "zj1t1m3 d3lku r3t3zc3";
int g_diff = 'a'-'A';	
int g_evenmask = 0xF0F0F0F0;
int g_oddmask =  0x0F0F0F0F;
int g_nibblesize = 4;
int g_arr[4] = {0x18801000,0x100,0x1000,0x10000};
int g_arrlen = 4;
int g_intsize = 4;

int main()
{
	
    printf( "text before = '%s'\n", g_text );
    strtoupper();
    printf( "text after= '%s'\n", g_text );

	for(int i = 0;i<g_arrlen;i++)
	{
	printf("numbers before %08X\n",g_arr[i]);
	}
	switchnibble();
	
	for(int i = 0;i<g_arrlen;i++)
	{
	printf("numbers after %08X\n",g_arr[i]);
	}	
	
	for(int i = 0;i<g_arrlen;i++)
	{
	printf("numbers to sum %d	\n",g_arr[i]);
	}	
	
	
	sumarr();
	printf("Sum %d Average %d\n",g_sum,g_average);
	posneg();
	printf("Pos %d Neg %d\n",g_countp,g_countn);
	
}
