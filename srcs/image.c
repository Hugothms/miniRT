/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:43:06 by hthomas           #+#    #+#             */
/*   Updated: 2020/02/03 17:56:36 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void        	ft_put_pixel(char *data, t_couple pixel, int color, int win_width)
{
	int (*tab)[win_width][1]; // prepare the cast

	tab = (void *)data; // cast for change 1 dimension array to 2 dimensions
	*tab[pixel.w][pixel.h] = color; // set the pixel at the coord x,y with the color value
}

unsigned char	*file_header_bmp(int filesize)
{
	unsigned char	*bmpfileheader;

	if(!(bmpfileheader = malloc(14 * sizeof(unsigned char))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	ft_memcpy(bmpfileheader, (char[]){'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0}, 14);
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);
	return (bmpfileheader);
}

unsigned char	*info_header_bmp(t_couple resolution)
{
		unsigned char	*bmpinfoheader;

	if(!(bmpinfoheader = malloc(40 * sizeof(unsigned char))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
		ft_memcpy(bmpinfoheader, (char[]){40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0}, 40);
	bmpinfoheader[4] = (unsigned char)(resolution.w);
	bmpinfoheader[5] = (unsigned char)(resolution.w >> 8);
	bmpinfoheader[6] = (unsigned char)(resolution.w >> 16);
	bmpinfoheader[7] = (unsigned char)(resolution.w >> 24);
	bmpinfoheader[8] = (unsigned char)(resolution.h);
	bmpinfoheader[9] = (unsigned char)(resolution.h >> 8);
	bmpinfoheader[10] = (unsigned char)(resolution.h >> 16);
	bmpinfoheader[11] = (unsigned char)(resolution.h >> 24);
	return (bmpinfoheader);
}

void			write_pixels(int f, const unsigned char *pixels, t_couple resolution, unsigned char bmppad[])
{
	int i;
	int filesize;

	i = 0;
	filesize = 54 + 3 * resolution.w * resolution.h;
	while(i < resolution.h)
	{
		write(f, pixels + (resolution.w * (resolution.h - i - 1 ) * 3), resolution.w);
		write(f, bmppad, filesize - 54);
		i++;
	}
}

void			save_img(const char *filename, const unsigned char *pixels, t_couple resolution)
{
	unsigned char	bmppad[3];
	int				filesize;
	int				f;
	unsigned char	*bmpfileheader;
	unsigned char	*bmpinfoheader;

	ft_memcpy(bmppad, (char[]){0,255,0}, 3);
	filesize = 54 + 3 * resolution.w * resolution.h;
	f = open(filename, O_WRONLY | O_APPEND | O_CREAT);
	bmpfileheader = file_header_bmp(filesize);
	write(f, bmpfileheader, 14);
	free(bmpfileheader);
	bmpinfoheader = info_header_bmp(resolution);
	write(f, bmpinfoheader, 40);
	free(bmpinfoheader);
	write_pixels(f, pixels, resolution, bmppad);
	close(f);
}
