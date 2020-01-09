/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fscene.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:51:14 by hthomas           #+#    #+#             */
/*   Updated: 2020/01/09 09:59:03 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include"elements.h"

typedef struct		s_scene
{
	struct s_pixel			resolution;
	struct s_ambient_light	ambient_light;
	struct s_camera			*camera;
	struct s_light			*light;
	struct s_sphere			*sphere;
	struct s_plane			*plane;
	struct s_sqare			*sqare;
	struct s_cylinder		*cylinder;
	struct s_triangle		*triangle;
}					t_scene;

#endif
