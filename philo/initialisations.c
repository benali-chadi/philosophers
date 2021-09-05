/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:05:23 by cbenali-          #+#    #+#             */
/*   Updated: 2021/09/05 19:31:03 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_utils(t_utils *utils, char **av)
{
	utils->options.num_of_philos = ft_atoi(av[1]);
	utils->options.time_to_die = ft_atoi(av[2]);
	utils->options.time_to_eat = ft_atoi(av[3]);
	utils->options.time_to_sleep = ft_atoi(av[4]);
	utils->options.num_must_eat = -1;
	if (av[5])
		utils->options.num_must_eat = ft_atoi(av[5]);
}

void	init_forks(t_utils *utils)
{
	int	i;

	utils->forks = malloc(sizeof(pthread_mutex_t)
			* utils->options.num_of_philos);
	i = -1;
	while (++i < utils->options.num_of_philos)
		pthread_mutex_init(&utils->forks[i], NULL);
	pthread_mutex_init(&utils->printing, NULL);
}

void	init_philos(t_philo **philos, t_utils *utils)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * utils->options.num_of_philos);
	i = -1;
	while (++i < utils->options.num_of_philos)
	{
		(*philos)[i].utils = utils;
		(*philos)[i].id = i;
		(*philos)[i].n_eat = 0;
	}
}
