/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mck-d <mck-d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:44:56 by adaifi            #+#    #+#             */
/*   Updated: 2021/11/25 16:22:12 by mck-d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*ptrd;
	const unsigned char	*ptrs;
	unsigned char		*d;
	const unsigned char	*s;

	ptrd = dst;
	ptrs = src;
	if (!src && !dst)
		return (NULL);
	if (ptrd < ptrs)
	{
		while (n--)
			*ptrd++ = *ptrs++;
	}
	else
	{
		d = ptrd + (n - 1);
		s = ptrs + (n - 1);
		while (n--)
			*d-- = *s--;
	}
	return (dst);
}
