/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:28:33 by crios             #+#    #+#             */
/*   Updated: 2025/03/14 13:05:58 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vec3	normalize(t_Vec3 v)
{
	double	length;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length == 0)
		return ((t_Vec3){0, 0, 0});
	return ((t_Vec3){v.x / length, v.y / length, v.z / length});
}

t_Vec3	scalar_mult(t_Vec3 v, double scalar)
{
	return ((t_Vec3){v.x * scalar, v.y * scalar, v.z * scalar});
}

t_Vec3	cross(t_Vec3 v1, t_Vec3 v2)
{
	return ((t_Vec3){v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x
		* v2.y - v1.y * v2.x});
}

double	dot(t_Vec3 v1, t_Vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
