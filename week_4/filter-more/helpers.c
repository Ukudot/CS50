#include "helpers.h"

#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	int	grey;
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			grey = 0;
			grey += image[i][j].rgbtBlue;
			grey += image[i][j].rgbtGreen;
			grey += image[i][j].rgbtRed;
			grey /= 3;
			image[i][j].rgbtBlue = grey;
			image[i][j].rgbtGreen = grey;
			image[i][j].rgbtRed = grey;
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
			image[i][j] = image[i][width - j - 1];
			image[i][width - j - 1] = tmp;
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
	int		r;
	int		g;
	int		b;
	int		count;
	RGBTRIPLE	tmp_image[height][width];

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			count = 0;
			r = 0;
			g = 0;
			b = 0;
			y = i - 1;
			if (y < 0)
				y = 0;
			while (y <= i + 1 && y < height)
			{
				x = j - 1;
				if (x < 0)
					x = 0;
				while (x <= j + 1 && x < width)
				{
					r +=  image[y][x].rgbtRed;
					g += image[y][x].rgbtGreen;
					b += image[y][x].rgbtBlue;
					x++;
					count++;
				}
				y++;
			}
			r /= count;
			g /= count;
			b /= count;
			tmp_image[i][j].rgbtRed = r;
			tmp_image[i][j].rgbtGreen = g;
			tmp_image[i][j].rgbtBlue = b;
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
			image[i][j].rgbtRed = tmp_image[i][j].rgbtRed;
			image[i][j].rgbtGreen = tmp_image[i][j].rgbtGreen;
			image[i][j].rgbtBlue = tmp_image[i][j].rgbtBlue;
			j++;
		}
		i++;
	}
	return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		k;
	int		gx[3][3];
	int		gy[3][3];
	int		xcolors[3];
	int		ycolors[3];
	int		f_colors[3];
	RGBTRIPLE	tmp_image[height][width];

	// initialize gx
	gx[0][0] = -1;
	gx[0][1] = 0;
	gx[0][2] = 1;
	gx[1][0] = -2;
	gx[1][1] = 0;
	gx[1][2] = 2;
	gx[2][0] = -1;
	gx[2][1] = 0;
	gx[2][2] = 1;
	// initialize gy
	gy[0][0] = -1;
	gy[0][1] = -2;
	gy[0][2] = -1;
	gy[1][0] = 0;
	gy[1][1] = 0;
	gy[1][2] = 0;
	gy[2][0] = 1;
	gy[2][1] = 2;
	gy[2][2] = 1;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			k = 0;
			while (k < 3)
			{
				xcolors[k] = 0;
				ycolors[k] = 0;
				k++;
			}
			y = i - 1;
			if (y < 0)
				y = 0;
			while (y <= i + 1 && y < height)
			{
				x = j - 1;
				if (x < 0)
					x = 0;
				while (x <= j + 1 && x < width)
				{
					xcolors[0] += gx[y - i + 1][x - j + 1] * image[y][x].rgbtBlue;
					xcolors[1] += gx[y - i + 1][x - j + 1] * image[y][x].rgbtGreen;
					xcolors[2] += gx[y - i + 1][x - j + 1] * image[y][x].rgbtRed;

					ycolors[0] += gy[y - i + 1][x - j + 1] * image[y][x].rgbtBlue;
					ycolors[1] += gy[y - i + 1][x - j + 1] * image[y][x].rgbtGreen;
					ycolors[2] += gy[y - i + 1][x - j + 1] * image[y][x].rgbtRed;
					x++;
				}
				y++;
			}
			f_colors[0] = (int) sqrt(xcolors[0] * xcolors[0] + ycolors[0] * ycolors[0]);
			if (f_colors[0] > 255)
				f_colors[0] = 255;
			f_colors[1] = (int) sqrt(xcolors[1] * xcolors[1] + ycolors[1] * ycolors[1]);
			if (f_colors[1] > 255)
				f_colors[1] = 255;
			f_colors[2] = (int) sqrt(xcolors[2] * xcolors[2] + ycolors[2] * ycolors[2]);
			if (f_colors[2] > 255)
				f_colors[2] = 255;
			tmp_image[i][j].rgbtBlue = f_colors[0];
			tmp_image[i][j].rgbtGreen = f_colors[1];
			tmp_image[i][j].rgbtRed = f_colors[2];
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
			image[i][j].rgbtBlue = 255 - tmp_image[i][j].rgbtBlue;
			image[i][j].rgbtGreen = 255 - tmp_image[i][j].rgbtGreen;
			image[i][j].rgbtRed = 255 - tmp_image[i][j].rgbtRed;
			j++;
		}
		i++;
	}
	return;
}
