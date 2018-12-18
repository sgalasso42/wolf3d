/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:46:24 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/18 18:57:55 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdio.h>

# include "libft.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <pthread.h>

# define C_NONE         "\033[0m"
# define C_BOLD         "\033[1m"
# define C_BLACK        "\033[30m"
# define C_RED          "\033[31m"
# define C_GREEN        "\033[32m"
# define C_BROWN        "\033[33m"
# define C_BLUE         "\033[34m"
# define C_MAGENTA      "\033[35m"
# define C_CYAN         "\033[36m"
# define C_GRAY         "\033[37m"

# define WIN_H 700
# define WIN_W 1000
# define BLOC_SIZE 50
# define DIST_SCREEN 277

# define ZOOM_P 1.1
# define ZOOM_L 0.9

typedef struct s_limit	t_limit;
typedef struct s_pos	t_pos;
typedef struct s_size	t_size;
typedef struct s_coef	t_coef;
typedef struct s_ray	t_ray;
typedef struct s_thread	t_thread;
typedef struct s_sdl	t_sdl;
typedef struct s_player	t_player;
typedef struct s_data	t_data;

struct					s_limit
{
	int					t;
	int					b;
	int					l;
	int					r;
};

struct					s_pos
{
	double				x;
	double				y;
};

struct					s_size
{
	int					h;
	int					w;
};

struct					s_coef
{
	int					x;
	int					y;
};

struct					s_ray
{
	double				angle_d;
	double				distance;
	double				dist_minimap;
	double				wall_top;
	double				wall_bot;
	double				wall_color;
	int					color;
};

struct					s_thread
{
	pthread_t			th;
	t_data				*data;
	int					x_start;
	t_ray				ray[WIN_W / 8];
};

struct					s_sdl
{
	SDL_Event			event;
	SDL_Window      	*window;
	SDL_Renderer    	*renderer;
};

struct					s_player
{
	t_pos				position;
	double				direction;
	int					cam_height;
	int					visual_field;
};

struct					s_data
{
	t_sdl				sdl;
	TTF_Font			*font;
	int					**map;	// map
	t_size				map_sz;	// map size
	t_player			player;	// position camera
	t_thread			thread[8];
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	double				mnp_size;
};

void					ft_init_data(char *map, t_data *data);
void					ft_get_map(char *map, t_data *data);

SDL_Color				ft_hex_to_rgb(int hexa); // to remove si non utilise
void					ft_setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void					ft_exit(t_data *data);
int						ft_is_inwall(t_pos *pos, t_data *data);
int						ft_get_events(t_data *data);
void					ft_rc_wolfcalc(t_data *data);

void					ft_minimap(t_data *data);

void					ft_err_malloc(void);
void					ft_err_malloc_free(char *line, int fd, t_data *data);
void					ft_arg_invalid(void);
void					ft_map_invalid(void);
void					ft_map_invalid_free(char *line, int fd, t_data *data);
int						ft_isspace(int c);
void					ft_check_valid_map(char *line, int fd);

#endif
