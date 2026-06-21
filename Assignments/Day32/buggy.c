/*The program is supposes to print numbers from 1 to 5 but because of a type mistake in the loop
condition(i>5) instead of (i<=5), the loop never runs */

#include <stdio.h>

int main()
{
	int i = 1;
	while (i > 5) //Logical Error
	{
		printf("Number: %d\n", i);
		i++;
	}

	printf("Loop finished. Value of i is: %d\n", i);
	return 0;
}
