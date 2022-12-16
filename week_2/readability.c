#include <stdio.h>
#include <ctype.h>
#include <cs50.h>

int		counter_letters(char *text);
int		counter_words(char *text);
int		counter_sentences(char *text);
float	coleman_liau_index(int letters, int words, int sentences);

int	main(void)
{
	char	*text;
	int		letters;
	int		words;
	int		sentences;
	float	index;

	text = get_string("Text: ");
	letters = counter_letters(text);
	words = counter_words(text);
	sentences = counter_sentences(text);
	index = coleman_liau_index(letters, words, sentences);
	if (index < 1)
		printf("Before Grade 1\n");
	else if (index > 15)
		printf("Grade 16+\n");
	else
		printf("Grade %.0f\n", index);
	return (0);
}

int	counter_letters(char *text)
{
	int	letters;
	int	i;

	i = 0;
	letters = 0;
	while (text[i])
	{
		if (isalpha(text[i]))
			letters++;
		i++;
	}
	return (letters);
}

int	counter_words(char *text)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (text[i])
	{
		if (text[i] != ' ')
		{
			words++;
			while (text[i] != ' ' && text[i])
				i++;
		}
		if (text[i])
			i++;
	}
	return (words);
}

int	counter_sentences(char *text)
{
	int	sentences;
	int	i;

	sentences = 0;
	i = 0;
	while (text[i])
	{
		if (text[i] == '.' || text[i] == '?' || text[i] == '!')
			sentences++;
		i++;
	}
	return (sentences);
}

float	coleman_liau_index(int letters, int words, int sentences)
{
	float	l;
	float	s;
	float	index;

	l = letters * 100.0 / words;
	s = sentences * 100.0 / words;
	index = 0.0588 * l - 0.296 * s - 15.8;
	return (index);
}
