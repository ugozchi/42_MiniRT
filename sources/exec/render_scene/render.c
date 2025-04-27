/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:42:22 by crios             #+#    #+#             */
/*   Updated: 2025/03/14 13:01:07 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	clamp_and_convert_color(t_Vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(color.x * 255);
	g = (int)(color.y * 255);
	b = (int)(color.z * 255);
	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);
}

void	set_default_color(t_Vec3 *color)
{
	if (color->x == 0 && color->y == 0 && color->z == 0)
	{
		color->x = 0.2;
		color->y = 0.2;
		color->z = 0.2;
	}
}

void	set_pixel_color(t_Scene *scene, int x, int y, t_Vec3 color)
{
	int	color_value;

	set_default_color(&color);
	color_value = clamp_and_convert_color(color);
	mlx_pixel_put(scene->mlx.mlx, scene->mlx.win, x, y, color_value);
}

void	render_scene(t_Scene *scene)
{
	t_Ray	ray;
	t_Vec3	color;
	int		x;
	int		y;

	scene->mlx.img = mlx_new_image(scene->mlx.mlx, scene->mlx.width,
			scene->mlx.height);
	scene->mlx.addr = mlx_get_data_addr(scene->mlx.img,
			&scene->mlx.bits_per_pixel, &scene->mlx.line_length,
			&scene->mlx.endian);
	y = 0;
	while (y < scene->mlx.height)
	{
		x = 0;
		while (x < scene->mlx.width)
		{
			ray = generate_ray(x, y, scene);
			color = trace_ray(ray, scene);
			set_pixel_color(scene, x, y, color);
			x++;
		}
		y++;
	}
}
