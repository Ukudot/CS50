#include <stdio.h>

void	draw(int height);
void	draw_left(int row, int height);
void	draw_right(int row, int height);

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

	i = 0;
	while (i < height)
	{
		draw_left(i, height);
		printf(" ");
		draw_right(i, height);
		printf("\n");
		i++;
	}
}

void	draw_left(int row, int height)
{
	int	j;

	j = 0;
	while (j < height)
	{
		if (j >= height - 1 - row)
			printf("#");
		else
			printf(" ");
		j++;
	}
}

void	draw_right(int row, int height)
{
	int	j;

	j = 0;
	while (j < height)
	{
		if (j <= row)
			printf("#");
		else
			printf(" ");
		j++;
	}
}
