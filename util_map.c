/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoshin <seoshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:53:32 by seoshin           #+#    #+#             */
/*   Updated: 2023/01/26 18:48:40 by seoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_square_check(t_game	*g, char *fname)
{
	int		fd;
	char	*line;

	fd = open(fname, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		destroy_map("Error\nCheck map\n");
	g->col = ft_strlen(line) - 1;
	while (line)
	{
		free(line);
		g->row++;
		line = get_next_line(fd);
		if (line && check_len(line) != g->col)
		{
			free(line);
			destroy_map("Error\nCheck map\n");
		}
	}
	close(fd);
}

char	**read_map(t_game *g, char *fname)
{
	int		fd;
	int		idx;
	char	*line;

	map_square_check(g, fname);
	fd = open(fname, O_RDONLY);
	g->map = (char **)malloc(sizeof(char *) * g->row);
	if (!g->map)
		destroy_map("Error\nCheck map\n");
	idx = 0;
	while (idx < g->row)
	{
		g->map[idx] = (char *)malloc(g->col + 2);
		if (!g->map[idx])
		{
			free_some(g, idx - 1);
			exit(1);
		}
		line = get_next_line(fd);
		ft_strcpy(g->map[idx], line);
		free(line);
		idx++;
	}
	close(fd);
	return (g->map);
}

void	map_error_check(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < g->row)
	{
		j = 0;
		while (j < g->col)
		{
			if ((i == 0 || j == 0 || i == g->row - 1 || j == g->col - 1)
				&& (g->map[i][j] != '1'))
			{
				free_all(g);
				destroy_map("Error\nCheck map\n");
			}
			check_char(g, g->map[i][j]);
			j++;
		}
		i++;
	}
	if (g->collectible < 1 || g->exit != 1 || g->start != 1)
	{
		free_all(g);
		destroy_map("Error\nCheck map\n");
	}
}

int	check_len(char *line)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != '\n')
			len++;
		i++;
	}
	return (len);
}

void	check_char(t_game *g, char c)
{
	if (c == 'C')
		g->collectible++;
	else if (c == 'E')
		g->exit++;
	else if (c == 'P')
		g->start++;
	else if (c != '0' && c != '1')
	{
		free_all(g);
		destroy_map("Error\nCheck map\n");
	}
}
