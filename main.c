#include "philo.h"

pthread_mutex_t *fork_x;

void	*threadFuncRet()
{
	int *result = malloc(sizeof(int));

	*result = 10;
	printf("Return add: %p\n", result);
	return ((void *)result);
}

void	philo_eat(int x)
{
	pthread_mutex_lock(&fork_x[x - 1]); //01234 
	pthread_mutex_lock(&fork_x[x % 5]);
	printf("%d %i %s\n", ft_time(), x, "is eating");
	usleep(g_argv.eating);
	pthread_mutex_unlock(&fork_x[x - 1]);
	pthread_mutex_unlock(&fork_x[x % 5]);
	printf("%d %i %s\n", ft_time(), x, "done eating");
}

void philo_sleep(int x)
{
	printf("%d %i %s\n", ft_time(), x, "is sleeping");
	usleep(g_argv.sleeping);
}

// void philo_think(int x)
// {
// 	int timestamp;

// 	timestamp = ft_time();
// 	printf("%d %i %s\n", timestamp, x, "is thinking");
// }

void *philo_routine(void *arg) //remove arg input
{
	t_philo philo;
	static int i;

	// philo.x = *(int *)arg;
	philo.x = i + 1;
	i++;
	while (1) //no free if sig interupt
	{
		philo_eat(philo.x);
		philo_sleep(philo.x);
		// philo_think(philo.x);
		// usleep (1000000);
	}
	// free(arg);
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
	fork_x = malloc(sizeof(pthread_mutex_t) * n_of_philos);
	n = 0;
	while (n < n_of_philos)
	{
		pthread_mutex_init(&fork_x[n], NULL);
		n++;
	}
	printf("Before thread\n");
	n = 0;
	while (n < n_of_philos)
	{
		// int *a = malloc(sizeof(int));
		// *a = n + 1;
		if (pthread_create(&th[n], NULL, philo_routine, NULL) != 0)
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
	pthread_mutex_destroy(fork_x);
	free(fork_x);
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
