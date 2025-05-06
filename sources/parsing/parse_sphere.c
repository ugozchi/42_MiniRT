/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:21:19 by crios             #+#    #+#             */
/*   Updated: 2025/04/28 20:10:17 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minirt.h"

// void	parse_sphere(char *line, t_Scene *scene)
// {
// 	t_Sphere	new_sphere;
// 	t_Sphere	*new_spheres;
// 	char		**tokens;
// 	char		**pos_tokens;

// 	int r, g, b;
// 	tokens = ft_split_whitespace(line);
// 	if (!tokens)
// 	{
// 		printf("Error: Memory allocation failed\n");
// 		return ;
// 	}
// 	// Check basic format: should be "sp", position, diameter, color
// 	if (count_tokens(tokens) != 4 || strcmp(tokens[0], "sp") != 0)
// 	{
// 		printf("Error: Invalid sphere format.
//				Expected: sp x,y,z diameter r,g,b\n");
// 		free_tokens(tokens);
// 		return ;
// 	}
// 	// Parse position (x,y,z)
// 	pos_tokens = ft_split(tokens[1], ',');
// 	if (count_tokens(pos_tokens) != 3 || !parse_double(pos_tokens[0],
// 			&new_sphere.center.x) || !parse_double(pos_tokens[1],
// 			&new_sphere.center.y) || !parse_double(pos_tokens[2],
// 			&new_sphere.center.z))
// 	{
// 		printf("Error: Invalid sphere position format\n");
// 		free_tokens(tokens);
// 		free_tokens(pos_tokens);
// 		return ;
// 	}
// 	// Parse diameter
// 	if (!parse_double(tokens[2], &new_sphere.radius) || new_sphere.radius <= 0)
// 	{
// 		printf("Error: Invalid sphere diameter\n");
// 		free_tokens(tokens);
// 		free_tokens(pos_tokens);
// 		return ;
// 	}
// 	new_sphere.radius /= 2.0; // Convert diameter to radius
// 	// Parse color (r,g,b)
// 	if (!parse_color(tokens[3], &r, &g, &b))
// 	{
// 		printf("Error: Invalid sphere color format\n");
// 		free_tokens(tokens);
// 		free_tokens(pos_tokens);
// 		return ;
// 	}
// 	new_sphere.color.x = (double)r / 255.0;
// 	new_sphere.color.y = (double)g / 255.0;
// 	new_sphere.color.z = (double)b / 255.0;
// 	// Add sphere to scene
// 	new_spheres = realloc(scene->spheres, sizeof(t_Sphere)
// 			* (scene->sphere_count + 1));
// 	if (!new_spheres)
// 	{
// 		printf("Error: Memory allocation failed\n");
// 		free_tokens(tokens);
// 		free_tokens(pos_tokens);
// 		return ;
// 	}
// 	scene->spheres = new_spheres;
// 	scene->spheres[scene->sphere_count] = new_sphere;
// 	scene->sphere_count++;
// 	// Clean up
// 	free_tokens(tokens);
// 	free_tokens(pos_tokens);
// }

#include "minirt.h"

static int	parse_sphere_position(char *str, t_Vec3 *center)
{
	char	**tokens;
	int		success;

	tokens = ft_split(str, ',');
	if (count_tokens(tokens) != 3)
		return (free_tokens(tokens), 0);
	success = parse_double(tokens[0], &center->x);
	if (success)
		success = parse_double(tokens[1], &center->y);
	if (success)
		success = parse_double(tokens[2], &center->z);
	free_tokens(tokens);
	return (success);
}

static int	parse_sphere_color(char *str, t_Vec3 *color)
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

static int	fill_sphere_data(char **tokens, t_Sphere *sphere)
{
	if (count_tokens(tokens) != 4 || ft_strcmp(tokens[0], "sp") != 0)
		return (0);
	if (!parse_sphere_position(tokens[1], &sphere->center)
		|| !parse_double(tokens[2], &sphere->radius) || sphere->radius <= 0
		|| !parse_sphere_color(tokens[3], &sphere->color))
		return (0);
	sphere->radius /= 2.0;
	return (1);
}

static int	add_sphere_to_scene(t_Scene *scene, t_Sphere *sphere)
{
	t_Sphere	*new_spheres;

	new_spheres = realloc(scene->spheres, sizeof(t_Sphere)
			* (scene->sphere_count + 1));
	if (!new_spheres)
		return (0);
	scene->spheres = new_spheres;
	scene->spheres[scene->sphere_count] = *sphere;
	scene->sphere_count++;
	return (1);
}

void	parse_sphere(char *line, t_Scene *scene)
{
	t_Sphere	new_sphere;
	char		**tokens;

	tokens = ft_split_whitespace(line);
	if (!tokens)
		return ((void)printf("Error: Memory allocation failed\n"));
	if (!fill_sphere_data(tokens, &new_sphere))
	{
		printf("Error: Invalid sphere format\n");
		free_tokens(tokens);
		return ;
	}
	if (!add_sphere_to_scene(scene, &new_sphere))
		printf("Error: Memory allocation failed\n");
	free_tokens(tokens);
}
