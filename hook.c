/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:34:11 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/06 16:53:38 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	d_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= (data->screen_width * TILE) || \
	y >= (data->screen_height * TILE) || x < 0 || y < 0)
		return ;
	dst = data->mlx_addr + (y * data->line_length + \
	x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_redraw(t_map *map, t_data *data)
{
	data->player.rotation_angle += data->player.angle_dir * \
	data->player.rotation_speed;
	if (data->player.rotation_angle < 0)
		data->player.rotation_angle += 2 * M_PI;
	mlx_destroy_image(data->mlx, data->mlx_img);
	draw(map, data);
}

int	key(int key, t_data *data)
{
	if (key == 124)
		data->player.angle_dir = 1;
	if (key == 123)
		data->player.angle_dir = -1;
	if (key == 13)
		data->player.walking_dir = 1;
	if (key == 1)
		data->player.walking_dir = -1;
	if (key == 2)
	{
		data->flag_dir = 1;
		data->player.walking_dir = -1;
	}
	if (key == 0)
	{
		data->flag_dir = 1;
		data->player.walking_dir = 1;
	}
	if (key == 53)
		exit(0);
	clear_redraw(data->map, data);
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == 124)
		data->player.angle_dir = 0;
	if (key == 123)
		data->player.angle_dir = 0;
	if (key == 13)
		data->player.walking_dir = 0;
	if (key == 1)
		data->player.walking_dir = 0;
	if (key == 2)
	{
		data->flag_dir = 0;
		data->player.walking_dir = 0;
	}
	if (key == 0)
	{
		data->flag_dir = 0;
		data->player.walking_dir = 0;
	}
	if (key == 53)
		exit(0);
	return (0);
}
