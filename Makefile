NAME = cub3D
M_SRC = main.c \
		get_next_line.c \
		error_handling.c \
		parsing.c \
		utils.c \
		colors.c \
		map_info.c \
		extra.c \
		get_map.c \
		viewing.c \
		

M_OBJ = $(M_SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O3 #remove the sanitize flag

LIBFTPATH = libft
LIBFT = -L${LIBFTPATH} -lft
MINILIBX_PATH = minilibx
MINILIBX_LIB = -Lminilibx -lmlx -framework OpenGL -framework AppKit

$(NAME): $(M_OBJ)
	@ cd $(LIBFTPATH) && make
	@cd $(MINILIBX_PATH) && make
# silent mlx and flags
	@ $(CC) $(M_OBJ) $(CFLAGS) $(LIBFT) $(MINILIBX_LIB) -o $(NAME)
# @$(CC) $(M_OBJ) $(CFLAGS) $(LIBFT) -o $(NAME)
	@ echo "$(COLOUR_GREEN)compiled $(words $(M_OBJ)) files $(COLOUR_END)"

all: $(NAME)

clean:
	@ cd libft && make clean
	@ cd $(MINILIBX_PATH) && make clean
	@ rm -f $(M_OBJ)
# @ rm -f $(M_OBJ)

fclean: clean
	@ rm -f $(NAME)

re: fclean all
