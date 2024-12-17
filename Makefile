NAME	:= cub3D

CC		:= cc

CFLAGS	:=  -Wall -Wextra  -I./inc -g -fsanitize=address
#-Werror

MFLAGS	:=	-framework OpenGL -framework AppKit -Lmlx -lmlx 

HEADER	:= ./inc/cub3d_parse.h 

LIBRARY	:= lib/libft.a

SRC		:=	parse/errors.c \
			parse/file_check.c \
			parse/tools.c \
			parse/map_check.c \
			parse/get_file_data.c \
			parse/fill_sp.c \
			parse.c \
			stuff/do_stuff.c \
			stuff/game_loop_stuff.c \
			stuff/pandoras_box.c \
			stuff/init_stuff.c \
			stuff/hookers.c \

OBG		:= $(SRC:.c=.o)

all	: $(NAME)

libft	:
	make -C lib

$(NAME) : $(OBG) libft
	 $(CC)  $(CFLAGS) $(MFLAGS) $(OBG) $(LIBRARY)  -o $(NAME)

%.o : %.c $(HEADER)
	 $(CC) $(CFLAGS) -Imlx -c $< -o $@

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

