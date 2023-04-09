/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:47:11 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/09 01:09:00 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

bool	check_extension(const char *file, int flag)
{
	int	length;

	length = ft_strlen(file);
	if (flag == 0)
	{
		if (file[length - 1] == 'b')
			if (file[length - 2] == 'u')
				if (file[length - 3] == 'c')
					if (file[length - 4] == '.')
						return (true);
	}
	else if (flag == 1)
	{
		length = ft_strlen(file);
		if (file[length - 1] == 'm')
			if (file[length - 2] == 'p')
				if (file[length - 3] == 'x')
					if (file[length - 4] == '.')
						return (true);
	}
	return (false);
}

void	d_free_2d(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

int	read_file(int fd)
{
	int		size;
	char	*line;

	size = 0;
	line = get_next_line(fd);
	if (!line)
		return (-1);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		size++;
	}
	free(line);
	return (size);
}

bool	check_file(char *file)
{
	if (check_extension(file, 1) == true)
		if (access(file, F_OK | R_OK) == 0)
			return (true);
	return (false);
}
