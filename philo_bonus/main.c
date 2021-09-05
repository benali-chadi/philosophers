#include "philo_bonus.h"

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

void	launch(t_utils_two *utils)
{
	int	i;

	i = -1;
	while (++i < utils->options.num_of_philos)
	{
		utils->id = i;
		utils->last_meal = get_time(utils->initial_time);
		utils->pids[i] = fork();
		if (!utils->pids[i])
		{
			pthread_create(&utils->philo, NULL, &philo_routine, utils);
			supervisor(*utils);
		}
	}
}

int main(int ac, char **av)
{
	t_utils_two		utils;
	int				i;

	if (ac < 5 || ac > 6)
	{
		printf("Error in arguments!\n");
		return (1);
	}
	init_utils(&utils, av);
	if (!utils.options.num_must_eat)
		return(0);
	launch(&utils);
	// i = -1;
	// while (++i < utils.options.num_of_philos)
	// {
	// 	utils.id = i;
	// 	utils.last_meal = get_time(utils.initial_time);
	// 	utils.pids[i] = fork();
	// 	if (!utils.pids[i])
	// 	{
	// 		pthread_create(&utils.philo, NULL, &philo_routine, &utils);
	// 		supervisor(utils);
	// 	}
	// }
	int status;
	while (wait(&status) != -1)
	{
		if (status == 256)
		{
			i = -1;
			while (++i < utils.options.num_of_philos)
				kill(utils.pids[i], SIGKILL);
			return(1);
		}
	}
	return (0);
}