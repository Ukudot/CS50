#include <stdio.h>

int		ft_type(long int n_card);
int		ft_validation(long int n_card);
void	ft_print(int type, int valid);

int	main(void)
{
	long int	n_card;
	int			valid;
	int			type;

	printf("Number: ");
	scanf("%li", &n_card);
	type = ft_type(n_card);
	if (type == -1)
	{
		printf("INVALID\n");
		return (0);
	}
	valid = ft_validation(n_card);
	ft_print(type, valid);
	return (0);
}

int	ft_type(long int n_card)
{
	int			digits;
	long int	f_d;

	digits = 0;
	while (n_card > 0)
	{
		digits++;
		if (n_card / 10 > 0)
			f_d = n_card % 100;
		n_card /= 10;
	}
	if (digits == 13 && f_d / 10 == 4)
		return (1);
	else if (digits == 15 && (f_d == 34 || f_d == 37))
		return (2);
	else if (digits == 16 && f_d / 10 == 4)
		return (1);
	else if (digits == 16 && (f_d > 50 && f_d < 56))
		return (3);
	else
		return (-1);
}

int	ft_validation(long int n_card)
{
	long int	sum;
	int			i;

	i = 0;
	sum = 0;
	while (n_card > 0)
	{
		if (i % 2 == 1)
		{
			if (n_card % 10 < 5)
				sum = sum + (n_card % 10) * 2;
			else
				sum = sum + 2 * (n_card % 10) - 9;
		}
		else
			sum = sum + n_card % 10;
		i++;
		n_card /= 10;
	}
	if (sum % 10 == 0)
		return (1);
	return (0);
}

void	ft_print(int type, int valid)
{
	if (valid)
	{
		if (type == 1)
			printf("VISA\n");
		else if (type == 2)
			printf("AMEX\n");
		else if (type == 3)
			printf("MASTERCARD\n");
		else
			printf("INVALID\n");
	}
	else
		printf("INVALID\n");
}
