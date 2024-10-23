/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:51:42 by aaitelka          #+#    #+#             */
/*   Updated: 2024/10/21 17:52:59 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	ft_error(char *where, char *msg)
{
	if (ft_strchr(where, '\n'))
		where[ft_strlen(where) - 1] = '\0';
	ft_putendl_fd(R3D "Error" RESET, STDERR_FILENO);
	ft_putstr_fd("cube3D: ", STDERR_FILENO);
	ft_putstr_fd(ORNG, STDERR_FILENO);
	ft_putstr_fd(where, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	else
		perror("");
	return (FAILED);
}
