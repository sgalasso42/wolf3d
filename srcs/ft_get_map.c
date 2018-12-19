/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:56:04 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/19 14:48:01 by sgalasso         ###   ########.fr       */
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
		ft_map_invalid();
	if (get_next_line(fd, &line) > 0)
		data->map_sz.w = ft_nbwords(line);
	else
		ft_map_invalid();
	data->map_sz.h++;
	free(line);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_nbwords(line) != data->map_sz.w)
			ft_map_invalid_free(line, fd, data);
		data->map_sz.h++;
		free(line);
	}
	close(fd);
}

static void		ft_parse_line(int fd, int index, char *line, t_data *data)
{
	int		val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	val = 0;
	data->map[index][j++] = 3;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i])
		{
			val = ft_atoi(&(line[i]));
			if (val == 2 && data->player.position.x != -1)
				ft_map_invalid_free(line, fd, data);
			else if (val == 2)
			{
				data->player.position.x = j + 0.5;
				data->player.position.y = index + 0.5;
			}
			data->map[index][j++] = val;
			i++;
		}
	}
	data->map[index][j] = 3;
}

void			ft_get_map(char *map, t_data *data)
{
	char	*line;
	int		fd;
	int		i;
	int		j;

	i = 1;
	ft_get_size_map(map, data);
	if ((fd = open(map, O_RDONLY)) == -1)
		ft_map_invalid(); // recup exit

	if (!(data->map =
	(int **)(ft_memalloc(sizeof(int *) * (data->map_sz.h + 2)))))
		ft_err_malloc(); // recup exit
	if (!(data->map[0] =
	(int *)(ft_memalloc(sizeof(int) * (data->map_sz.w + 2)))))
		exit(EXIT_FAILURE); // recup exit
	j = 0;
	while (j < data->map_sz.w + 2)
		data->map[0][j++] = 3;

	while (i - 1 < data->map_sz.h)
	{
		get_next_line(fd, &line);
		ft_check_valid_map(line, fd);
		if (!(data->map[i] =
		(int *)(ft_memalloc(sizeof(int) * (data->map_sz.w + 2)))))
			ft_err_malloc_free(line, fd, data); // recup exit
		ft_parse_line(fd, i, line, data);
		free(line);
		i++;
	}
	if (!(data->map[i] =
	(int *)(ft_memalloc(sizeof(int) * (data->map_sz.w + 2)))))
		exit(EXIT_FAILURE); // recup exit
	j = 0;
	while (j < data->map_sz.w + 2)
		data->map[i][j++] = 3;
	data->map_sz.w += 2;
	data->map_sz.h += 2;
	if (data->player.position.x == -1)
		ft_map_invalid_free(line, fd, data);
	close(fd);
}
