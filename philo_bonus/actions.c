/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 19:25:31 by cbenali-          #+#    #+#             */
/*   Updated: 2021/09/06 19:59:38 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating_two(t_utils_two *philo)
{
	sem_wait(philo->forks);
	ft_print_two(*philo, "has taken a fork");
	sem_wait(philo->forks);
	ft_print_two(*philo, "has taken a fork");
	philo->last_meal = get_time(philo->initial_time);
	ft_print_two(*philo, "is eating");
	ft_sleep(philo->options.time_to_eat, philo->initial_time);
	sem_post(philo->forks);
	sem_post(philo->forks);
	philo->n_eat += 1;
}

void	supervisor(t_utils_two *utils)
{
	while (1)
	{
		if (utils->options.num_must_eat > 0
			&& utils->n_eat >= utils->options.num_must_eat)
			exit(0);
		if ((get_time(utils->initial_time) - utils->last_meal
				>= utils->options.time_to_die))
		{
			ft_print_two(*utils, "died");
			ft_free(utils);
			exit(1);
		}
	}
}
