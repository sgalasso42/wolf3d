/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:46:24 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/12 11:14:08 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdio.h>

# include "libft.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>

# define WIN_W 1800
# define WIN_H 1000

typedef struct s_size	t_size;
typedef struct s_sdl	t_sdl;
typedef struct s_data	t_data;

struct					s_size
{
	int					h;
	int					w;
};

struct					s_sdl
{
	SDL_Event			event;
	SDL_Window      	*window;
	SDL_Renderer    	*renderer;
};

struct					s_data
{
	t_sdl				sdl;
	TTF_Font			*font;
	int					**map;	// map
	t_size				map_sz;	// map size
};

void					ft_exit(t_data *data);

void					ft_init_data(char *map, t_data *data);
void					ft_get_map(char *map, t_data *data);

int						ft_get_events(t_data *data);

#endif
