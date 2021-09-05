FLAGS = -Wall -Wextra -Werror -pthread

NAME = philo_bonus

SRC =	main.c \
		utils.c \
		actions.c \
		../philo/philo_utils.c \
		../philo/actions.c

all : $(NAME)

$(NAME) : $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean :
	rm -f $(NAME)

fclean : clean

re : fclean all
