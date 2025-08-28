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

int	is_a_valid_float(char *str)
{
	int		i;
	int		has_digit;
	int		dot;

	i = 0;
	has_digit = 0;
	dot = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			has_digit = 1;
		else if (str[i] == '.')
		{
			if (dot)
				return (0);
			dot = 1;
		}
		else
			return (0);
		i++;
	}
	return (has_digit);
}

float	string_to_float(char *str)
{
	int	sign;
	int	i;
	int	result;
	int	div;

	i = 0;
	result = 0;
	div = 1;
	sign = parse_sign(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
			div *= 10;
			i++;
		}
	}
	return (sign * ((float)result / div));
}

void	parse_coordination(char *str, t_v3d *c)
{
	char	**parts;
	int		i;

	if (!validate_commas(str, ',', 2))
		print_error("Invalid format. Expected x,y,z");
	parts = ft_split(str, ',');
	if (!parts)
		print_error("Malloc failed in parse_coordination");
	i = 0;
	while (i < 3)
	{
		if (!is_a_valid_float(parts[i]))
		{
			free_arr(parts);
			print_error("Numbers must be a float");
		}
		if (i == 0)
			c->x = string_to_float(parts[i]);
		else if (i == 1)
			c->y = string_to_float(parts[i]);
		else
			c->z = string_to_float(parts[i]);
		i++;
	}
	free_arr(parts);
}

void	parse_color(char *str, t_color *c)
{
	char	**parts;
	int		i;

	if (!validate_commas(str, ',', 2))
		print_error("Invalid format. Expected R,G,B");
	parts = ft_split(str, ',');
	if (!parts)
		print_error("Malloc failed in parse_color");
	i = 0;
	while (i < 3)
	{
		if (!check_color(parts[i]))
		{
			free_arr(parts);
			print_error("Color components must be digits in [0,255]");
		}
		if (i == 0)
			c->r = ft_atoi(parts[i]);
		else if (i == 1)
			c->g = ft_atoi(parts[i]);
		else
			c->b = ft_atoi(parts[i]);
		i++;
	}
	free_arr(parts);
}

void	parse_vector(char *s, t_v3d *v)
{
	parse_coordination(s, v);
	if (v->x < -1.0f || v->x > 1.0f
		|| v->y < -1.0f || v->y > 1.0f
		|| v->z < -1.0f || v->z > 1.0f)
		print_error("Vector components must be in [-1,1]");
	if (v->x == 0.0f && v->y == 0.0f && v->z == 0.0f)
		print_error("Zero vector is not a valid direction");
}

float	parse_d_h(char *s)
{
	char	**parts;
	float	d;

	parts = ft_split(s, ',');
	if (counter(parts) != 1)
	{
		free_arr(parts);
		print_error("Only one argument needed");
	}
	free_arr(parts);
	if (!is_a_valid_float(s))
		print_error("Must be a valid number");
	d = string_to_float(s);
	if (d <= 0.0f)
		print_error("Must be greater than 0");
	return (d);
}

bool	safe_parse_coordination(char *str, t_v3d *c)
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
		{
			free_arr(parts);
			return (false);
		}
		if (i == 0)
			c->x = string_to_float(parts[i]);
		else if (i == 1)
			c->y = string_to_float(parts[i]);
		else
			c->z = string_to_float(parts[i]);
		i++;
	}
	free_arr(parts);
	return (true);
}

bool	safe_parse_color(char *str, t_color *c)
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
		{
			free_arr(parts);
			return (false);
		}
		if (i == 0)
			c->r = ft_atoi(parts[i]);
		else if (i == 1)
			c->g = ft_atoi(parts[i]);
		else
			c->b = ft_atoi(parts[i]);
		i++;
	}
	free_arr(parts);
	return (true);
}

bool	safe_parse_vector(char *s, t_v3d *v)
{
	if (!safe_parse_coordination(s, v))
		return (false);
	if (v->x < -1.0f || v->x > 1.0f
		|| v->y < -1.0f || v->y > 1.0f
		|| v->z < -1.0f || v->z > 1.0f)
		return (false);
	if (v->x == 0.0f && v->y == 0.0f && v->z == 0.0f)
		return (false);
	return (true);
}

bool	safe_parse_d_h(char *s, float *out)
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
