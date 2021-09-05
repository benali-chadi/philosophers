#include "../philo_header.h"

void	eating_two(t_utils_two *philo)
{
	sem_wait(philo->forks);
	ft_print_two(*philo, "has taken a fork");
	sem_wait(philo->forks);
	ft_print_two(*philo, "has taken a fork");
	philo->last_meal = get_time(philo->initial_time);
	philo->n_eat += 1;
	ft_print_two(*philo, "is eating");
	ft_sleep(philo->options.time_to_eat, philo->initial_time);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	*philo_routine(void *arg)
{
	t_utils_two philo;

	philo = *(t_utils_two *)arg;
	while (1)
	{
		eating_two((t_utils_two *)arg);
		ft_print_two(philo, "is sleeping");
		ft_sleep(philo.options.time_to_sleep, philo.initial_time);
		ft_print_two(philo, "is thinking");
	}
	return (NULL);
}

int main(int ac, char **av)
{
	t_utils_two		utils;
	struct timeval	time_v;
	int				i;

	if (ac < 5 || ac > 6)
	{
		printf("Error in arguments!\n");
		return (1);
	}
	sem_unlink("forks");
	// INITIALISTION
	
	utils.options.num_of_philos = ft_atoi(av[1]);
	utils.options.time_to_die = ft_atoi(av[2]);
	utils.options.time_to_eat = ft_atoi(av[3]);
	utils.options.time_to_sleep = ft_atoi(av[4]);
	utils.options.num_must_eat = -1;
	if (av[5])
		utils.options.num_must_eat = ft_atoi(av[5]);
	gettimeofday(&time_v, NULL);
	utils.initial_time = (time_v.tv_sec * 1000) + (time_v.tv_usec / 1000);
	// sem_init(&utils.forks, utils.options.num_of_philos, utils.options.num_of_philos);
	utils.forks = sem_open("forks", O_CREAT, 0600, utils.options.num_of_philos);

	// EXECUTION

	i = -1;
	while (++i < utils.options.num_of_philos)
	{
		utils.id = i;
		utils.last_meal = get_time(utils.initial_time);
		if (!fork())
		{
			pthread_create(&utils.philo, NULL, &philo_routine, &utils);
			while (1);
		}
	}
	while (wait(NULL) != -1);
	return (0);
}