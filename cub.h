/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:54:00 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/09 04:40:42 by adaifi           ###   ########.fr       */
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
	int			bpp;
	int			ll;
	int			endian;
	int			key;
	int			width;
	int			height;
	int			flag_dir;
	double		real_pwh;
	double		pwh;
	double		begin;
	t_player	player;
	t_map		*map;
	t_textures	*textures;
}	t_data;

void			*ft_memmove(void *dst, const void *src, size_t n);
char			*get_next_line(int fd);
char			*ft_strjoin_freed(char const *s1, char const *s2);
size_t			ft_strlen(const char	*str);
void			d_free_2d(char **ptr);
int				dyo_dimen_size(char **tab);
int				column_calc(char *rgb);
char			*join_line(char *buff, char *line, int fd);
///parser
int				read_file(int fd);
bool			check_file(char *file);
void			get_width(t_map *map, int index);
void			line_edit(t_map *map, int i);
bool			check_textures(t_map *map);
bool			check_map(t_map *map);
bool			chroma(t_map *map, char **rgb);
bool			chroma_store(t_map *map, int *nb, char *rgb);
bool			we_ea(t_map *map, char **tab);
bool			so_no(t_map *map, char **tab);
bool			check_extension(const char *file, int flag);
bool			check_moji(t_map *map, int index);
bool			check_orozintios(t_map *map, int index);
bool			orizontios_itter(t_map *map, int i, int j);
bool			check_sichocu(t_map *map, int index);
bool			sichocu_itter(t_map *map, int i, int j);
bool			parse_dragons(t_map **map, char *line);
bool			parse_chart_lower(t_map *map, int index);
bool			parse_chart(t_map *map);
void			chart_store(t_map *map);
void			free_map(t_map *map);
void			open_file(t_map *map, const char *file);
/// rendering
void			cast_ray(t_data *data);
int				calc_dis(t_data *data);
void			d_mlx_put_pixel(t_data *data, int x, int y, int color);
void			draw_line_dir(t_data *data, t_player *player);
void			draw(t_map *map, t_data *data, int i);
void			draw_view(t_data *data, t_player *player, double deg);
double			normalize_angle(double deg);
void			rendering(t_map *map);
int				short_dis(t_data *data, double hor_dis, double ver_dis);
void			rendering_wall(t_data *data, int colum, int flag);
void			floor_draw(t_data *data, int y, int mid_point);
void			celling_draw(t_data *data);
bool			check_hor_hit(t_data *data, int i, int j, double f_ray);
bool			check_ver_hit(t_data *data, int i, int j, double deg);
void			calc_nexthor_grid(t_data *data, double f_ray);
void			calc_nextver_grid(t_data *data, double f_ray);
void			sichoucu_hit(t_data *data, double deg);
void			orizontios_hit(t_data *data, double f_ray);
void			textures(t_textures *textures, double deg, int Hor_ver);
void			draw_player(t_data *data);
int				isplayer(t_data *data, char p);
void			cast_ray(t_data *data);
void			player_angle(t_data *data, t_map *map);
void			wall_coloision(t_data *data, double x1, double y1);
unsigned int	texture_mapping(t_data *data, int hor_ver, double y);
void			textures_img(t_data data);
/// hook
int				key_release(int key, t_data *data);
int				key(int key, t_data *data);
void			clear_redraw(t_map *map, t_data *data);
void			destroy_img(t_data *data);
#endif
