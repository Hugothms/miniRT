/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:43:06 by hthomas           #+#    #+#             */
/*   Updated: 2020/03/12 17:47:33 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

unsigned char	*file_header_bmp(int filesize)
{
	unsigned char	*bmpfileheader;

	if(!(bmpfileheader = (unsigned char*) malloc(14 * sizeof(unsigned char))))
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

	if(!(bmpinfoheader = (unsigned char*) malloc(40 * sizeof(unsigned char))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	ft_memcpy(bmpinfoheader, (char[]){40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 32,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}, 40);
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

void			write_data(int f, const unsigned char *data, t_couple resolution, const int filesize)
{
	int 			line;

	line = resolution.h;
	while(--line + 1)
		write(f, data + resolution.w * line * 4, resolution.w * 4);
}

void			save_bmp(const char *filename, const unsigned char *data, const t_couple resolution)
{
	int				filesize;
	int				f;
	unsigned char	*bmpfileheader;
	unsigned char	*bmpinfoheader;

	filesize = 14 + 40 + 3 * resolution.w * resolution.h;
	f = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0755);
	bmpfileheader = file_header_bmp(filesize);
	write(f, bmpfileheader, 14);
	free(bmpfileheader);
	bmpinfoheader = info_header_bmp(resolution);
	write(f, bmpinfoheader, 40);
	free(bmpinfoheader);
	write_data(f, data, resolution, filesize);
	close(f);
}
