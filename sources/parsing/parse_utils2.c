/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
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

float	parse_d_h_or_exit(char *s)
{
	float	result;

	result = 0.0f;
	if (!parse_d_h(s, &result))
		print_error("Only one argument needed or must be a valid number > 0");
	return (result);
}

void	parse_vector_or_exit(char *s, t_v3d *v)
{
	if (!parse_vector(s, v))
		print_error("Vector components must be in [-1,1] or non-zero");
}

void	parse_color_or_exit(char *str, t_color *c)
{
	if (!parse_color(str, c))
		print_error("Invalid format. Expected R,G,B or color in [0,255]");
}
