# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/16 08:47:29 by rluis-ya          #+#    #+#              #
#    Updated: 2025/09/18 21:24:14 by rluis-ya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

UNIT = unit

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft -g

SRCS_DIR = srcs
INCS_DIR = include
TEST_DIR = unit_test

SRCS = main.c driver.c pipex.c pipex_utils.c parser.c garbage_collector.c garbage_collector_utils.c

BONUS_SRCS = srcs/bonus/main_bonus.c srcs/bonus/here_doc_bonus.c srcs/driver.c srcs/pipex.c srcs/pipex_utils.c srcs/parser.c srcs/garbage_collector.c srcs/garbage_collector_utils.c

PATH_SRCS = $(patsubst %, $(SRCS_DIR)/%, $(SRCS))

LFT = libft/libft.a

all: $(NAME)

$(LFT):
	@$(MAKE) -C libft

$(NAME): $(PATH_SRCS) $(LFT)
	$(CC) $(CFLAGS) $^ -o $@

bonus: $(BONUS_SRCS) $(LFT)
	$(CC) $(CFLAGS) $^ -o pipex

clean:
	@$(MAKE) -C libft clean 

fclean: clean
	@$(MAKE) -C libft fclean 
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re unit bonus
