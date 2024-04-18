
// Variable
#include <stdio.h>
extern void push(int val);
extern int pop();
extern int peek();



int main()
{
	push(4);
	push(6);

	
	int peekval = peek();
	printf("Stack top number: %d\n",peekval);
	int popval = pop();

	printf("Stack top number: %d\n",popval);
	peekval = peek();
	printf("Stack top number: %d\n",peekval);
}
