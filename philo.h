#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_options {
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_must_eat;
}				t_options;

typedef struct s_utils {
	t_options			options;
	pthread_mutex_t		*forks;
	pthread_mutex_t		printing;
	unsigned long long	initial_time;
	int					died;
}				t_utils;

typedef struct s_philo {
	pthread_t			philo_t;
	t_utils				*utils;
	int					id;
	unsigned long long	last_meal_t;
	int					n_eat;
}				t_philo;

/*
	** UTILS
*/

unsigned long long	get_time(void);
void				ft_print(t_philo philo, char *msg);
int					ft_atoi(const char *str);

/*
	** INITIALISATIONS
*/

void				init_utils(t_utils *utils, char **av);
void				init_forks(t_utils *utils);
void				init_philos(t_philo **philos, t_utils *utils);

/*
	** ACITONS
*/

void				ft_sleep(int sleep_time);
void				eating(t_philo *philo);
void				ft_exit(t_philo **philos, t_utils *utils);
void				supervisor(t_philo **philos, t_utils *utils);

#endif