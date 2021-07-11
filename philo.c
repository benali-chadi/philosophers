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
		pthread_create(&philos[i].philo_t, NULL, &philo_routine, NULL);
	}
    i = -1;
    while (++i < options.num_of_philos)
        pthread_join(philos[i].philo_t, NULL);
}

int main (int ac, char **av)
{
	t_options	options;
	t_philo		*philos;
	if (ac > 4)
	{
		options.num_of_philos = atoi(av[1]);
		philos = malloc(sizeof(t_philo) * atoi(av[1]) + 1);
		options.time_to_die = atoi(av[2]);
		options.time_to_eat = atoi(av[3]);
		options.time_to_sleep = atoi(av[4]);
		options.num_must_eat = 0;
		if (atoi(av[5]))
			options.num_must_eat = atoi(av[5]);
		init_philos(options, philos);
	}
	return (0);
}
