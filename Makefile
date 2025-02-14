SRCS	= cub3d.c ./get_next_line/get_next_line_utils.c ./get_next_line/get_next_line.c ./get_next_line/split.c \
		engine/move_player.c engine/windows_utils.c  engine/raycaster.c

OBJ = $(SRCS:.c=.o)

CFLAGS = -g #-Wall -Wextra -Werror 
NAME = cub3d
RM = rm -f
CC = cc

all: $(NAME)

$(NAME):$(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -I ./minilibx-linux -L ./minilibx-linux -lmlx -lm -lX11 -lXext -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean all
