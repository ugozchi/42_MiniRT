/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:37:27 by crios             #+#    #+#             */
/*   Updated: 2025/03/13 15:52:23 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vec3	apply_ambient_light(t_Vec3 object_color, t_AmbientLight ambient)
{
	t_Vec3	result;

	result.x = object_color.x * (ambient.ratio * ambient.color.x);
	result.y = object_color.y * (ambient.ratio * ambient.color.y);
	result.z = object_color.z * (ambient.ratio * ambient.color.z);
	result.x = fmax(0.0, fmin(1.0, result.x));
	result.y = fmax(0.0, fmin(1.0, result.y));
	result.z = fmax(0.0, fmin(1.0, result.z));
	return (result);
}
