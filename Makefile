# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/16 08:47:29 by rluis-ya          #+#    #+#              #
#    Updated: 2025/09/22 18:21:27 by rluis-ya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Flags #

CC = cc

NAME = pipex

NAME_BONUS = .bonus

HEADER = include/libpipex.h

HEADER_BONUS = include/libpipex_bonus.h

CFLAGS = -Wall -Werror -Wextra -Iinclude -Ilibft -g

# Files #

SRC = srcs/main.c \
			srcs/driver.c \
			srcs/pipex.c \
			srcs/pipex_utils.c \
			srcs/parser.c \
			srcs/garbage_collector.c \
			srcs/garbage_collector_utils.c

SRC_BONUS = bonus_dir/main_bonus.c \
			 bonus_dir/driver_bonus.c \
			 bonus_dir/pipex_bonus.c \
			 bonus_dir/pipex_utils_bonus.c \
			 bonus_dir/parser_bonus.c \
			 bonus_dir/garbage_collector_bonus.c \
			 bonus_dir/garbage_collector_utils_bonus.c \
			 bonus_dir/here_doc_bonus.c

LFT = libft/libft.a

OBJS = $(SRC:.c=.o)

OBJS_BONUS = $(SRC_BONUS:.c=.o)

%.o:%.c 
	@$(CC) $(CFLAGS) -c $< -o $@

# Rules #

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(LFT)
	@rm -rf $(NAME_BONUS)
	@$(CC) $(CFLAGS) $^ -o $(NAME)
	@echo "Compiled Program"

$(NAME_BONUS): $(OBJS_BONUS) $(LFT)
	@rm -rf srcs/main.o
	@touch $(NAME_BONUS) 
	@$(CC) $(CFLAGS) $^ -o $(NAME)
	@echo "Compiled Bonus"

$(LFT):
		@$(MAKE) -C libft
norm:
	@norminette -R CheckForbiddenSourceHeader $(SRC) $(HEADER) $(SRC_BONUS) $(HEADER_BONUS)

clean:
	@$(MAKE) -C libft clean
	@rm -rf $(NAME_BONUS)
	@rm -f $(OBJS) $(OBJS_BONUS)
	@echo "Cleaned object files"

fclean: clean
	@$(MAKE) -C libft fclean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "Removed Program"

re: fclean all

.PHONY: all clean fclean re bonus
