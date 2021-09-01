#include "philo.h"

int	eating(t_all all)
{
	int	l_fork;
	int	r_fork;

	l_fork = all.num;
	r_fork = (all.num + 1) % all.options.num_of_philos;
	
	pthread_mutex_lock(&all.forks[l_fork]);
	ft_print(all, "has taken a fork");
	pthread_mutex_lock(&all.forks[r_fork]);
	ft_print(all, "has taken a fork");

	unsigned long long current_t = get_time();
	if (get_time() - all.philos[all.num].last_meal_t >= all.options.time_to_die)
		return (1);
	all.philos[all.num].last_meal_t = current_t;
	
	ft_print(all, "is eating");
	usleep(all.options.time_to_eat * 1000);
	
	pthread_mutex_unlock(&all.forks[l_fork]);
	pthread_mutex_unlock(&all.forks[r_fork]);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_all *all = (t_all *)arg;
	printf("num = %d\n", all->num);
	while (1)
	{
		//	Eating
		if (eating(*all))
		{
			ft_print(*all, "died");
			all->died = 1;
			return;
		}
		//	Sleeping
		ft_print(*all, "is sleeping");
		usleep(all->options.time_to_sleep * 1000);
		//	Thinking
		ft_print(*all, "is thinking");
	}
}

void	init_philos(t_all all)
{
	int	i;

	i = -1;

	while (++i < all.options.num_of_philos)
		pthread_mutex_init(&all.forks[i], NULL);
	i = -1;
	while (++i < all.options.num_of_philos)
	{
		all.num = i;
		all.philos[i].last_meal_t = all.initial_time;
		pthread_create(&all.philos[i].philo_t, NULL, &philo_routine, &all);
	}
	while (1)
	{
		if (all.died)
			return;
	}
}

int main (int ac, char **av)
{
	t_all	all;
	all.initial_time = get_time();
	all.died = 0;
	if (ac > 4)
	{
		all.options.num_of_philos = atoi(av[1]);
		all.philos = malloc(sizeof(t_philo) * atoi(av[1]) + 1);
		all.forks = malloc(sizeof(t_philo) * atoi(av[1]) + 1);
		all.options.time_to_die = atoi(av[2]);
		all.options.time_to_eat = atoi(av[3]);
		all.options.time_to_sleep = atoi(av[4]);
		all.options.num_must_eat = 0;
		if (av[5])
			all.options.num_must_eat = atoi(av[5]);
		init_philos(all);
	}
	return (0);
}
