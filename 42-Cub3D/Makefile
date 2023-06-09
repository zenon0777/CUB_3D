# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfritz <jfritz@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 16:37:58 by jfritz            #+#    #+#              #
#    Updated: 2022/04/13 17:10:10 by jfritz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Conditional
GET_OS := $(shell uname -s)

ifeq ($(GET_OS), Darwin)
	OS			=		macOS
	mlxpath		=		./minilibx_macos
else
	OS			=		Linux
	mlxpath		=		./minilibx_linux
endif

# Color
Set_Color		=		\033[0m						# Text Reset
Red				=		\033[0;31m					# Red
Green			=		\033[0;32m					# Green
Yellow			=		\033[0;33m					# Yellow
Cyan			=		\033[0;36m					# Cyan

CC = gcc

NAME = cub3D

ENTRY = ./src/main.c

PARSING =	./src/parsing/identifiers.c \
			./src/parsing/lst.c \
			./src/parsing/map.c \
			./src/parsing/parser.c \
			./src/parsing/spawn_player.c \
			./src/parsing/spawn_player_direction.c \
			./src/parsing/rgb_helper.c \
			./src/parsing/map_checking_helper.c

GNL		=	./src/gnl/get_next_line.c \
			./src/gnl/get_next_line_utils.c

UTILS =		./src/utils/build_charmap.c \
			./src/utils/put_pixel.c \
			./src/utils/create_vector2.c \
			./src/utils/ternary_helper.c \
			./src/utils/exit_error.c

CONTROLS = ./src/controls/keyhandler.c

CLEARDATA =	./src/clear_data/clear_data.c

RENDERING =	./src/rendering/render_preparing.c \
			./src/rendering/render_walls.c \
			./src/rendering/draw_line_color.c \
			./src/textures/shading.c \
			./src/rendering/render_wall_helper.c \
			./src/rendering/mlx_helper.c

RENDERING_BONUS =	./bonus/render_preparing_bonus.c \
			./src/rendering/render_walls.c \
			./src/rendering/draw_line_color.c \
			./src/textures/shading.c \
			./src/rendering/render_wall_helper.c \
			./src/rendering/mlx_helper.c

TEXTURES =	./src/textures/textures.c \
			./src/textures/new_texture.c \
			./src/textures/fill_floor_ceiling.c \
			./src/textures/get_texture_direction.c

CACHE	=	./src/cache/player_cache.c

MINIMAP	=	./src/minimap/minimap.c

MOVEMENT	=	./src/movement/movement.c \
				./src/movement/rotation.c \
				./src/movement/mouse_handler.c

SRCS = $(PARSING) $(CACHE) $(MOVEMENT) $(MINIMAP) $(RENDERING) $(TEXTURES) $(CONTROLS) $(CLEARDATA) $(GNL) $(UTILS) $(ENTRY)

SRCS_BONUS = $(PARSING) $(CACHE) $(MOVEMENT) $(MINIMAP) $(RENDERING_BONUS) $(TEXTURES) $(CONTROLS) $(CLEARDATA) $(GNL) $(UTILS) $(ENTRY)

PRINT_HEADER	=		echo "                     ";echo "			         _   ___   _ ";echo "			 ___ _ _| |_|_  |_| |";echo "			|  _| | | . |_  | . |";echo "			|___|___|___|___|___|";echo "                     ";

OBJS			=		$(SRCS:.c=.o)

BONUSO			=		$(BONUS:.c=.o)

LIB				=		@make -C ./libft

MLX				=		@make -C $(mlxpath)

CFLAGS			=		-Wall -Werror -Wextra

DEBUG			=		-g -fsanitize=address

MLXFLAGS		=		-framework OpenGL -framework AppKit

.c.o			:
						@gcc $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME)			:		$(OBJS)
						@$(PRINT_HEADER)
						$(LIB)
						@echo "$(Cyan)Libft 100%$(Set_Color)"
						$(MLX)
						@echo "$(Yellow)MinilibX 100%$(Set_Color)"
						@gcc $(CFLAGS) $(OBJS) libft/libft.a $(mlxpath)/libmlx.a $(MLXFLAGS) -o $(NAME)
						@echo "$(Green)Cub3d for $(OS) has been created$(Set_Color)"

bonus_com			:	$(SRCS_BONUS)
						@$(PRINT_HEADER)
						$(LIB)
						@echo "$(Cyan)Libft 100%$(Set_Color)"
						$(MLX)
						@echo "$(Yellow)MinilibX 100%$(Set_Color)"
						@gcc $(CFLAGS) $(SRCS_BONUS) libft/libft.a $(mlxpath)/libmlx.a $(MLXFLAGS) -o $(NAME)
						@echo "$(Green)Cub3d for $(OS) has been created$(Set_Color)"

devmode			:		$(OBJS)
						$(LIB)
						@echo "$(Red)YOU ARE COMPILING WITHOUT FLAGS! YOU ARE COMPILING WITHOUT FLAGS! YOU ARE COMPILING WITHOUT FLAGS!$(Set_Color)"
						@echo "$(Cyan)Libft 100%$(Set_Color)"
						$(MLX)
						@echo "$(Yellow)MinilibX 100%$(Set_Color)"
						@gcc $(CFLAGS) $(DEBUG) $(OBJS) libft/libft.a $(mlxpath)/libmlx.a $(MLXFLAGS) -o $(NAME)
						@echo "$(Green)Cub3d for $(OS) has been created$(Set_Color)"
						@echo "$(Red)YOU ARE COMPILING WITHOUT FLAGS! YOU ARE COMPILING WITHOUT FLAGS! YOU ARE COMPILING WITHOUT FLAGS!$(Set_Color)"

lib				:
						$(LIB)
						@echo "$(Cyan)Libft 100%$(Set_Color)"

mlx				:
						$(MLX)
						@echo "$(Yellow)MinilibX 100%$(Set_Color)"

clean			:
						@rm -f $(OBJS)
						@echo "$(Red)Objects removed$(Set_Color)"

libclean			:
						@cd ./libft && make fclean
						@echo "$(Red)Libft removed$(Set_Color)"

mlxclean			:
						@cd $(mlxpath) && make clean
						@echo "$(Red)MinilibX removed$(Set_Color)"

fclean			:		clean libclean
						@rm -f $(NAME)
						@echo "$(Red)Cub3d has been removed$(Set_Color)"

all				:		$(NAME)

re				:		fclean all

bonus				:	fclean bonus_com

map_test			:	
						sh ./maps/map_test.sh

.PHONY			:		clean fclean all re bonus
