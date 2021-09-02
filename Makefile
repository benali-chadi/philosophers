FLAGS = -Wall -Wextra -Werror -lncurses -g

NAME = philo

NAMELIB = libftprintf.a

SRC = philo.c philo_utils.c initialisations.c actions.c

all : $(NAME)

$(NAME) : $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean :
	rm -f $(NAME)

fclean : clean

# bonus : fclean $(NAMELIB)
# 	gcc $(FLAGS) $(SRC) -D BONUS=1 -o $(NAME)

re : fclean all