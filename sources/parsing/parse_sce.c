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
	if (scene->has_ambient)
		print_error("Too many ambient lights –only one allowed");
	if (counter(tokens) != 3)
		print_error("Ambient light needs 2 arguments");
	scene->ambient.ratio = parse_ratio(tokens[1]);
	parse_color(tokens[2], &scene->ambient.color);
	scene->has_ambient = 1;
}

void	parse_light(char **tokens, t_parsed_scene *scene)
{
	if (scene->has_light)
		print_error("Too many lights only -one allowed");
	if (counter(tokens) != 4)
		print_error("Light needs 3 arguments");
	parse_coordination(tokens[1], &scene->light.coord);
	scene->light.ratio = parse_ratio(tokens[2]);
	parse_color(tokens[3], &scene->light.color);
	scene->has_light = 1;
}

void	parse_camera(char **tok, t_parsed_scene *sc)
{
	if (sc->has_camera)
		print_error("Only one camera allowed");
	if (counter(tok) != 4)
		print_error("Camera needs exactly 3 arguments");
	parse_coordination(tok[1], &sc->cam.coord);
	parse_vector(tok[2], &sc->cam.ori);
	if (!is_a_valid_float(tok[3]))
		print_error("FOV must be a float");
	sc->cam.fov = string_to_float(tok[3]);
	if (sc->cam.fov <= 0.0f || sc->cam.fov > 180.0f)
		print_error("FOV must be in (0 & 180]");
	sc->has_camera = 1;
}
