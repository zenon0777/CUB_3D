/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:54:00 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/07 00:53:06 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include<stdio.h>
# include<unistd.h>
# include<math.h>
# include<stdbool.h>
# include<stdlib.h>
# include<fcntl.h>
# include"libft/libft.h"
# include<mlx.h>
# define TILE 20
# define HOR 1
# define VER 2

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_map
{
	int			file;
	const char	*file_name;
	char		*n_texture;
	char		*s_texture;
	char		*w_texture;
	char		*e_texture;
	char		**map_input;
	size_t		map_width;
	int			map_length;
	int			first;
	int			end;
	int			flagofdragon;
	int			no;
	int			so;
	int			ea;
	int			we;
	int			c;
	int			f;
	int			index;
	t_color		*f_color;
	t_color		*c_color;
}	t_map;

typedef struct textures
{
	int			t_bpp;
	int			t_ll;
	int			t_endian;
	char		*texture_add;
	void		*texture_image;
}	t_textures;

typedef struct player
{
	double	p_x;
	double	p_y;
	double	rotation_angle;
	double	rotation_speed;
	double	walking_dir;
	double	angle_dir;
	double	move_speed;
	double	fov;
}	t_player;

typedef struct data
{
	double		gridhor_y;
	double		gridhor_x;
	double		gridver_y;
	double		gridver_x;
	double		x_inc;
	double		y_inc;
	double		short_dis_x;
	double		short_dis_y;
	double		short_dis;
	double		projection_plane_dis;
	double		x;
	double		y;
	char		*mlx_addr;
	void		*mlx;
	void		*mlx_win;
	void		*mlx_img;
	int			img_width;
	int			img_height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			key;
	int			screen_width;
	int			screen_height;
	int			flag_dir;
	double		real_pwh;
	double		pwh;
	double		begin;
	t_player	player;
	t_map		*map;
	t_textures	*textures;
}	t_data;

bool			check_textures(t_map *map);
bool			check_map(t_map *map);
bool			check_extension(const char *file, int flag);
void			*ft_memmove(void *dst, const void *src, size_t n);
char			*get_next_line(int fd);
char			*ft_strjoin_freed(char const *s1, char const *s2);
size_t			ft_strlen(const char	*str);
bool			check_moji(t_map *map, int index);
void			rendering(t_map *map);
void			draw(t_map *map, t_data *data);
void			draw_line_dir(t_data *data, t_player *player);
void			cast_ray(t_data *data);
double			normalize_angle(double deg);
void			draw_view(t_data *data, t_player *player, double deg);
int				calc_dis(t_data *data);
int				short_dis(t_data *data, double hor_dis, double ver_dis);
void			d_mlx_put_pixel(t_data *data, int x, int y, int color);
void			rendering_wall(t_data *data, int colum, int flag);
void			draw(t_map *map, t_data *data);
void			floor_draw(t_data *data, int y, int mid_point);
void			celling_draw(t_data *data);
void			calc_nexthor_grid(t_data *data, double f_ray);
void			calc_nextver_grid(t_data *data, double f_ray);
void			sichoucu_hit(t_data *data, double deg);
void			orizontios_hit(t_data *data, double f_ray);
void			textures(t_textures *textures, double deg, int Hor_ver);
void			draw_player(t_data *data);
int				isplayer(t_data *data, char p, int flag);
void			cast_ray(t_data *data);
void			player_angle(t_data *data, t_map *map);
void			wall_coloision(t_data *data, double x1, double y1);
unsigned int	texture_mapping(t_data *data, int hor_ver, double y);
void			textures_img(t_data data);
int				key_release(int key, t_data *data);
int				key(int key, t_data *data);
void			clear_redraw(t_map *map, t_data *data);
#endif
