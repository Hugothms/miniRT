/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:46:14 by hthomas           #+#    #+#             */
/*   Updated: 2020/02/17 15:09:12 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void        	ft_put_pixel(unsigned char *data, t_couple pixel, int color, int win_width)
{
	int	(*tab)[win_width][1]; // prepare the cast

	tab = (void *)data; // cast for change 1 dimension array to 2 dimensions
	*tab[pixel.h][pixel.w] = color; // set the pixel at the coord x,y with the color value
}

/***
 * cree un ray depuis la posision de la camera qui passe par le pixel demandé
 * en prenant en compre la resolution de l'image et l'angle de vision de la camera
 ***/
t_ray generate_ray(const t_list *cameras, const t_couple resolution, t_couple pixel)
{
	t_vect vect_dir;

	//Ray = { starting point, direction };
	vect_dir = set_vect_dir_cam(((t_camera *)cameras->content), resolution, pixel.h, pixel.w);
	//printf("position:\t(% .3f,\t% .3f,\t% .3f)\n",\
											((t_camera*)cameras->content)->pos.x,\
											((t_camera*)cameras->content)->pos.y,\
											((t_camera*)cameras->content)->pos.z);
	//printf("direction:%s\t(% .3f,\t% .3f,\t % .3f)\n\n",\
											i  == resolution.h / 2 \
											&& pixel.w == resolution.w / 2 ? "\tmiddle\n\n" : "",\
											vect_dir.x,\
											vect_dir.y,\
											vect_dir.z);
	return (new_ray(((t_camera *)(cameras))->pos, vect_dir));
}

/***
 * trouve l'objet le plus proche dans la direction du ray
 ***/
t_impact	*closest_object(const t_ray ray, const t_scene *scene, void **object)
{
	t_impact	*impact;

	//for each object in the scene
	if(!(impact = malloc(sizeof(*impact))))
		print_err_and_exit("Malloc failed", MALLOC_ERROR);
	impact->dist = INFINITY;
	//printf("%p\n", object);
	ray_spheres(ray, scene, impact, object);
	//printf("%p\n", object);
	// ray_planes(ray, scene, impact, object);
	// ray_squares(ray, scene, impact, object);
	// ray_cyinders(ray, scene, impact, object);
	// ray_triangles(ray, scene, impact, object);
	//printf("ok\n");
	if (*object)
		return (impact);
	//printf("nothing\n");
	return (NULL);
}
int		manage_light(const t_scene *scene, void *object, t_impact *impact)
{
	t_list		*lights;
	t_light		*light;
	int			color;
	t_ray		to_light;
	t_impact	*closest;

	lights = scene->lights;
	while (lights->next)
	{
		//if the light is not in shadow of another object
		light = (t_light*)(lights->content);
		to_light = new_ray(impact->pos, add_vect(impact->pos, minus_vect(light->pos)));
		closest = closest_object(to_light, scene, &object);
		if (object && closest->dist > distance(impact->pos, light->pos))
		{
			//add this light contribution to computed color;
			return (rgb_to_int(((t_sphere*)object)->color));
		}
		//printf("%d,%d\n", pixel.w, pixel.h);
		lights = lights->next;
	}
	return (0);
}

void		print_img(const t_mlx *mlx,  t_img *img,const t_scene *scene)
{
	t_couple	pixel;
	int			color;
	t_ray		ray;
	void		*object;
	float		reflection_factor;
	int			depth;
	t_impact	*impact;

	pixel.h = -1;
	while (++pixel.h < scene->resolution.h)
	{
		pixel.w = -1;
		while (++pixel.w < scene->resolution.w)
		{
			color = rgb_to_int(int_to_rgb(0, 0, 0));
			reflection_factor = 1;
			depth = 1;
			object = NULL; // peut etre a deplacer dans le while suivant
			impact = NULL; // idem
			while (depth-- && reflection_factor > 1e-6)
			{
				ray = generate_ray(scene->cameras, scene->resolution, pixel);
				impact = closest_object(ray, scene, &object);
				//get_obj(scene->type, object);
				if (impact)
				{
					color = manage_light(scene, object, impact);
					//color = rgb_to_int(((t_sphere*)object)->color);
				}
				//Final color = Final color + computed color * previous reflection factor;
				//reflection factor = reflection factor * surface reflection property;
			}
			ft_put_pixel(img->data, pixel, color, scene->resolution.w);
		}
	}
}



































/*
		// compute primary ray direction
		Ray primRay;
		computePrimRay(i, j, &primRay);
		// shoot prim ray in the scene and search for intersection
		Point pHit;
		Normal nHit;
		float minDist = INFINITY;
		Object object = NULL;
		for (int k = 0; k < objects.size(); ++k)
		{
			if (Intersect(objects[k], primRay, &pHit, &nHit))
			{
				float distance = Distance(eyePosition, pHit);
				if (distance < minDistance)
				{
					object = objects[k];
					minDistance = distance; // update min distance
				}
			}
		}
		if (object != NULL)
		{
			// compute illumination
			Ray shadowRay;
			shadowRay.direction = lightPosition - pHit;
			bool isShadow = false;
			for (int k = 0; k < objects.size(); ++k)
			{
				if (Intersect(objects[k], shadowRay))
				{
					isInShadow = true;
					break;
				}
			}
		}
		if (!isInShadow)
			pixels[i][j] = object->color * light.brightness;
		else
			pixels[i][j] = 0;
*/



/*
for each pixel do
	compute viewing ray
	set pixel color to background color
	if (ray hits an object with t ∈ [0,∞)) then
		Compute n
		Evaluate lighting equation and set pixel to that color

Here the statement “if ray hits an object...” can be implemented as a function that tests for hits in the interval t ∈ [t0, t1]:
	hit = false
	for each object o do
		if (object is hit at ray parameter t and t ∈ [t0, t1]) then
			hit = true
			hitobject = o
			t1 = t
	return hit
*/




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
