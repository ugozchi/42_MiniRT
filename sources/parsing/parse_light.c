/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:22:39 by crios             #+#    #+#             */
/*   Updated: 2025/04/16 19:34:04 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_light_position(char **token, t_Vec3 *position)
{
	*token = ft_strtok(NULL, ",");
	if (!*token)
	{
		printf("Error: Missing light position (x)\n");
		return (0);
	}
	position->x = ft_strtod(*token, NULL);
	*token = ft_strtok(NULL, ",");
	if (!*token)
	{
		printf("Error: Missing light position (y)\n");
		return (0);
	}
	position->y = ft_strtod(*token, NULL);
	*token = ft_strtok(NULL, " ");
	if (!*token)
	{
		printf("Error: Missing light position (z)\n");
		return (0);
	}
	position->z = ft_strtod(*token, NULL);
	return (1);
}

int	parse_light_intensity(char **token, double *intensity)
{
	*token = ft_strtok(NULL, " ");
	if (!*token)
	{
		printf("Error: Missing light intensity\n");
		return (0);
	}
	*intensity = ft_strtod(*token, NULL);
	if (*intensity < 0.0 || *intensity > 1.0)
	{
		printf("Error: Light intensity must be in range [0.0, 1.0]\n");
		return (0);
	}
	return (1);
}

int	parse_light_color(char **token, t_Vec3 *color)
{
	if (!parse_color_component(token, &color->x, "red"))
		return (0);
	if (!parse_color_component(token, &color->y, "green"))
		return (0);
	*token = ft_strtok(NULL, "\n");
	if (!*token)
	{
		printf("Error: Missing light color (blue)\n");
		return (0);
	}
	color->z = ft_strtol(*token, NULL, 10) / 255.0;
	if (color->z < 0.0 || color->z > 1.0)
	{
		printf("Error: Light blue value must be in range [0, 255]\n");
		return (0);
	}
	return (1);
}

void	parse_light(char *line, t_Scene *scene)
{
	t_Light	new_light;
	char	*token;

	token = ft_strtok(line, " ");
	if (!parse_light_identifier(&token))
		return ;
	if (!parse_light_position(&token, &new_light.position))
		return ;
	if (!parse_light_intensity(&token, &new_light.intensity))
		return ;
	if (!parse_light_color(&token, &new_light.color))
		return ;
	if (!add_light_to_scene(scene, &new_light))
		return ;
}
