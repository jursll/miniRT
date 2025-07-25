/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:13:49 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/24 15:24:01 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	parse_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

float	abs_val(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	counter(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	validate_commas(char *s, char sep, int count)
{
	int	i;
	int	found;

	if (!s || s[0] == sep || s[ft_strlen(s) - 1] == sep)
		return (0);
	found = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == sep)
		{
			found++;
			if (s[i + 1] == sep)
				return (0);
		}
		i++;
	}
	if (found != count)
		return (0);
	return (1);
}

float	parse_ratio(char *s)
{
	float	v;

	if (!is_a_valid_float(s))
		print_error("Ratio must be a float");
	v = string_to_float(s);
	if (v < 0.0f || v > 1.0f)
		print_error("Ratio must be between 0.0 and 1.0");
	return (v);
}
