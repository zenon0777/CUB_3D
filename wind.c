/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:28:51 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/06 17:06:07 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include "cub.h"

void	celling_draw(t_data *data)
{
	int		c_color;
	int		mid_point;
	double	x;
	double	y;

	c_color = (data->map->c_color->red << 16) + \
		(data->map->c_color->green << 8) + data->map->c_color->blue;
	mid_point = data->screen_height / 2;
	y = 0;
	while (y <= mid_point)
	{
		x = 0;
		while (x < data->screen_width)
		{
			d_mlx_put_pixel(data, x, y, c_color);
			x++;
		}
		y++;
	}
	floor_draw(data, y, mid_point);
}

void	floor_draw(t_data *data, int y, int mid_point)
{
	int	f_color;
	int	x;

	f_color = (data->map->f_color->red << 16) + \
		(data->map->f_color->green << 8) + data->map->f_color->blue;
	while (y > mid_point && y < data->screen_height)
	{
		x = 0;
		while (x < data->screen_width)
		{
			d_mlx_put_pixel(data, x, y, f_color);
			x++;
		}
		y++;
	}
}

double	normalize_angle(double deg)
{
	deg = fmod(deg, (2 * M_PI));
	if (deg < 0)
		deg += (2 * M_PI);
	return (deg);
}

void	draw(t_map *map, t_data *data)
{
	int	i;
	int	j;

	i = map->index - 1;
	data->mlx_img = mlx_new_image(data->mlx, data->screen_width, \
		data->screen_height);
	data->mlx_addr = mlx_get_data_addr(data->mlx_img, \
		&data->bits_per_pixel, &data->line_length, &data->endian);
	celling_draw(data);
	while (++i < map->map_length)
	{
		j = -1;
		while (++j < (int)map->map_width)
		{
			data->x = j * TILE;
			data->y = (i - 12) * TILE;
			if (isplayer(data, map->map_input[i][j], 0) == true)
			{
				data->player.p_x += data->x + TILE / 2;
				data->player.p_y += data->y + TILE / 2;
				draw_player(data);
			}
		}
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->mlx_img, 1, 1);
}

void	rendering(t_map *map)
{
	t_data	data;

	data.x = 0;
	data.y = 0;
	data.map = map;
	data.textures = (t_textures *)malloc(4 * sizeof(t_textures));
	data.img_height = 800;
	data.img_width = 1500;
	data.screen_height = 800;
	data.screen_width = 1500;
	data.player.angle_dir = 0;
	data.player.walking_dir = 0;
	data.player.move_speed = 10;
	data.flag_dir = 0;
	player_angle(&data, map);
	data.player.fov = 60 * (M_PI / 180);
	data.player.rotation_speed = 8 * (M_PI / 180);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 1500, 800, "mlx");
	textures_img(data);
	draw(map, &data);
	mlx_hook(data.mlx_win, 02, 1L << 0, key, &data);
	mlx_hook(data.mlx_win, 03, 1L << 1, key_release, &data);
	mlx_loop(data.mlx);
}
