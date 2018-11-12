/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:01:46 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/18 16:22:40 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		len(char const *s1)
{
	int	len;
	int n;

	n = 0;
	while ((s1[n] == ' ') || (s1[n] == '\t') || (s1[n] == '\n'))
		n++;
	len = ft_strlen(s1);
	while ((s1[len - 1] == ' ') || (s1[len - 1] == '\t')
			|| (s1[len - 1] == '\n'))
		len--;
	if (len - n > 0)
		return (len - n);
	return (0);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		istr;

	i = 0;
	istr = 0;
	if (s == NULL)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(char) * (len(s) + 1))))
		return (NULL);
	while ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n'))
		i++;
	while (istr < len(s))
	{
		str[istr] = s[i + istr];
		istr++;
	}
	str[istr] = 0;
	i = len(s);
	return (str);
}
