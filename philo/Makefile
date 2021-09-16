FLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread

NAME = philo

SRC =	main.c \
		philo_utils.c \
		initialisations.c \
		actions.c \
		supervisor.c

all : $(NAME)

$(NAME) : $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean :
	rm -f $(NAME) $(NAME_BN)

fclean : clean

re : fclean all
