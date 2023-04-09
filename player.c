/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:57:49 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/09 04:47:58 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	player_angle(t_data *data, t_map *map)
{
	int	i;
	int	j;

	i = map->index;
	while (i < map->map_length)
	{
		j = 0;
		while (j < (int)map->map_width)
		{
			if (isplayer(data, map->map_input[i][j]) == 0)
				return ;
			j++;
		}
		i++;
	}
}

int	isplayer(t_data *data, char p)
{
	if (p == 'N')
	{
		data->player.rotation_angle = (3 * M_PI) / 2;
		return (0);
	}
	else if (p == 'E')
	{
		data->player.rotation_angle = M_PI;
		return (0);
	}
	else if (p == 'S')
	{
		data->player.rotation_angle = M_PI / 2;
		return (0);
	}
	else if (p == 'W')
	{
		data->player.rotation_angle = 0;
		return (0);
	}
	return (-1);
}
