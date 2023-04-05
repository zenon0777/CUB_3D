#include <mlx.h>
#include<stdlib.h>
#include "cub.h"


void d_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char *dst;

	if (x >= data->screen_width || y >= data->screen_height || x < 0 || y < 0)
		return ;
	dst = data->mlx_addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

void	clear_redraw(t_map *map, t_data *data)
{
	data->player.rotation_angle += data->player.angle_dir  * data->player.rotation_speed;
	if (data->player.rotation_angle < 0)
		data->player.rotation_angle += 2 * M_PI;
	mlx_destroy_image(data->mlx, data->mlx_img);
	draw(map, data);
}

int key(int key, t_data *data)
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
	return 0;
}

int key_release(int key, t_data *data)
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
	return 0;
}

void	draw_player(t_data *data, int color)
{
	double	rad;
	double	step;
	int	i;
	int	j;
	double	x1;
	double	y1;

	(void)color;
	rad = 5;
	x1 = data->player.p_x;
	y1 = data->player.p_y;
	step = data->player.walking_dir * data->player.move_speed;
	if (data->flag_dir == 1)
	{
		x1 += step * sin(data->player.rotation_angle);
		y1 -= step * cos(data->player.rotation_angle);
	}
	else
	{
		x1 += step * cos(data->player.rotation_angle);
		y1 += step * sin(data->player.rotation_angle);
	}
	i = (int)floor(y1 / (double)TILE) + data->map->index;
	j = (int)floor(x1 / (double)TILE);
	int	i1 = (int)floor(data->player.p_y / (double)TILE) + data->map->index;
	int j1 = (int)floor(data->player.p_x / (double)TILE);
	if (data->map->map_input[i1][j] != '1' && data->map->map_input[i][j1] != '1'
		&& data->map->map_input[i][j] != '1')
	{
		data->player.p_x = x1;
		data->player.p_y = y1;
	}
	cast_Ray(data);
	data->player.p_x -= data->x + TILE / 2;
	data->player.p_y -= data->y + TILE / 2;
}

void	floor_celling_draw(t_data *data)
{
	int		F_color;
	int		C_color;
	int		mid_point;
	double	x;
	double	y;

	C_color = (data->map->C_color->red << 16) + (data->map->C_color->green << 8) + data->map->C_color->blue;
	F_color = (data->map->F_color->red << 16) + (data->map->F_color->green << 8) + data->map->F_color->blue;
	mid_point = data->screen_height / 2;
	y = 0;
	while (y <= mid_point)
	{
		x = 0;
		while (x < data->screen_width)
		{
			d_mlx_put_pixel(data, x, y, C_color);
			x++;
		}
		y++;
	}
	while (y > mid_point && y < data->screen_height)
	{
		x = 0;
		while (x < data->screen_width)
		{
			d_mlx_put_pixel(data, x, y, F_color);
			x++;
		}
		y++;
	}
}

void	orizontios_hit(t_data *data, double f_ray)
{
	double	Y_inc;
	double	X_inc;
	int		i;
	int		j;

	Y_inc = (double)TILE;
	X_inc = (double)TILE / tan(f_ray);
	data->GridHor_y = floor(data->player.p_y / (double)TILE) * (double)TILE;
	if (f_ray > 0 && f_ray < M_PI)
		data->GridHor_y += (double)TILE;
	if (f_ray >= M_PI && f_ray <= 2 * M_PI)
	{
		data->GridHor_y -= 0.00001;
		Y_inc *= -1;
	}
	data->GridHor_x = data->player.p_x - ((data->player.p_y - data->GridHor_y) / tan(f_ray));
	if ((f_ray <= M_PI / 2 || f_ray >= (3 * M_PI) / 2) && X_inc < 0)
		X_inc *= -1;
	else if ((f_ray > M_PI / 2 && f_ray < 3 * (M_PI / 2)) && X_inc > 0)
		X_inc *= -1;
	while ((int)data->GridHor_x <= data->screen_width && (int)data->GridHor_x > 0 && (int)data->GridHor_y <= data->screen_height && (int)data->GridHor_y > 0)
	{
		i = (int)floor(data->GridHor_y / (double)TILE) + data->map->index;
		j = (int)floor(data->GridHor_x / (double)TILE);
		if (i >= data->map->map_length || j >= (int)data->map->map_width)
		{
			data->GridHor_x = data->player.p_x;
			data->GridHor_y = data->player.p_y;
			return ;
		}
		if (data->map->map_input[i][j] == '1')
		{
			if (f_ray >= M_PI && f_ray <= 2 * M_PI)
				data->GridHor_y += 0.00001;
			return ;
		}
		data->GridHor_x += X_inc;
		data->GridHor_y += Y_inc;
	}
	data->GridHor_x = data->player.p_x;
	data->GridHor_y = data->player.p_y;
}

