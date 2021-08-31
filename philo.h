#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct	s_options {
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_must_eat;
}				t_options;

typedef	struct	s_philo {
	pthread_t	philo_t;
	int			last_meal_t;
	int			n_eat;
	
}				t_philo;

typedef struct	s_time {
	struct timeval	time_v;
	int				initial_t;
	int				current_t;
}				t_time;

typedef struct	s_all {
	t_philo			*philos;
	t_options		options;
	pthread_mutex_t	*forks;
	t_time			time;
	int 			num;
}				t_all;
