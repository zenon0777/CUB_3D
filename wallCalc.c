/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallCalc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:20:30 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/06 17:09:20 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

void	calc_nexthor_grid(t_data *data, double f_ray)
{
	data->y_inc = TILE;
	data->x_inc = (double)TILE / tan(f_ray);
	data->gridhor_y = floor(data->player.p_y / (double)TILE) * (double)TILE;
	if (f_ray > 0 && f_ray < M_PI)
		data->gridhor_y += (double)TILE;
	if (f_ray >= M_PI && f_ray <= 2 * M_PI)
	{
		data->gridhor_y -= 0.00001;
		data->y_inc *= -1;
	}
	data->gridhor_x = data->player.p_x - \
		((data->player.p_y - data->gridhor_y) / tan(f_ray));
	if ((f_ray <= M_PI / 2 || f_ray >= (3 * M_PI) / 2) && data->x_inc < 0)
		data->x_inc *= -1;
	else if ((f_ray > M_PI / 2 && f_ray < 3 * (M_PI / 2)) && data->x_inc > 0)
		data->x_inc *= -1;
}

void	orizontios_hit(t_data *data, double f_ray)
{
	int		i;
	int		j;

	calc_nexthor_grid(data, f_ray);
	while (data->gridhor_x <= (data->screen_width * TILE) && data->gridhor_x > 0 && data->gridhor_y <= (data->screen_height * TILE) && data->gridhor_y > 0)
	{
		i = (int)floor(data->gridhor_y / (double)TILE) + data->map->index;
		j = (int)floor(data->gridhor_x / (double)TILE);
		if (i >= data->map->map_length || j >= (int)data->map->map_width)
		{
			data->gridhor_x = data->player.p_x;
			data->gridhor_y = data->player.p_y;
			return ;
		}
		if (data->map->map_input[i][j] == '1')
		{
			if (f_ray >= M_PI && f_ray <= 2 * M_PI)
				data->gridhor_y += 0.00001;
			return ;
		}
		data->gridhor_x += data->x_inc;
		data->gridhor_y += data->y_inc;
	}
	data->gridhor_x = data->player.p_x;
	data->gridhor_y = data->player.p_y;
}

void	calc_nextver_grid(t_data *data, double f_ray)
{
	data->x_inc = (double)TILE;
	data->y_inc = (double)TILE * tan(f_ray);
	data->gridver_x = floor(data->player.p_x / (double)TILE) * (double)TILE;
	if (f_ray < M_PI / 2 || f_ray > (3 * M_PI) / 2)
		data->gridver_x += (double)TILE;
	if (f_ray >= M_PI / 2 && f_ray <= (3 * M_PI) / 2)
	{
		data->x_inc *= -1;
		data->gridver_x -= 0.00001;
	}
	data->gridver_y = data->player.p_y - \
		((data->player.p_x - data->gridver_x) * tan(f_ray));
	if ((f_ray >= M_PI && f_ray <= 2 * M_PI) && data->y_inc > 0)
		data->y_inc *= -1;
	else if ((f_ray > 0 && f_ray < M_PI) && data->y_inc < 0)
		data->y_inc *= -1;
}

void	sichoucu_hit(t_data *data, double deg)
{
	int		i;
	int		j;

	calc_nextver_grid(data, deg);
	while (data->gridver_x <= (data->screen_width * TILE) && data->gridver_x > 0 && data->gridver_y <= (data->screen_height * TILE) && data->gridver_y > 0)
	{
		i = (int)floor(data->gridver_y / (double)TILE) + data->map->index;
		j = (int)floor(data->gridver_x / (double)TILE);
		if (i >= data->map->map_length || j >= (int)data->map->map_width)
		{
			data->gridver_x = data->player.p_x;
			data->gridver_y = data->player.p_y;
			return ;
		}
		else if (data->map->map_input[i][j] == '1')
		{
			if (deg >= M_PI / 2 && deg <= (3 * M_PI) / 2)
				data->gridver_x += 0.00001;
			return ;
		}
		data->gridver_x += data->x_inc;
		data->gridver_y += data->y_inc;
	}
	data->gridver_x = data->player.p_x;
	data->gridver_y = data->player.p_y;
}
