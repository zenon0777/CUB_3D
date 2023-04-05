/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 01:39:36 by adaifi            #+#    #+#             */
/*   Updated: 2021/11/11 01:41:16 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || s1 == s2)
	{
		return (0);
	}
	while (i < n - 1 && s1[i] && s2[i])
	{
		if (s1[i] && s1[i] != s2[i])
			return ((unsigned char)(s1)[i] - (unsigned char )(s2)[i]);
		i++;
	}
	return ((unsigned char)(s1)[i] - (unsigned char )(s2)[i]);
}
