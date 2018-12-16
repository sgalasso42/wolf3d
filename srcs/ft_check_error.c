/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 12:03:09 by jsauron           #+#    #+#             */
/*   Updated: 2018/12/16 13:14:09 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_err_malloc(void)
{
	ft_putstr(C_RED"Malloc failled\n"C_NONE);
	exit(EXIT_FAILURE);
}

void	ft_err_malloc_free(char *line, int fd)
{
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

void	ft_map_invalid_free(char *line, int fd)
{
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
	int c;

	i = 0;
	c = 0;
	while (line[i])
	{
	if (!(ft_isdigit(line[i]) || ft_isspace(line[i]) || line[i]  == ',') 
			|| c > 1)
	{
		free(line);
		close(fd);
		ft_map_invalid();
	}
	if (line[i] == '2')
		c++;
	i++;
	}
}

