/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 00:38:04 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/07 01:46:15 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

bool	check_extension(const char *file, int flag)
{
	int	length;

	length = ft_strlen(file);
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

int	read_file(int fd)
{
	int		size;
	char	*line;

	size= 0;
	line = get_next_line(fd);
	while(line)
	{
		free(line);
		line = get_next_line(fd);
		size++;
	}
	free(line);
	return (size);
}

bool	check_file(char *file)
{
	if (check_extension(file, 1) == true)
		if (access(file, F_OK | R_OK) != 0)
			return (false);
	return (true);
}

void	get_width(t_map *map, int index)
{
	int	i;

	i = index;
	while (map->map_input[i])
	{
		if (ft_strlen(map->map_input[i]) > map->map_width)
			map->map_width = ft_strlen(map->map_input[i]);
		i++;
	}
}

bool	chroma(t_map *map, char **rgb)
{
	char	**tab;
	int		nb[3];
	int		i;
	int		j;

	i = -1;
	tab = ft_split(rgb[1], ',');
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			if (ft_isdigit(tab[i][j]) == 0)
				return (d_free_2d(tab), false);
		nb[i] = ft_atoi(tab[i]);
		if (nb[i] < 0 && nb[i] > 255)
			return (d_free_2d(rgb), false);
	}
	if (!ft_strcmp(rgb[0], "F"))
	{
		map->f_color->red = nb[0];
		map->f_color->green = nb[1];
		map->f_color->blue = nb[2];
		return (map->flagofdragon += 1, d_free_2d(rgb), true);
	}
	map->c_color->red = nb[0];
	map->c_color->green = nb[1];
	map->c_color->blue = nb[2];
	return (map->flagofdragon += 1, d_free_2d(rgb), true);
}

bool	parse_dragons(t_map **map, char* line)
{
	char	**tab;

	line = ft_strtrim(line, " \t");
	if (line[0] == '\n' || line[0] == '\0')
		return (true);
	tab = ft_split(line, ' ');
	if (!ft_strcmp(tab[0], "NO") && (*map)->no == 0 && check_file(tab[1]))
	{
		(*map)->n_texture = tab[1];
		(*map)->no = 1;
		(*map)->flagofdragon += 1;
		return (true);
	}
	if (!ft_strcmp(tab[0], "SO") && (*map)->so == 0 && check_file(tab[1]))
	{
		(*map)->s_texture = tab[1];
		(*map)->so = 1;
		(*map)->flagofdragon += 1;
		return (true);
	}
	if (!ft_strcmp(tab[0], "WE") && (*map)->we == 0 && check_file(tab[1]))
	{
		(*map)->w_texture = tab[1];
		(*map)->we = 1;
		(*map)->flagofdragon += 1;
		return (true);
	}
	if (!ft_strcmp(tab[0], "EA") && (*map)->ea == 0 && check_file(tab[1]))
	{
		(*map)->e_texture = tab[1];
		(*map)->ea = 1;
		(*map)->flagofdragon += 1;
		return (true);
	}
	if (!ft_strcmp(tab[0], "F"))
		if (chroma(*map, tab) == true)
			return (true);
	if (!ft_strcmp(tab[0], "C"))
		if (chroma(*map, tab) == true)
			return (true);
	return (write(1, "Error\n", 7),  d_free_2d(tab), false);
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

bool	check_moji(t_map *map, int i)
{
	int	j;
	int	player;

	player = 0;
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

void	ft_init(t_map *map, const char *file)
{
	map->file = open(file, O_RDONLY);
	map->map_length = read_file(map->file);
	map->file = open(file, O_RDONLY);
	map->map_input = (char **)malloc(sizeof(char *) * (map->map_length + 1));
	if (!map->map_input)
		return (close(map->file), free(map), exit(1));
	map->flagofdragon = 0;
	map->first = 0;
	map->map_width = 0;
	map->no = 0;
	map->so = 0;
	map->ea = 0;
	map->we = 0;
	map->n_texture = NULL;
	map->s_texture = NULL;
	map->w_texture = NULL;
	map->e_texture = NULL;
	map->c_color->red = 0;
	map->c_color->green = 0;
	map->c_color->blue = 0;
	map->f_color->red = 0;
	map->f_color->green = 0;
	map->f_color->blue = 0;
}

int	main(int ac, const char **av)
{
	t_map *map;
	int i;

	i = 0;
	if(ac != 2)
		return (printf("Error"), 1);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (printf("Error-mem\n"), 1);
	map->f_color = (t_color *)malloc(sizeof(t_color));
	map->c_color = (t_color *)malloc(sizeof(t_color));
	if (!map->f_color)
		return (printf("Error\n"), free(map), 1);
	if (!map->c_color)
		return (printf("Error\n"), free(map), free(map->c_color), 1);
	if (check_extension(av[1], 0) == false)
		return(free(map), printf("Error-extension\n"), 1);
	ft_init(map, av[1]);
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
