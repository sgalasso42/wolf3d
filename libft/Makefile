NAME = libft.a

SRCS =	ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_atoi.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strdup.c \
		ft_strlen.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strstr.c \
		ft_strnstr.c \
		ft_strcpy.c \
		ft_strncpy.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_strclr.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strsplit.c \
		ft_itoa.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putendl.c \
		ft_putnbr.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		lib_extra/get_next_line.c \
		lib_math/ft_sq.c \
		lib_math/ft_pow.c \
		lib_math/ft_sqrt.c \
		lib_math/ft_abs.c \

OBJS =	$(SRCS:.c=.o)

INCLUDES = ./

all:	$(NAME)

$(NAME):    $(OBJS)
	ar rc $(NAME) $(OBJS) && ranlib $(NAME)

%.o:	%.c $(INCLUDES)libft.h Makefile
	gcc -Wall -Wextra -Werror -o $@ -c $< -I $(INCLUDES)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:		fclean all

.PHONY : all clean fclean re
