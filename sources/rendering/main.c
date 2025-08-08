/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:32:25 by julrusse          #+#    #+#             */
/*   Updated: 2025/08/08 12:24:47 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include "../include/parsing.h"

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

int	main(int argc, char **argv)
{
	t_rt			rt;
	t_parsed_scene	ps;
	int				fd;

	rt = (t_rt){0};
	ps = (t_parsed_scene){0};
	if (argc != 2)
	{
		printf("Usage: %s <scene_file.rt>\n", argv[0]);
		return (1);
	}
	fd = open_and_init(argc, argv, &ps);
	parse_scene_file(fd, &ps);
	validate_scene(&ps);
	rt.scene = build_runtime_scene(&ps);
	free_scene_objects(&ps);
	init_selection(&rt);
	make_window(&rt);
	return (0);
}
