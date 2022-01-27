/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_triangles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:16:38 by hthomas           #+#    #+#             */
/*   Updated: 2022/01/27 11:40:28 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// bool	intersect_triangle(const t_ray ray, const t_triangle triangle, t_impact *impact)
// {
// 	(void)impact;
// 	t_vect v0v1 = sub_vect(triangle.v1, triangle.v0);
// 	t_vect v0v2 = sub_vect(triangle.v2, triangle.v0);
// 	t_vect pvec = cross_product(ray.dir, v0v2);
// 	double det = dot_product(v0v1, pvec);
// 	if (fabs(det) < EPSILON)
// 		return 0;
// 	double invDet = 1 / det;

// 	t_vect tvec = sub_vect(ray.pos, triangle.v0);
// 	double u = dot_product(tvec, pvec) * invDet;
// 	if (u < 0 || u > 1)
// 		return 0;

// 	t_vect qvec = cross_product(tvec, v0v1);
// 	double v = dot_product(ray.dir, qvec) * invDet;
// 	if (v < 0 || u + v > 1)
// 		return 0;

// 	double t = dot_product(v0v2, qvec) * invDet;
// 	(void)t;
// 	return 1;
// 	/*
// 	// compute plane's normal
// 	Vec3f v0v1 = v1 - v0;
// 	Vec3f v0v2 = v2 - v0;
// 	// no need to normalize
// 	Vec3f N = cross_product(v0v1, v0v2); // N
// 	double denom = dot_product(N, N);

// 	// Step 1: finding P

// 	// check if ray and plane are parallel ?
// 	double NdotRayray.Direction = dot_product(N, ray.dir);
// 	if (fabs(NdotRayray.Direction) < EPSILON) // almost 0
// 		return false; // they are parallel so they don't intersect !

// 	// compute d parameter using equation 2
// 	double d = dot_product(N, v0);

// 	// compute t (equation 3)
// 	t = (dot_product(N, ray.pos) + d) / NdotRayray.Direction;
// 	// check if the triangle is in behind the ray
// 	if (t < 0) return false; // the triangle is behind

// 	// compute the intersection point using equation 1
// 	Vec3f P = ray.pos + t * ray.dir;

// 	// Step 2: inside-outside test
// 	Vec3f C; // vector perpendicular to triangle's plane

// 	// edge 0
// 	Vec3f edge0 = v1 - v0;
// 	Vec3f vp0 = P - v0;
// 	C = cross_product(edge0, vp0);
// 	if (dot_product(N, C) < 0) return false; // P is on the right side

// 	// edge 1
// 	Vec3f edge1 = v2 - v1;
// 	Vec3f vp1 = P - v1;
// 	C = cross_product(edge1, vp1);
// 	if ((u = dot_product(N, C)) < 0)  return false; // P is on the right side

// 	// edge 2
// 	Vec3f edge2 = v0 - v2;
// 	Vec3f vp2 = P - v2;
// 	C = cross_product(edge2, vp2);
// 	if ((v = dot_product(N, C)) < 0) return false; // P is on the right side;

// 	u /= denom;
// 	v /= denom;

// 	return true; // this ray hits the triangle

// }




// bool	intersect_triangle(const t_ray ray, const t_triangle triangle, t_impact *impact)
// {
// 	t_vect v0v1;
// 	t_vect v0v2;
// 	t_vect pvec;
// 	t_vect tvec;
// 	t_vect qvec;
// 	float det;
// 	float inv_det;
// 	float u;
// 	float v;
// 	float t;

// 	v0v1 = sub_vect(triangle.v1, triangle.v0);
// 	v0v2 = sub_vect(triangle.v2, triangle.v0);
// 	pvec = cross_product(ray.dir, v0v2);
// 	det = dot_product(v0v1, pvec);
// 	if (det < EPSILON)
// 		return (false);
// 	inv_det = 1.0 / det;
// 	tvec = sub_vect(ray.pos, triangle.v0);
// 	u = dot_product(tvec, pvec) * inv_det;
// 	if (u < 0.0 || u > 1.0)
// 		return (false);
// 	qvec = cross_product(tvec, v0v1);
// 	v = dot_product(ray.dir, qvec) * inv_det;
// 	if (v < 0.0 || u + v > 1.0)
// 		return (false);
// 	t = dot_product(v0v2, qvec) * inv_det;
// 	if (t > EPSILON)
// 	{
// 		impact->dist = t;
// 		impact->pos = add_vect(ray.pos, multi_vect(ray.dir, t));
// 		impact->normal = normalize(cross_product(v0v1, v0v2));
// 		return (true);
// 	}
// 	return (false);
// }








// #define TEST_CULL

bool	intersect_triangle(const t_ray ray, const t_triangle triangle, t_impact *impact)
{
	t_vect v0 = triangle.v0;
	t_vect v1 = triangle.v1;
	t_vect v2 = triangle.v2;
	t_vect e1,e2,pvec,qvec,tvec;

	e1 = sub_vect(v1,v0);
	e2 = sub_vect(v2,v0);

	pvec = cross_product(ray.dir,e2);

	normalize(ray.dir); //todo commented
	// NORMALIZE(pvec);
	float det = dot_product(pvec,e1);
	#ifdef TEST_CULL
		if (det < EPSILON)
		{
		   return false;
		}
		tvec = sub_vect(ray.pos,v0);
		float u = dot_product(tvec,pvec);
		if (u < 0.0 || u > det)
		{
		   return false;
		}
		qvec = cross_product(tvec,e1);
		float v = dot_product(ray.dir,qvec);
		if (v < 0.0f || v + u > det)
		{
		   return false;
		}
	#else
		if (det < EPSILON && det > -EPSILON )
		{
		    return false;
		}
		float invDet = 1.0f / det;
		tvec = sub_vect(ray.pos,v0);
		// NORMALIZE(tvec);
		float u = invDet * dot_product(tvec,pvec);
		if (u <0.0f || u > 1.0f)
		{
			return false;
		}
		qvec = cross_product(tvec,e1);
		// NORMALIZE(qvec);
		float v = invDet* dot_product(qvec,ray.dir);
		if (v < 0.0f || u+v > 1.0f)
		{
			return false;
		}
	#endif
	impact->dist = 40;//dot_product(e2,qvec);
	impact->pos = add_vect(ray.pos, multi_vect(ray.dir, impact->dist));
	impact->normal = normalize(cross_product(e1,e2));
	return true;
}




void	ray_triangles(const t_ray ray, const t_scene *scene, t_impact *impact, void **object)
{
	t_list		*triangles;
	t_triangle	*triangle;

	triangles = scene->triangles;
	while (triangles->next)
	{
		triangle = (t_triangle*)(triangles->content);
		if (intersect_triangle(ray, *triangle, impact))
		{
			*object = triangle;
			impact->type = "sq";
		}
		triangles = triangles->next;
	}
}
