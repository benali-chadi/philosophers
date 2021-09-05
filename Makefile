FLAGS = -Wall -Wextra -Werror

NAME = philo

NAME_BN = philo_bonus

SRC =	philo_one/main.c \
		philo_one/philo_utils.c \
		philo_one/initialisations.c \
		philo_one/actions.c \
		philo_one/supervisor.c

SRC_BN =	philo_two/main.c \
			philo_one/philo_utils.c \
			philo_one/actions.c

all : $(NAME)

$(NAME) : $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean :
	rm -f $(NAME) $(NAME_BN)

fclean : clean

bonus :
	gcc $(FLAGS) $(SRC_BN) -o $(NAME_BN)

re : fclean all
