NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = srcs
INCS_DIR = include
OBJS_DIR = bin

SRCS = $(SRCS_DIR)/main.c
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Create directories if they don't exist
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

# Compile object files
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

# Link object files to create executable
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

# Default target
all: $(NAME)

# Clean object files
clean:
	rm -f $(OBJS)

# Clean everything
fclean: clean
	rm -f $(NAME)

	# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
