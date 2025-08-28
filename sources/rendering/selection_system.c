/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:27:18 by julrusse          #+#    #+#             */
/*   Updated: 2025/08/28 14:56:38 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	init_selection(t_rt *rt)
{
	rt->selection_index = 0;
	rt->current_selection = get_selection_at_index(rt, 0);
}

int	get_total_objects(t_rt *rt)
{
	int	total;

	total = 1;
	total += rt->scene.num_spheres;
	total += rt->scene.num_planes;
	total += rt->scene.num_cylinders;
	total += rt->scene.num_lights;
	return (total);
}

void	get_object_info(t_rt *rt, char *info_str)
{
	t_selection	sel;

	sel = rt->current_selection;
	if (sel.type == SEL_CAMERA)
		format_camera_info(rt, info_str);
	else if (sel.type == SEL_SPHERE)
		format_sphere_info(rt, info_str);
	else if (sel.type == SEL_PLANE)
		format_plane_info(rt, info_str);
	else if (sel.type == SEL_CYLINDER)
		format_cylinder_info(rt, info_str);
	else if (sel.type == SEL_LIGHT)
		format_light_info(rt, info_str);
}

char	*format_vec(t_v3d v, int precision)
{
	char	*x;
	char	*y;
	char	*z;
	char	*result;
	char	*tmp;

	x = ft_dtoa(v.x, precision);
	y = ft_dtoa(v.y, precision);
	z = ft_dtoa(v.z, precision);
	if (!x || !y || !z)
		return (NULL);
	tmp = ft_strjoin(x, ", ");
	result = ft_strjoin_free(tmp, y);
	tmp = ft_strjoin(result, ", ");
	free(result);
	result = ft_strjoin_free(tmp, z);
	tmp = ft_strjoin("(", result);
	free(result);
	result = ft_strjoin_free(tmp, ")");
	free(x);
	free(y);
	free(z);
	return (result);
}

void	draw_selection_info(t_rt *rt)
{
	char	info_str[256];
	int		x;
	int		y;

	get_object_info(rt, info_str);
	y = 10;
	while (y < 30)
	{
		x = 10;
		while (x < 600)
		{
			my_mlx_pixel_put(rt->mlbx->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
	mlx_string_put(rt->mlbx->mlx, rt->mlbx->mlx_win,
		15, 25, 0xFFFFFF, info_str);
}
