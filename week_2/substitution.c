#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>

int		ft_isallalpha(char *text);
void	ft_substitute(char *text, char *key);
void	ft_convert_key(char *key);

int	main(int argc, char *argv[])
{
	char	*text;

	if (argc != 2)
	{
		printf("Usage: ./substitution key\n");
		return (1);
	}
	if (strlen(argv[1]) != 26 || !ft_isallalpha(argv[1]))
	{
		printf("Key must contain 26 alphabetic characters.\n");
		return (1);
	}
	text = get_string("plaintext:  ");
	ft_substitute(text, argv[1]);
	printf("cyphertext: %s\n", text);
	return (0);
}

int	ft_isallalpha(char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (!isalpha(text[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_substitute(char *text, char *key)
{
	int	i;

	ft_convert_key(key);
	i = 0;
	while (text[i])
	{
		if (isupper(text[i]))
			text[i] = 65 + key[text[i] - 65];
		else if (islower(text[i]))
			text[i] = 97 + key[text[i] - 97];
		i++;
	}
}

void	ft_convert_key(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		key[i] = tolower(key[i]) - 97;
		i++;
	}
}
