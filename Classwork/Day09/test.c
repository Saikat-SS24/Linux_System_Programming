#include <stdio.h>

int global_var=100;

void function1(void) {
	printf("Function - global_var: %d\n", global_var);
}

void function2(void) {
	int local_var = 50;
	printf("Function2 - local_var: %d\n", local_var);
	printf("Function2 - global_var: %d\n", global_var);
}

int main(void)
{
	int main_var = 25;

	printf("Main - global_var: %d\n", global_var);
	printf("Main - main_var: %d\n", main_var);

	function1();
	function2();

	{
		int block_var = 10;
		printf("Block - block_var: %d\n", block_var);
	}

	return 0;
}
