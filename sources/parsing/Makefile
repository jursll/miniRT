# ─────────────────────────────────────────────────────────────
# Makefile for parsing/ folder
# ─────────────────────────────────────────────────────────────

# Name of the parsing‐only executable
NAME       := parse_test

# Compiler and flags
CC         := gcc
CFLAGS     := -Wall -Wextra -Werror \
              -I../../include \
              -I../../libft

# Path to your libft
LIBFT_DIR  := ../../libft
LIBFT_LIB  := $(LIBFT_DIR)/libft.a

# All .c files in this directory
SRCS       := $(wildcard *.c)
# Corresponding .o files
OBJS       := $(SRCS:.c=.o)

.PHONY: all libft clean fclean re

all: libft $(NAME)

# Build libft first
libft:
	@$(MAKE) -C $(LIBFT_DIR)

# Link objects + libft into final binary
$(NAME): $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME)

# Pattern rule: how to compile each .c → .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove just the object files
clean:
	rm -f $(OBJS)

# Remove objects and the executable
fclean: clean
	rm -f $(NAME)

# Full rebuild
re: fclean all

# ─────────────────────────────────────────────────────────────
