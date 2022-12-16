#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <cs50.h>

void	ft_rotate(char *text, int key);

int	main(int argc, char *argv[])
{
	int		i;
	char	*text;

	if (argc != 2)
	{
		printf("Usage: ./caesar key\n");
		return (1);
	}
	i = 0;
	while (argv[1][i])
	{
		if (!isdigit(argv[1][i]))
		{
			printf("Usage: ./caesar key\n");
			return (1);
		}
		i++;
	}
	i = atoi(argv[1]);
	text = get_string("plaintext:  ");
	ft_rotate(text, i);
	printf("cyphertext: %s\n", text);
	return (0);
}

void	ft_rotate(char *text, int key)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (islower(text[i]))
			text[i] = (text[i] - 97 + key) % 26 + 97;
		else if (isupper(text[i]))
			text[i] = (text[i] - 65 + key) % 26 + 65;
		i++;
	}
}
