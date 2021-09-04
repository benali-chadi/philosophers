/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:05:06 by cbenali-          #+#    #+#             */
/*   Updated: 2021/09/04 16:15:11 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	while (1)
	{
		eating((t_philo *)arg);
		ft_print(philo, "is sleeping");
		ft_sleep(philo.utils->options.time_to_sleep, philo.utils->initial_time);
		ft_print(philo, "is thinking");
	}
	return (NULL);
}

void	launch(t_philo **philos, t_utils *utils)
{
	struct timeval	time_v;
	int				i;

	gettimeofday(&time_v, NULL);
	utils->initial_time = (time_v.tv_sec * 1000) + (time_v.tv_usec / 1000);
	i = 0;
	while (i < utils->options.num_of_philos)
	{
		(*philos)[i].last_meal_t = get_time(utils->initial_time);
		pthread_create(&(*philos)[i].philo_t,
			NULL, &philo_routine, &(*philos)[i]);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < utils->options.num_of_philos)
	{
		(*philos)[i].last_meal_t = get_time(utils->initial_time);
		pthread_create(&(*philos)[i].philo_t, NULL,
			&philo_routine, &(*philos)[i]);
		i += 2;
	}
}

int	main(int ac, char **av)
{
	static t_philo	*philos;
	static t_utils	utils;

	if (ac < 5)
	{
		printf("Not enough arguments!\n");
		return (1);
	}
	init_utils(&utils, av);
	init_forks(&utils);
	if (!utils.options.num_must_eat)
		return (0);
	init_philos(&philos, &utils);
	launch(&philos, &utils);
	supervisor(&philos, &utils);
	return (0);
}
