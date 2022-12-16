#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	int	i;
	int	j;
	BYTE	grey_scale;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			grey_scale = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
			image[i][j].rgbtBlue = grey_scale;
			image[i][j].rgbtGreen = grey_scale;
			image[i][j].rgbtRed = grey_scale;
			j++;
		}
		i++;
	}
	return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
