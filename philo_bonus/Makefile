NAME	=	philo_bonus

SRCS	=	main.c	utils.c
OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = clean fclean re
