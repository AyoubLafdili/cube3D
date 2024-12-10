/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_lst_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:55:49 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/06 21:36:54 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_door_lst	*door_lst_new(t_crd d_idx)
{
	t_door_lst	*new;

	new = malloc(sizeof(t_door_lst));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_door_lst));
	new->door.door_idxs = d_idx;
	new->door.is_close = true;
	new->next = NULL;
	return (new);
}

void	door_add_lst(t_door_lst **head, t_door_lst *new)
{
	if (!head || !new)
		return ;
	new->next = *head;
	*head = new;
}

void	door_lst_clear(t_door_lst **head)
{
	t_door_lst	*tmp;

	tmp = NULL;
	if (!head)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

bool	add_to_list(t_cube *data, t_crd d_idx)
{
	t_door_lst	*new;

	new = door_lst_new(d_idx);
	if (!new)
		return (EXIT_FAILURE);
	door_add_lst(&data->head, new);
	return (EXIT_SUCCESS);
}
