#include <stdio.h>
#include <stdlib.h>

int	collatz(int step, int n);

int	main(int argc, char *argv[])
{
	int	step;
	int	n;

	n = atoi(argv[1]);
	step = collatz(0, n);
	printf("%d\n", step);
}

int	collatz(int step, int n)
{
	if (n <= 1)
		return (step);
	if (n % 2 == 0)
		collatz(step + 1, n / 2);
	else
		collatz(step + 1, 3 * n + 1);
}
