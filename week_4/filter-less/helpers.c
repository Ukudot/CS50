#include "helpers.h"

#include <stdio.h>
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
	int	i;
	int	j;
	float	sepia_r;
	float	sepia_g;
	float	sepia_b;
	float	org_r;
	float	org_g;
	float	org_b;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			org_r = image[i][j].rgbtRed;
			org_g = image[i][j].rgbtGreen;
			org_b = image[i][j].rgbtBlue;
			sepia_r = .393 * org_r + .769 * org_g + .189 * org_b;
			sepia_g = .349 * org_r + .686 * org_g + .168 * org_b;
			sepia_b = .272 * org_r + .534 * org_g + .131 * org_b;
			if (sepia_r > 255.0)
				sepia_r = 255;
			if (sepia_g > 255.0)
				sepia_g = 255;
			if (sepia_b > 255.0)
				sepia_b = 255;
			image[i][j].rgbtRed = sepia_r;
			image[i][j].rgbtGreen = sepia_g;
			image[i][j].rgbtBlue = sepia_b;
			j++;
		}
		i++;
	}
	return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	int		i;
	int		j;
	RGBTRIPLE	tmp;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width / 2)
		{
			tmp = image[i][j];
			image[i][j] = image[i][width - 1 - j];
			image[i][width - 1 - j] = tmp;
			j++;
		}
		i++;
	}
	return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		count;
	int		blue;
	int		green;
	int		red;
	RGBTRIPLE	image_tmp[height][width];

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			y = i - `;
			if (y < 0)
				y = 0;
			blue = 0;
			green = 0;
			red = 0;
			count = 0;
			while (y <= i + 1)
			{
				if (y == height)
					break;
				x = j - 1;
				if (x < 0)
					x = 0;
				while (x <= j + 1)
				{
					if (x == width)
						break;
					blue += image[y][x].rgbtBlue;
					green += image[y][x].rgbtGreen;
					red += image[y][x].rgbtRed;
					x++;
					count++;
				}
				y++;
			}
			image_tmp[i][j].rgbtBlue = blue / count;
			image_tmp[i][j].rgbtGreen = green / count;
			image_tmp[i][j].rgbtRed = red / count;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			image[i][j].rgbtBlue = image_tmp[i][j].rgbtBlue;
			image[i][j].rgbtGreen = image_tmp[i][j].rgbtGreen;
			image[i][j].rgbtRed = image_tmp[i][j].rgbtRed;
			j++;
		}
		i++;
	}
	return;
}
