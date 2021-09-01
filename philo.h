#ifndef PHILO_H
#define PHILO_H

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
	pthread_t			philo_t;
	unsigned long long	last_meal_t;
	int					n_eat;
}				t_philo;

// typedef struct	s_time {
// 	int				initial_t;
// 	int				current_t;
// }				t_time;

typedef struct	s_all {
	t_philo				*philos;
	t_options			options;
	pthread_mutex_t		*forks;
	unsigned long long	initial_time;
	int 				num;
	int					died;
}				t_all;

/*
	** UTILS
*/

unsigned long long	get_time();
void				ft_print(t_all all, char *msg);

#endif