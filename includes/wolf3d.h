/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:46:24 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 23:17:16 by sgalasso         ###   ########.fr       */
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
# include <time.h>

# define H_GREEN		0x00FF00FF
# define H_RED			0xFF0000FF

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
# define DIST_SCREEN 900
# define NB_RAY 125

# define ZOOM_P 1.1
# define ZOOM_L 0.9

typedef struct s_limit	t_limit;
typedef struct s_pos	t_pos;
typedef struct s_size	t_size;
typedef struct s_vec	t_vec;
typedef struct s_coef	t_coef;
typedef struct s_ray	t_ray;
typedef struct s_thread	t_thread;
typedef struct s_object	t_object;
typedef struct s_sdl	t_sdl;
typedef struct s_player	t_player;
typedef struct s_mnmap	t_mnmap;
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

struct					s_vec
{
	t_pos				a;
	t_pos				b;
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

struct					s_sdl
{
	SDL_Event			event;
	SDL_Window      	*window;
	SDL_Renderer    	*renderer;
};
 
struct					s_ray
{
	int					x;		// intersection x
	int					y;		// intersection y
	int					axis;	// axe d'intersection
	double				angle_d;
	double				distance;
	double				dist_minimap;
	double				wall_top;
	double				wall_bot;
	double				wall_color; // to remove if not use
	Uint32				color; // to remove if not use
};

struct					s_thread
{
	pthread_t			th;
	t_data				*data;
	int					x_start;
	t_ray				ray[NB_RAY];
};

struct					s_object
{
	SDL_Surface			*img_srf;
};

struct					s_player
{
	t_pos				position;
	double				direction;
	int					cam_height;
	int					visual_field;
	int					sensibility;
	double				speed;
};

struct					s_mnmap
{
	double				mnp_size;
	t_pos				origin;
	t_limit				limit;
	t_size				map_size;
	t_pos				pos_play;
	t_pos				centre;
	t_pos				diff;
};

struct					s_data
{
	t_sdl				sdl;
	TTF_Font			*font;
	int					**map;
	t_object			object[4];
	t_size				map_sz;
	t_player			player;
	t_thread			thread[8];
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	t_mnmap				minimap;
	int					lightshade;
	int					gamemode;
	int					setting;
	int					dev_mode;
	t_coef				mouse;
	Uint32				time_last;
	int					nb_frame;
	int					fps;
};

void					ft_init_data(char *map, t_data *data);
void					ft_get_map(char *map, t_data *data);

double					ft_pythagore(int a, int b);
void					draw_line(t_data *data, t_vec *vec,
						Uint32 color, t_limit *limit);
void					ft_draw_rect(SDL_Rect rect, Uint32 color,
						t_limit *limit, t_data *data);
void					ft_draw_border(SDL_Rect rect, Uint32 color,
						t_data *data);
SDL_Color				ft_hex_to_rgb(int hexa);
void					ft_setpixel(SDL_Surface *surface,
						int x, int y, Uint32 pixel);
Uint32					ft_getpixel(SDL_Surface *surface, int x, int y);
void    				ft_set_string(SDL_Rect rect, char *text,
						SDL_Color color, t_data *data);
Uint32					ft_light_shade(double distance, Uint32 color);
void					ft_set_cursor(t_data *data);
SDL_Color				ft_set_color(t_data *data, int i);

void					ft_exit(t_data *data);
void					ft_err_exit(char *msg);
void					ft_close_exit(char *msg, t_data *data);
void					ft_freemap_exit(char *msg, t_data *data);
void					ft_failure_exit(char *msg, t_data *data);
void					ft_fdclose_exit(int fd, int free,
						char *msg, t_data *data);

int						ft_is_inwall(t_pos *pos, t_data *data);
int						ft_get_events(t_data *data);
void					ft_movement_plus(double angle_r, t_data *data);
void					ft_movement_minus(double angle_r, t_data *data);
int						ft_keyboard1(t_data *data);
int						ft_keyboard2(t_data *data);
int						ft_movement_normal(const Uint8 *state, t_data *data);
int						ft_rotation_normal(const Uint8 *state, t_data *data);
int						ft_movement_gaming(const Uint8 *state, t_data *data);
int						ft_lateral_gaming(const Uint8 *state, t_data *data);
int						ft_mouse_motion(t_data *data);

void					ft_rc_wolfcalc(t_data *data);
void					ft_minimap(t_data *data);
void					ft_set_infos(t_data *data);
void					ft_set_interface(t_data *data);
void					ft_set_config(t_data *data);
void					ft_set_menu_config(t_data *data);
void					ft_dev_mode(t_data *data);

#endif
