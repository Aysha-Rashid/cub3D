NAME = cub3D
M_SRC = main.c \
		get_next_line.c \
		error_handling.c \
		parsing.c \
		utils.c \
		colors.c \
		map_info.c \
		dfs.c \
		get_map.c \
		viewing.c \
		checking.c \
		controls.c \
		moves.c \
		dda_utils.c \
		mouse.c \

M_OBJ = $(M_SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFTPATH = libft
LIBFT = -L${LIBFTPATH} -lft
MINILIBX_PATH = minilibx
MINILIBX_LIB = -Lminilibx -lmlx -framework OpenGL -framework AppKit

$(NAME): $(M_OBJ)
	@ cd $(LIBFTPATH) && make
	@ cd $(MINILIBX_PATH) && make
	@ $(CC) $(M_OBJ) $(CFLAGS) $(LIBFT) $(MINILIBX_LIB) -o $(NAME)
	@ echo "$(COLOUR_GREEN)compiled $(words $(M_OBJ)) files $(COLOUR_END)"

all: $(NAME)

clean:
	@ cd libft && make clean
	@ cd $(MINILIBX_PATH) && make clean
	@ rm -f $(M_OBJ)

fclean: clean
	@ cd libft && make fclean
	@ rm -f $(NAME)

re: fclean all
