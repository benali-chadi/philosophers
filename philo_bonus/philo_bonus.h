#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_options {
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_must_eat;
}				t_options;

typedef struct	s_utils_two {
	t_options	options;
	pthread_t	philo;
	sem_t		*forks;
    sem_t       *printing;
    int         *pids;
	int			id;
	int			initial_time;
	int			last_meal;
	int			n_eat;
}               t_utils_two;

/*
	** UTILS
*/

int		get_time(int initial_time);
void	ft_print_two(t_utils_two philo, char *msg);
int		ft_atoi(const char *str);
void	init_utils(t_utils_two *utils, char **av);

/*
    ** ACTIONS
*/

void	eating_two(t_utils_two *philo);
void	ft_sleep(int sleep_time, int initial_time);
void	supervisor(t_utils_two utils);

#endif