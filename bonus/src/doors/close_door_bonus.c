/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_door_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:30:52 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/07 22:50:18 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	close_door(t_door_lst *head)
{
	while (head)
	{
		if (head->door.be_close && head->door.is_open)
			head->door.offset -= 2;
		if (head->door.be_close && head->door.offset <= 0)
		{
			head->door.be_close = false;
			head->door.is_close = true;
			head->door.is_open = false;
		}
		head = head->next;
	}
}
