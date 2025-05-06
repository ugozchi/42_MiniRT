/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:22:09 by crios             #+#    #+#             */
/*   Updated: 2025/04/28 20:09:52 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_plane_identifier(char **token)
{
	if (!*token || ft_strcmp(*token, "pl") != 0)
	{
		printf("Error: Invalid plane format (missing 'pl' identifier)\n");
		return (0);
	}
	return (1);
}

int	validate_color(t_Vec3 *color)
{
	if (color->x < 0.0 || color->x > 1.0 || color->y < 0.0 || color->y > 1.0
		|| color->z < 0.0 || color->z > 1.0)
	{
		printf("Error: Color values must be in range [0, 255]\n");
		return (0);
	}
	return (1);
}

int	parse_plane_color(char **token, t_Vec3 *color)
{
	if (!parse_color_component(token, &color->x, "red"))
		return (0);
	if (!parse_color_component(token, &color->y, "green"))
		return (0);
	*token = ft_strtok(NULL, "\n");
	if (!*token)
	{
		printf("Error: Missing color (blue)\n");
		return (0);
	}
	color->z = ft_strtol(*token, NULL, 10) / 255.0;
	if (!validate_color(color))
		return (0);
	return (1);
}

int	add_plane_to_scene(t_Scene *scene, t_Plane *new_plane)
{
	t_Plane	*new_planes;

	new_planes = realloc(scene->planes, sizeof(t_Plane) * (scene->plane_count
				+ 1));
	if (!new_planes)
	{
		printf("Error: Memory allocation failed\n");
		return (0);
	}
	scene->planes = new_planes;
	scene->planes[scene->plane_count] = *new_plane;
	scene->plane_count++;
	return (1);
}

void	parse_plane(char *line, t_Scene *scene)
{
	t_Plane	new_plane;
	char	*token;

	token = ft_strtok(line, " ");
	if (!parse_plane_identifier(&token))
		return ;
	if (!parse_vector3(&token, &new_plane.center, "plane position"))
		return ;
	if (!parse_vector3(&token, &new_plane.normal, "plane normal"))
		return ;
	if (!parse_plane_color(&token, &new_plane.color))
		return ;
	if (!add_plane_to_scene(scene, &new_plane))
		return ;
}
