/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:20:39 by crios             #+#    #+#             */
/*   Updated: 2025/04/26 17:18:29 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minirt.h"

// int	parse_cylinder_data(char *line, t_Cylinder *cylinder)
// {
// 	char	**tokens;
// 	char	**pos_tokens;
// 	char	**axis_tokens;
// 	char	**color_tokens;
// 	int		token_count;

// 	tokens = ft_split_whitespace(line);
// 	if (!tokens)
// 	{
// 		printf("Error: Memory allocation failed\n");
// 		return (0);
// 	}
// 	token_count = count_tokens(tokens);
// 	if (token_count != 6 || ft_strcmp(tokens[0], "cy") != 0)
// 	{
// 		printf("Error: Invalid cylinder format. Expected:
//				cy x,y,z dx,dy,dz diameter height r,g,b\n");
// 		free_tokens(tokens);
// 		return (0);
// 	}
// 	// Parse position (x,y,z)
// 	pos_tokens = ft_split(tokens[1], ',');
// 	if (count_tokens(pos_tokens) != 3 || !parse_double(ft_strtrim(pos_tokens[0],
// 				" \t"), &cylinder->position.x)
// 		|| !parse_double(ft_strtrim(pos_tokens[1], " \t"),
// 			&cylinder->position.y) || !parse_double(ft_strtrim(pos_tokens[2],
// 				" \t"), &cylinder->position.z))
// 	{
// 		printf("Error: Invalid cylinder position format\n");
// 		free_tokens(tokens);
// 		free_tokens(pos_tokens);
// 		return (0);
// 	}
// 	// Parse axis (dx,dy,dz)
// 	axis_tokens = ft_split(tokens[2], ',');
// 	if (count_tokens(axis_tokens) != 3
// 		|| !parse_double(ft_strtrim(axis_tokens[0], " \t"), &cylinder->axis.x)
// 		|| !parse_double(ft_strtrim(axis_tokens[1], " \t"), &cylinder->axis.y)
// 		|| !parse_double(ft_strtrim(axis_tokens[2], " \t"), &cylinder->axis.z))
// 	{
// 		printf("Error: Invalid cylinder axis format\n");
// 		free_tokens(tokens);
// 		free_tokens(pos_tokens);
// 		free_tokens(axis_tokens);
// 		return (0);
// 	}
// 	// Parse diameter
// 	if (!parse_double(tokens[3], &cylinder->diameter)
// 		|| cylinder->diameter <= 0)
// 	{
// 		printf("Error: Invalid cylinder diameter\n");
// 		free_tokens(tokens);
// 		free_tokens(pos_tokens);
// 		free_tokens(axis_tokens);
// 		return (0);
// 	}
// 	// Parse height
// 	if (!parse_double(tokens[4], &cylinder->height) || cylinder->height <= 0)
// 	{
// 		printf("Error: Invalid cylinder height\n");
// 		free_tokens(tokens);
// 		free_tokens(pos_tokens);
// 		free_tokens(axis_tokens);
// 		return (0);
// 	}
// 	// Parse color (r,g,b)
// 	color_tokens = ft_split(tokens[5], ',');
// 	int r, g, b;
// 	if (!parse_color(tokens[5], &r, &g, &b))
// 	{
// 		printf("Error: Invalid cylinder color format\n");
// 		free_tokens(tokens);
// 		free_tokens(pos_tokens);
// 		free_tokens(axis_tokens);
// 		return (0);
// 	}
// 	// Convert and normalize color values to 0-1 range
// 	cylinder->color.x = (double)r / 255.0;
// 	cylinder->color.y = (double)g / 255.0;
// 	cylinder->color.z = (double)b / 255.0;
// 	// Clean up
// 	free_tokens(tokens);
// 	free_tokens(pos_tokens);
// 	free_tokens(axis_tokens);
// 	free_tokens(color_tokens);
// 	return (1);
// }

// void	add_cylinder_to_scene(t_Scene *scene, t_Cylinder *cylinder)
// {
// 	t_Cylinder	*new_cylinders;

// 	new_cylinders = realloc(scene->cylinders, sizeof(t_Cylinder)
// 			* (scene->cylinder_count + 1));
// 	if (!new_cylinders)
// 	{
// 		printf("Error: Memory allocation failed\n");
// 		return ;
// 	}
// 	scene->cylinders = new_cylinders;
// 	scene->cylinders[scene->cylinder_count] = *cylinder;
// 	scene->cylinder_count++;
// }

// void	parse_cylinder(char *line, t_Scene *scene)
// {
// 	t_Cylinder	new_cylinder;

// 	if (!parse_cylinder_data(line, &new_cylinder))
// 		return ;
// 	add_cylinder_to_scene(scene, &new_cylinder);
// }

#include "minirt.h"

static int	parse_cylinder_position(char *str, t_Vec3 *position)
{
	char	**tokens;
	int		success;

	tokens = ft_split(str, ',');
	if (count_tokens(tokens) != 3)
		return (free_tokens(tokens), 0);
	success = parse_double(tokens[0], &position->x)
		&& parse_double(tokens[1], &position->y)
		&& parse_double(tokens[2], &position->z);
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
	success = parse_double(tokens[0], &axis->x)
		&& parse_double(tokens[1], &axis->y)
		&& parse_double(tokens[2], &axis->z);
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
			&& cylinder->diameter > 0
			&& parse_double(tokens[4], &cylinder->height)
			&& cylinder->height > 0
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
