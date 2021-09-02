#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

int	ft_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	long millisecond = time.tv_sec % 1000 * 1000 + time.tv_usec / 1000;
	return ((int)millisecond);
}

pthread_mutex_t mutex;

void	*threadFuncRet()
{
	int *result = malloc(sizeof(int));

	*result = 10;
	printf("Return add: %p\n", result);
	return ((void *)result);
}

int primes[10] = {2,3,5,7,11,13,17,19,23,29};

void	*myThreadFunc(void *arg)
{
	int timestamp;
	int *i = (int *)arg;
	pthread_mutex_lock(&mutex);
	timestamp = ft_time();
	printf("First line: %d Timestamp: %i\n", primes[*i], timestamp);
	free(arg);
	pthread_mutex_unlock(&mutex);
	sleep(1);
	printf("Second line\n");
}

int	main(void)
{
	pthread_t th[10];
	int i;

	printf("Before thread\n");
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < 2)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, myThreadFunc, a) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (1);
		i++;
	}
	printf("After thread\n");
	pthread_t ret;
	int *ret_val;
	if (pthread_create(&ret, NULL, threadFuncRet, NULL) != 0)
		return (1);
	if (pthread_join(ret, (void **)&ret_val) != 0)
		return (1);
	printf("Return add (main): %p\n", ret_val);
	free(ret_val);
	pthread_mutex_destroy(&mutex);
}
