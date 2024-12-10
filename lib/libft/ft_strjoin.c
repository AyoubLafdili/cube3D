/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:25:46 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/05 21:10:19 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1len;
	size_t	dstlen;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	s1len = ft_strlen(s1);
	dstlen = s1len + ft_strlen(s2);
	str = malloc(dstlen + 1);
	if (!str)
		return ((void *)0);
	ft_strlcpy(str, s1, s1len + 1);
	ft_strlcat(str, s2, dstlen + 1);
	return (str);
}
