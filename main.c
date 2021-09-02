#include "philo.h"

pthread_mutex_t mutex;

void	*threadFuncRet()
{
	int *result = malloc(sizeof(int));

	*result = 10;
	printf("Return add: %p\n", result);
	return ((void *)result);
}

void	philo_eat(int philo_x)
{
	int timestamp;
	pthread_mutex_lock(&mutex);
	timestamp = ft_time();
	printf("%d %i %s\n", timestamp, philo_x, "is eating");
	usleep(g_argv.eating);
	pthread_mutex_unlock(&mutex);
	printf("%d %i %s\n", timestamp, philo_x, "done eating");
}

void philo_sleep(int philo_x)
{
	int timestamp;
	timestamp = ft_time();
	printf("%d %i %s\n", timestamp, philo_x, "is sleeping");
}

void philo_think(int philo_x)
{
	int timestamp;
	timestamp = ft_time();
	printf("%d %i %s\n", timestamp, philo_x, "is thinking");
}

void *philo_routine(void *arg)
{
	t_thread philo;

	philo.philo_x = *(int *)arg;
	while (1) //no free if sig interupt
	{
		philo_eat(philo.philo_x);
		philo_sleep(philo.philo_x);
		philo_think(philo.philo_x);
		usleep (1000000);
	}
	free(arg);
}
int	main(int argc, char *argv[])
{
	pthread_t *th;
	int n;
	int n_of_philos;

	if (!(ft_init_arg(argc, argv)))
		return (-1);
	printf("Time to eat: %d\n", g_argv.eating);

	n_of_philos = ft_atoi(argv[1]);
	th = malloc(sizeof(pthread_t) * n_of_philos);
	printf("Before thread\n");
	pthread_mutex_init(&mutex, NULL);
	n = 0;
	while (n < n_of_philos)
	{
		int *a = malloc(sizeof(int));
		*a = n + 1;
		if (pthread_create(&th[n], NULL, philo_routine, a) != 0)
			return (1);
		n++;
	}
	n = 0;
	while (n < n_of_philos)
	{
		if (pthread_join(th[n], NULL) != 0)
			return (1);
		n++;
	}
	printf("After thread\n");
	pthread_mutex_destroy(&mutex);
	free(th);
	
	pthread_t ret;
	int *ret_val;
	if (pthread_create(&ret, NULL, threadFuncRet, NULL) != 0)
		return (1);
	if (pthread_join(ret, (void **)&ret_val) != 0)
		return (1);
	printf("Return add (main): %p\n", ret_val);
	free(ret_val);
}
