/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambiant_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:22:59 by crios             #+#    #+#             */
/*   Updated: 2025/04/28 20:08:44 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (count != 3 || ft_strcmp(tokens[0], "A") != 0 || !parse_double(tokens[1],
			&ratio) || !parse_color(tokens[2], &rgb[0], &rgb[1], &rgb[2])
		|| !check_ratio(ratio) || !check_color(rgb[0], rgb[1], rgb[2]))
	{
		printf("Error: Invalid ambient light format\n");
		free_tokens(tokens);
		return ;
	}
	scene->ambient.ratio = ratio;
	scene->ambient.color = (t_Vec3){rgb[0] / 255.0, rgb[1] / 255.0, rgb[2]
		/ 255.0};
	free_tokens(tokens);
}
