#include "philo_bonus.h"

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

void	supervisor(t_utils_two utils)
{
	while (1)
	{
		if ((get_time(utils.initial_time) - utils.last_meal
			>= utils.options.time_to_die))
		{
			printf("last meal = %d\t initial time = %d\n", utils.last_meal, utils.initial_time);
			ft_print_two(utils, "died");
			free(utils.pids);
			sem_close(utils.forks);
			sem_close(utils.printing);
			exit(1);
		}
		if (utils.options.num_must_eat > 0 && utils.n_eat >= utils.options.num_must_eat)
		{
			printf("id = %d\tn_eat = %d\tnum_must_eat = %d\n", utils.id, utils.n_eat, utils.options.num_must_eat);
			exit(0);
		}
	}
}