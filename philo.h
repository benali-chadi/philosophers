#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_options {
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_must_eat;
}		t_options;

typedef	struct	s_philo {
	pthread_t	philo_t;
	int		num;
	int		n_eat;
	
}		t_philo;

