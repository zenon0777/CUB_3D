/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:33:57 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/07 01:15:16 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

void	textures(t_textures *textures, double deg, int Hor_ver)
{
	void	*img;

	img = NULL;
	if ((deg > 0 && deg < M_PI) && Hor_ver == HOR)
		img = textures[2].texture_image;
	else if ((deg > M_PI && deg < 2 * M_PI) && Hor_ver == HOR)
		img = textures[3].texture_image;
	else if ((deg < M_PI / 2 || deg > (3 * M_PI) / 2) && Hor_ver == VER)
		img = textures[0].texture_image;
	else if ((deg >= M_PI / 2 && deg <= (3 * M_PI) / 2) && Hor_ver == VER)
		img = textures[1].texture_image;
	textures->texture_add = mlx_get_data_addr(img, &textures->t_bpp, \
		&textures->t_ll, &textures->t_endian);
}

void	textures_img(t_data data)
{
	data.textures[0].texture_image = mlx_xpm_file_to_image(data.mlx, \
		"./textures/eastwall.xpm", &data.img_width, &data.img_height);
	data.textures[1].texture_image = mlx_xpm_file_to_image(data.mlx, \
		"./textures/3.xpm", &data.img_width, &data.img_height);
	data.textures[2].texture_image = mlx_xpm_file_to_image(data.mlx, \
		"./textures/northwall.xpm", &data.img_width, &data.img_height);
	data.textures[3].texture_image = mlx_xpm_file_to_image(data.mlx, \
		"./textures/southwall.xpm", &data.img_width, &data.img_height);
}

unsigned int	texture_mapping(t_data *data, int hor_ver, double y)
{
	int				offset;
	t_textures		*tex;
	unsigned int	color;
	char			*dst;
	double			y1;

	tex = data->textures;
	offset = 0;
	if (hor_ver == HOR)
		offset = fmod(data->short_dis_x, TILE);
	else if (hor_ver == VER)
		offset = fmod(data->short_dis_y, TILE);
	y1 = (y - data->begin) * (TILE / data->real_pwh);
	dst = tex->texture_add + ((int)fmod(y1, 20) * tex->t_ll + \
		(int)fmod(offset, 20) * (tex->t_bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}
