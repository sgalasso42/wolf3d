/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 12:03:09 by jsauron           #+#    #+#             */
/*   Updated: 2018/12/16 14:28:19 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_err_malloc(void)
{
	ft_putstr(C_RED"Malloc failled\n"C_NONE);
	exit(EXIT_FAILURE);
}

void	ft_free_map(t_data *data)
{
	int i;

	i = 0;
	while (i < data->map_sz.h)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}

void	ft_err_malloc_free(char *line, int fd, t_data *data)
{
	ft_free_map(data);
	free(line);
	close(fd);
	ft_err_malloc();
}

void	ft_arg_invalid(void)
{
	ft_putstr(C_GREEN"./wolf3d <map>\n"C_NONE);
	exit(EXIT_FAILURE);
}

void	ft_map_invalid(void)
{
	ft_putstr(C_RED"Map invalid\n"C_NONE);
	exit(EXIT_FAILURE);
}

void	ft_map_invalid_free(char *line, int fd, t_data *data)
{
	ft_free_map(data);
	if (line)
		free(line);
	close(fd);
	ft_putstr(C_RED"Map invalid\n"C_NONE);
	exit(EXIT_FAILURE);
}

int		ft_isspace(int c)
{
	return (c == ' ' || c == '\v' || c == '\t'
			|| c == '\n' || c == '\r' || c == '\f');
}

void	ft_check_valid_map(char *line, int fd)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!(ft_isdigit(line[i]) || ft_isspace(line[i]) || line[i]  == ','))
		{
			free(line);
			close(fd);
			ft_map_invalid();
		}
	i++;
	}
}

