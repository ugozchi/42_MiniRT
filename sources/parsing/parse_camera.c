/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:23:34 by crios             #+#    #+#             */
/*   Updated: 2025/04/28 20:09:09 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minirt.h"

// void	parse_camera(char *line, t_Scene *scene)
// {
// 	char	**tokens;
// 	char	**pos_tokens;
// 	char	**orient_tokens;
// 	int		token_count;

// 	tokens = ft_split_whitespace(line);
// 	if (!tokens)
// 	{
// 		printf("Error: Memory allocation failed\n");
// 		return ;
// 	}
// 	token_count = count_tokens(tokens);
// 	if (token_count != 4 || strcmp(tokens[0], "C") != 0)
// 	{
// 		printf("Error: Invalid camera format.
//					Expected: C x,y,z dx,dy,dz fov\n");
// 		free_tokens(tokens);
// 		return ;
// 	}
// 	pos_tokens = ft_split(tokens[1], ',');
// 	if (count_tokens(pos_tokens) != 3 || !parse_double(pos_tokens[0],
// 			&scene->camera.position.x) || !parse_double(pos_tokens[1],
// 			&scene->camera.position.y) || !parse_double(pos_tokens[2],
// 			&scene->camera.position.z))
// 	{
// 		printf("Error: Invalid camera position format\n");
// 		free_tokens(tokens);
// 		free_tokens(pos_tokens);
// 		return ;
// 	}
// 	orient_tokens = ft_split(tokens[2], ',');
// 	if (count_tokens(orient_tokens) != 3 || !parse_double(orient_tokens[0],
// 			&scene->camera.orientation.x) || !parse_double(orient_tokens[1],
// 			&scene->camera.orientation.y) || !parse_double(orient_tokens[2],
// 			&scene->camera.orientation.z))
// 	{
// 		printf("Error: Invalid camera orientation format\n");
// 		free_tokens(tokens);
// 		free_tokens(pos_tokens);
// 		free_tokens(orient_tokens);
// 		return ;
// 	}
// 	double length = sqrt(scene->camera.orientation.x
// 			* scene->camera.orientation.x + scene->camera.orientation.y
// 			* scene->camera.orientation.y + scene->camera.orientation.z
// 			* scene->camera.orientation.z);
// 	if (fabs(length - 1.0) > 0.0001)
// 	{
// 		printf("Error: Camera orientation must be a normalized vector\n");
// 		free_tokens(tokens);
// 		free_tokens(pos_tokens);
// 		free_tokens(orient_tokens);
// 		return ;
// 	}
// 	if (!parse_double(tokens[3], &scene->camera.fov) || scene->camera.fov < 0
// 		|| scene->camera.fov > 180)
// 	{
// 		printf("Error: Camera FOV must be between 0 and 180 degrees\n");
// 		free_tokens(tokens);
// 		free_tokens(pos_tokens);
// 		free_tokens(orient_tokens);
// 		return ;
// 	}
// 	free_tokens(tokens);
// 	free_tokens(pos_tokens);
// 	free_tokens(orient_tokens);
// }

#include "minirt.h"

static int	parse_position(char *token, t_Vec3 *position)
{
	char	**pos_tokens;
	int		success;

	pos_tokens = ft_split(token, ',');
	if (count_tokens(pos_tokens) != 3)
		return (free_tokens(pos_tokens), 0);
	success = parse_double(pos_tokens[0], &position->x);
	if (success)
		success = parse_double(pos_tokens[1], &position->y);
	if (success)
		success = parse_double(pos_tokens[2], &position->z);
	free_tokens(pos_tokens);
	return (success);
}

static int	parse_orientation(char *token, t_Vec3 *orientation)
{
	char	**orient_tokens;
	double	length;
	int		success;

	orient_tokens = ft_split(token, ',');
	if (count_tokens(orient_tokens) != 3)
		return (free_tokens(orient_tokens), 0);
	success = parse_double(orient_tokens[0], &orientation->x);
	if (success)
		success = parse_double(orient_tokens[1], &orientation->y);
	if (success)
		success = parse_double(orient_tokens[2], &orientation->z);
	if (success)
	{
		length = sqrt(orientation->x * orientation->x + orientation->y
				* orientation->y + orientation->z * orientation->z);
		if (fabs(length - 1.0) > 0.0001)
			success = 0;
	}
	free_tokens(orient_tokens);
	return (success);
}

void	parse_camera(char *line, t_Scene *scene)
{
	char	**tokens;
	double	fov;

	tokens = ft_split_whitespace(line);
	if (!tokens)
		return ((void)printf("Error: Memory allocation failed\n"));
	if (count_tokens(tokens) != 4 || ft_strcmp(tokens[0], "C") != 0
		|| !parse_position(tokens[1], &scene->camera.position)
		|| !parse_orientation(tokens[2], &scene->camera.orientation)
		|| !parse_double(tokens[3], &fov) || fov < 0.0 || fov > 180.0)
	{
		printf("Error: Invalid camera format\n");
		free_tokens(tokens);
		return ;
	}
	scene->camera.fov = fov;
	free_tokens(tokens);
}
