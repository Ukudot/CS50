#include <stdio.h>

void	draw(int height);

int	main(void)
{
	int	height;

	printf("Height: ");
	scanf("%d", &height);
	if (height > 0 && height < 9)
		draw(height);
	return (0);
}

void	draw(int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < height)
		{
			if (j >= height -1 - i)
				printf("#");
			else
				printf(" ");
			j++;
		}
		printf("\n");
		i++;
	}
}
