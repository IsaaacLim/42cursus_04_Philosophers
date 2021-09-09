#include "philo.h"

pthread_mutex_t *fork_x;

void	philo_eat(int x, char *color)
{
	int left;
	int right;

	left = x - 1;
	right = x % 5;
	pthread_mutex_lock(&fork_x[x - 1]);
	printf("%d %s%i %s%s %i\n", ft_time(), color, x, "has taken a fork", RESET , left);
	pthread_mutex_lock(&fork_x[x % 5]);
	printf("%d %s%i %s%s %i\n", ft_time(), color, x, "has taken a fork", RESET, right);
	printf("%d %s%i %s%s\n", ft_time(), color, x, "is eating", RESET);
	usleep(g_argv.eating);
	// t_last_meal[x - 1] = ft_time();
	pthread_mutex_unlock(&fork_x[x - 1]);
	pthread_mutex_unlock(&fork_x[x % 5]);
}

void philo_sleep(int x)
{
	printf("%d %i %s\n", ft_time(), x, "is sleeping");
	usleep(g_argv.sleeping);
}

void philo_think(int x)
{
 	printf("%d %i %s\n", ft_time(), x, "is thinking");
}

void *philo_routine(void *arg) //remove arg input
{
	t_philos *philo;
	philo = (t_philos *)arg;

	char colors[6][10] = {"\033[0;31m","\033[0;32m","\033[0;33m","\033[0;34m","\033[0;35m","\033[0;36m"};
	if (philo->x % 2 == 0)
		usleep (150000);
	// while (1) //no free if sig interupt
	// {
		philo_eat(philo->x, colors[(philo->x - 1) % 6]);
		philo_sleep(philo->x);
		philo_think(philo->x);
	// }
}
int	main(int argc, char *argv[])
{
	int n;
	pthread_t *th;
	t_philos	**philo;

	if (!(ft_init_arg(argc, argv)))
		return (-1);

	th = malloc(sizeof(pthread_t) * g_argv.n_philos);
	fork_x = malloc(sizeof(pthread_mutex_t) * g_argv.n_philos);
	philo = malloc(sizeof(t_philos *) * g_argv.n_philos);
	n = 0;
	while (n < g_argv.n_philos)
	{
		pthread_mutex_init(&fork_x[n], NULL);
		philo[n] = malloc(sizeof(t_philos));
		philo[n]->x = n + 1;
		n++;
	}
	n = 0;
	while (n < g_argv.n_philos)
	{
		if (pthread_create(&th[n], NULL, philo_routine, &(philo[n]->x)) != 0)
			return (1);
		n++;
	}
	n = 0;
	while (n < g_argv.n_philos)
	{
		if (pthread_join(th[n], NULL) != 0)
			return (1);
		n++;
	}
	n = -1;
	while (++n < g_argv.n_philos)
	{
		pthread_mutex_destroy(&fork_x[n]);
		free(philo[n]);
	}
	free(fork_x);
	free(th);
	free(philo);
}
