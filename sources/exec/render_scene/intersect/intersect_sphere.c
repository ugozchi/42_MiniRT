/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:27:43 by crios             #+#    #+#             */
/*   Updated: 2025/03/13 16:54:37 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	intersect_ray_with_sphere(t_Ray ray, t_Sphere *sphere)
{
	t_Vec3			oc;
	t_Intersection	intersection;
	double			a;
	double			b;
	double			c;

	oc = vector_sub(ray.origin, sphere->center);
	a = dot(ray.direction, ray.direction);
	b = 2.0 * dot(oc, ray.direction);
	c = dot(oc, oc) - (sphere->radius * sphere->radius);
	intersection.discriminant = b * b - 4 * a * c;
	if (intersection.discriminant < 0)
		return (-1);
	intersection.discriminant = sqrt(intersection.discriminant);
	intersection.t0 = (-b - intersection.discriminant) / (2.0 * a);
	intersection.t1 = (-b + intersection.discriminant) / (2.0 * a);
	if (intersection.t0 > 0)
		return (intersection.t0);
	else if (intersection.t1 > 0)
		return (intersection.t1);
	else
		return (-1);
}
