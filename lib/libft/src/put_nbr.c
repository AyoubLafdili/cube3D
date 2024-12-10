/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_nbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:42:45 by aaitelka          #+#    #+#             */
/*   Updated: 2024/10/25 22:58:08 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	put_nbr(long nbr, int fd)
{
	int	counter;

	counter = 0;
	if (nbr < 0)
	{
		counter += put_char('-', fd);
		counter += put_nbr(-nbr, fd);
	}
	else if (nbr > 9)
	{
		counter += put_nbr(nbr / 10, fd);
		counter += put_nbr(nbr % 10, fd);
	}
	else
		counter += put_char(nbr + '0', fd);
	return (counter);
}
