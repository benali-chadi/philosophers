/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:08:41 by cbenali-          #+#    #+#             */
/*   Updated: 2021/09/16 19:46:28 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	starve(t_philo **philos, t_utils *utils)
{
	int	i;

	i = -1;
	while (++i < utils->options.num_of_philos)
	{
		if (get_time(utils->initial_time) - (*philos)[i].last_meal
			>= utils->options.time_to_die && !(*philos)[i].eating)
		{
			pthread_mutex_lock(&utils->printing);
			printf("%d %d died\n", get_time(utils->initial_time),
				(*philos)[i].id + 1);
			ft_exit(philos, utils);
			return (1);
		}
	}
	return (0);
}

int	must_eat_num(t_philo **philos, t_utils *utils)
{
	int	i;

	i = -1;
	i = -1;
	while (++i < utils->options.num_of_philos)
		if ((*philos)[i].n_eat < utils->options.num_must_eat)
			return (0);
	ft_exit(philos, utils);
	return (1);
}

void	supervisor(t_philo **philos, t_utils *utils)
{
	while (1)
	{
		if (starve(philos, utils))
			return ;
		if (utils->options.num_must_eat > 0)
			if (must_eat_num(philos, utils))
				return ;
	}
}
