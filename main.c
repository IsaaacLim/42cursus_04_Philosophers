#include "philo.h"

pthread_mutex_t *fork_x;
pthread_mutex_t print;

void	ft_print(int philo, char *str, char *color)
{
	pthread_mutex_lock(&print);
	printf("%d %s%i %s%s\n", ft_time(), color, philo, str, RESET);
	pthread_mutex_unlock(&print);
}

void	philo_lo(t_philos *philo, char *color)
{
	pthread_mutex_lock(&fork_x[philo->x - 1]);
	ft_print(philo->x, "has taken a fork", color);
	pthread_mutex_lock(&fork_x[philo->x % g_argv.n_philos]);
	ft_print(philo->x, "has taken a fork", color);
	ft_print(philo->x, "is eating", color);
	usleep(g_argv.eating);
	philo->t_last_meal = ft_time();
	pthread_mutex_unlock(&fork_x[philo->x - 1]);
	pthread_mutex_unlock(&fork_x[philo->x % g_argv.n_philos]);
	ft_print(philo->x, "is sleeping", color);
	usleep(g_argv.sleeping);
	ft_print(philo->x, "is thinking", color);
}

void *philo_routine(void *arg) //remove arg input
{
	t_philos *philo;
	philo = (t_philos *)arg;

	char colors[6][10] = {RED, GREEN, YELLOW, BLUE, PURPLE, CYAN};
	if (philo->x % 2 == 0)
		usleep (150000);
	// while (1) //no free if sig interupt
	// {
		philo_lo(philo, colors[(philo->x - 1) % 6]);
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
	pthread_mutex_init(&print, NULL);
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
		printf("%d %d t_last_meal\n", philo[n]->t_last_meal, n + 1);
		free(philo[n]);
	}
	pthread_mutex_destroy(&print);
	free(fork_x);
	free(th);
	free(philo);
}
