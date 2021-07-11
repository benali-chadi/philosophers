#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*
 *		THE PROBLEM
 * Create 10 threads, each taking a unique prime
 * from the primes array and print it on the screen
 */

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void *pick_and_print(void *a)
{
	int index = *(int *)a;
	int *sum = malloc(sizeof(int));
	*sum = 0;
	for (int i = 0; i < 5; i++)
		*sum += primes[index + i];
	free(a);
	return ((void *)sum);
}

int main (int ac, char **av)
{
	int num = 2;
	pthread_t th[num];
	int *results[num];

	for (int i = 0; i < num; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &pick_and_print, a) != 0)
			return (1);
	}
	for (int i = 0; i < num; i++)
	{
		if (pthread_join(th[i], (void **)&results[i]) != 0)
			return (1);
	}

	printf("res0= %d\tres1= %d\n", *results[0], *results[1]);
	int sum = *results[0] + *results[1];
	printf("sum: %d\n", sum);
	for (int i = 0; i < num; i++)
		free(results[i]);

	return (0);
}
