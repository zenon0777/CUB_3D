/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:09:02 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/09 02:02:04 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

bool	we_ea(t_map *map, char **tab)
{
	if (!ft_strcmp(tab[0], "WE") && map->we == 0 && check_file(tab[1]))
	{
		map->w_texture = tab[1];
		map->we = 1;
		map->flagofdragon += 1;
		return (true);
	}
	if (!ft_strcmp(tab[0], "EA") && map->ea == 0 && check_file(tab[1]))
	{
		map->e_texture = tab[1];
		map->ea = 1;
		map->flagofdragon += 1;
		return (true);
	}
	return (false);
}

bool	so_no(t_map *map, char **tab)
{
	if (!ft_strcmp(tab[0], "NO") && map->no == 0 && check_file(tab[1]))
	{
		map->n_texture = tab[1];
		map->no = 1;
		map->flagofdragon += 1;
		return (true);
	}
	if (!ft_strcmp(tab[0], "SO") && map->so == 0 && check_file(tab[1]))
	{
		map->s_texture = tab[1];
		map->so = 1;
		map->flagofdragon += 1;
		return (true);
	}
	return (false);
}

bool	parse_dragons(t_map **map, char *line)
{
	char	**tab;

	line = ft_strtrim(line, " \t");
	if (!line)
		return (free_map(*map), exit(1), 0);
	if (line[0] == '\n' || line[0] == '\0')
		return (free(line), true);
	tab = ft_split(line, ' ');
	if (!tab)
		return (free(line), free_map(*map), 1);
	if (so_no(*map, tab) == true)
		return (d_free_2d(tab), free(line), true);
	else if (we_ea(*map, tab) == true)
		return (d_free_2d(tab), free(line), true);
	else if (!ft_strcmp(tab[0], "F"))
		if (chroma(*map, tab) == true)
			return (free(line), d_free_2d(tab), true);
	if (!ft_strcmp(tab[0], "C"))
		if (chroma(*map, tab) == true)
			return (free(line), d_free_2d(tab), true);
	return (free(line), d_free_2d(tab), false);
}

bool	chroma(t_map *map, char **rgb)
{
	char	**tab;
	int		nb[3];
	int		i;
	int		j;

	i = -1;
	if (column_calc(rgb[1]) > 2 || column_calc(rgb[1]) < 2)
		return (false);
	tab = ft_split(rgb[1], ',');
	if (!tab)
		return (free_map(map), d_free_2d(rgb), 0);
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			if (ft_isdigit(tab[i][j]) == 0)
				return (d_free_2d(tab), false);
		nb[i] = ft_atoi(tab[i]);
		if (nb[i] < 0 && nb[i] > 255)
			return (d_free_2d(tab), false);
	}
	if (chroma_store(map, nb, rgb[0]) == true)
		return (d_free_2d(tab), true);
	return (d_free_2d(tab), false);
}

bool	chroma_store(t_map *map, int *nb, char *rgb)
{
	if (!ft_strcmp(rgb, "F"))
	{
		map->f_color->red = nb[0];
		map->f_color->green = nb[1];
		map->f_color->blue = nb[2];
		map->flagofdragon += 1;
		return (true);
	}
	else if (!ft_strcmp(rgb, "C"))
	{
		map->c_color->red = nb[0];
		map->c_color->green = nb[1];
		map->c_color->blue = nb[2];
		map->flagofdragon += 1;
		return (true);
	}
	return (false);
}
