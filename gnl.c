/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:20 by med-doba          #+#    #+#             */
/*   Updated: 2023/02/21 19:35:04 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*get_next_line(int fd)
{
	char	buff[2];
	char	*line;
	int		n;
	void	*d_ptr;

	if (fd < 0)
		return (NULL);
	buff[0] = 0;
	buff[1] = 0;
	line = ft_strdup("");
	n = 1;
	while (n > 0)
	{
		n = read(fd, buff, 1);
		if (n <= 0)
			continue ;
		d_ptr = line;
		if (buff[0] == '\n')
			return (line);
		line = ft_strjoin(line, buff);
		free(d_ptr);
	}
	if (line && !*line)
		return (free(line), NULL);
	return (line);
}