/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:56:04 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 19:19:17 by sgalasso         ###   ########.fr       */
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

static int		ft_check_map(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int		ft_get_size_map(char *map, t_data *data)
{
	char	*line;
	int		fd;

	data->map_sz.w = 0;
	data->map_sz.h = 0;
	if ((fd = open(map, O_RDONLY)) == -1)
		return (0);
	if (get_next_line(fd, &line) > 0)
		data->map_sz.w = ft_nbwords(line);
	else
	{
		close(fd);
		return (0);
	}
	data->map_sz.h++;
	free(line);
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_check_map(line))
		{
			free(line);
			return (0);
		}
		if (ft_nbwords(line) != data->map_sz.w)
		{
			free(line);
			return (0);
		}
		data->map_sz.h++;
		free(line);
	}
	close(fd);
	return (1);
}

static int		ft_parse_line(int index, char *line, t_data *data)
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
				return (0);
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
	return (1);
}

void			ft_get_map(char *map, t_data *data)
{
	char	*line;
	int		fd;
	int		i;
	int		j;

	i = 1;
	if (!(ft_get_size_map(map, data)))
		ft_close_exit("wolf3d: error: bad map", data);
	if ((fd = open(map, O_RDONLY)) == -1)
		ft_close_exit("wolf3d: error: can't open the map", data);

	if (!(data->map = (int **)(ft_memalloc(sizeof(int *) * (data->map_sz.h + 2)))))
	{
		close(fd);
		ft_close_exit("wolf3d: error: out of memory", data);
	}
	if (!(data->map[0] = (int *)(ft_memalloc(sizeof(int) * (data->map_sz.w + 2)))))
	{
		close(fd);
		ft_memdel((void *)(&data->map));
		ft_close_exit("wolf3d: error: out of memory", data);
	}
	j = 0;
	while (j < data->map_sz.w + 2)
		data->map[0][j++] = 3;


	while (i - 1 < data->map_sz.h)
	{
		if ((get_next_line(fd, &line)) == -1)
		{
			close(fd);
			ft_freemap_exit("wolf3d: error: gnl error", data);
		}
		if (!(data->map[i] =
		(int *)(ft_memalloc(sizeof(int) * (data->map_sz.w + 2)))))
		{
			close(fd);
			ft_freemap_exit("wolf3d: error: out of memory", data);
		}
		if (!(ft_parse_line(i, line, data)))
		{
			close(fd);
			ft_freemap_exit("wolf3d: error: out of memory", data);
		}
		free(line);
		i++;
	}
	if (!(data->map[i] =
	(int *)(ft_memalloc(sizeof(int) * (data->map_sz.w + 2)))))
	{
		close(fd);
		ft_freemap_exit("wolf3d: error: out of memory", data);
	}
	j = 0;
	while (j < data->map_sz.w + 2)
		data->map[i][j++] = 3;
	data->map_sz.w += 2;
	data->map_sz.h += 2;
	if (data->player.position.x == -1)
	{
		close(fd);
		ft_freemap_exit("wolf3d: error: spawn", data);
	}
	close(fd);
}
