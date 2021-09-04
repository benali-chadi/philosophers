/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:06:19 by cbenali-          #+#    #+#             */
/*   Updated: 2021/09/04 16:16:45 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(int initial_time)
{
	struct timeval	time_v;

	gettimeofday(&time_v, NULL);
	return ((time_v.tv_sec * 1000) + (time_v.tv_usec / 1000) - initial_time);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		signe;
	long	res;

	res = 0;
	i = 0;
	signe = 1;
	while (str[i] > 0 && str[i] <= 32 && str[i] != '\e')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		res = res * 10 + (str[i] - 48);
		i++;
		if (res > 2147483648 && signe == -1)
			return (0);
		else if (res > 2147483647 && signe == 1)
			return (-1);
	}
	return (res * signe);
}

void	ft_print(t_philo philo, char *msg)
{
	int	current_t;

	pthread_mutex_lock(&philo.utils->printing);
	current_t = get_time(philo.utils->initial_time);
	printf("%d %d %s\n", current_t, philo.id + 1, msg);
	pthread_mutex_unlock(&philo.utils->printing);
}
