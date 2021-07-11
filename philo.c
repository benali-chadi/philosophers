#include "philo.h"

void	*philo_routine(void *arg)
{
	//	Eating
	//	Sleeping
	//	Thinking
	//	Dying
}

void	init_philos(t_options options, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < options.num_of_philos)
	{
		philos[i].num = i + 1;
		pthread_create(philos[i].philo_t, NULL, &philo_routine, NULL);
	}
}

int main (int ac, char **av)
{
	t_options	options;
	t_philo		*philos;
	if (ac > 4)
	{
		options.num_of_philos = av[1];
		philos = malloc(sizeof(t_philo) * av[1] + 1);
		options.time_to_die = av[2];
		options.time_to_eat = av[3];
		options.time_to_sleep = av[4];
		options.num_must_eat = 0;
		if (av[5])
			options.num_must_eat = av[5];
		init_philos(options, philos);
	}
	return (0);
}
