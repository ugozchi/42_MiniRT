/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:05:16 by crios             #+#    #+#             */
/*   Updated: 2025/03/14 13:06:02 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vec3	add_vectors(t_Vec3 v1, t_Vec3 v2)
{
	return ((t_Vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_Vec3	vector_sub(t_Vec3 v1, t_Vec3 v2)
{
	return ((t_Vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

double	vector_length(t_Vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
