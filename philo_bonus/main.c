/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 19:24:09 by cbenali-          #+#    #+#             */
/*   Updated: 2021/09/06 19:24:10 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philo_routine(void *arg)
{
	t_utils_two	*philo;

	philo = (t_utils_two *)arg;
	while (1)
	{
		eating_two(philo);
		ft_print_two(*philo, "is sleeping");
		ft_sleep(philo->options.time_to_sleep, philo->initial_time);
		ft_print_two(*philo, "is thinking");
	}
	return (NULL);
}

void	launch(t_utils_two *utils)
{
	struct timeval	time_v;
	int				i;

	i = -1;
	gettimeofday(&time_v, NULL);
	utils->initial_time = (time_v.tv_sec * 1000) + (time_v.tv_usec / 1000);
	while (++i < utils->options.num_of_philos)
	{
		utils->id = i;
		utils->last_meal = get_time(utils->initial_time);
		utils->pids[i] = fork();
		if (!utils->pids[i])
		{
			pthread_create(&utils->philo, NULL, &philo_routine, utils);
			supervisor(utils);
		}
	}
}

int	main(int ac, char **av)
{
	t_utils_two		utils;
	int				i;
	int				status;

	if (ac < 5 || ac > 6)
	{
		printf("Error in arguments!\n");
		return (1);
	}
	init_utils(&utils, av);
	if (!utils.options.num_must_eat)
		return (0);
	launch(&utils);
	while (wait(&status) != -1)
	{
		if (status == 256)
		{
			i = -1;
			while (++i < utils.options.num_of_philos)
				kill(utils.pids[i], SIGKILL);
			return (1);
		}
	}
	return (0);
}
