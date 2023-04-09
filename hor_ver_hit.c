/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hor_ver_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:29:03 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/08 20:30:03 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	check_hor_hit(t_data *data, int i, int j, double f_ray)
{
	if (i >= data->map->map_length || j >= (int)data->map->map_width)
	{
		data->gridhor_x = data->player.p_x;
		data->gridhor_y = data->player.p_y;
		return (true);
	}
	if (data->map->map_input[i][j] == '1')
	{
		if (f_ray >= M_PI && f_ray <= 2 * M_PI)
			data->gridhor_y += 0.00001;
		return (true);
	}
	return (false);
}

bool	check_ver_hit(t_data *data, int i, int j, double deg)
{
	if (i >= data->map->map_length || j >= (int)data->map->map_width)
	{
		data->gridver_x = data->player.p_x;
		data->gridver_y = data->player.p_y;
		return (true);
	}
	else if (data->map->map_input[i][j] == '1')
	{
		if (deg >= M_PI / 2 && deg <= (3 * M_PI) / 2)
			data->gridver_x += 0.00001;
		return (true);
	}
	return (false);
}
