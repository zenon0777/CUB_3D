#include"cub.h"

void	draw_view(t_data *data, t_player *player, double deg)
{
	double	x;
	double	y;
	int		step;
	int		i;

	x = data->player.p_x + cos(deg) * 30;
	y = data->player.p_y + sin(deg) * 30;
	i = 0;
	double dx = x - player->p_x;
	double dy = y - player->p_y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	double x_inc = dx / step;
	double y_inc = dy / step;
	x = player->p_x;
	y = player->p_y;
	while (i < step)
	{
		d_mlx_put_pixel(data, x, y, 0xFFFFFF);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

void	draw_line_dir(t_data *data, t_player *player)
{
	double	x;
	double	y;
	int		step;
	int		i;

	x = data->short_dis_x;
	y = data->short_dis_y;
	i = 0;
	double dx = x - player->p_x;
	double dy = y - player->p_y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	double x_inc = dx / step;
	double y_inc = dy / step;
	x = player->p_x;
	y = player->p_y;
	while (i < step)
	{
		d_mlx_put_pixel(data, x, y, 0xFF0000);
		x += x_inc;
		y += y_inc;
		i++;
	}
}
