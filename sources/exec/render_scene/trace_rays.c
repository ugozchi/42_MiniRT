/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:02:30 by crios             #+#    #+#             */
/*   Updated: 2025/03/14 12:31:20 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vec3	apply_lighting(t_Scene *scene, t_Intersection *intersection)
{
	t_Vec3	color;
	t_Vec3	diffuse;
	int		i;

	color = apply_ambient_light(intersection->color, scene->ambient);
	i = 0;
	while (i < scene->light_count)
	{
		if (!is_in_shadow(scene, intersection->intersection_point,
				scene->lights[i]))
		{
			diffuse = apply_diffuse_light(intersection->color, scene->lights[i],
					intersection->intersection_point, intersection->normal);
			color = add_vectors(color, diffuse);
		}
		i++;
	}
	return (color);
}

t_Vec3	trace_ray(t_Ray ray, t_Scene *scene)
{
	t_Intersection	intersection;

	intersection.closest_t = INFINITY;
	intersection.color = (t_Vec3){0, 0, 0};
	check_sphere_intersection(ray, scene, &intersection);
	check_plane_intersection(ray, scene, &intersection);
	check_cylinder_intersection(ray, scene, &intersection);
	if (intersection.closest_t == INFINITY)
		return ((t_Vec3){0, 0, 0});
	return (apply_lighting(scene, &intersection));
}
