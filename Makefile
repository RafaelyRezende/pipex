NAME = pipex

UNIT = unit

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft -g

SRCS_DIR = srcs
INCS_DIR = include
TEST_DIR = unit_test

SRCS = main.c driver.c pipex.c parser.c garbage_collector.c

TEST_SRC = unit.c

PATH_SRCS = $(patsubst %, $(SRCS_DIR)/%, $(SRCS))

PATH_TEST = $(patsubst %, $(TEST_DIR)/%, $(TEST_SRC))

LFT = libft/libft.a

all: $(NAME)

$(LFT):
	@$(MAKE) -C libft

$(NAME): $(PATH_SRCS) $(LFT)
	$(CC) $(CFLAGS) $^ -o $@

$(UNIT): $(PATH_TEST) $(LFT)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@$(MAKE) -C libft clean 

fclean: clean
	@$(MAKE) -C libft fclean 
	@rm -f $(UNIT) 
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test unit
