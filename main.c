/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:50:21 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/09 02:35:14 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	open_file(t_map *map, const char *file)
{
	if (map->file > 0)
		close(map->file);
	map->file = open(file, O_RDONLY);
	if (map->file < 0)
		return (free_map(map), exit(1));
}

void	ft_init(t_map *map, const char *file)
{
	open_file(map, file);
	map->map_length = read_file(map->file);
	if (map->map_length == -1)
		return (close(map->file), free_map(map), exit(1));
	map->map_input = (char **)malloc(sizeof(char *) * (map->map_length + 1));
	if (!map->map_input)
		return (close(map->file), free_map(map), exit(1));
	open_file(map, file);
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

void	chart_store(t_map *map)
{
	int		i;

	i = 0;
	while (i < map->map_length)
	{
		map->map_input[i] = get_next_line(map->file);
		if (!map->map_input)
			return (free_map(map), exit(1));
		i++;
	}
	map->map_input[i] = NULL;
}

int	main(int ac, const char **av)
{
	t_map	*map;

	if (ac != 2)
		return (printf("Error\nbad arguments"), 1);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (printf("Error\nmem\n"), 1);
	map->f_color = (t_color *)malloc(sizeof(t_color));
	map->c_color = (t_color *)malloc(sizeof(t_color));
	if (!map->f_color)
		return (printf("Error\nmem"), free_map(map), 1);
	if (!map->c_color)
		return (printf("Error\nmem"), free_map(map), 1);
	if (check_extension(av[1], 0) == false)
		return (free_map(map), printf("Error\nextension\n"), 1);
	ft_init(map, av[1]);
	if (map->map_length <= 6)
		return (free_map(map), ft_putendl_fd("Error\ndragon_parser", 1), 1);
	chart_store(map);
	if (parse_chart(map) == false)
		return (free_map(map), ft_putendl_fd("Error\nchart_error", 1), 1);
	rendering(map);
	return (0);
}
