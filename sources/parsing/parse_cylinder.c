/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:20:39 by crios             #+#    #+#             */
/*   Updated: 2025/04/28 20:06:42 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_cylinder_position(char *str, t_Vec3 *position)
{
	char	**tokens;
	int		success;

	tokens = ft_split(str, ',');
	if (count_tokens(tokens) != 3)
		return (free_tokens(tokens), 0);
	success = parse_double(tokens[0], &position->x);
	if (success)
		success = parse_double(tokens[1], &position->y);
	if (success)
		success = parse_double(tokens[2], &position->z);
	free_tokens(tokens);
	return (success);
}

static int	parse_cylinder_axis(char *str, t_Vec3 *axis)
{
	char	**tokens;
	int		success;

	tokens = ft_split(str, ',');
	if (count_tokens(tokens) != 3)
		return (free_tokens(tokens), 0);
	success = parse_double(tokens[0], &axis->x);
	if (success)
		success = parse_double(tokens[1], &axis->y);
	if (success)
		success = parse_double(tokens[2], &axis->z);
	free_tokens(tokens);
	return (success);
}

static int	parse_cylinder_color(char *str, t_Vec3 *color)
{
	int	r;
	int	g;
	int	b;

	if (!parse_color(str, &r, &g, &b))
		return (0);
	color->x = (double)r / 255.0;
	color->y = (double)g / 255.0;
	color->z = (double)b / 255.0;
	return (1);
}

int	parse_cylinder_data(char *line, t_Cylinder *cylinder)
{
	char	**tokens;
	int		success;

	tokens = ft_split_whitespace(line);
	if (!tokens)
		return ((void)printf("Error: Memory allocation failed\n"), 0);
	success = (count_tokens(tokens) == 6 && ft_strcmp(tokens[0], "cy") == 0
			&& parse_cylinder_position(tokens[1], &cylinder->position)
			&& parse_cylinder_axis(tokens[2], &cylinder->axis)
			&& parse_double(tokens[3], &cylinder->diameter)
			&& cylinder->diameter > 0 && parse_double(tokens[4],
				&cylinder->height) && cylinder->height > 0
			&& parse_cylinder_color(tokens[5], &cylinder->color));
	if (!success)
		printf("Error: Invalid cylinder format\n");
	free_tokens(tokens);
	return (success);
}

void	parse_cylinder(char *line, t_Scene *scene)
{
	t_Cylinder	new_cylinder;

	if (!parse_cylinder_data(line, &new_cylinder))
		return ;
	add_cylinder_to_scene(scene, &new_cylinder);
}
