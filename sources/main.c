/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:32:25 by julrusse          #+#    #+#             */
/*   Updated: 2025/06/20 14:47:13 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int main(void)
{
    void *mlx;
    void *win;

    /* Test Libft functionality */
    ft_putstr_fd("Testing Libft: Hello, World!\n", 1);

    /* Initialize MiniLibX */
    mlx = mlx_init();
    if (!mlx)
    {
        ft_putstr_fd("Failed to initialize MLX.\n", 1);
        return (1);
    }

    /* Create a window 400x400 named "miniRT Test" */
    win = mlx_new_window(mlx, 400, 400, "miniRT Test");
    if (!win)
    {
        ft_putstr_fd("Failed to create window.\n", 1);
        return (1);
    }

    /* Draw a red pixel at the center */
    mlx_pixel_put(mlx, win, 200, 200, 0x00FF0000);

    /* Draw a test string in white at position (50,50) */
    mlx_string_put(mlx, win, 50, 50, 0x00FFFFFF, "miniRT: libft + mlx");

    /* Enter the MLX event loop */
    mlx_loop(mlx);

    return (0);
}
