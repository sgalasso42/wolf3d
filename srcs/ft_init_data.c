/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:49:26 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 21:55:56 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_sdl_err_exit(char *msg, t_data *data)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	ft_putendl(SDL_GetError());
	ft_putendl(TTF_GetError());
	if (data->sdl.renderer)
		SDL_DestroyRenderer(data->sdl.renderer);
	if (data->sdl.window)
		SDL_DestroyWindow(data->sdl.window);
	if (data->font)
		TTF_CloseFont(data->font);
	TTF_Quit();
	SDL_Quit();
	ft_err_exit(0);
}

void	ft_init_sdl(t_data *data)
{
	data->sdl.window = 0;
	data->sdl.renderer = 0;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_sdl_err_exit(0, data);
	if (TTF_Init() < 0)
		ft_sdl_err_exit(0, data);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	if (!(data->sdl.window = SDL_CreateWindow("WOLF_3D",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0)))
		ft_sdl_err_exit(0, data);
	if (!(data->sdl.renderer = SDL_CreateRenderer(data->sdl.window, -1,
	SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED)))
		ft_sdl_err_exit(0, data);
	if (SDL_SetRenderDrawBlendMode(data->sdl.renderer, SDL_BLENDMODE_BLEND) < 0)
		ft_sdl_err_exit(0, data);
	SDL_RaiseWindow(data->sdl.window);
}

void	ft_init_fonts(t_data *data)
{
	if (!(data->font = TTF_OpenFont("ressources/fonts/Arial.ttf", 100)))
		ft_sdl_err_exit("wolf3d: error: font failure", data);
}

void	ft_make_texture(t_data *data)
{
	if (!(data->object[0].img_srf = IMG_Load("ressources/img/crate.png")))
		ft_failure_exit("wolf3d: error: bad textures", data);
	if (!(data->object[1].img_srf = IMG_Load("ressources/img/stone.png")))
		ft_failure_exit("wolf3d: error: bad textures", data);
	if (!(data->object[2].img_srf = IMG_Load("ressources/img/BrownFloor.png")))
		ft_failure_exit("wolf3d: error: bad textures", data);
	if (!(data->object[3].img_srf = IMG_Load("ressources/img/unnamed.png")))
		ft_failure_exit("wolf3d: error: bad textures", data);
}

void	ft_init_data(char *map, t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->player.position.x = -1;
	data->player.position.y = -1;
	data->player.direction = 90;
	data->player.sensibility = 3;
	data->player.speed = 0.12;
	data->minimap.mnp_size = 20;
	ft_init_sdl(data);
	ft_init_fonts(data);
	ft_get_map(map, data);
	ft_make_texture(data);
	// demo ---------------------
	int i = -1;
	int	j = -1;
	while (++i < data->map_sz.h)
	{
		j = -1;
		while (++j < data->map_sz.w)
			printf("%d ", data->map[i][j]);
		printf("\n");
	}
	// --------------------------
}
