/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambiant_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:22:59 by crios             #+#    #+#             */
/*   Updated: 2025/04/26 16:57:44 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minirt.h"

// void	parse_ambient_light(char *line, t_Scene *scene)
// {
// 	char	**tokens;
// 	int		count;
// 	double	ratio;

// 	int r, g, b;
// 	tokens = ft_split_whitespace(line);
// 	if (!tokens)
// 	{
// 		printf("Error: Memory allocation failed\n");
// 		return ;
// 	}
// 	count = 0;
// 	while (tokens[count])
// 		count++;
// 	if (count != 3 || strcmp(tokens[0], "A") != 0)
// 	{
// 		printf("Error: Invalid ambient light format\n");
// 		free_tokens(tokens);
// 		return ;
// 	}
// 	if (!parse_double(tokens[1], &ratio))
// 	{
// 		printf("Error: Invalid ambient ratio format\n");
// 		free_tokens(tokens);
// 		return ;
// 	}
// 	if (!parse_color(tokens[2], &r, &g, &b))
// 	{
// 		printf("Error: Invalid ambient color format\n");
// 		free_tokens(tokens);
// 		return ;
// 	}
// 	if (ratio < 0.0 || ratio > 1.0)
// 	{
// 		printf("Error: Ambient ratio must be in [0.0, 1.0]\n");
// 		free_tokens(tokens);
// 		return ;
// 	}
// 	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
// 	{
// 		printf("Error: Ambient RGB values must be in [0, 255]\n");
// 		free_tokens(tokens);
// 		return ;
// 	}
// 	scene->ambient.ratio = ratio;
// 	scene->ambient.color = (t_Vec3){r / 255.0, g / 255.0, b / 255.0};
// 	free_tokens(tokens);
// }

#include "minirt.h"

static int	check_ratio(double ratio)
{
	if (ratio < 0.0 || ratio > 1.0)
	{
		printf("Error: Ambient ratio must be in [0.0, 1.0]\n");
		return (0);
	}
	return (1);
}

static int	check_color(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error: Ambient RGB values must be in [0, 255]\n");
		return (0);
	}
	return (1);
}

void	parse_ambient_light(char *line, t_Scene *scene)
{
	char	**tokens;
	int		rgb[3];
	int		count;
	double	ratio;

	tokens = ft_split_whitespace(line);
	if (!tokens)
		return ((void)printf("Error: Memory allocation failed\n"));
	count = 0;
	while (tokens[count])
		count++;
	if (count != 3 || strcmp(tokens[0], "A") != 0
		|| !parse_double(tokens[1], &ratio)
		|| !parse_color(tokens[2], &rgb[0], &rgb[1], &rgb[2])
		|| !check_ratio(ratio)
		|| !check_color(rgb[0], rgb[1], rgb[2]))
	{
		printf("Error: Invalid ambient light format\n");
		free_tokens(tokens);
		return ;
	}
	scene->ambient.ratio = ratio;
	scene->ambient.color = (t_Vec3){rgb[0] / 255.0, rgb[1] / 255.0,
		rgb[2] / 255.0};
	free_tokens(tokens);
}
