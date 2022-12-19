// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 27 * 27 * 27 * 27;

// Hash table
node *table[N];

// Protorypes
void	ft_cpword(char *dest, char *src);
void	ft_insert(char *word);
int	ft_toupper(const char c);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
	node	*current;

	current = table[hash(word)];
	while (current)
	{
		if (strcasecmp(current->word, word) == 0)
			return (true);
		current = current->next;
	}
	return (false);
}

// Hashes word to a number
unsigned int hash(const char *word)
{
	int	i;
	int	j;
	int	k;
	int	x;
	int	len;

	len = strlen(word);
	i = (ft_toupper(word[0]) - 'A') * 27 * 27 * 27;
	if (len == 1)
		return (i);
	j = (ft_toupper(word[1]) - 'A') * 27 * 27;
	if (len == 2)
		return (i + j);
	k = (ft_toupper(word[2]) - 'A') * 27;
	if (len == 3)
		return (i + j + k);
	x = (ft_toupper(word[3]) - 'A');
	return (i + j + k + x);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
	FILE	*dict;
	char	word[LENGTH + 1];
	char	c;
	int	index;

	dict = fopen(dictionary, "r");
	if (!dict)
		return (false);
	index = 0;
	while (fread(&c, sizeof(char), 1, dict))
	{
		if (c != '\n')
		{
			word[index] = c;
			index++;
		}
		else
		{
			word[index] = '\0';
			ft_insert(word);
			index = 0;
		}
	}
	fclose(dict);

	// Test per constrollare il dizionario
	/*
	node	*current;
	printf("Loaded dictionary:\n");
	while (index < N)
	{
		current = table[index];
		while (current)
		{
			printf("%s\n", current->word);
			current = current->next;
		}
		index++;
	}
	*/
	return (true);
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
	int	size;
	int	i;
	node	*current;

	i = 0;
	size = 0;
	while (i < N)
	{
		current = table[i];
		while (current)
		{
			size++;
			current = current->next;
		}
		i++;
	}
	return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
	int	i;
	node	*next;
	node	*current;

	i = 0;
	while (i < N)
	{
		current = table[i];
		while(current)
		{
			next = current->next;
			free(current);
			current = next;
		}
		i++;
	}
	return (true);
}

void	ft_insert(char *word)
{
	node		*cell;
	unsigned int	i;

	i = hash(word);
	if (!table[i])
	{
		table[i] = (node *) calloc(1, sizeof(node));
		ft_cpword(table[i]->word, word);
	}
	else
	{
	cell = table[i];
		while (cell->next)
			cell = cell->next;
		cell->next = (node *) calloc(1, sizeof(node));
		ft_cpword(cell->next->word, word);
	}
}

void	ft_cpword(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}

int	ft_toupper(const char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	if (c == '\'')
		return ('Z' + 1);
	return (c);
}
