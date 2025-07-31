/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:13:50 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 16:46:54 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	check_rt_extension(char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len < 3 || ft_strcmp(name + len - 3, ".rt") != 0)
		print_error("Scene file must have a .rt extension");
}

void	validate_scene(t_parsed_scene *scene)
{
	if (!scene->has_ambient)
		print_error("Missing ambient light (A)");
	if (!scene->has_camera)
		print_error("Missing camera (C)");
	if (!scene->has_light)
		print_error("Missing point light (L)");
}

void	parse_scene_file(int fd, t_parsed_scene *scene)
{
	char	*line;
	char	*trimmed;
	char	**tokens;

	line = get_next_line(fd);
	while (line != NULL)
	{
		trimmed = ft_strtrim(line, " \t\r\n");
		free(line);
		normalize_whitespace(trimmed);
		if (trimmed[0] != '\0' && trimmed[0] != '#')
		{
			tokens = ft_split(trimmed, ' ');
			if (!tokens)
				print_error("Malloc failed on split");
			dispatch_tokens(tokens, scene);
			free_arr(tokens);
		}
		free(trimmed);
		line = get_next_line(fd);
	}
	close(fd);
}

int	open_and_init(int argc, char **argv, t_parsed_scene *scene)
{
	int	fd;

	if (argc != 2)
		print_error("Usage: ./miniRT <scene.rt>");
	check_rt_extension(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		print_error("Could not open scene file");
	ft_memset(scene, 0, sizeof(*scene));
	return (fd);
}
