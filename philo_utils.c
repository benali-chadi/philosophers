#include "philo.h"

unsigned long long	get_time()
{
	struct timeval	time_v;

	gettimeofday(&time_v, NULL);
	return ((time_v.tv_sec * 1000) + (time_v.tv_usec / 1000));
}

// ft_atoi

void	ft_print(t_all all, char *msg)
{
	unsigned long long current_t;
	
	current_t = get_time() - all.initial_time;
	printf("%ld %d %s\n", current_t, all.num + 1, msg);
}
