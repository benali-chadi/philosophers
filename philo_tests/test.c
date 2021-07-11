#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void	*role_dice(void *ptr)
{
	int val = (rand() %6) + 1;
	int *res = malloc(sizeof(int));
	*res = val;
	return (void *) res;
}

int	main()
{
	pthread_t th[8];
	int *result[8];

	srand (time(NULL));
	
	for (int i = 0; i < 8; i++)
		if (pthread_create(&th[i], NULL, &role_dice, NULL) != 0)
			return (1);
	
	for (int i = 0; i < 8; i++)
		if (pthread_join(th[i], (void **) &result[i]) != 0)
			return (1);
	for (int i = 0; i < 8; i++)
		printf("result[%d]: %d\n", i, *result[i]);
	return (0);
}
