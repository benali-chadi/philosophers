#include "philo.h"

int	eating(t_philo *philo)
{
	int	l_fork;
	int	r_fork;

	l_fork = philo->id;
	r_fork = (philo->id + 1) % philo->utils->options.num_of_philos;

	pthread_mutex_lock(&philo->utils->forks[l_fork]);
	ft_print(*philo, "has taken a fork");
	pthread_mutex_lock(&philo->utils->forks[r_fork]);
	ft_print(*philo, "has taken a fork");

	unsigned long long current_t = get_time();
	if (get_time() - philo->last_meal_t >= philo->utils->options.time_to_die)
	{
		printf("diff = %llu\n", current_t - philo->last_meal_t);
		return (1);
	}
	philo->last_meal_t = current_t;
	ft_print(*philo, "is eating");
	philo->n_eat += 1;
	int time = get_time();
	usleep(philo->utils->options.time_to_eat * 1000 /*- 14000*/);
	// while (get_time() - time <= philo->utils->options.time_to_sleep * 1000);
	
	pthread_mutex_unlock(&philo->utils->forks[r_fork]);
	pthread_mutex_unlock(&philo->utils->forks[l_fork]);
	return (0);
}

void	*philo_routine(void *arg)
{
	// t_all *all = (t_all *)arg;
	t_philo philo = *(t_philo *)arg;

	while (1)
	{
		//	Eating
		if (eating((t_philo *)arg))
		{
			ft_print(philo, "died");
			philo.utils->died = 1;
			break;
		}
		//	Sleeping
		ft_print(philo, "is sleeping");
		int time = get_time();
		usleep(philo.utils->options.time_to_sleep * 1000 - 14000);
		while (get_time() - time <= philo.utils->options.time_to_sleep * 1000);

		//	Thinking
		ft_print(philo, "is thinking");
		printf("n eat = %d\n", philo.n_eat);
		if (philo.utils->options.num_must_eat && philo.n_eat >= philo.utils->options.num_must_eat)
			break;
	}
}

// void	init_philos(t_all all)
// {
// 	int	i;

// 	i = -1;

// 	while (++i < all.options.num_of_philos)
// 		pthread_mutex_init(&all.forks[i], NULL);
// 	i = -1;
// 	while (++i < all.options.num_of_philos)
// 	{
// 		// all.philos->id = i;
// 		// all.philos[i].last_meal_t = all.initial_time;
// 		pthread_create(&all.philos[i].philo_t, NULL, &philo_routine, &all);
// 	}
// 	while (1)
// 	{
// 		if (all.died)
// 			return;
// 	}
// }

void	init_utils(t_utils *utils, char **av)
{
	utils->options.num_of_philos = atoi(av[1]);
	utils->initial_time = get_time();
	utils->died = 0;
	utils->options.time_to_die = atoi(av[2]);
	utils->options.time_to_eat = atoi(av[3]);
	utils->options.time_to_sleep = atoi(av[4]);
	utils->options.num_must_eat = 0;
	if (av[5])
		utils->options.num_must_eat = atoi(av[5]);
}

void	free_all(t_philo **philos)
{
	free((*philos)[0].utils->forks);
	free(*philos);
}

void	launch(t_philo **philos, int num_of_philos)
{
	int i;

	i = -1;
	while (++i < num_of_philos)
		pthread_create(&(*philos)[i].philo_t, NULL, &philo_routine, &(*philos)[i]);
	while (1)
	{
		if ((*philos)[0].utils->died)
		{
			free_all(philos);
			return;
		}
	}
}

void	supervisor(t_philo *philos)
{

}

int main (int ac, char **av)
{
	t_philo			*philos;
	static t_utils	utils;
	int				i;

	if (ac > 4)
	{
		init_utils(&utils, av);

		utils.forks = malloc(sizeof(pthread_mutex_t) * atoi(av[1]) + 1);
		while (++i < utils.options.num_of_philos)
			pthread_mutex_init(&utils.forks[i], NULL);
		pthread_mutex_init(&utils.printing, NULL);
		
		philos = malloc(sizeof(t_philo) * atoi(av[1]) + 1);
		i = -1;
		while (++i < utils.options.num_of_philos)
		{
			// philos[i].forks = &forks;
			philos[i].utils = &utils;
			philos[i].id = i;
			philos[i].last_meal_t = utils.initial_time;
			philos[i].n_eat = 0;
		}
		// launch(&philos, utils.options.num_of_philos);
		i = -1;
		while (++i < utils.options.num_of_philos)
		{
			pthread_create(&philos[i].philo_t, NULL, &philo_routine, &philos[i]);
		}
			printf("ok\n");
		while (1)
		{
			if (utils.died)
			{
				free(utils.forks);
				free(philos);
				return (0);
			}
			// if (utils.options.num_must_eat)
			// {
				int i = -1;
				while (utils.options.num_must_eat && ++i < utils.options.num_of_philos)
				{
					if (philos[i].n_eat < utils.options.num_must_eat)
					{
						// printf("n_eat=%d\tnum must eat=%d\n", philos[i].n_eat, utils.options.num_must_eat);
						break;
					}
				}
				if (i > utils.options.num_of_philos)
				{
					printf("here\n");
					ft_print(philos[1], "died");
					return (0);
				}
			// }
		}
	}
	return (0);
}
