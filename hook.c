/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:34:11 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/09 05:09:38 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	d_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= data->width || \
	y >= data->height || x < 0 || y < 0)
		return ;
	dst = data->mlx_addr + (y * data->ll + \
	x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	clear_redraw(t_map *map, t_data *data)
{
	data->player.rotation_angle += data->player.angle_dir * \
	data->player.rotation_speed;
	data->player.rotation_angle = fmod(data->player.rotation_angle, 2 * M_PI);
	if (data->player.rotation_angle < 0)
		data->player.rotation_angle += 2 * M_PI;
	mlx_destroy_image(data->mlx, data->mlx_img);
	mlx_clear_window(data->mlx, data->mlx_win);
	draw(map, data, map->index);
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
	{
		destroy_img(data);
		return (free_map(data->map), free(data->textures), exit(0), 1);
	}
	clear_redraw(data->map, data);
	return (0);
}

void	destroy_img(t_data *data)
{
	if (data->mlx_img)
		mlx_destroy_image(data->mlx, data->mlx_img);
	if (data->textures[0].texture_image)
		mlx_destroy_image(data->mlx, data->textures[0].texture_image);
	if (data->textures[1].texture_image)
		mlx_destroy_image(data->mlx, data->textures[1].texture_image);
	if (data->textures[2].texture_image)
		mlx_destroy_image(data->mlx, data->textures[2].texture_image);
	if (data->textures[3].texture_image)
		mlx_destroy_image(data->mlx, data->textures[3].texture_image);
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
	return (0);
}
