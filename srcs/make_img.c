/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:46:14 by hthomas           #+#    #+#             */
/*   Updated: 2022/01/26 09:33:22 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_put_pixel(unsigned char *data, const t_couple pixel, const int color, const t_couple resolution)
{
	int	(*tab)[resolution.w][1]; // prepare the cast

	tab = (void *)data; // cast for change 1 dimension array to 2 dimensions
	*tab[pixel.h][pixel.w] = color; // set the pixel at the coord x,y with the color value
}

/**
 * cree un ray depuis la posision de la camera qui passe par le pixel demandé en prenant en compre la resolution de l'image et l'angle de vision de la camera
 **/
t_ray	generate_ray(const t_camera *camera, const t_couple resolution, t_couple pixel)
{
	t_vect vect_dir;
	vect_dir = set_vect_dir_cam(camera, resolution, pixel.h, pixel.w);
	//printf("position:\t(% .3f,\t% .3f,\t% .3f)\n",\
											(camera->pos.x,\
											(camera->pos.y,\
											(camera->pos.z);
	//printf("direction:%s\t(% .3f,\t% .3f,\t % .3f)\n\n",\
											i  == resolution.h / 2 \
											&& pixel.w == resolution.w / 2 ? "\tmiddle\n\n" : "",\
											vect_dir.x,\
											vect_dir.y,\
											vect_dir.z);
	return (new_ray(camera->pos, vect_dir));
}

/**
 * trouve l'objet le plus proche dans la direction du ray
 **/
t_impact	*closest_object(const t_ray ray, const t_scene *scene, void **object)
{
	t_impact	*impact;

	if(!(impact = malloc(sizeof(*impact))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	impact->dist = INFINITY;
	//for each object in the scene
	ray_spheres(ray, scene, impact, object);
	ray_planes(ray, scene, impact, object);
	//ray_squares(ray, scene, impact, object);
	ray_cylinders(ray, scene, impact, object);
	ray_triangles(ray, scene, impact, object);
	return (impact);
}

/**
 * set la color en fonction des lumieres, de la normale du point d'impact et des eventuels obstacles
 * @param color	real color
 **/
t_rgb	*manage_light(const t_scene *scene, t_impact *impact, t_rgb *color, t_couple	pixel)
{
	t_list		*lights;
	t_light		*light;
	t_ray		to_light;
	void		*obstacle;
	t_impact	*impact_obstacle;
	t_rgb		diffuse;
	t_rgb		specular;

	diffuse = *int_to_rgb(0, 0, 0);
	lights = scene->lights;
	while (lights->next)
	{
		obstacle = NULL;
		light = (t_light*)(lights->content);
		to_light = new_ray(impact->pos, sub_vect(light->pos, impact->pos));
		//printf("\t\t");
		impact_obstacle = closest_object(to_light, scene, &obstacle);
		if (pixel.w == 680 && pixel.h == 5)
		{
			// printf("shade %.2f\t\t%.2f %.2f %.2f\t\t%.2f %.2f %.2f\t\t%.2f %.2f %.2f\n", impact_obstacle->dist, impact_obstacle->pos.x, impact_obstacle->pos.y, impact_obstacle->pos.z, impact_obstacle->normal.x, impact_obstacle->normal.y, impact_obstacle->normal.z, impact->normal.x, impact->normal.y, impact->normal.z);
			//printf("\n%.2f\t%.2f\n", impact_obstacle->dist, distance(impact->pos, light->pos));
		}
		if (pixel.w == 699 && pixel.h == 5)
		{
			// printf("lumin %.2f\t\t%.2f %.2f %.2f\t\t%.2f %.2f %.2f\t\t%.2f %.2f %.2f\n", impact_obstacle->dist, impact_obstacle->pos.x, impact_obstacle->pos.y, impact_obstacle->pos.z, impact_obstacle->normal.x, impact_obstacle->normal.y, impact_obstacle->normal.z, impact->normal.x, impact->normal.y, impact->normal.z);
			//printf("\n%.2f\t%.2f\n", impact_obstacle->dist, distance(impact->pos, light->pos));
		}
		if (impact_obstacle->dist > distance(impact->pos, light->pos) )
		{
			double normal_dot_light = ft_max_float(dot_product(impact->normal, to_light.dir), 0.0) / (distance(impact->pos, light->pos) * (distance(impact->pos, light->pos)));
			t_rgb color_l = *mult_rgb_double(light->color, normal_dot_light);
			diffuse = *add_rgb_rgb(diffuse, color_l);
			//add_vect(to_light.dir, multi_vect(impact->normal, -2. * normal_dot_light));
		}
		lights = lights->next;
	}
	diffuse = *mult_rgb_double(diffuse, ALBEDO);
	*color = *mult_rgb_rgb(*add_rgb_rgb(scene->al.color, diffuse), *color);
	// *color = *int_to_rgb((fabsf(impact->normal.z)) * 255, (fabsf(impact->normal.x)) * 255, (fabsf(impact->normal.y)) * 255); // color en gradient en fonction de la normale a la surface
	// *color = *int_to_rgb((fabsf(impact->pos.z)) * 255, (fabsf(impact->pos.x)) * 255, (fabsf(impact->pos.y)) * 255); // color en gradient en fonction de la position a la surface
	// *color = *int_to_rgb((fabsf(to_light.pos.z)) * 2, (fabsf(to_light.pos.x)) * 2, (fabsf(to_light.pos.y)) * 2); // color en gradient en fonction de la position de la source lumineuse
	min_rgb(color);
	return (NULL);
}

void	make_img(unsigned char *data, const t_scene *scene, const t_camera *camera, const t_couple start)
{
	t_couple	pixel;
	t_ray		ray;
	double		reflec;
	int			depth;
	t_rgb		*color; // real color
	void		*object;
	t_impact	*impact;

	pixel.h = start.h - 1;
	while (++pixel.h < scene->resolution.h)
	{
		pixel.w = start.w - 1;
		while (++pixel.w < scene->resolution.w)
		{
			color = int_to_rgb(0, 0, 0);
			reflec = REFLEC;
			depth = DEPTH;
			object = NULL; // peut etre a deplacer dans le while suivant ou a supprimer
			impact = NULL; // peut etre a deplacer dans le while suivant
			while (depth-- && reflec > EPSILON)
			{
				//printf("\nw%dh%d", pixel.w, pixel.h);
				ray = generate_ray(camera, scene->resolution, pixel);
				impact = closest_object(ray, scene, &object);
				if (object)
				{
					*color = get_color(scene->type, object);
					if (dot_product(impact->normal, ray.dir) >= 0)
						impact->normal = minus_vect(impact->normal);
					manage_light(scene, impact, color, pixel);
				}
				//Final color = Final color + computed color * previous reflection factor;
				//reflec = reflec * ((t_sphere*)object)->reflec;
			}
			ft_put_pixel(data, pixel, rgb_to_int(*color), scene->resolution);
			free(color);
		}
	}
}



/*
Procedure RenderPicture()
  For each pixel on the screen,
	Generate a ray R from the viewing position through the point on the view
	  plane corresponding to this pixel.
	Call the procedure RayTrace() with the arguments R and 0
	Plot the pixel in the colour value returned by RayTrace()
  Next pixel
End Procedure
Procedure RayTrace(ray R, integer Depth) returns colour
  Set the numerical variable Dis to a maximum value
  Set the object pointer Obj to null
  For each object in the scene
	Calculate the distance (from the starting point of R) of the nearest
	  intersection of R with the object in the forward direction
	If this distance is less than Dis
	  Update Dis to this distance
	  Set Obj to point to this object
	End if
  Next object
  If Obj is not null
	Set the position variable Pt to the nearest intersection point of R and Obj
	Set the total colour C to black
	For each light source in the scene
	  For each object in the scene
		If this object blocks the light coming from the light source to Pt
		  Attenuate the intensity of the received light by the transmittivity
			of the object
		End if
	  Next object
	  Calculate the perceived colour of Obj at Pt due to this light source
		using the value of the attenuated light intensity
	  Add this colour value to C
	Next light source
	If Depth is less than a maximum value
	  Generate two rays Refl and Refr in the reflected and refracted directions,
		starting from Pt
	  Call RayTrace with arguments Refl and Depth + 1
	  Add (the return value * reflectivity of Obj) to C
	  Call RayTrace with arguments Refr and Depth + 1
	  Add (the return value * transmittivity of Obj) to C
	End if
  Else
	Set the total colour C to the background colour
  End if
  Return C
End Procedure
*/
