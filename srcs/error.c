/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 18:54:35 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/10 19:01:04 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	print_err_and_exit(char *str, int err)
{
	write(STDERR_FILENO, "Error: ", 7);
	while(*str)
		write(STDERR_FILENO, str++, 1);
	write(STDERR_FILENO, "\n", 1);
	exit(err);
}
