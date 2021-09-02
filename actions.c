#include "philo.h"

void	ft_sleep(int sleep_time)
{
	int	time;

	time = get_time();
	usleep(sleep_time * 1000 - 14000);
	while (get_time() - time <= (unsigned long long)sleep_time * 1000);

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
	philo->last_meal_t = get_time();
	ft_print(*philo, "is eating");
	philo->n_eat += 1;ft_sleep(philo->utils->options.time_to_eat);

	pthread_mutex_unlock(&philo->utils->forks[r_fork]);
	pthread_mutex_unlock(&philo->utils->forks[l_fork]);
}

void	ft_exit(t_philo **philos, t_utils *utils)
{
	int i;

	i = -1;
	while (++i < utils->options.num_of_philos)
		pthread_mutex_destroy(&utils->forks[i]);
	free(utils->forks);
	free(*philos);
}

void	supervisor(t_philo **philos, t_utils *utils)
{
	int					i;
	unsigned long long	current_t;

	while (1)
	{
		i = -1;
		while (++i < utils->options.num_of_philos)
		{
			current_t = get_time();
			if (get_time() - (*philos)[i].last_meal_t >= (unsigned long long)utils->options.time_to_die)
			{
				ft_print((*philos)[i], "died");
				ft_exit(philos, utils);
				return ;
			}
		}
		if (utils->options.num_must_eat > 0)
		{
			i = -1;
			while (++i < utils->options.num_of_philos)
				if ((*philos)[i].n_eat < utils->options.num_must_eat)
					break ;
			if (i >= utils->options.num_of_philos)
			{
				ft_exit(philos, utils);
				break ;
			}
		}
	}
}