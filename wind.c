/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:28:51 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/09 05:15:40 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include "cub.h"

double	normalize_angle(double deg)
{
	deg = fmod(deg, (2 * M_PI));
	if (deg < 0)
		deg += (2 * M_PI);
	return (deg);
}

void draw_square(t_data *data, int color)
{
	int i = 0;
	while (i < TILE)
	{
		int j = 0;
		while (j < TILE)
		{
			d_mlx_put_pixel(data, data->x + i, data->y + j, color);
			j++;
		}
		i++;
	}
	return ;
}

void	draw(t_map *map, t_data *data, int i)
{
	int	j;

	//i -= 1;
	data->mlx_img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->mlx_img)
		return (free_map(map), free(data->textures), exit(1));
	data->mlx_addr = mlx_get_data_addr(data->mlx_img, &data->bpp, &data->ll, \
	&data->endian);
	celling_draw(data);
	while (i < map->map_length)
	{
		j = 0;
		while (j < (int)map->map_width)
		{
			data->x = j * TILE;
			data->y = (i - 12) * TILE;
			if (map->map_input[i][j] == '1')
				draw_square(data, 255);
			if (map->map_input[i][j] == ' ')
				draw_square(data, 0);
			if (map->map_input[i][j] == '0')
				draw_square(data, 100);
			j++;
		}
		i++;
	}
	i = map->index - 1;
	while (++i < map->map_length)
	{
		j = -1;
		while (++j < (int)map->map_width)
		{
			data->x = j * TILE;
			data->y = (i - 12) * TILE;
			if (ft_strchr("NSWE", map->map_input[i][j]) != 0)
			{
				data->player.p_x += data->x + TILE / 2;
				data->player.p_y += data->y + TILE / 2;
				draw_player(data);
			}
		}
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->mlx_img, 1, 1);
}

void	d_init_data(t_data *data, t_map *map)
{
	data->x = 0;
	data->y = 0;
	data->map = map;
	data->textures = (t_textures *)malloc(4 * sizeof(t_textures));
	if (!data->textures)
		return (free_map(map), exit(1));
	data->img_height = 800;
	data->img_width = 1500;
	data->height = 800;
	data->width = 1500;
	data->player.angle_dir = 0;
	data->player.walking_dir = 0;
	data->player.move_speed = 10;
	data->flag_dir = 0;
}

void	rendering(t_map *map)
{
	t_data	data;

	d_init_data(&data, map);
	player_angle(&data, map);
	data.player.fov = 60 * (M_PI / 180);
	data.player.rotation_speed = 8 * (M_PI / 180);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (free(data.textures), free_map(map), exit(1));
	data.mlx_win = mlx_new_window(data.mlx, 1500, 800, "mlx");
	if (!data.mlx_win)
		return (free(data.textures), free_map(map), exit(1));
	textures_img(data);
	draw(map, &data, map->index);
	mlx_hook(data.mlx_win, 02, 1L << 0, key, &data);
	mlx_hook(data.mlx_win, 03, 1L << 1, key_release, &data);
	mlx_loop(data.mlx);
}
