/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 01:46:15 by adaifi            #+#    #+#             */
/*   Updated: 2021/11/26 03:50:03 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	d;
	const char		*tmp;

	tmp = (const char *)s;
	d = ft_strlen(s);
	s = (s + d);
	while (*s != *tmp && *s != (unsigned char)c)
		s--;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (0);
}
