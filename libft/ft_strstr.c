/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:07:35 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/23 10:27:34 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *meule_de_foin, const char *aiguille)
{
	int n;

	n = 0;
	if (ft_strlen(aiguille) == 0)
		return ((char *)meule_de_foin);
	while (ft_strncmp(&meule_de_foin[n], aiguille, ft_strlen(aiguille))
			&& meule_de_foin[n] != 0)
		n++;
	if (meule_de_foin[n] == 0)
		return (0);
	return ((char *)&meule_de_foin[n]);
}
