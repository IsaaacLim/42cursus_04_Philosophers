#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int primes[10] = {2,3,5,7,11,13,17,19,23,29};

void	*myThreadFunc(void *arg)
{
	int *i = (int *)arg;
	printf("First line: %d\n", primes[*i]);
	free(arg);
	sleep(1);
	printf("Second line\n");
}

int	main(void)
{
	pthread_t th[10];
	int i;

	printf("Before thread\n");
	i = 0;
	while (i < 10)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, myThreadFunc, a) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (1);
		i++;
	}
	printf("After thread\n");
}
