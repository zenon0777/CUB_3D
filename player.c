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
			if (isplayer(data, map->map_input[i][j], 1) == true)
				return ;
			j++;
		}
		i++;
	}
}

int	isplayer(t_data *data, char p, int flag)
{
	if (flag == 0 && (p == 'N' || p == 'S' || p == 'w' || p == 'S'))
		return (1);
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

