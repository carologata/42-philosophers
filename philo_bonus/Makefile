NAME	:= philo_bonus
CFLAGS	:= -Wextra -Wall -Werror -g3

HEADERS	:= -I. -pthread

SRCS = main.c validate.c init_table.c child_process.c meal.c meal_alone.c safe_functions.c time.c print.c parent_monitor.c utils.c finish.c 

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
		./$(NAME) 4 410 200 200 
# ./$(NAME) 5 1800 200 200 

drd: all
	valgrind \
		--tool=drd \
		-s \
		./$(NAME) 5 1800 200 200 5
#       --log-file=drd-out.txt \

clean:
	@rm -rf $(OBJS)
	# @rm -rf $(OBJS_BONUS)

fclean: clean
	@rm -rf $(NAME)
	# @rm -rf $(NAME_BONUS)

re: clean all

.PHONY: all, clean, fclean, re