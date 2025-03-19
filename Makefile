NAME	:= cub3D

CC		:= cc

CFLAGS	:=  -Wall -Wextra  -I./inc 
#-g -fsanitize=address
#-Werror

MFLAGS	:=	-framework OpenGL -framework AppKit -Lmlx -lmlx 

MINUX	:= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

HEADER	:= ./inc/cub3d_parse.h 

LIBRARY	:= lib/libft.a

SRC		:=	parse/errors.c \
			parse/file_check.c \
			parse/tools.c \
			parse/map_check.c \
			parse/get_file_data.c \
			parse/fill_sp.c \
			parse.c \
			stuff/controls.c \
			stuff/game_loop.c \
			stuff/init_stuff.c \
			stuff/hookers.c \
			stuff/drawing.c \
			stuff/tex_loading.c \

OBG		:= $(SRC:.c=.o)

all	: $(NAME)

libft	:
	make -C lib

$(NAME) : $(OBG) libft
	 $(CC)  $(CFLAGS) $(OBG) $(MINUX) $(LIBRARY) -o $(NAME)

%.o : %.c $(HEADER)
	 $(CC) $(CFLAGS)  -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	make clean -C lib
	rm -rf $(OBG)

fclean:	clean
	make fclean -C lib
	rm -rf $(NAME)

re:	fclean all

push: fclean
	git add .
	git commit -m "$(filter-out $@, $(MAKECMDGOALS))"
	git push

commit:
	git add .
	git commit -m "$(filter-out $@, $(MAKECMDGOALS))"

.PHONY:	all fclean re clean

