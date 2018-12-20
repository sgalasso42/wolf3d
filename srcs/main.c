/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:45:51 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 15:56:52 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_exit(t_data *data)
{
	SDL_FreeSurface(data->object[0].img_srf);
	SDL_FreeSurface(data->object[1].img_srf);
	SDL_FreeSurface(data->object[2].img_srf);
	SDL_FreeSurface(data->object[3].img_srf);
	SDL_DestroyRenderer(data->sdl.renderer);
	SDL_DestroyWindow(data->sdl.window);
	TTF_CloseFont(data->font);
	TTF_Quit();
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

static void		ft_make_frame(t_data *data)
{
	data->nb_frame++;
	data->time_last = clock();
	ft_rc_wolfcalc(data);
	if (data->gamemode == 1 || data->dev_mode == 1)
		ft_minimap(data);
	ft_set_interface(data);
	if (data->gamemode == 1 && data->setting == 0)
		ft_set_cursor(data);
	data->texture = SDL_CreateTextureFromSurface(
	data->sdl.renderer, data->surface);
	SDL_FreeSurface(data->surface);
	SDL_RenderCopy(data->sdl.renderer, data->texture, 0, 0);
	data->fps = 1000 / (clock() / 10000 - data->time_last / 10000);
	ft_set_infos(data);
}

static void		ft_game_loop(t_data *data)
{
	ft_make_frame(data);
	SDL_RenderPresent(data->sdl.renderer);
	while (1)
	{
		if (ft_get_events(data))
		{
			SDL_RenderClear(data->sdl.renderer);
			ft_make_frame(data);
			SDL_RenderPresent(data->sdl.renderer);
		}
		SDL_FlushEvent(SDL_KEYDOWN | SDL_KEYUP | SDL_MOUSEMOTION);
	}
}

int		main(int argc, char **argv)
{
	t_data			data;

	if (argc != 2)
		ft_arg_invalid();
	ft_init_data(argv[1], &data);
	ft_game_loop(&data);
	return (0);
}
