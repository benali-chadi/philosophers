#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo philo = *(t_philo *)arg;

	while (1)
	{
		eating((t_philo *)arg);
		ft_print(philo, "is sleeping");
		ft_sleep(philo.utils->options.time_to_sleep);
		ft_print(philo, "is thinking");
	}
	return (NULL);
}

int main (int ac, char **av)
{
	static t_philo	*philos;
	static t_utils	utils;
	int				i;

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
	i = -1;
	utils.initial_time = get_time();
	while (++i < utils.options.num_of_philos)
	{
		pthread_create(&philos[i].philo_t, NULL, &philo_routine, &philos[i]);
		usleep(100);  
	}
	supervisor(&philos, &utils);
	return (0);
}
