/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlbx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:20:39 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/03 10:40:12 by julrusse         ###   ########.fr       */
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

/* creates the graphical window */
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
	mlx_key_hook(mlbx->mlx_win, esc_key, rt);
	mlx_loop(mlbx->mlx);
}

/* close the window and exit the program */
int	destroy(t_rt *rt)
{
	mlx_destroy_window(rt->mlbx->mlx, rt->mlbx->mlx_win);
	free_rt(rt);
	exit(0);
	return (0);
}

/* updates the displayed image */
int	display(t_rt *rt)
{
	launch_rays(rt);
	mlx_put_image_to_window(rt->mlbx->mlx, rt->mlbx->mlx_win,
		rt->mlbx->img.img, 0, 0);
	return (0);
}

/* draws a pixel at (x, y) in color */
void	my_mlx_pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		dst = img.addr + (y * img.line_length
				+ x * (img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
