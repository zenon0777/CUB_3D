/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 00:38:04 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/09 01:42:49 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

void	get_width(t_map *map, int index)
{
	int	i;

	i = index;
	while (map->map_input[i])
	{
		if (ft_strlen(map->map_input[i]) > map->map_width)
			map->map_width = ft_strlen(map->map_input[i]);
		i++;
	}
}

void	line_edit(t_map *map, int i)
{
	size_t	length;

	length = 0;
	while (map->map_input[i])
	{
		length = ft_strlen(map->map_input[i]);
		while (length < map->map_width)
		{
			map->map_input[i] = ft_strjoin_freed(map->map_input[i], " ");
			if (!map->map_input[i])
				return (free_map(map), exit(1));
			length++;
		}
		i++;
	}
}

bool	check_moji(t_map *map, int i)
{
	int	j;
	int	player;

	player = 0;
	while (i < map->map_length)
	{
		j = 0;
		while (map->map_input[i][j] != '\0')
		{
			if (map->map_input[i][j] != 'N' && map->map_input[i][j] != ' ' &&
				map->map_input[i][j] != '1' && map->map_input[i][j] != '0' &&
				map->map_input[i][j] != 'W' && map->map_input[i][j] != 'E' &&
				map->map_input[i][j] != 'S')
				return (false);
			if (map->map_input[i][j] == 'N' || map->map_input[i][j] == 'W' ||
				map->map_input[i][j] == 'E' || map->map_input[i][j] == 'S')
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		return (false);
	return (true);
}

bool	parse_chart_lower(t_map *map, int index)
{
	get_width(map, index);
	if (check_moji(map, index) == false)
		return (false);
	line_edit(map, index);
	if (check_sichocu(map, index) == false)
		return (false);
	if (check_orozintios(map, index) == false)
		return (false);
	return (true);
}

bool	parse_chart(t_map *map)
{
	int	i;

	i = 0;
	while (map->map_input[i])
	{
		if (map->flagofdragon >= 6)
			break ;
		if (map->flagofdragon < 6 && \
			(map->map_input[i][0] == '0' || map->map_input[i][0] == '1'))
			return (false);
		if (map->flagofdragon < 6)
			if (parse_dragons(&map, map->map_input[i]) == false)
				return (false);
		i++;
	}
	map->index = i;
	if (parse_chart_lower(map, i) == false)
		return (false);
	return (true);
}
