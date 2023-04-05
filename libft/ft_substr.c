/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mck-d <mck-d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 02:24:17 by adaifi            #+#    #+#             */
/*   Updated: 2021/11/24 21:25:17 by mck-d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;
	size_t	len1;
	size_t	index;

	i = 0;
	len1 = ft_strlen(s);
	if (!s)
		return (0);
	if (len1 < len)
		len = ft_strlen(s);
	s1 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s1)
		return (0);
	index = start;
	while (index < len1 && i < len)
	{
		s1[i] = s[index++];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
