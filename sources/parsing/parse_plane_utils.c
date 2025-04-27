/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:45:10 by crios             #+#    #+#             */
/*   Updated: 2025/04/16 19:34:12 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_vector3(char **token, t_Vec3 *vector, const char *vector_name)
{
	*token = ft_strtok(NULL, ",");
	if (!*token)
	{
		printf("Error: Missing %s (x)\n", vector_name);
		return (0);
	}
	vector->x = ft_strtod(*token, NULL);
	*token = ft_strtok(NULL, ",");
	if (!*token)
	{
		printf("Error: Missing %s (y)\n", vector_name);
		return (0);
	}
	vector->y = ft_strtod(*token, NULL);
	*token = ft_strtok(NULL, " ");
	if (!*token)
	{
		printf("Error: Missing %s (z)\n", vector_name);
		return (0);
	}
	vector->z = ft_strtod(*token, NULL);
	return (1);
}
