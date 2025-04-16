NAME	:= cub3D

BONUS	:= cub3D_bonus

CC		:= cc

CFLAGS	:=  -Wall -Wextra -Werror -I./inc -g -fsanitize=address

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
			stuff/rays_go_brrr.c \
			stuff/tex_loading.c \
			stuff/wall_textures.c \
			stuff/niminap.c

BNS		:= 	bonus/parse/errors_bonus.c \
			bonus/parse/file_check_bonus.c \
			bonus/parse/tools_bonus.c \
			bonus/parse/map_check_bonus.c \
			bonus/parse/get_file_data_bonus.c \
			bonus/parse/fill_sp_bonus.c \
			bonus/main_bonus.c \
			bonus/stuff/controls_bonus.c \
			bonus/stuff/game_loop_bonus.c \
			bonus/stuff/init_stuff_bonus.c \
			bonus/stuff/hookers_bonus.c \
			bonus/stuff/rays_go_brrr_bonus.c \
			bonus/stuff/tex_loading_bonus.c \
			bonus/stuff/wall_textures_bonus.c \
			bonus/stuff/niminap_bonus.c
			
BOBG	:= $(BNS:.c=.o)
		
OBG		:= $(SRC:.c=.o)

all	: $(NAME)

libft	:
	make -C lib

$(NAME) : $(OBG) libft
	 $(CC)  $(CFLAGS) $(OBG) $(MINUX) $(LIBRARY) -o $(NAME)

$(BONUS) : $(BOBG) libft ./inc/cub3d_bonus.h
	 $(CC)  $(CFLAGS) $(BOBG) $(MINUX) $(LIBRARY) -o $(BONUS)

%_bonus.o : %_bonus.c ./inc/cub3d_bonus.h
	$(CC) $(CFLAGS)  -I/usr/include -Imlx_linux -O3 -c $< -o $@

%.o : %.c $(HEADER)
	 $(CC) $(CFLAGS)  -I/usr/include -Imlx_linux -O3 -c $< -o $@

bonus : $(BONUS)

clean :
	make clean -C lib
	rm -rf $(OBG) $(BOBG)

fclean:	clean
	make fclean -C lib
	rm -rf $(NAME) $(BONUS)

re:	fclean all

push: fclean
	git add .
	git commit -m "$(filter-out $@, $(MAKECMDGOALS))"
	git push

commit:
	git add .
	git commit -m "$(filter-out $@, $(MAKECMDGOALS))"

.PHONY:	all fclean re clean

