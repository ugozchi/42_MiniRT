/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:31:00 by crios             #+#    #+#             */
/*   Updated: 2025/03/14 12:48:00 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	check_sphere_intersection(t_Ray ray, t_Scene *scene,
		t_Intersection *intersection)
{
	double		t;
	t_Sphere	*sphere;
	int			i;

	i = 0;
	while (i < scene->sphere_count)
	{
		sphere = &scene->spheres[i];
		t = intersect_ray_with_sphere(ray, sphere);
		if (t > 0 && t < intersection->closest_t)
		{
			intersection->closest_t = t;
			intersection->intersection_point = add_vectors(ray.origin,
					scalar_mult(ray.direction, t));
			intersection->normal = normalize(vector_sub(intersection
						->intersection_point, sphere->center));
			intersection->color = sphere->color;
		}
		i++;
	}
	return (intersection->closest_t);
}

double	check_plane_intersection(t_Ray ray, t_Scene *scene,
		t_Intersection *intersection)
{
	double	t;
	t_Plane	*plane;
	int		i;

	i = 0;
	while (i < scene->plane_count)
	{
		plane = &scene->planes[i];
		t = intersect_ray_with_plane(ray, plane);
		if (t > 0 && t < intersection->closest_t)
		{
			intersection->closest_t = t;
			intersection->intersection_point = add_vectors(ray.origin,
					scalar_mult(ray.direction, t));
			intersection->normal = plane->normal;
			intersection->color = plane->color;
		}
		i++;
	}
	return (intersection->closest_t);
}

void	calculate_cylinder_body(t_Ray ray, t_Cylinder *cylinder, double t_cyl,
		t_Intersection *intersection)
{
	double	projection;
	t_Vec3	cp;
	t_Vec3	point_on_axis;

	intersection->intersection_point = add_vectors(ray.origin,
			scalar_mult(ray.direction, t_cyl));
	cp = vector_sub(intersection->intersection_point, cylinder->position);
	projection = dot(cp, cylinder->axis);
	point_on_axis = add_vectors(cylinder->position, scalar_mult(cylinder->axis,
				projection));
	intersection->normal = normalize(vector_sub(intersection
				->intersection_point, point_on_axis));
}

void	handle_cylinder_caps(t_Cylinder *cylinder, t_Ray ray,
		t_Intersection *intersection)
{
	double	cap_distance;

	cap_distance = vector_length(vector_sub(intersection->intersection_point,
				cylinder->position));
	if (fabs(cap_distance - cylinder->height / 2.0) < 1e-6)
	{
		intersection->normal = cylinder->axis;
		if (dot(intersection->normal, ray.direction) > 0)
			intersection->normal = scalar_mult(intersection->normal, -1);
	}
}

double	check_cylinder_intersection(t_Ray ray, t_Scene *scene,
		t_Intersection *intersection)
{
	double		t_cyl;
	t_Cylinder	*cylinder;
	int			i;

	i = 0;
	while (i < scene->cylinder_count)
	{
		cylinder = &scene->cylinders[i];
		if (intersect_ray_with_cylinder(ray, cylinder, &t_cyl) && t_cyl > 0
			&& t_cyl < intersection->closest_t)
		{
			intersection->closest_t = t_cyl;
			calculate_cylinder_body(ray, cylinder, t_cyl, intersection);
			handle_cylinder_caps(cylinder, ray, intersection);
			intersection->color = cylinder->color;
		}
		i++;
	}
	return (intersection->closest_t);
}
