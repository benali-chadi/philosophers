#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	struct timeval time_v;
	gettimeofday(&time_v, NULL);
	int current_t = time_v.tv_usec;
	printf("in seconds = %d\tcurrent time = %d\n", time_v.tv_sec,current_t);
	sleep(2);
	gettimeofday(&time_v, NULL);
	current_t = time_v.tv_usec - current_t;
	printf("in seconds = %d\ttime_v.tv_usec = %d\tcurrent time = %d\n", time_v.tv_sec,time_v.tv_usec, current_t);
	return (0);
}