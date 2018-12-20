# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaille <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 00:22:44 by abaille           #+#    #+#              #
#    Updated: 2018/12/20 19:42:17 by sgalasso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= wolf3d 

CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror -g #-fsanitize=address
LIBFT 		= ./libft

ID_UN 		= $(shell id -un)
SRC_PATH 	= ./srcs/
OBJ_PATH 	= ./objs/
INC_PATH	= ./includes/ \
			  ./libft/

INC_PATH	+= /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.8/include/ \
			   /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.8/include/SDL2/ \
			   /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.14/include/ \
			   /Users/$(ID_UN)/.brew/Cellar/sdl2_image/2.0.3/include/ \
			   /Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/2.0.2_3/include/ \

SRC_NAME 	= main.c \
			  ft_get_map.c \
			  ft_init_data.c \
			  ft_get_events.c \
			  ft_rc_wolfcalc.c \
			  ft_check_error.c \
			  ft_minimap.c \
			  ft_utils.c \
			  ft_set_infos.c \
			  ft_set_interface.c \

HED	= ./includes/wolf3d.h 

OBJ_NAME = $(SRC_NAME:.c=.o)
LSDL2 	 = -L/Users/$(ID_UN)/.brew/lib/ -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) \
	-L$(LIBFT) -lft $(INC) $(LSDL2)

$(OBJ) : $(HED) Makefile | $(OBJ_PATH)

$(OBJ_PATH) :
	mkdir objs

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	make -C $(LIBFT) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
