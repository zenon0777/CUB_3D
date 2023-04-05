/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 00:38:04 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/05 04:34:07 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

bool	check_extension(const char* file, int flag)
{
	int length = ft_strlen(file);
	if (flag == 0)
	{
		if (file[length - 1] == 'b')
			if (file[length - 2] == 'u')
				if (file[length - 3] == 'c')
					if (file[length - 4] == '.')
						return true;
	}
	else if (flag == 1)
	{
		length = ft_strlen(file);
		write(1, &length, 2);
		if(file[length - 1] == 'm')
			if(file[length - 2] == 'p')
				if(file[length - 3] == 'x')
					if(file[length - 4] == '.')
						return true;
	}
	return false;
}

void	d_free_2d(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

int read_file(int fd)
{
	int size= 0;
	char *line = get_next_line(fd);
	while(line)
	{
		free(line);
		line = get_next_line(fd);
		size++;
	}
	free(line);
	return size;
}

bool check_file(char *file)
{
	 // just for the rendering without texture we assum it true.
	if (check_extension(file, 1) == true)
		if (access(file, F_OK | R_OK) == 0)
			return false;
	return true;
}

void    get_width(t_map *map, int index)
{
	int i = index;

	while (map->map_input[i])
	{
		if (ft_strlen(map->map_input[i]) > map->map_width)
			map->map_width = ft_strlen(map->map_input[i]);
		i++;
	}
}

bool	chroma(t_map *map, char **rgb)
{
	char **tab;
	int nb[3];
	int i;
	int j;

	i = -1;
	tab = ft_split(rgb[1], ',');
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			if (ft_isdigit(tab[i][j]) == 0)
				return (d_free_2d(tab), ft_putendl_fd("err", 1), false);
		nb[i] = ft_atoi(tab[i]);
		if(nb[i] < 0 && nb[i] > 255)
			return (d_free_2d(rgb), false);
	}
	if (!ft_strcmp(rgb[0], "F"))
	{
		map->F_color->red = nb[0];
		map->F_color->green = nb[1];
		map->F_color->blue = nb[2];
		return (map->flagofdragon += 1, d_free_2d(rgb), true);
	}
	map->C_color->red = nb[0];
	map->C_color->green = nb[1];
	map->C_color->blue = nb[2];
	return (map->flagofdragon += 1, d_free_2d(rgb), true);
}

bool	parse_dragons(t_map **map, char* line)
{
	line = ft_strtrim(line, " \t");
	if (line[0] == '\n' || line[0] == '\0')
		return (true);
	char **tab = ft_split(line, ' ');
	if (!ft_strcmp(tab[0], "NO") && (*map)->NO == 0 && check_file(tab[1]))
	{
		(*map)->N_texture = tab[1];
		(*map)->NO = 1;
		(*map)->flagofdragon += 1;
		return (true);
	}
	if (!ft_strcmp(tab[0], "SO") && (*map)->SO == 0 && check_file(tab[1]))
	{
		(*map)->S_texture = tab[1];
		(*map)->SO = 1;
		(*map)->flagofdragon += 1;
		return (true);
	}
	if (!ft_strcmp(tab[0], "WE") && (*map)->WE == 0 && check_file(tab[1]))
	{
		(*map)->W_texture = tab[1];
		(*map)->WE = 1;
		(*map)->flagofdragon += 1;
		return (true);
	}
	if (!ft_strcmp(tab[0], "EA") && (*map)->EA == 0 && check_file(tab[1]))
	{
		(*map)->E_texture = tab[1];
		(*map)->EA = 1;
		(*map)->flagofdragon += 1;
		return ( true);
	}
	if (!ft_strcmp(tab[0], "F") || !ft_strcmp(tab[0], "C"))
	{
		if (chroma(*map, tab))
			return (true);
	}
	return (write(1, "Error => texture\n", 18),  d_free_2d(tab), false);
}

void	line_edit(t_map *map, int index)
{
	size_t length = 0;
	while (map->map_input[index])
	{
		length = ft_strlen(map->map_input[index]);
		while (length < map->map_width)
		{
			map->map_input[index] = ft_strjoin_freed(map->map_input[index], " ");
			length++;
		}
		index++;
	}
}

