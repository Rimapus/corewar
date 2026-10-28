##
## EPITECH PROJECT, 2025
## corewar
## File description:
## Makefile for corewar
##

CC = gcc
CFLAGS = -I./include -Wall -Wextra -g
CFLAGS += $(CUSTOMCFLAGS)
LDFLAGS = -L./lib -lmy_printf
TARGET = corewar

SRCS := $(shell find src -name "*.c")
OBJS = $(SRCS:.c=.o)

# Colors
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m
BOLD=\27[48;5;1m
RESET=\033[0m

PREIX=[$(BLUE)${TARGET}$(RESET)]

all: $(TARGET)

$(TARGET): $(OBJS)
	@make -C lib/my_printf --no-print-directory
	@echo "$(PREIX)$(BLUE)Linking $(PURPLE)$(TARGET)$(RESET)"
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS) 1>/dev/null
	@echo "$(PREIX)$(GREEN)Build successful!$(RESET)"

%.o: %.c
	@echo "$(PREIX)$(YELLOW)Compiling $(RESET)$(CYAN)$(dir $<)\
	$(GREEN)$(notdir $<)$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ 1>/dev/null

dev: all

clean:
	@echo "$(PREIX)$(CYAN)Cleaning objects$(RESET)"
	@rm -f $(OBJS) $(TEST_OBJS)
	@find . -type f -name "*.gcda" -delete
	@find . -type f -name "*.gcno" -delete

fclean: clean
	@echo "$(PREIX)$(CYAN)Cleaning Executables/Libraries$(RESET)"
	@rm -f $(TARGET) unit_tests
	@make -C lib/my_printf fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean
