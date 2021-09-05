/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:07:57 by cbenali-          #+#    #+#             */
/*   Updated: 2021/09/05 19:31:03 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(int sleep_time, int initial_time)
{
	int	time;

	time = get_time(initial_time);
	usleep(sleep_time * 1000 - 14000);
	while (get_time(initial_time) - time < sleep_time)
		;
}

void	eating(t_philo *philo)
{
	int	l_fork;
	int	r_fork;

	r_fork = philo->id;
	l_fork = (philo->id + 1) % philo->utils->options.num_of_philos;
	pthread_mutex_lock(&philo->utils->forks[l_fork]);
	ft_print(*philo, "has taken a fork");
	pthread_mutex_lock(&philo->utils->forks[r_fork]);
	ft_print(*philo, "has taken a fork");
	philo->last_meal = get_time(philo->utils->initial_time);
	philo->n_eat += 1;
	ft_print(*philo, "is eating");
	ft_sleep(philo->utils->options.time_to_eat, philo->utils->initial_time);
	pthread_mutex_unlock(&philo->utils->forks[r_fork]);
	pthread_mutex_unlock(&philo->utils->forks[l_fork]);
}

void	ft_exit(t_philo **philos, t_utils *utils)
{
	int	i;

	i = -1;
	while (++i < utils->options.num_of_philos)
		pthread_mutex_destroy(&utils->forks[i]);
	free(utils->forks);
	free(*philos);
}
