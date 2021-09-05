#include "philo_bonus.h"

void	ft_print_two(t_utils_two philo, char *msg)
{
	int	current_t;
    
    sem_wait(philo.printing);
	current_t = get_time(philo.initial_time);
	printf("%d %d %s\n", current_t, philo.id + 1, msg);
    sem_post(philo.printing);
}

void	init_utils(t_utils_two *utils, char **av)
{
	struct timeval	time_v;

	sem_unlink("forks");
	sem_unlink("print");
	utils->options.num_of_philos = ft_atoi(av[1]);
	utils->options.time_to_die = ft_atoi(av[2]);
	utils->options.time_to_eat = ft_atoi(av[3]);
	utils->options.time_to_sleep = ft_atoi(av[4]);
	utils->options.num_must_eat = -1;
    utils->n_eat = 0;
	if (av[5])
		utils->options.num_must_eat = ft_atoi(av[5]);
	gettimeofday(&time_v, NULL);
	utils->initial_time = (time_v.tv_sec * 1000) + (time_v.tv_usec / 1000);
    utils->pids = malloc(sizeof(int) * utils->options.num_of_philos);
	utils->forks = sem_open("forks", O_CREAT, 0600, utils->options.num_of_philos);
	utils->printing = sem_open("print", O_CREAT, 0600, 1);
}
