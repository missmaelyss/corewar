/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:41:39 by nbrucker          #+#    #+#             */
/*   Updated: 2018/01/23 08:53:04 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_alloc_word(const char *s, char c)
{
	size_t	len;
	size_t	i;
	char	*new_s;

	len = 0;
	i = 0;
	while (s[len] && s[len] != c)
		len++;
	if ((new_s = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (i < len)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

static int	ft_count_words(const char *s, char c)
{
	size_t	i;
	int		words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] == c)
			words++;
		i++;
	}
	return (words);
}

char		**ft_strksplit(const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**new_array;

	if (!s || !c)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_count_words(s, c);
	if ((new_array = (char **)malloc(sizeof(char *) * (len + 1))) == NULL)
		return (NULL);
	while (i < len)
	{
		if (s[j] == c)
			j++;
		if ((new_array[i] = ft_alloc_word(s + j, c)) == NULL)
			return (NULL);
		while (s[j] != c && s[j])
			j++;
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}
