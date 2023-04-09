CC=gcc
CFLAGS= -Werror -Wall -Wextra #-g -fsanitize=address,undefined,integer

SRCS= parser.c wind.c wallCalc.c raycast_engine.c \
	textures.c Wall_rendering.c player.c hook.c ori_sichu.c \
	dragon_parser.c parser_utils.c main.c utils.c floor_celling.c \
	hor_ver_hit.c


INC= cub.h
LIB= libft/libft.a
OBJ =$(subst .c,.o,$(SRCS))

%.o: %.c $(INC)
	$(CC) -Imlx -c -o $@ $< $(CFLAGS)
all: cub

$(LIB): force
	@make -C libft

force:

cub: $(OBJ) $(LIB)
		$(CC) -lmlx -framework OpenGL -framework AppKit   -o $@ $^ $(CFLAGS)
clean:
	rm -rf $(OBJ)
fclean : clean
	@make fclean -C libft
	rm -rf cub
re:fclean
	$(MAKE)
