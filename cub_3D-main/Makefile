# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mawad <mawad@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 00:23:33 by mawad             #+#    #+#              #
#    Updated: 2024/05/21 19:51:08 by mawad            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = mandatory/srcs
SRCS = $(addprefix $(SRCS_DIR)/, main.c player_utils.c raycast.c raycast_utils.c general_utils.c movement1.c movement2.c movement_utils.c drawing1.c drawing2.c)

PARSE_DIR = mandatory/parsing
PARSE = $(addprefix $(PARSE_DIR)/, get_map.c get_map_utils.c map_utils2.c parse.c parse_utils.c parse_colors.c \
			parse_colors_utils.c parse_textures.c map_dfs_utils.c map_dfs.c parse_map.c get_next_line.c)

BONUS_SRCS_DIR = bonus/srcs_bonus
BONUS_SRCS = $(addprefix $(BONUS_SRCS_DIR)/, drawing1_bonus.c drawing2_bonus.c general_utils_bonus.c main_bonus.c minimap_bonus.c movement_utils_bonus.c \
				 movement1_bonus.c movement2_bonus.c player_utils_bonus.c raycast_bonus.c raycast_utils_bonus.c wall_collisions_utils_bonus.c \
				 wall_collisions1_bonus.c wall_collisions2_bonus.c)

BONUS_PARSE_DIR = bonus/parsing_bonus
BONUS_PARSE_SRCS = $(addprefix $(BONUS_PARSE_DIR)/, get_map_bonus.c get_map_utils_bonus.c get_next_line_bonus.c map_dfs_bonus.c map_dfs_utils_bonus.c \
						map_utils2_bonus.c parse_bonus.c parse_colors_bonus.c parse_colors_utils_bonus.c parse_map_bonus.c parse_textures_bonus.c \
						parse_utils_bonus.c)

SRCS_OBJS = $(SRCS:.c=.o)
PARSE_OBJS = $(PARSE:.c=.o)

BONUS_SRCS_OBJS = $(BONUS_SRCS:.c=.o)
BONUS_PARSE_OBJS = $(BONUS_PARSE_SRCS:.c=.o)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

#MAC_OS
$(NAME): $(SRCS_OBJS) $(PARSE_OBJS)
	$(CC) $(SRCS_OBJS) $(PARSE_OBJS) -o $(NAME) -Lmlx -lmlx -framework OpenGL -framework AppKit $(LIBFT)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

#LINUX
#$(NAME): $(SRCS_OBJS) $(PARSE_OBJS)
#	$(CC) $(SRCS_OBJS) $(PARSE_OBJS) -o $(NAME) -Lmlx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(LIBFT)

#%.o: %.c
#	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

bonus: $(LIBFT) $(NAME_BONUS)
#MAC_OS
$(NAME_BONUS): $(BONUS_SRCS_OBJS) $(BONUS_PARSE_OBJS)
	$(CC) $(BONUS_SRCS_OBJS) $(BONUS_PARSE_OBJS) -o $(NAME_BONUS) -Lmlx -lmlx -framework OpenGL -framework AppKit $(LIBFT)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

#LINUX
#$(NAME_BONUS): $(BONUS_SRCS_OBJS) $(BONUS_PARSE_OBJS)
#	$(CC) $(BONUS_SRCS_OBJS) $(BONUS_PARSE_OBJS) -o $(NAME_BONUS) -Lmlx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(LIBFT)

#%.o: %.c
#	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(SRCS_OBJS) $(PARSE_OBJS) $(BONUS_SRCS_OBJS) $(BONUS_PARSE_OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

rebonus: fclean bonus

.PHONY: all bonus clean fclean re rebonus