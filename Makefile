NAME = cub3D
B_NAME = b_cub3D
B_PATH = bonus
M_PATH = mandatory

M_SRC = $(M_PATH)/main.c \
		$(M_PATH)/get_next_line.c \
		$(M_PATH)/error_handling.c \
		$(M_PATH)/parsing.c \
		$(M_PATH)/utils.c \
		$(M_PATH)/colors.c \
		$(M_PATH)/checking.c \
		$(M_PATH)/dda_utils.c \
		$(M_PATH)/map_info.c \
		$(M_PATH)/dfs.c \
		$(M_PATH)/get_map.c \
		$(M_PATH)/viewing.c \
		$(M_PATH)/controls.c \
		$(M_PATH)/moves.c \

B_SRC = $(B_PATH)/main.c \
		$(B_PATH)/get_next_line.c \
		$(B_PATH)/error_handling.c \
		$(B_PATH)/parsing.c \
		$(B_PATH)/utils.c \
		$(B_PATH)/colors.c \
		$(B_PATH)/checking.c \
		$(B_PATH)/dda_utils.c \
		$(B_PATH)/map_info.c \
		$(B_PATH)/dfs.c \
		$(B_PATH)/get_map.c \
		$(B_PATH)/viewing.c \
		$(B_PATH)/controls.c \
		$(B_PATH)/moves.c \
		$(B_PATH)/mouse.c \


M_OBJ = $(M_SRC:.c=.o)
B_OBJ = $(B_SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -O3

LIBFTPATH = libft
LIBFT = -L${LIBFTPATH} -lft
MINILIBX_PATH = minilibx
MINILIBX_LIB = -Lminilibx -lmlx -framework OpenGL -framework AppKit

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

m: $(NAME)

$(NAME): $(M_OBJ)
	@ cd $(LIBFTPATH) && make
	@ cd $(MINILIBX_PATH) && make
	$(CC) $(CFLAGS) $(MINILIBX_LIB) $(LIBFT) $(M_OBJ) -o $(NAME)

b: $(B_NAME)

$(B_NAME): $(B_OBJ)
	@ cd $(LIBFTPATH) && make
	@ cd $(MINILIBX_PATH) && make
	$(CC) $(CFLAGS) $(MINILIBX_LIB) $(LIBFT) $(B_OBJ) -o $(B_NAME)

all: m b

clean:
	@ cd $(LIBFTPATH) && make clean
	@ rm -f $(M_OBJ) $(B_OBJ) $(MINILIBX_LIB)
	@ cd $(MINILIBX_PATH) && make clean

fclean: clean
	@ cd $(LIBFTPATH) && make fclean
	@ rm -f $(NAME) $(B_NAME)

re: fclean all
