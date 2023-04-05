/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:57:32 by adaifi            #+#    #+#             */
/*   Updated: 2021/11/26 03:37:08 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	number_of_str(char const *str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (!str[i] || str[i] == c)
	{
		j = 0;
		i++;
	}
	i = 0;
	while (str[i])
		if (str[i++] == c && str[i] != c && str[i])
			j++;
	return (j);
}

static	char	**free_memory(char **p, int i)
{
	while (i--)
		free(p[i]);
	free(p);
	return (NULL);
}

static char	**word_maker(char **tab, char const *str, int size, char c)
{
	int		i;
	int		k;

	i = 0;
	while (*str != '\0')
	{
		k = 0;
		while (str[k] && str[k] != c)
			k++;
		if (k != 0 && i < size)
		{
			tab[i] = (char *)malloc(k + 1);
			if (tab[i] == NULL)
				free_memory(tab, i);
			ft_memcpy(tab[i], str, k);
			tab[i][k] = '\0';
			str += k;
			i++;
		}
		else
			str++;
	}
	tab[size] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	char	**tab;

	if (!s)
		return (NULL);
	j = number_of_str(s, c);
	tab = (char **) malloc((j + 1) * sizeof (char *));
	if (!(tab))
		return (NULL);
	word_maker(tab, s, j, c);
	return (tab);
}
