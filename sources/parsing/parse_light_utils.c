/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:33:44 by crios             #+#    #+#             */
/*   Updated: 2025/04/28 20:09:33 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_light_identifier(char **token)
{
	if (!*token || ft_strcmp(*token, "L") != 0)
	{
		printf("Error: Invalid light format (missing 'L' identifier)\n");
		return (0);
	}
	return (1);
}

int	add_light_to_scene(t_Scene *scene, t_Light *new_light)
{
	t_Light	*new_lights;

	new_lights = realloc(scene->lights, sizeof(t_Light) * (scene->light_count
				+ 1));
	if (!new_lights)
	{
		printf("Error: Memory allocation failed\n");
		return (0);
	}
	scene->lights = new_lights;
	scene->lights[scene->light_count] = *new_light;
	scene->light_count++;
	return (1);
}

int	parse_color_component(char **token, double *component,
		const char *component_name)
{
	*token = ft_strtok(NULL, ",");
	if (!*token)
	{
		printf("Error: Missing light color (%s)\n", component_name);
		return (0);
	}
	*component = ft_strtol(*token, NULL, 10) / 255.0;
	if (*component < 0.0 || *component > 1.0)
	{
		printf("Error: Light %s value must be in range [0, 255]\n",
			component_name);
		return (0);
	}
	return (1);
}
