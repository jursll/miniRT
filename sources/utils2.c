/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:36:05 by julrusse          #+#    #+#             */
/*   Updated: 2025/07/03 12:36:43 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	free_objects(t_rt *rt)
{
	t_objects	*obj;

	while (rt->sc->obj)
	{
		obj = rt->sc->obj->next;
		free(rt->sc->obj);
		rt->sc->obj = obj;
	}
}

void	free_inter(t_inter *inter)
{
	if (inter)
		free (inter);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free (tab[i]);
			i++;
		}
		free (tab);
	}
}

void	free_scene(t_scene *scene)
{
	if (scene->obj)
		free (scene->obj);
	free (scene);
}

void	free_rt(t_rt *rt)
{
	if (rt->mlbx)
	{
		free (rt->mlbx->img.addr);
		free (rt->mlbx->img.img);
		free (rt->mlbx);
	}
	if (rt->sc->obj)
		free_objects(rt);
	if (rt->sc)
		free_scene(rt->sc);
	free (rt);
}
