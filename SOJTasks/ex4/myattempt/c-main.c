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

int palindrom(unsigned int num);
void changecase(char* str,int toupper);
int isprime(int number);
void onlyprimes(int * nums,int count);
char *no_digit( char *t_str );

// Variables
//
int main()
{
	int nums[10] = {11,13,2,4,5,1,7,17,8,9};
	int N= 10;
	char str []="Jachc1 d0m 21 a rychl3";
	unsigned int num = 0x80000001;
	int prime = 31;
	printf("%08X : %08X\n",num,palindrom(num));
	printf("%s\n",str);
	changecase(str,0);
	printf("%s\n",str);
	printf("%d prime = %d\n",prime,isprime(prime));
	for(int i = 0;i < N;i++)
	{
			printf("%d,",nums[i]);
	}printf("\n");
	onlyprimes(nums,N);
	for(int i = 0;i < N;i++)
	{
			printf("%d,",nums[i]);
	}printf("\n");
	printf("%s -> %s\n",str,no_digit(str));
	
}
