/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:51:42 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/07 02:10:36 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_error(char *where, char *msg)
{
	if (ft_strchr(where, '\n'))
		where[ft_strlen(where) - 1] = '\0';
	ft_dprintf(2, RD "Error\n" RS "cube3d: " ORNG "%s" RS ": ", where);
	if (msg)
		ft_dprintf(2, "%s\n", msg);
	else
		perror("");
	return (FAILED);
}

int	ft_maperror(char *where, int r, int c)
{
	ft_dprintf(2, RD "Error\n" RS "cube3d: ");
	ft_dprintf(2, ORNG"%s"RS IN RD"[%d] "RS"col"RD" [%d]\n" RS, where, r, c);
	return (FAILED);
}
