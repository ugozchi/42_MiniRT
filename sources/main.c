/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:00:59 by crios             #+#    #+#             */
/*   Updated: 2025/05/06 12:31:53 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 

static void	print_error(char *msg)
{
	ssize_t	ret;

	ret = write(2, msg, strlen(msg));
	(void)ret;
}

static void	parse_line(char *line, t_Scene *scene)
{
	if (line[0] == 'A')
		parse_ambient_light(line, scene);
	else if (line[0] == 'C')
		parse_camera(line, scene);
	else if (line[0] == 'L')
		parse_light(line, scene);
	else if (ft_strncmp(line, "sp", 2) == 0)
		parse_sphere(line, scene);
	else if (ft_strncmp(line, "pl", 2) == 0)
		parse_plane(line, scene);
	else if (ft_strncmp(line, "cy", 2) == 0)
		parse_cylinder(line, scene);
	else
		print_error("Warning: Unrecognized line format\n");
}

static void	process_line(char *line, int len, t_Scene *scene)
{
	if (len > 0)
	{
		line[len] = '\0';
		parse_line(line, scene);
	}
}

static void	read_scene(int fd, t_Scene *scene)
{
	char	buf;
	char	line[256];
	int		i;
	ssize_t	bytes_read;

	i = 0;
	bytes_read = read(fd, &buf, 1);
	while (bytes_read > 0)
	{
		if (buf == '\n' || i >= 255)
		{
			process_line(line, i, scene);
			i = 0;
		}
		else
			line[i++] = buf;
		bytes_read = read(fd, &buf, 1);
	}
	if (i > 0)
		process_line(line, i, scene);
}

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	t_Scene	scene;

// 	if (argc != 2)
// 	{
// 		print_error("Usage: ./miniRT <scene.rt>\n");
// 		return (1);
// 	}
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	init_scene(&scene);
// 	read_scene(fd, &scene);
// 	close(fd);
// 	start_window(&scene);
// 	mlx_key_hook(scene.mlx.win, key_hook, &scene);
// 	mlx_hook(scene.mlx.win, 17, 0, close_window, &scene);
// 	render_scene(&scene);
// 	mlx_loop(scene.mlx.mlx);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	int			fd;
	t_Scene		scene;

	if (argc != 2 || !ft_strrchr(argv[1], '.')
		|| ft_strcmp(ft_strrchr(argv[1], '.'), ".rt"))
	{
		print_error("Usage: ./miniRT <scene.rt>\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	init_scene(&scene);
	read_scene(fd, &scene);
	close(fd);
	start_window(&scene);
	mlx_key_hook(scene.mlx.win, key_hook, &scene);
	mlx_hook(scene.mlx.win, 17, 0, close_window, &scene);
	render_scene(&scene);
	mlx_loop(scene.mlx.mlx);
	return (0);
}
