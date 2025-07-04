/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:07:20 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/04 17:08:24 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	free_rt(t_rt *rt)
{
	/* Free scene objects if allocated */
	if (rt->scene.spheres)
		free(rt->scene.spheres);
	if (rt->scene.planes)
		free(rt->scene.planes);
	if (rt->scene.cylinders)
		free(rt->scene.cylinders);
	if (rt->scene.lights)
		free(rt->scene.lights);

	/* Free MLX resources if allocated */
	if (rt->mlbx)
	{
		if (rt->mlbx->img.img)
			mlx_destroy_image(rt->mlbx->mlx, rt->mlbx->img.img);
		free(rt->mlbx);
	}
}
