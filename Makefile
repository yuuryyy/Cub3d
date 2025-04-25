NAME	:= cub3D

BONUS	:= cub3D_bonus

CC		:= cc

CFLAGS	:=  -Wall -Wextra -Werror -I./inc 

MFLAGS	:=	-framework OpenGL -framework AppKit -Lmlx -lmlx 

MINUX	:= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

HEADER	:= ./inc/cub3d_parse.h 

LIBRARY	:= lib/libft.a

SRC		:=	Mandatory/parse/errors.c \
			Mandatory/parse/file_check.c \
			Mandatory/parse/tools.c \
			Mandatory/parse/map_check.c \
			Mandatory/parse/get_file_data.c \
			Mandatory/parse/fill_sp.c \
			Mandatory/cub.c \
			Mandatory/src/controls.c \
			Mandatory/src/game_loop.c \
			Mandatory/src/init_stuff.c \
			Mandatory/src/hookers.c \
			Mandatory/src/rays_go_brrr.c \
			Mandatory/src/tex_loading.c \
			Mandatory/src/wall_textures.c \

BNS		:= 	Bonus/parse/errors_bonus.c \
			Bonus/parse/file_check_bonus.c \
			Bonus/parse/tools_bonus.c \
			Bonus/parse/map_check_bonus.c \
			Bonus/parse/get_file_data_bonus.c \
			Bonus/parse/fill_sp_bonus.c \
			Bonus/main_bonus.c \
			Bonus/src/controls_bonus.c \
			Bonus/src/game_loop_bonus.c \
			Bonus/src/init_stuff_bonus.c \
			Bonus/src/hookers_bonus.c \
			Bonus/src/rays_go_brrr_bonus.c \
			Bonus/src/tex_loading_bonus.c \
			Bonus/src/wall_textures_bonus.c \
			Bonus/src/niminap_bonus.c	\
			Bonus/src/sprites_bonus.c \
			Bonus/src/more_rays_bonus.c
			
BOBG	:= $(BNS:.c=.o)
		
OBG		:= $(SRC:.c=.o)

all	: $(NAME)

libft	:
	make -C lib

$(NAME) : $(OBG) libft
	 $(CC)  $(CFLAGS) $(OBG) $(MINUX) $(LIBRARY) -o $(NAME)

$(BONUS) : $(BOBG) libft ./inc/cub3d_bonus.h
	 $(CC)  $(CFLAGS) $(BOBG) $(MINUX) $(LIBRARY) -o $(BONUS)

%_bonus.o : %_bonus.c ./inc/cub3d_bonus.h ./inc/g_header.h
	$(CC) $(CFLAGS)  -I/usr/include -Imlx_linux -O3 -c $< -o $@

%.o : %.c $(HEADER) ./inc/g_header.h
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

