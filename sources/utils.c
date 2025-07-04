/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:32:32 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/03 12:55:31 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_inter	*calloc_utils(void)
{
	t_inter	*new;

	new = ft_calloc(sizeof(t_inter), 1);
	if (!new)
		print_error("Error: Malloc initialisation failed \n");
	return (new);
}

void	print_v3d(t_v3d vec)
{
	printf("vector x: %f\n", vec.x);
	printf("vector y: %f\n", vec.y);
	printf("vector z: %f\n", vec.z);
}

void	print_inter(t_inter *inter)
{
	printf("Type: %u\n", inter->type);
	printf("distance: %f\n", inter->dist);
	printf("point vector: \n");
	print_v3d(inter->point);
	printf("normal vector: \n");
	print_v3d(inter->normal);
}

int	print_error(char *error_message)
{
	ft_printf("\033[31mError\n%s\033[30m\n", error_message);
	exit (EXIT_FAILURE);
}
