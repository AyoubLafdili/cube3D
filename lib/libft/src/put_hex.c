/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:02:42 by aaitelka          #+#    #+#             */
/*   Updated: 2024/10/25 22:53:59 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	put_hex(unsigned long decimal, char placeholder, int fd)
{
	int	counter;
	int	remainder;

	counter = 0;
	remainder = decimal % 16;
	if (decimal / 16)
		counter += put_hex(decimal / 16, placeholder, fd);
	if (remainder < 10)
		counter += put_nbr(remainder, fd);
	else if (remainder > 9 && placeholder == 'x')
		counter += put_char(remainder + 87, fd);
	else if (remainder > 9 && placeholder == 'X')
		counter += put_char(remainder + 55, fd);
	return (counter);
}
