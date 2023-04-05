/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mck-d <mck-d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 23:49:04 by adaifi            #+#    #+#             */
/*   Updated: 2021/11/25 23:48:02 by mck-d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*str;

	total = count * size;
	(str = malloc(total));
	if (!str)
		return (NULL);
	ft_bzero(str, total);
	return (str);
}
