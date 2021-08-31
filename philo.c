#include "philo.h"

int	ft_print(t_all all, char *msg)
{
	int current_t;
	
	gettimeofday(&all.time.time_v, NULL);
	current_t = all.time.time_v.tv_usec - all.time.initial_t;
	printf("%d %d %s\n", current_t, all.num, msg);
	return (current_t);
}

void	eating(t_all all)
{
	int	l_fork;
	int	r_fork;

	l_fork = all.num;
	r_fork = (all.num + 1) % all.options.num_of_philos;
	pthread_mutex_lock(&all.forks[l_fork]);
	ft_print(all, "has taken a fork");
	pthread_mutex_lock(&all.forks[r_fork]);
	ft_print(all, "has taken a fork");
	all.philos[all.num].last_meal_t = ft_print(all, "is eating");
	usleep(all.options.time_to_eat);
	pthread_mutex_unlock(&all.forks[l_fork]);
	pthread_mutex_unlock(&all.forks[r_fork]);
}

void	*philo_routine(void *arg)
{
	t_all all = *(t_all *)arg;
	printf("num = %d\n", all.num);
	while (1)
	{
		//	Eating
		eating(all);
		//	Sleeping
		ft_print(all, "is sleeping");
		usleep(all.options.time_to_sleep);
		//	Thinking
		ft_print(all, "is thinking");
		//	Dying
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
		printf("i=%d\n", i);
		all.num = i;
		pthread_create(&all.philos[i].philo_t, NULL, &philo_routine, &all);
	}
	// i = -1;
	// while (++i < all.options.num_of_philos)
	// 	pthread_join(all.philos[i].philo_t, NULL);
}

int main (int ac, char **av)
{
	// t_options	options;
	// t_philo		*philos;
	t_all	all;
	gettimeofday(&all.time.time_v, NULL);
	all.time.initial_t = all.time.time_v.tv_usec;
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
