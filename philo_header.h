/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:15:56 by cbenali-          #+#    #+#             */
/*   Updated: 2021/09/05 19:27:27 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>

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
	int					initial_time;
}				t_utils;

typedef struct s_philo {
	pthread_t			philo_t;
	t_utils				*utils;
	int					id;
	int					last_meal;
	int					n_eat;
}				t_philo;

typedef struct	s_utils_two {
	t_options	options;
	pthread_t	philo;
	sem_t		*forks;
	int			id;
	int			initial_time;
	int			last_meal;
	int			n_eat;
}				t_utils_two;

/*
	** UTILS
*/

int		get_time(int initial_time);
void	ft_print(t_philo philo, char *msg);
int		ft_atoi(const char *str);

void	ft_print_two(t_utils_two philo, char *msg);

/*
	** INITIALISATIONS
*/

void	init_utils(t_utils *utils, char **av);
void	init_forks(t_utils *utils);
void	init_philos(t_philo **philos, t_utils *utils);

/*
	** ACITONS
*/

void	ft_sleep(int sleep_time, int initial_time);
void	eating(t_philo *philo);
void	ft_exit(t_philo **philos, t_utils *utils);
void	supervisor(t_philo **philos, t_utils *utils);

#endif