void	sichoucu_hit(t_data *data, double f_ray)
{
	double	Y_inc;
	double	X_inc;
	int		i;
	int		j;

	X_inc = (double)TILE;
	Y_inc = (double)TILE * tan(f_ray);
	data->GridVer_x = floor(data->player.p_x / (double)TILE) * (double)TILE;
	if (f_ray < M_PI / 2 || f_ray > (3 * M_PI) / 2)
		data->GridVer_x += (double)TILE;
	if (f_ray >= M_PI / 2 && f_ray <= (3 * M_PI) / 2)
	{
		X_inc *= -1;
		data->GridVer_x -= 0.00001; // get the exact hit point by adding 0.00001
	}
	data->GridVer_y = data->player.p_y - ((data->player.p_x - data->GridVer_x) * tan(f_ray));
	if ((f_ray >= M_PI && f_ray <= 2 * M_PI) && Y_inc > 0)
		Y_inc *= -1;
	else if ((f_ray > 0 && f_ray < M_PI) && Y_inc < 0)
		Y_inc *= -1;
	while ((int)data->GridVer_x <= data->screen_width && (int)data->GridVer_x > 0 && (int)data->GridVer_y <= data->screen_height && (int)data->GridVer_y > 0)
	{
		i = (int)floor(data->GridVer_y / (double)TILE) + data->map->index;
		j = (int)floor(data->GridVer_x / (double)TILE);
		if (i >= data->map->map_length || j >= (int)data->map->map_width)
		{
			data->GridVer_x = data->player.p_x;
			data->GridVer_y = data->player.p_y;
			return ;
		}
		else if (data->map->map_input[i][j] == '1')
		{
			if (f_ray >= M_PI / 2 && f_ray <= (3 * M_PI) / 2)
				data->GridVer_x += 0.00001;
			return ;
		}
		data->GridVer_x += X_inc;
		data->GridVer_y += Y_inc;
	}
	data->GridVer_x = data->player.p_x;
	data->GridVer_y = data->player.p_y;
}

//bool	check_wall(t_data *data, double Grid_x, double Grid_y)
//{
//	int		i;
//	int		j;

//	while ((int)data->GridVer_x <= data->screen_width && (int)data->GridVer_x > 0 && (int)data->GridVer_y <= data->screen_height && (int)data->GridVer_y > 0)
//	{
//		i = (int)floor(data->GridVer_y / (double)TILE) + data->map->index;
//		j = (int)floor(data->GridVer_x / (double)TILE);
//		if (i >= data->map->map_length || j >= (int)data->map->map_width)
//		{
//			data->GridVer_x = data->player.p_x;
//			data->GridVer_y = data->player.p_y;
//			return ;
//		}
//		else if (data->map->map_input[i][j] == '1')
//		{
//			if (f_ray >= M_PI / 2 && f_ray <= (3 * M_PI) / 2)
//				data->GridVer_x += 0.00001;
//			return true;
//		}
//		data->GridVer_x += X_inc;
//		data->GridVer_y += Y_inc;
//	}
//	return false;
//}

