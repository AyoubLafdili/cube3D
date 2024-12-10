/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:00:35 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/07 22:50:02 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	open_door(t_door_lst *head)
{
	while (head)
	{
		if (head->door.be_open && head->door.is_close)
			head->door.offset += 2;
		if (head->door.be_open && head->door.offset >= CS - DOOR_LIMIT)
		{
			head->door.be_open = false;
			head->door.is_open = true;
			head->door.is_close = false;
		}
		head = head->next;
	}
}
