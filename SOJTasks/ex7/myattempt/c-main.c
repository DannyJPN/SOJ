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

 long palindrom(unsigned long num);

int isprime(long number);
void onlyprimes(long * nums,int count);
char *no_chars( char *t_str ,char *t_remove);

// Variables
//
int main()
{
	long nums[10] = {11,13,2,4,5,1,7,17,8,9};
	int N= 10;
	char str []="Jachc1 d0m 21 a rychl3";
	char torem []= "acd";
	unsigned long num = 0x8000000000000001;
	long prime = 32;
	printf("%016llX : %016llX\n",num,palindrom(num));
	printf("%llu prime = %d\n",prime,isprime(prime));
	for(int i = 0;i < N;i++)
	{
			printf("%llu,",nums[i]);
	}printf("\n");
	onlyprimes(nums,N);
	for(int i = 0;i < N;i++)
	{
			printf("%llu,",nums[i]);
	}printf("\n");
	printf("%s  ->",str);
	
	printf(" -%s-\n",no_chars(str,torem));
	//printf(" %d\n",(int)no_chars(str,torem));
	
}
