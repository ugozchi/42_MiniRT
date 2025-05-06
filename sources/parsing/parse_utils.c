/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:26:40 by crios             #+#    #+#             */
/*   Updated: 2025/04/28 20:10:28 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Free token array */
void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

/* Parse double value from string */
int	parse_double(char *str, double *value)
{
	char	*endptr;

	*value = ft_strtod(str, &endptr);
	return (*endptr == '\0');
}

/* Parse RGB color from string */
int	parse_color(char *str, int *r, int *g, int *b)
{
	char	*comma1;
	char	*comma2;
	char	*endptr;

	comma1 = ft_strchr(str, ',');
	if (!comma1)
		return (0);
	comma2 = ft_strchr(comma1 + 1, ',');
	if (!comma2)
		return (0);
	*comma1 = '\0';
	*comma2 = '\0';
	*r = ft_strtol(str, &endptr, 10);
	if (*endptr != '\0')
		return (0);
	*g = ft_strtol(comma1 + 1, &endptr, 10);
	if (*endptr != '\0')
		return (0);
	*b = ft_strtol(comma2 + 1, &endptr, 10);
	if (*endptr != '\0')
		return (0);
	return (1);
}

/* Count number of tokens */
int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	if (!tokens)
		return (0);
	while (tokens[count])
		count++;
	return (count);
}
