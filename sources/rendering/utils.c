/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 09:37:53 by julrusse          #+#    #+#             */
/*   Updated: 2025/08/07 10:10:33 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_dtoa(double n, int precision)
{
	int		int_part;
	int		dec_part;
	char	*int_str;
	char	*dec_str;
	char	*tmp;

	int_part = (int)n;
	n -= int_part;
	while (precision-- > 0)
		n *= 10;
	dec_part = (int)(n + 0.5);
	int_str = ft_itoa(int_part);
	dec_str = ft_itoa(dec_part);
	tmp = ft_strjoin(int_str, ".");
	free(int_str);
	int_str = ft_strjoin(tmp, dec_str);
	free(tmp);
	free(dec_str);
	return (int_str);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	joined = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = '\0';
	free(s1);
	return (joined);
}
