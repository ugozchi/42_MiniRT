/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:26:19 by crios             #+#    #+#             */
/*   Updated: 2025/03/13 16:50:55 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	compute_quadratic_coefficients(t_Ray ray, t_Cylinder *cylinder,
		t_Intersection *intersection)
{
	t_Vec3	oc;
	t_Vec3	axis;

	oc = vector_sub(ray.origin, cylinder->position);
	axis = normalize(cylinder->axis);
	intersection->a = dot(ray.direction, ray.direction) - pow(dot(ray.direction,
				axis), 2);
	intersection->b = 2 * (dot(ray.direction, oc) - dot(ray.direction, axis)
			* dot(oc, axis));
	intersection->c = dot(oc, oc) - pow(dot(oc, axis), 2) - (cylinder->diameter
			/ 2.0) * (cylinder->diameter / 2.0);
}

int	solve_quadratic(t_Intersection *intersection)
{
	double	discriminant;
	double	sqrt_discriminant;

	discriminant = intersection->b * intersection->b - 4 * intersection->a
		* intersection->c;
	if (discriminant < 0)
		return (0);
	sqrt_discriminant = sqrt(discriminant);
	intersection->t0 = (-intersection->b - sqrt_discriminant) / (2
			* intersection->a);
	intersection->t1 = (-intersection->b + sqrt_discriminant) / (2
			* intersection->a);
	return (1);
}

int	check_height_within_bounds(t_Ray ray, double t0, double t1,
		t_Cylinder *cylinder)
{
	t_Vec3	axis;
	double	height0;
	double	height1;

	axis = normalize(cylinder->axis);
	height0 = dot(vector_sub((t_Vec3){ray.origin.x + t0 * ray.direction.x,
				ray.origin.y + t0 * ray.direction.y, ray.origin.z + t0
				* ray.direction.z}, cylinder->position), axis);
	height1 = dot(vector_sub((t_Vec3){ray.origin.x + t1 * ray.direction.x,
				ray.origin.y + t1 * ray.direction.y, ray.origin.z + t1
				* ray.direction.z}, cylinder->position), axis);
	if (height0 < 0 || height0 > cylinder->height)
		t0 = -1;
	if (height1 < 0 || height1 > cylinder->height)
		t1 = -1;
	if (t0 < 0 && t1 < 0)
		return (0);
	return (1);
}

int	find_closest_intersection(double t0, double t1, double *t)
{
	if (t0 >= 0 && (t0 < t1 || t1 < 0))
		*t = t0;
	else
		*t = t1;
	return (1);
}

int	intersect_ray_with_cylinder(t_Ray ray, t_Cylinder *cylinder, double *t)
{
	t_Intersection	intersection;

	compute_quadratic_coefficients(ray, cylinder, &intersection);
	if (!solve_quadratic(&intersection))
		return (0);
	if (!check_height_within_bounds(ray, intersection.t0, intersection.t1,
			cylinder))
		return (0);
	return (find_closest_intersection(intersection.t0, intersection.t1, t));
}
