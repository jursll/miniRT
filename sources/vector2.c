/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:47:58 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/03 11:10:26 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_v3d	sc_mult(t_v3d a, double nb)
{
	t_v3d	res;

	res.x = a.x * nb;
	res.y = a.y * nb;
	res.z = a.z * nb;
	return (res);
}

double	vec_dot(t_v3d a, t_v3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	vec_norm(t_v3d a)
{
	double	res;

	res = sqrt(pow(a.x, 2.0) + pow(a.y, 2.0) + pow(a.z, 2.0));
	return (res);
}
