/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:26:22 by aaitelka          #+#    #+#             */
/*   Updated: 2024/10/25 23:11:47 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	put_str(char *s, int fd)
{
	int	counter;

	counter = 0;
	if (!s)
		return (put_str("(null)", fd));
	while (*s)
		counter += put_char(*s++, fd);
	return (counter);
}
