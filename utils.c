/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:10:18 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/09 03:42:13 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

int	dyo_dimen_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*ft_strjoin_freed(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!s1 || !s2)
		return (0);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, len1);
	ft_memmove(str + len1, s2, len2 + 1);
	free((void *)s1);
	return (str);
}

char	*get_next_line(int fd)
{
	char	buff[2];
	char	*line;
	void	*d_ptr;

	if (fd < 0)
		return (NULL);
	buff[0] = 0;
	buff[1] = 0;
	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (read(fd, buff, 1) > 0)
	{
		d_ptr = line;
		if (buff[0] == '\n')
			return (line);
		line = ft_strjoin(line, buff);
		if (!line)
			return (free(d_ptr), NULL);
		free(d_ptr);
	}
	if (line && !*line)
		return (free(line), NULL);
	return (line);
}

void	free_map(t_map *map)
{
	if (map->f_color)
		free(map->f_color);
	if (map->c_color)
		free(map->c_color);
	if (map->map_input)
		d_free_2d(map->map_input);
	if (map)
		free(map);
}

int	column_calc(char *rgb)
{
	int	i;

	i = 0;
	while (*rgb)
	{
		if (*rgb == ',')
			i++;
		rgb++;
	}
	return (i);
}
