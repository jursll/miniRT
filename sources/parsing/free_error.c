/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:21:01 by jjakupi           #+#    #+#             */
/*   Updated: 2025/07/25 15:37:15 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_scene_objects(t_parsed_scene *scene)
{
	t_parsed_object	*cur;
	t_parsed_object	*next;

	cur = scene->obj;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	scene->obj = NULL;
}

int	print_error(char *error_message)
{
	printf("\033[31mError\n%s\033[30m\n", error_message);
	exit (EXIT_FAILURE);
}
