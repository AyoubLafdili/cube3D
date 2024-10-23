/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_nbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:42:45 by aaitelka          #+#    #+#             */
/*   Updated: 2024/05/06 20:30:34 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	put_nbr(long nbr)
{
	int	counter;

	counter = 0;
	if (nbr < 0)
	{
		counter += put_char('-');
		counter += put_nbr(-nbr);
	}
	else if (nbr > 9)
	{
		counter += put_nbr(nbr / 10);
		counter += put_nbr(nbr % 10);
	}
	else
		counter += put_char(nbr + '0');
	return (counter);
}
