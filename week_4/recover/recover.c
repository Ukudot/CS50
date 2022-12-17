#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int	isJPEG(unsigned char *block);
void	ft_putnbr(char *str, int nbr);

int main(int argc, char *argv[])
{
	int		i;
	int		name;
	char		s_name[] = "000.jpg";
	FILE 		*inptr;
	FILE		*outptr;
	unsigned char	*block;

	if (argc != 2)
	{
		printf("usage: ./recover forensic.raw\n");
		return (1);
	}
	inptr = fopen(argv[1], "r");
	if (!inptr)
	{
		printf("Error: cannot open %s\n", argv[1]);
		return (1);
	}
	block = (unsigned char *) calloc(BLOCK_SIZE, sizeof(unsigned char));
	if (!block)
	{
		printf("Error: memory error\n");
		return (1);
	}
	i = 0;
	name = 0;
	while (fread(block, sizeof(unsigned char), BLOCK_SIZE, inptr) == BLOCK_SIZE)
	{
		if (isJPEG(block) && i == 0)
		{
			outptr = fopen(s_name, "w");
			if (!outptr)
			{
				printf("Error: cannot open %s\n", s_name);
				fclose(inptr);
				free(block);
				return (1);
			}
			i++;
			name++;
		}
		else if (isJPEG(block))
		{
			fclose(outptr);
			ft_putnbr(s_name, name);
			outptr = fopen(s_name, "w");
			if (!outptr)
			{
				printf("Error: cannot open %s\n", s_name);
				fclose(inptr);
				free(block);
				return (1);
			}
			name++;
		}
		if (i != 0 && fwrite(block, sizeof(unsigned char), BLOCK_SIZE, outptr) != BLOCK_SIZE)
		{
			printf("Error: cannot write in %s", s_name);
			fclose(outptr);
			fclose(inptr);
			free(block);
			return (1);
		}
	}
	free(block);
	fclose(inptr);
	fclose(outptr);
}

int	isJPEG(unsigned char *block)
{
	if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff)
	{
		if (block[3] >= 0xe0 && block[3] <= 0xef)
			return (1);
	}
	return (0);
}
void	ft_putnbr(char *str, int nbr)
{
	int	i;

	i = 2;
	while (nbr >= 10)
	{
		str[i] = nbr % 10 + 48;
		nbr /= 10;
		i--;
	}
	str[i] = nbr + 48;
}
