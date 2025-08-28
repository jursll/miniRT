/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:22:11 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 16:21:45 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	parse_ambient(char **tokens, t_parsed_scene *scene)
{
	scene->ambient.ratio = parse_ratio(tokens[1]);
	parse_color(tokens[2], &scene->ambient.color);
	scene->has_ambient = 1;
}

void	parse_light(char **tokens, t_parsed_scene *scene)
{
	parse_coordination(tokens[1], &scene->light.coord);
	scene->light.ratio = parse_ratio(tokens[2]);
	parse_color(tokens[3], &scene->light.color);
	scene->has_light = 1;
}

void	parse_camera(char **tok, t_parsed_scene *sc)
{
	parse_coordination(tok[1], &sc->cam.coord);
	parse_vector(tok[2], &sc->cam.ori);
	sc->cam.fov = string_to_float(tok[3]);
	sc->has_camera = 1;
}
