/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:32:25 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/17 15:19:25 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* Simple free function */
void	free_rt(t_rt *rt)
{
	if (rt->scene.spheres)
		free(rt->scene.spheres);
	if (rt->scene.planes)
		free(rt->scene.planes);
	if (rt->scene.cylinders)
		free(rt->scene.cylinders);
	if (rt->scene.lights)
		free(rt->scene.lights);
	if (rt->mlbx)
		free(rt->mlbx);
}

int	main(void)
{
	t_rt	rt;

	// Create test scene
	create_lit_scene(&rt);

	// Open window and render
	make_window(&rt);

	return (0);
}

/*
int	main(int argc, char **argv)
{
	t_rt	*rt;

	(void) argv;
	rt = ft_calloc(sizeof(t_rt), 1);
	if (argc == 2)
	{
		file_parsing(argv[1], rt);
		make_window(rt);
	}
	else
	{
		ft_putstr_fd("\033[31m2 Usage:\n\033[0m", 2);
		ft_putstr_fd("\033[31m./miniRT [scene_path]\n\033[0m", 2);
	}
}
*/
