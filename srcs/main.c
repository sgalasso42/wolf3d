/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:45:51 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/10 19:07:44 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ft_make_frame(t_data *data)
{
	data->nb_frame++;
	data->time_last = clock();

	ft_rc_wolfcalc(data);
	ft_set_interface(data);
	data->fps = 1000 / (clock() / 10000 - data->time_last / 10000);
	ft_set_infos(data);

	data->texture = SDL_CreateTextureFromSurface(
	data->sdl.renderer, data->surface);
	lt_release(data->surface);
	if ((SDL_RenderCopy(data->sdl.renderer, data->texture, 0, 0)) != 0)
		ft_err_exit("wolf3d: error: RenderCopy failure", data);
	SDL_DestroyTexture(data->texture);
	SDL_RenderPresent(data->sdl.renderer);
}

static void		ft_game_loop(t_data *data)
{
	ft_make_frame(data);
	while (1)
	{
		if (ft_get_events(data))
		{
			if ((SDL_RenderClear(data->sdl.renderer)) != 0)
				ft_err_exit("wolf3d: error: RenderClear failure", data);
			ft_make_frame(data);
		}
		SDL_FlushEvent(SDL_KEYDOWN | SDL_MOUSEMOTION);
	}
}

int				main(int argc, char **argv)
{
	t_data			data;

	if (argc != 2)
	{
		ft_putendl_fd("[->] usage: ./wolf3d [map]", 2);
		ft_err_exit("[->] README for more informations", &data);
	}
	ft_init_data(argv[1], &data);
	ft_game_loop(&data);
	return (0);
}
