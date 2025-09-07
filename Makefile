NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft -g

SRCS_DIR = srcs
INCS_DIR = include

SRCS = main.c pipex.c

PATH_SRCS = $(patsubst %, $(SRCS_DIR)/%, $(SRCS))

LFT = libft/libft.a

all: $(NAME)

$(LFT):
	$(MAKE) -C libft

$(NAME): $(PATH_SRCS) $(LFT)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@$(MAKE) -C libft clean 

fclean: clean
	@$(MAKE) -C libft fclean 
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
