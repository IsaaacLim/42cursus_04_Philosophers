NAME	=	philo

SRCS	=	main.c	initialize.c	philosophers.c	utils.c	
OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = clean fclean re
