/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:56:04 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/12 11:20:03 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		ft_nbwords(char *line)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i])
			c++;
		i++;
	}
	return (c);
}

static void		ft_get_size_map(char *map, t_data *data)
{
	char	*line;
	int		fd;

	data->map_sz.w = 0;
	data->map_sz.h = 0;
	if ((fd = open(map, O_RDONLY)) == -1)
		exit(EXIT_FAILURE); // recup exit
	if (get_next_line(fd, &line) > 0)
		data->map_sz.w = ft_nbwords(line);
	data->map_sz.h++;
	free(line);
	while (get_next_line(fd, &line) > 0)
	{
		data->map_sz.h++;
		free(line);
	}
	close(fd);
}

static void		ft_parse_line(int index, char *line, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i])
			data->map[index][j++] = ft_atoi(&(line[i++]));
	}
}

void			ft_get_map(char *map, t_data *data)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	ft_get_size_map(map, data);
	if ((fd = open(map, O_RDONLY)) == -1)
		exit(EXIT_FAILURE); // recup exit
	if (!(data->map = (int **)(ft_memalloc(sizeof(int *) * (data->map_sz.h)))))
		exit(EXIT_FAILURE); // recup exit
	while (get_next_line(fd, &line) > 0)
	{
		if (!(data->map[i] = (int *)(ft_memalloc(sizeof(int) * (data->map_sz.w)))))
			exit(EXIT_FAILURE); // recup exit
		ft_parse_line(i, line, data);
		free(line);
		i++;
	}
	close(fd);
}
