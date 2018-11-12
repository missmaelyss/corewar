/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 13:42:58 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/23 10:26:20 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *meule_de_foin, const char *aiguille, size_t i)
{
	size_t n;

	n = 0;
	if (ft_strlen(aiguille) == 0)
		return ((char *)meule_de_foin);
	while (ft_strncmp(&meule_de_foin[n], aiguille, ft_strlen(aiguille))
			&& meule_de_foin[n] != 0 && n < i)
		n++;
	if ((meule_de_foin[n] == 0) || (n + ft_strlen(aiguille) > i))
		return (0);
	return ((char *)&meule_de_foin[n]);
}
