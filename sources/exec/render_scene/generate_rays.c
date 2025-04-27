/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:02:49 by crios             #+#    #+#             */
/*   Updated: 2025/03/14 12:53:45 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Ray	generate_ray(int x, int y, t_Scene *scene)
{
	t_Camera	*cam;
	t_Vec3		forward;
	t_Vec3		right;
	t_Vec3		up;

	cam = &scene->camera;
	forward = normalize(cam->orientation);
	right = normalize(cross((t_Vec3){0, 1, 0}, forward));
	up = normalize(cross(forward, right));
	return ((t_Ray){cam->position,
		normalize(add_vectors(add_vectors(scalar_mult(right, (2.0 * (x + 0.5)
							/ scene->mlx.width - 1.0)
						* ((double)scene->mlx.width / scene->mlx.height)
						* tan(cam->fov * M_PI / 360.0)), scalar_mult(up, (1.0
							- 2.0 * (y + 0.5) / scene->mlx.height)
						* tan(cam->fov * M_PI / 360.0))), scalar_mult(forward,
					1.0)))});
}
