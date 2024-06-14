NAME	:= philo_bonus
CFLAGS	:= -Wextra -Wall -Werror -g3

HEADERS	:= -I. -pthread

SRCS = main.c validate.c init.c meal.c monitor.c print.c time.c utils.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

hel: all
	valgrind \
		--tool=helgrind \
		--history-level=none \
		-s \
		./$(NAME) 5 1800 200 200 

clean:
	@rm -rf $(OBJS)
	# @rm -rf $(OBJS_BONUS)

fclean: clean
	@rm -rf $(NAME)
	# @rm -rf $(NAME_BONUS)

re: clean all

.PHONY: all, clean, fclean, re