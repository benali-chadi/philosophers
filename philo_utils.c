#include "philo.h"

unsigned long long	get_time()
{
	struct timeval	time_v;

	gettimeofday(&time_v, NULL);
	return ((time_v.tv_sec * 1000) + (time_v.tv_usec / 1000));
}

// ft_atoi

void	ft_print(t_philo philo, char *msg)
{
	unsigned long long current_t;

	pthread_mutex_lock(&philo.utils->printing);

	current_t = get_time() - philo.utils->initial_time;
	printf("%llu %d %s\n", current_t, philo.id + 1, msg);
	pthread_mutex_unlock(&philo.utils->printing);
}
