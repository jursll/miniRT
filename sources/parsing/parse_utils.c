/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:01:34 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 11:35:36 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

bool	parse_coordination(char *str, t_v3d *c)
{
	char	**parts;
	int		i;

	if (!validate_commas(str, ',', 2))
		return (false);
	parts = ft_split(str, ',');
	if (!parts)
		return (false);
	i = 0;
	while (i < 3)
	{
		if (!is_a_valid_float(parts[i]))
			return (free_arr(parts), false);
		if (i == 0)
			c->x = string_to_float(parts[i]);
		else if (i == 1)
			c->y = string_to_float(parts[i]);
		else
			c->z = string_to_float(parts[i]);
		i++;
	}
	return (free_arr(parts), true);
}

void	parse_coordination_or_exit(char *str, t_v3d *c)
{
	if (!parse_coordination(str, c))
		print_error("Invalid format. Expected x,y,z");
}

bool	parse_color(char *str, t_color *c)
{
	char	**parts;
	int		i;

	if (!validate_commas(str, ',', 2))
		return (false);
	parts = ft_split(str, ',');
	if (!parts)
		return (false);
	i = 0;
	while (i < 3)
	{
		if (!check_color(parts[i]))
			return (free_arr(parts), false);
		if (i == 0)
			c->r = ft_atoi(parts[i]);
		else if (i == 1)
			c->g = ft_atoi(parts[i]);
		else
			c->b = ft_atoi(parts[i]);
		i++;
	}
	return (free_arr(parts), true);
}

bool	parse_vector(char *s, t_v3d *v)
{
	if (!parse_coordination(s, v))
		return (false);
	if (v->x < -1.0f || v->x > 1.0f
		|| v->y < -1.0f || v->y > 1.0f
		|| v->z < -1.0f || v->z > 1.0f)
		return (false);
	if (v->x == 0.0f && v->y == 0.0f && v->z == 0.0f)
		return (false);
	return (true);
}

bool	parse_d_h(char *s, float *out)
{
	char	**parts;

	parts = ft_split(s, ',');
	if (!parts)
		return (false);
	if (counter(parts) != 1)
	{
		free_arr(parts);
		return (false);
	}
	free_arr(parts);
	if (!is_a_valid_float(s))
		return (false);
	*out = string_to_float(s);
	if (*out <= 0.0f)
		return (false);
	return (true);
}
