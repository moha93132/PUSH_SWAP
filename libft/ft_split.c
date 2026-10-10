/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohasnao <mohasnao@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 12:18:43 by mohasnao          #+#    #+#             */
/*   Updated: 2026/10/06 15:04:21 by mohasnao         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	occ_c(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	if (s[i - 1] != c)
		count++;
	return (count);
}

int	word_end(char const *s, int i, char c)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**free_split(char **str, int x)
{
	while (x > 0)
	{
		x--;
		free(str[x]);
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		x;

	i = 0;
	j = 0;
	x = 0;
	str = malloc((occ_c(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (x < occ_c(s, c))
	{
		while (s[j] == c)
			j++;
		i = j;
		j = word_end(s, j, c);
		str[x] = malloc(j - i + 1);
		if (!str[x])
			return (free_split(str, x));
		ft_strlcpy(str[x], &s[i], j - i + 1);
		x++;
	}
	str[x] = NULL;
	return (str);
}
