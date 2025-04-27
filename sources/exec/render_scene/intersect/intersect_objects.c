/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:42:46 by crios             #+#    #+#             */
/*   Updated: 2025/03/13 17:00:42 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_ray_with_planes_and_spheres(t_Ray ray, t_Scene *scene,
		double max_dist, double epsilon)
{
	double	t;
	int		i;

	i = 0;
	while (i < scene->plane_count)
	{
		t = intersect_ray_with_plane(ray, &scene->planes[i++]);
		if (t > epsilon && t < max_dist)
			return (1);
	}
	i = 0;
	while (i < scene->sphere_count)
	{
		t = intersect_ray_with_sphere(ray, &scene->spheres[i++]);
		if (t > epsilon && t < max_dist)
			return (1);
	}
	return (0);
}

int	intersect_ray_with_cylinders(t_Ray ray, t_Scene *scene, double max_dist,
		double epsilon)
{
	double	t_cyl;
	int		i;

	i = 0;
	while (i < scene->cylinder_count)
	{
		if (intersect_ray_with_cylinder(ray, &scene->cylinders[i++], &t_cyl)
			&& t_cyl > epsilon && t_cyl < max_dist)
			return (1);
	}
	return (0);
}

int	intersect_ray_with_objects(t_Ray ray, t_Scene *scene, double max_dist)
{
	double	epsilon;

	epsilon = 1e-6;
	if (intersect_ray_with_planes_and_spheres(ray, scene, max_dist, epsilon))
		return (1);
	if (intersect_ray_with_cylinders(ray, scene, max_dist, epsilon))
		return (1);
	return (0);
}
