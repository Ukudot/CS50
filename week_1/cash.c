#include <stdio.h>

int	get_quarters(int cents);
int	get_dimes(int cents);
int	get_nickels(int cents);
int	get_pennies(int cents);

int	main(void)
{
	int	cents;
	int	coins[4];
	int	change;

	coins[0] = 0;
	coins[1] = 0;
	coins[2] = 0;
	coins[3] = 0;
	cents = -1;
	while (cents < 0)
	{
		printf("Change owed: ");
		scanf("%d", &cents);
		printf("\n");
	}
	coins[0] = get_quarters(cents);
	cents -= coins[0] * 25;
	coins[1] = get_dimes(cents);
	cents -= coins[1] * 10;
	coins[2] = get_nickels(cents);
	cents -= coins[2] * 5;
	coins[3] = get_pennies(cents);
	printf("%i\n", coins[0] + coins[1] + coins[2] + coins[3]);
}

int	get_quarters(int cents)
{
	int	quarters;

	quarters = 0;
	while (cents >= 25)
	{
		quarters++;
		cents -= 25;
	}
	return (quarters);
}

int	get_dimes(int cents)
{
	int	dimes;

	dimes = 0;
	while (cents >= 10)
	{
		dimes++;
		cents -= 10;
	}
	return (dimes);
}

int	get_nickels(int cents)
{
	int	nickels;

	nickels = 0;
	while (cents >= 5)
	{
		nickels++;
		cents -= 5;
	}
	return (nickels);
}

int	get_pennies(int cents)
{
	return (cents);
}
