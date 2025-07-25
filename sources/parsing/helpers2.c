/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:18:11 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 11:35:56 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	is_normalized(t_v3d v)
{
	float	len2;

	len2 = v.x * v.x + v.y * v.y + v.z * v.z;
	if (abs_val(len2 - 1.0f) < 0.001f)
		return (1);
	return (0);
}

bool	check_color(char *str)
{
	int	i;
	int	v;

	if (!str[0])
		return (false);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	v = ft_atoi(str);
	return (v >= 0 && v <= 255);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while ((*s1 && *s2) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	normalize_whitespace(char *s)
{
	while (*s)
	{
		if (*s == '\t' || *s == '\r' || *s == '\v' || *s == '\f')
			*s = ' ';
		s++;
	}
}
