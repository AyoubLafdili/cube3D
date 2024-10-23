/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:31:27 by aaitelka          #+#    #+#             */
/*   Updated: 2024/10/22 20:52:00 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

size_t	ft_array_size(char **array)
{
	size_t			size;

	if (!array)
		return (0);
	size = -1;
	while (array[++size])
		;
	return (size);
}

void	ft_clear_array(char **array, int size)
{
	int				index;

	index = 0;
	if (!array)
		return ;
	while (index < size)
	{
		if (array[index] != NULL)
			free(array[index]);
		index++;
	}
	free(array);
}
