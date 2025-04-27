/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:04:23 by crios             #+#    #+#             */
/*   Updated: 2025/02/28 19:03:27 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_window(t_Scene *scene)
{
	if (scene->mlx.win)
		mlx_destroy_window(scene->mlx.mlx, scene->mlx.win);
	exit(0);
}

void	start_window(t_Scene *scene)
{
	scene->mlx.mlx = mlx_init();
	if (!scene->mlx.mlx)
	{
		fprintf(stderr, "Error: Failed to initialize MiniLibX\n");
		return ;
	}
	scene->mlx.win = mlx_new_window(scene->mlx.mlx, 1280, 720, "miniRT");
	if (!scene->mlx.win)
	{
		fprintf(stderr, "Error: Failed to create window\n");
		return ;
	}
	printf("Window created successfully!\n");
}
