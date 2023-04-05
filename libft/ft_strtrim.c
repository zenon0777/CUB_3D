/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 01:49:06 by adaifi            #+#    #+#             */
/*   Updated: 2021/11/23 04:14:49 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*ptr;

	if (!(s1) || !(set))
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i - 1]))
		i--;
	ptr = (char *)malloc(i + 1);
	if (!ptr)
		return (NULL);
	ptr[i] = '\0';
	return (ft_memcpy(ptr, s1, i));
}
