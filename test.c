#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int j = 0;
pthread_mutex_t mutex;

void	*func(void *arg)
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		j++;
		pthread_mutex_unlock(&mutex);
	}
}

int	main()
{
	pthread_t t1;
	pthread_t t2;
	pthread_mutex_init(&mutex, NULL);

	if (pthread_create(&t1, NULL, func, "testing"))
	{
		printf("%s\n", strerror(errno));
		return (1);
	}
	
	if (pthread_create(&t2, NULL, func, "testing 2"))
	{
		printf("%s\n", strerror(errno));
		return (1);
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&mutex);
	printf("j = %d\n", j);

	return (0);
}