bool	check_sichocu(t_map *map, int index)
{
	int	j;
	int	i;
	int	length;

	j = 0;
	length = map->map_length;
	while (j < (int)map->map_width)
	{
		i = index;
		while(i < length - 1)
		{
			if (i == index && map->map_input[i][j] != ' ')
			{
				if (map->map_input[i][j] != '1')
					return false;
			}
			else if (i != index && map->map_input[i][j] != ' ')
			{
				if (map->map_input[i - 1][j] == ' ' || map->map_input[i + 1][j] == ' ')
				{
					if (map->map_input[i][j] != '1')
						return false;
				}
			}
			else if (i == length - 1)
				if (map->map_input[i][j] != ' ' && map->map_input[i][j] != '1')
					return false;
			i++;
		}
		j++;
	}
	return true;
}

bool	check_orozintios(t_map *map, int index)
{
	int	j;
	int	i;
	int	length;

	j = 0;
	length = map->map_length;
	i = index;
	while (i < length)
	{
		j = 0;
		while(j < (int)map->map_width)
		{
			if (j == 0 && map->map_input[i][j] != ' ')
			{
				if (map->map_input[i][j] != '1')
					return false;
			}
			else if (j != 0 && map->map_input[i][j] != ' ')
			{
				if (map->map_input[i][j - 1] == ' ' || map->map_input[i][j + 1] == ' ')
				{
					if (map->map_input[i][j] != '1')
						return false;
				}
			}
			else if (j == (int)map->map_width - 1)
				if (map->map_input[i][j] != ' ' && map->map_input[i][j] != '1')
					return false;
			j++;
		}
		i++;
	}
	return true;
}

bool	check_moji(t_map *map, int index)
{
	int j;
	int i;
	int player;

	player = 0;
	i = index;
	while (i < map->map_length)
	{
		j = 0;
		while (map->map_input[i][j] != '\0')
		{

			if (map->map_input[i][j] != 'N' && map->map_input[i][j] != ' ' &&
				map->map_input[i][j] != '1' && map->map_input[i][j] != '0' &&
				map->map_input[i][j] != 'W' && map->map_input[i][j] != 'E' &&
				map->map_input[i][j] != 'S')
					return (false);
			if (map->map_input[i][j] == 'N' || map->map_input[i][j] == 'W' ||
				map->map_input[i][j] == 'E' || map->map_input[i][j] == 'S')
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		return (false);
	return (true);
}

bool	parse_chart_lower(t_map *map, int index)
{
	get_width(map, index);
	if (check_moji(map, index) == false)
		return (false);
	line_edit(map, index);
	if (check_sichocu(map, index) == false)
		return false;
	if (check_orozintios(map, index) == false)
		return false;
	return true;
}

bool	parse_chart(t_map *map)
{
	int i;

	i = 0;
	while (map->map_input[i])
	{
		if (map->flagofdragon >= 6)
			break ;
		if (map->flagofdragon < 6 && (map->map_input[i][0] == '0' || map->map_input[i][0] == '1'))
			return false;
		if (map->flagofdragon < 6)
		{
			if (parse_dragons(&map, map->map_input[i]) == false)
			return (true);
		}
		i++;
	}
	map->index = i;
	if (parse_chart_lower(map, i) == false)
		return false;
	rendering(map);
	return true;
}

int main(int ac, const char **av)
{
	t_map *map;
	int i;

	i = 0;
	if(ac != 2)
		exit(1);
	{
		map = (t_map *)malloc(sizeof(t_map));
		map->F_color = (t_color *)malloc(sizeof(t_color));
		map->C_color = (t_color *)malloc(sizeof(t_color));
		if (!map)
			return (printf("Error-mem\n"), 1);
	}
	if (check_extension(av[1], 0) == false)
		return(free(map), printf("Error-extension\n"), 1);
	map->file_name = av[1];
	map->file = open(map->file_name, O_RDONLY);
	map->map_length = read_file(map->file);
	map->file = open(map->file_name, O_RDONLY);
	map->map_input = (char **)malloc(sizeof(char *) * (map->map_length + 1));
	map->flagofdragon = 0;
	map->first = 0;
	map->map_width = 0;
	map->NO = 0;
	map->SO = 0;
	map->EA = 0;
	map->WE = 0;
	map->N_texture = NULL;
	map->S_texture = NULL;
	map->W_texture = NULL;
	map->E_texture = NULL;
	map->C_color->red = 0;
	map->C_color->green = 0;
	map->C_color->blue = 0;
	map->F_color->red = 0;
	map->F_color->green = 0;
	map->F_color->blue = 0;
	if (map->map_length <= 6)
		return (ft_putendl_fd("ERROR", 1), 1);
	while(i < map->map_length)
	{
		map->map_input[i] = get_next_line(map->file);
		i++;
	}
	map->map_input[i] = NULL;
	if (parse_chart(map) == false)
		return (ft_putendl_fd("ERROR", 1), 1);
	return 0;
}
