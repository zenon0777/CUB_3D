CC=gcc
CFLAGS= -Werror -Wall -Wextra -g -fsanitize=address,undefined,integer
SRCS= parser.c wind.c gnl.c ft_strjoin_freed.c wallCalc.c raycast_engine.c textures.c Wall_rendering.c player.c hook.c
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
