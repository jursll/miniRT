/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:32:25 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/04 16:52:28 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	create_test_scene(t_rt *rt)
{
	// Initialize scene
	rt->scene.num_spheres = 1;
	rt->scene.num_planes = 0;
	rt->scene.num_cylinders = 0;
	rt->scene.num_lights = 0;

	// Set up camera looking down +Z axis
	rt->scene.camera.position = vec(0, 0, -20);    // 20 units back
	rt->scene.camera.orientation = vec(0, 0, 1);   // Looking forward
	rt->scene.camera.fov = 70;                     // 70 degree field of view

	// Create one red sphere at origin
	rt->scene.spheres = malloc(sizeof(t_sphere) * 1);
	rt->scene.spheres[0].center = vec(0, 0, 0);    // At origin
	rt->scene.spheres[0].diameter = 10.0;          // 10 unit diameter
	rt->scene.spheres[0].color.r = 255;            // Red
	rt->scene.spheres[0].color.g = 0;
	rt->scene.spheres[0].color.b = 0;
}

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
	create_test_scene(&rt);

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
