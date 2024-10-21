/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:00:35 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/21 21:49:51 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_door(t_door_lst *head)
{
	while (head)
	{
		if (head->door.be_open && head->door.is_close)
			head->door.offset += 0.5;
		if (head->door.be_open && head->door.offset >= CS)
		{
			head->door.be_open = false;
			head->door.is_open = true;
			head->door.is_close = false;
		}
		head = head->next;
	}
}