unsigned int	textures(t_data *data, int hor_ver, double y, double begin, double PWH)
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
	y1 = (y - begin) * (TILE / PWH);
	dst = tex->texture_add + ((int)fmod(y1, 64) * tex->t_line_length + (int)fmod(offset, 64) * (tex->t_bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return color;
}

void	cast_Ray(t_data *data)
{
	double	colum;
	double	ang_inc;
	double	f_ray;
	int		flag;

	ang_inc = data->player.FOV / data->screen_width;
	f_ray = data->player.rotation_angle - (data->player.FOV / 2);
	data->projection_plane_dis = (data->screen_width / 2) / tan(data->player.FOV / 2);
	colum = 0;
	while (colum < data->screen_width)
	{
		f_ray = normalize_angle(f_ray);
		orizontios_hit(data, f_ray);
		sichoucu_hit(data, f_ray);
		flag = calc_dis(data);
		data->short_dis *= cos(data->player.rotation_angle - f_ray);
		rendering_wall(data, colum, flag);
		f_ray += ang_inc;
		colum++;
	}
}

void	rendering_wall(t_data *data, int colum, int flag)
{
	double			Projected_Wall_height;
	double			real_PWH;
	double			i;
	double			j;
	unsigned int	color;

	if ((real_PWH = ((double)TILE / data->short_dis) * data->projection_plane_dis) > data->screen_height)
		Projected_Wall_height = data->screen_height;
	else
		Projected_Wall_height = real_PWH;
	i = colum;
	j = (data->screen_height / 2) - (Projected_Wall_height / 2);
	while (j < Projected_Wall_height + ((data->screen_height / 2) - (Projected_Wall_height / 2)))
	{
		color = textures(data, flag, j, ((data->screen_height / 2) - (Projected_Wall_height / 2)), real_PWH);
		d_mlx_put_pixel(data, i, j, color);
		j++;
	}
}

int	calc_dis(t_data *data)
{
	double	Hor_dis;
	double	Ver_dis;

	Hor_dis = sqrt((data->player.p_x - data->GridHor_x) * (data->player.p_x - data->GridHor_x ) +
		(data->player.p_y - data->GridHor_y) * (data->player.p_y - data->GridHor_y));
	Ver_dis = sqrt((data->player.p_x - data->GridVer_x) * (data->player.p_x - data->GridVer_x) +
		(data->player.p_y - data->GridVer_y) * (data->player.p_y - data->GridVer_y));
	if (data->player.p_x == data->GridVer_x)
	{
		data->short_dis_x = data->GridHor_x;
		data->short_dis_y = data->GridHor_y;
		data->short_dis = Hor_dis;
		return HOR;
	}
	else if (data->player.p_x == data->GridHor_x)
	{
		data->short_dis_x = data->GridVer_x;
		data->short_dis_y = data->GridVer_y;
		data->short_dis = Ver_dis;
		return VER;
	}
	else if (Hor_dis <= Ver_dis)
	{
		data->short_dis_x = data->GridHor_x;
		data->short_dis_y = data->GridHor_y;
		data->short_dis = Hor_dis;
		return HOR;
	}
	else if (Hor_dis > Ver_dis)
	{
		data->short_dis_x = data->GridVer_x;
		data->short_dis_y = data->GridVer_y;
		data->short_dis = Ver_dis;
		return VER;
	}
	return 3;
}

double	normalize_angle(double deg)
{
	deg = fmod(deg, (2 * M_PI));
	if (deg < 0)
		deg += (2 * M_PI);
	return deg;
}

void	draw(t_map *map, t_data *data)
{
	int	i;
	int	j;

	i = map->index;
	data->mlx_img = mlx_new_image(data->mlx, data->screen_width, data->screen_height);
	data->mlx_addr = mlx_get_data_addr(data->mlx_img, &data->bits_per_pixel, &data->line_length, &data->endian);
	floor_celling_draw(data);
	while (i < map->map_length)
	{
		j = 0;
		while (j < (int)map->map_width)
		{
			data->x = j * TILE;
			data->y = (i - 12) * TILE;
			if (map->map_input[i][j] == 'N')
			{
				data->player.p_x += data->x + TILE / 2;
				data->player.p_y += data->y + TILE / 2;
				draw_player(data, 0xFF0000);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->mlx_img, 1, 1);
}

void rendering(t_map *map)
{
	t_data data;

	data.x = 0;
	data.y = 0;
	data.map = map;
	data.textures = (t_textures*)malloc(sizeof(t_textures));
	data.img_height = map->map_length * TILE;
	data.img_width = map->map_width * TILE;
	data.screen_height = map->map_length * TILE;
	data.screen_width = map->map_width * TILE;
	data.player.angle_dir = 0;
	data.player.walking_dir = 0;
	data.player.move_speed = 10;
	data.flag_dir = 0;
	data.player.FOV = 60 * (M_PI /180);
	data.player.rotation_speed = 8 * (M_PI / 180);
	data.player.rotation_angle = M_PI / 2;
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.screen_width, data.screen_height, "mlx");
	data.textures->texture_image = mlx_xpm_file_to_image(data.mlx, "./textures/6.xpm", &data.img_width, &data.img_height);
	data.textures->texture_add = mlx_get_data_addr(data.textures->texture_image, &data.textures->t_bits_per_pixel, &data.textures->t_line_length, &data.textures->t_endian);
	draw(map, &data);
	mlx_hook(data.mlx_win, 02, 1L<<0, key, &data);
	mlx_hook(data.mlx_win, 03, 1L<<1, key_release, &data);
	mlx_loop(data.mlx);
}
