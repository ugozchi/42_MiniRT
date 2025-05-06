/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:15:57 by uzanchi           #+#    #+#             */
/*   Updated: 2025/04/28 20:09:12 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_cylinder_to_scene(t_Scene *scene, t_Cylinder *cylinder)
{
	t_Cylinder	*new_cylinders;

	new_cylinders = realloc(scene->cylinders, sizeof(t_Cylinder)
			* (scene->cylinder_count + 1));
	if (!new_cylinders)
	{
		printf("Error: Memory allocation failed\n");
		return ;
	}
	scene->cylinders = new_cylinders;
	scene->cylinders[scene->cylinder_count] = *cylinder;
	scene->cylinder_count++;
}
