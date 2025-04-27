/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:36:39 by crios             #+#    #+#             */
/*   Updated: 2025/03/13 16:43:27 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_in_shadow(t_Scene *scene, t_Vec3 intersection_point, t_Light light)
{
	t_Ray	shadow_ray;
	double	max_dist;

	shadow_ray.origin = intersection_point;
	shadow_ray.direction = normalize(vector_sub(light.position,
				intersection_point));
	shadow_ray.origin = add_vectors(shadow_ray.origin,
			scalar_mult(shadow_ray.direction, 1e-2));
	max_dist = vector_length(vector_sub(light.position, intersection_point));
	if (intersect_ray_with_objects(shadow_ray, scene, max_dist))
		return (1);
	return (0);
}

t_Vec3	apply_diffuse_light(t_Vec3 object_color, t_Light light,
		t_Vec3 intersection_point, t_Vec3 normal)
{
	t_Vec3	light_dir;
	double	diff;
	t_Vec3	diffuse_color;

	light_dir = normalize(vector_sub(light.position, intersection_point));
	diff = fmax(dot(normal, light_dir), 0.0);
	diffuse_color.x = object_color.x * diff * light.intensity * light.color.x;
	diffuse_color.y = object_color.y * diff * light.intensity * light.color.y;
	diffuse_color.z = object_color.z * diff * light.intensity * light.color.z;
	return (diffuse_color);
}
