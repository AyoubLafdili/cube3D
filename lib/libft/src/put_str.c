/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:26:22 by aaitelka          #+#    #+#             */
/*   Updated: 2024/05/06 20:31:05 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	put_str(char *s)
{
	int	counter;

	counter = 0;
	if (!s)
		return (put_str("(null)"));
	while (*s)
		counter += put_char(*s++);
	return (counter);
}
