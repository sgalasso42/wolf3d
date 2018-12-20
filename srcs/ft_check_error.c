/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 12:03:09 by jsauron           #+#    #+#             */
/*   Updated: 2018/12/20 19:28:42 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_err_exit(char *msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void		ft_close_exit(char *msg, t_data *data)
{
	SDL_DestroyRenderer(data->sdl.renderer);
	SDL_DestroyWindow(data->sdl.window);
	TTF_CloseFont(data->font);
	TTF_Quit();
	SDL_Quit();
	ft_err_exit(msg);
}

void		ft_freemap_exit(char *msg, t_data *data)
{
	int		i;

	i = 0;
	while (i < data->map_sz.h)
	{
		ft_memdel((void *)(&(data->map[i])));
		i++;
	}
	ft_memdel((void *)(data->map));
	ft_close_exit(msg, data);
}

void		ft_failure_exit(char *msg, t_data *data)
{
	if (data->object[0].img_srf)
		SDL_FreeSurface(data->object[0].img_srf);
	if (data->object[1].img_srf)
		SDL_FreeSurface(data->object[1].img_srf);
	if (data->object[2].img_srf)
		SDL_FreeSurface(data->object[2].img_srf);
	if (data->object[3].img_srf)
		SDL_FreeSurface(data->object[3].img_srf);
	ft_freemap_exit(msg, data);
}
