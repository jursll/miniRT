/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlbx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:20:39 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/31 18:35:13 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	esc_key(const int keycode, t_rt *rt)
{
	if (keycode == 53)
	{
		destroy(rt);
	}
	return (0);
}

void	make_window(t_rt *rt)
{
	t_mlbx	*mlbx;

	mlbx = malloc(sizeof(t_mlbx));
	rt->mlbx = mlbx;
	rt->mlbx->mlx = mlx_init();
	rt->mlbx->mlx_win = mlx_new_window(mlbx->mlx, WIN_W, WIN_H, "MiniRT");
	rt->mlbx->img.img = mlx_new_image(mlbx->mlx, WIN_W, WIN_H);
	rt->mlbx->img.addr = mlx_get_data_addr(mlbx->img.img,
			&mlbx->img.bits_per_pixel, &mlbx->img.line_length,
			&mlbx->img.endian);
	display(rt);
	mlx_hook(mlbx->mlx_win, 17, 0, destroy, rt);
	mlx_hook(mlbx->mlx_win, 2, 1L << 0, handle_key, rt);
	mlx_loop(mlbx->mlx);
}

int	destroy(t_rt *rt)
{
	mlx_destroy_window(rt->mlbx->mlx, rt->mlbx->mlx_win);
	free_rt(rt);
	exit(0);
	return (0);
}

int	display(t_rt *rt)
{
	char	info_str[256];

	launch_rays(rt);
	draw_selection_info(rt);
	mlx_put_image_to_window(rt->mlbx->mlx, rt->mlbx->mlx_win,
		rt->mlbx->img.img, 0, 0);
	get_object_info(rt, info_str);
	mlx_string_put(rt->mlbx->mlx, rt->mlbx->mlx_win, 15, 25, 0xFFFFFF,
		info_str);
	return (0);
}

void	my_mlx_pixel_put(t_data img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		dst = img.addr + (y * img.line_length
				+ x * (img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
