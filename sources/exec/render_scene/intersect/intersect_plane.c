/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:28:03 by crios             #+#    #+#             */
/*   Updated: 2025/03/13 16:52:20 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	intersect_ray_with_plane(t_Ray ray, t_Plane *plane)
{
	double	denom;
	double	numerator;
	double	t;

	denom = dot(plane->normal, ray.direction);
	if (fabs(denom) < 1e-6)
		return (-1);
	numerator = dot(vector_sub(plane->center, ray.origin), plane->normal);
	t = numerator / denom;
	if (t >= 0)
		return (t);
	else
		return (-1);
}
