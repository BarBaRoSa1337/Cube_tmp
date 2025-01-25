SRCS	= cub3d.c ./get_next_line/get_next_line_utils.c ./get_next_line/get_next_line.c ./get_next_line/split.c \
		move_player.c windows_utils.c 

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
	$(CC) $(OBJ) -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean all
