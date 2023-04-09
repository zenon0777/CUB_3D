/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ori_sichu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:05:04 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/07 20:08:28 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

bool	sichocu_itter(t_map *map, int i, int j)
{
	if (i == map->index && map->map_input[i][j] != ' ')
	{
		if (map->map_input[i][j] != '1')
			return (false);
	}
	else if (i != map->index && map->map_input[i][j] != ' ')
	{
		if (map->map_input[i - 1][j] == ' ' || map->map_input[i + 1][j] == ' ')
		{
			if (map->map_input[i][j] != '1')
				return (false);
		}
	}
	else if (i == map->map_length - 1)
		if (map->map_input[i][j] != ' ' && map->map_input[i][j] != '1')
			return (false);
	return (true);
}

bool	check_sichocu(t_map *map, int index)
{
	int	j;
	int	i;

	j = 0;
	while (j < (int)map->map_width)
	{
		i = index;
		while (i < map->map_length - 1)
		{
			if (sichocu_itter(map, i, j) == false)
				return (false);
			i++;
		}
		j++;
	}
	return (true);
}

bool	orizontios_itter(t_map *map, int i, int j)
{
	if (j == 0 && map->map_input[i][j] != ' ')
	{
		if (map->map_input[i][j] != '1')
			return (false);
	}
	else if (j != 0 && map->map_input[i][j] != ' ')
	{
		if (map->map_input[i][j - 1] == ' ' || map->map_input[i][j + 1] == ' ')
		{
			if (map->map_input[i][j] != '1')
				return (false);
		}
	}
	else if (j == (int)map->map_width - 1)
		if (map->map_input[i][j] != ' ' && map->map_input[i][j] != '1')
			return (false);
	return (true);
}

bool	check_orozintios(t_map *map, int index)
{
	int	j;
	int	i;
	int	length;

	j = 0;
	length = map->map_length;
	i = index;
	while (i < length)
	{
		j = 0;
		while (j < (int)map->map_width)
		{
			if (orizontios_itter(map, i, j) == false)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
